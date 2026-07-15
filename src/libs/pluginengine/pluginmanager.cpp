#include "pluginmanager.h"
#include "pluginmanager_p.h"
#include "pluginspec.h"
#include "pluginspec_p.h"
#include "optionsparser.h"
#include "iplugin.h"
#include "plugincollection.h"
#include "instance.h"
#include <QCoreApplication>
#include <QEventLoop>
#include <QDateTime>
#include <QDir>
#include <QLibrary>
#include <QMetaProperty>
#include <QSettings>
#include <QTextStream>
#include <QTime>
#include <QWriteLocker>
#include <QDebug>
#include <QTimer>
#include <QOperatingSystemVersion>
#include <cobotlog.h>
#include <algorithm.h>
#include <inocassert.h>
#include "metapath.h"
#include "splashscreen.h"

Q_LOGGING_CATEGORY(pluginLog, "inocobottp.pluginengine")

const char C_IGNORED_PLUGINS[] = "Plugins/Ignored";
const char C_FORCEENABLED_PLUGINS[] = "Plugins/ForceEnabled";
const int DELAYED_INITIALIZE_INTERVAL = 5;  // ms

enum { debugLeaks = 0 };

/*!
    \namespace PluginEngine
    \brief The PluginEngine namespace provides classes that belong to the
           core plugin system.

    The basic extension system contains the plugin manager and its supporting classes,
    and the IPlugin interface that must be implemented by plugin providers.
*/

/*!
    \class PluginEngine::PluginManager
    \mainclass

    \brief The PluginManager class implements the core plugin system that
    manages the plugins, their life cycle, and their registered objects.

    The plugin manager is used for the following tasks:
    \list
    \li Manage plugins and their state
    \li Manipulate a 'common object pool'
    \endlist

    \section1 Plugins
    Plugins consist of an XML descriptor file, and of a library that contains a Qt plugin
    that must derive from the IPlugin class and has an IID of
    \c "com.qt-project.Inovance.InoCobotTPPlugin".
    The plugin manager is used to set a list of file system directories to search for
    plugins, retrieve information about the state of these plugins, and to load them.

    Usually, the application creates a PluginManager instance and initiates the
    loading.
    \code
        // 'plugins' and subdirs will be searched for plugins
        PluginManager::setPluginPaths(QStringList() << "plugins");
        PluginManager::loadPlugins(); // try to load all the plugins
    \endcode
    Additionally, it is possible to directly access the plugin specifications
    (the information in the descriptor file), the plugin instances (via PluginSpec),
    and their state.

    \section1 Object Pool
    Plugins (and everybody else) can add objects to a common 'pool' that is located in
    the plugin manager. Objects in the pool must derive from QObject, there are no other
    prerequisites. All objects of a specified type can be retrieved from the object pool
    via the getObjects() and getObject() functions.

    Whenever the state of the object pool changes a corresponding signal is emitted by the plugin manager.

    A common usecase for the object pool is that a plugin (or the application) provides
    an "extension point" for other plugins, which is a class / interface that can
    be implemented and added to the object pool. The plugin that provides the
    extension point looks for implementations of the class / interface in the object pool.
    \code
        // Plugin A provides a "MimeTypeHandler" extension point
        // in plugin B:
        MyMimeTypeHandler *handler = new MyMimeTypeHandler();
        PluginManager::instance()->addObject(handler);
        // In plugin A:
        QList<MimeTypeHandler *> mimeHandlers =
            PluginManager::getObjects<MimeTypeHandler>();
    \endcode


    The \c{PluginEngine::Invoker} class template provides "syntactic sugar"
    for using "soft" extension points that may or may not be provided by an
    object in the pool. This approach does neither require the "user" plugin being
    linked against the "provider" plugin nor a common shared
    header file. The exposed interface is implicitly given by the
    invokable functions of the "provider" object in the object pool.

    The \c{PluginEngine::invoke} function template encapsulates
    {PluginEngine::Invoker} construction for the common case where
    the success of the call is not checked.

    \code
        // In the "provide" plugin A:
        namespace PluginA {
        class SomeProvider : public QObject
        {
            Q_OBJECT

        public:
            Q_INVOKABLE QString doit(const QString &msg, int n) {
            {
                qDebug() << "I AM DOING IT " << msg;
                return QString::number(n);
            }
        };
        } // namespace PluginA


        // In the "user" plugin B:
        int someFuntionUsingPluginA()
        {
            using namespace PluginEngine;

            QObject *target = PluginManager::getObjectByClassName("PluginA::SomeProvider");

            if (target) {
                // Some random argument.
                QString msg = "REALLY.";

                // Plain function call, no return value.
                invoke<void>(target, "doit", msg, 2);

                // Plain function with no return value.
                qDebug() << "Result: " << invoke<QString>(target, "doit", msg, 21);

                // Record success of function call with return value.
                Invoker<QString> in1(target, "doit", msg, 21);
                qDebug() << "Success: (expected)" << in1.wasSuccessful();

                // Try to invoke a non-existing function.
                Invoker<QString> in2(target, "doitWrong", msg, 22);
                qDebug() << "Success (not expected):" << in2.wasSuccessful();

            } else {

                // We have to cope with plugin A's absence.
            }
        };
    \endcode

    \note The type of the parameters passed to the \c{invoke()} calls
    is deduced from the parameters themselves and must match the type of
    the arguments of the called functions \e{exactly}. No conversion or even
    integer promotions are applicable, so to invoke a function with a \c{long}
    parameter explicitly use \c{long(43)} or such.

    \note The object pool manipulating functions are thread-safe.
*/

/*!
    \fn void PluginManager::objectAdded(QObject *obj)
    Signals that \a obj has been added to the object pool.
*/

/*!
    \fn void PluginManager::aboutToRemoveObject(QObject *obj)
    Signals that \a obj will be removed from the object pool.
*/

/*!
    \fn void PluginManager::pluginsChanged()
    Signals that the list of available plugins has changed.

    \sa plugins()
*/

/*!
    \fn T *PluginManager::getObject()

    Retrieves the object of a given type from the object pool.

    This function uses \c qobject_cast to determine the type of an object.
    If there are more than one object of the given type in
    the object pool, this function will arbitrarily choose one of them.

    \sa addObject()
*/

/*!
    \fn T *PluginManager::getObject(Predicate predicate)

    Retrieves the object of a given type from the object pool that matches
    the \a predicate.

    This function uses \c qobject_cast to determine the type of an object.
    The predicate must be a function taking T * and returning a bool.
    If there is more than one object matching the type and predicate,
    this function will arbitrarily choose one of them.

    \sa addObject()
*/

/*!
    \fn QList<T *> PluginManager::getObjects()

    Retrieves all objects of a given type from the object pool.

    This function uses \c qobject_cast to determine the type of an object.

    \sa addObject()
*/

/*!
    \fn QList<T *> PluginManager::getObjects(Predicate predicate)

    Retrieves all objects of a given type from the object pool that
    match the \a predicate.

    This function uses \c qobject_cast to determine the type of an object.
    The predicate should be a unary function taking a T* parameter and
    returning a bool.

    \sa addObject()
*/

using namespace PluginEngine;
using namespace PluginEngine::Internal;

static Internal::PluginManagerPrivate *d = 0;
static PluginManager *m_instance = 0;

static bool lessThanByPluginName(const PluginSpec *one, const PluginSpec *two)
{
    return one->name() < two->name();
}

/*!
    Gets the unique plugin manager instance.
*/
PluginManager *PluginManager::instance()
{
    return m_instance;
}

/*!
    Creates a plugin manager. Should be done only once per application.
*/
PluginManager::PluginManager()
{
    m_instance = this;
    d = new PluginManagerPrivate(this);
}

PluginManager::~PluginManager()
{
    delete d;
    d = 0;
}

/*!
    Adds the object \a obj to the object pool, so it can be retrieved
    again from the pool by type.

    The plugin manager does not do any memory management - added objects
    must be removed from the pool and deleted manually by whoever is responsible for the object.

    Emits the objectAdded() signal.

    \sa PluginManager::removeObject()
    \sa PluginManager::getObject()
    \sa PluginManager::getObjects()
*/
void PluginManager::addObject(QObject *obj)
{
    d->addObject(obj);
}

/*!
    Emits aboutToRemoveObject() and removes the object \a obj from the object pool.
    \sa PluginManager::addObject()
*/
void PluginManager::removeObject(QObject *obj)
{
    d->removeObject(obj);
}

/*!
    Retrieves the list of all objects in the pool, unfiltered.

    Usually, clients do not need to call this function.

    \sa PluginManager::getObject()
    \sa PluginManager::getObjects()
*/
QList<QObject *> PluginManager::allObjects()
{
    return d->allObjects;
}

QReadWriteLock *PluginManager::listLock()
{
    return &d->m_lock;
}

/*!
    Tries to load all the plugins that were previously found when
    setting the plugin search paths. The plugin specs of the plugins
    can be used to retrieve error and state information about individual plugins.

    \sa setPluginPaths()
    \sa plugins()
*/
void PluginManager::loadPlugins()
{
    return d->loadPlugins();
}

/*!
    Returns true if any plugin has errors even though it is enabled.
    Most useful to call after loadPlugins().
*/
bool PluginManager::hasError()
{
    foreach (PluginSpec *spec, plugins()) {
        // only show errors on startup if plugin is enabled.
        if (spec->hasError() && spec->isEffectivelyEnabled())
            return true;
    }
    return false;
}

/*!
    Returns all plugins that require \a spec to be loaded. Recurses into dependencies.
 */
QSet<PluginSpec *> PluginManager::pluginsRequiringPlugin(PluginSpec *spec)
{
    QSet<PluginSpec *> dependingPlugins;
    dependingPlugins.insert(spec);
    foreach (PluginSpec *checkSpec, d->loadQueue()) {
        QHashIterator<PluginDependency, PluginSpec *> depIt(checkSpec->dependencySpecs());
        while (depIt.hasNext()) {
            depIt.next();
            if (depIt.key().type != PluginDependency::Required)
                continue;
            if (dependingPlugins.contains(depIt.value())) {
                dependingPlugins.insert(checkSpec);
                break;  // no use to check other dependencies, continue with load queue
            }
        }
    }
    dependingPlugins.remove(spec);
    return dependingPlugins;
}

/*!
    Returns all plugins that \a spec requires to be loaded. Recurses into dependencies.
 */
QSet<PluginSpec *> PluginManager::pluginsRequiredByPlugin(PluginSpec *spec)
{
    QSet<PluginSpec *> recursiveDependencies;
    recursiveDependencies.insert(spec);
    QList<PluginSpec *> queue;
    queue.append(spec);
    while (!queue.isEmpty()) {
        PluginSpec *checkSpec = queue.takeFirst();
        QHashIterator<PluginDependency, PluginSpec *> depIt(checkSpec->dependencySpecs());
        while (depIt.hasNext()) {
            depIt.next();
            if (depIt.key().type != PluginDependency::Required)
                continue;
            PluginSpec *depSpec = depIt.value();
            if (!recursiveDependencies.contains(depSpec)) {
                recursiveDependencies.insert(depSpec);
                queue.append(depSpec);
            }
        }
    }
    recursiveDependencies.remove(spec);
    return recursiveDependencies;
}

/*!
    Returns all plugins name.
 */
QStringList PluginManager::pluginNames()
{
    QStringList pluginNames;
    QList<PluginSpec *> specs = d->pluginSpecs;
    for (const PluginSpec *spec : specs) {
        if (spec) {
            pluginNames.append(spec->name());
        }
    }

    return pluginNames;
}

/*!
    Shuts down and deletes all plugins.
*/
void PluginManager::shutdown()
{
    d->shutdown();
}

/*!
    The list of paths were the plugin manager searches for plugins.

    \sa setPluginPaths()
*/
QStringList PluginManager::pluginPaths()
{
    return d->pluginPaths;
}

/*!
    Sets the plugin search paths, i.e. the file system paths where the plugin manager
    looks for plugin descriptions. All given \a paths and their sub directory trees
    are searched for plugin xml description files.

    \sa pluginPaths()
    \sa loadPlugins()
*/
void PluginManager::setPluginPaths(const QStringList &paths)
{
    d->setPluginPaths(paths);
}

/*!
    The IID that valid plugins must have.

    \sa setPluginIID()
*/
QString PluginManager::pluginIID()
{
    return d->pluginIID;
}

/*!
    Sets the IID that valid plugins must have. Only plugins with this IID are loaded, others are
    silently ignored.

    At the moment this must be called before setPluginPaths() is called.
    // ### TODO let this + setPluginPaths read the plugin meta data lazyly whenever loadPlugins() or plugins() is called.
*/
void PluginManager::setPluginIID(const QString &iid)
{
    d->pluginIID = iid;
}

/*!
    Defines the user specific settings to use for information about enabled and
    disabled plugins.
    Needs to be set before the plugin search path is set with setPluginPaths().
*/
void PluginManager::setSettings(QSettings *settings)
{
    d->setSettings(settings);
}

/*!
    Defines the global (user-independent) settings to use for information about
    default disabled plugins.
    Needs to be set before the plugin search path is set with setPluginPaths().
*/
void PluginManager::setGlobalSettings(QSettings *settings)
{
    d->setGlobalSettings(settings);
}

/*!
    Returns the user specific settings used for information about enabled and
    disabled plugins.
*/
QSettings *PluginManager::settings()
{
    return d->settings;
}

/*!
    Returns the global (user-independent) settings used for information about default disabled plugins.
*/
QSettings *PluginManager::globalSettings()
{
    return d->globalSettings;
}

void PluginManager::writeSettings()
{
    d->writeSettings();
}

/*!
    The arguments left over after parsing (that were neither startup nor plugin
    arguments). Typically, this will be the list of files to open.
*/
QStringList PluginManager::arguments()
{
    return d->arguments;
}

/*!
    List of all plugin specifications that have been found in the plugin search paths.
    This list is valid directly after the setPluginPaths() call.
    The plugin specifications contain the information from the plugins' xml description files
    and the current state of the plugins. If a plugin's library has been already successfully loaded,
    the plugin specification has a reference to the created plugin instance as well.

    \sa setPluginPaths()
*/
QList<PluginSpec *> PluginManager::plugins()
{
    return d->pluginSpecs;
}

QHash<QString, PluginCollection *> PluginManager::pluginCollections()
{
    return d->pluginCategories;
}

static const char argumentKeywordC[] = ":arguments";
static const char pwdKeywordC[] = ":pwd";

/*!
    Serializes plugin options and arguments for sending in a single string
    via QtSingleApplication:
    ":myplugin|-option1|-option2|:arguments|argument1|argument2",
    as a list of lists started by a keyword with a colon. Arguments are last.

    \sa setPluginPaths()
*/
QString PluginManager::serializedArguments()
{
    const QChar separator = QLatin1Char('|');
    QString rc;
    foreach (const PluginSpec *ps, plugins()) {
        if (!ps->arguments().isEmpty()) {
            if (!rc.isEmpty())
                rc += separator;
            rc += QLatin1Char(':');
            rc += ps->name();
            rc += separator;
            rc += ps->arguments().join(separator);
        }
    }
    if (!rc.isEmpty())
        rc += separator;
    rc += QLatin1String(pwdKeywordC) + separator + QDir::currentPath();
    if (!d->arguments.isEmpty()) {
        if (!rc.isEmpty())
            rc += separator;
        rc += QLatin1String(argumentKeywordC);
        foreach (const QString &argument, d->arguments)
            rc += separator + argument;
    }
    return rc;
}

/* Extract a sublist from the serialized arguments
 * indicated by a keyword starting with a colon indicator:
 * ":a,i1,i2,:b:i3,i4" with ":a" -> "i1,i2"
 */
static QStringList subList(const QStringList &in, const QString &key)
{
    QStringList rc;
    // Find keyword and copy arguments until end or next keyword
    const QStringList::const_iterator inEnd = in.constEnd();
    QStringList::const_iterator it = std::find(in.constBegin(), inEnd, key);
    if (it != inEnd) {
        const QChar nextIndicator = QLatin1Char(':');
        for (++it; it != inEnd && !it->startsWith(nextIndicator); ++it)
            rc.append(*it);
    }
    return rc;
}

/*!
    Parses the options encoded by serializedArguments() const
    and passes them on to the respective plugins along with the arguments.

    \a socket is passed for disconnecting the peer when the operation is done (for example,
    document is closed) for supporting the -block flag.
*/

void PluginManager::remoteArguments(const QString &serializedArgument, QObject *socket)
{
    if (serializedArgument.isEmpty())
        return;
    QStringList serializedArguments = serializedArgument.split(QLatin1Char('|'));
    const QStringList pwdValue = subList(serializedArguments, QLatin1String(pwdKeywordC));
    const QString workingDirectory = pwdValue.isEmpty() ? QString() : pwdValue.first();
    const QStringList arguments = subList(serializedArguments, QLatin1String(argumentKeywordC));
    foreach (const PluginSpec *ps, plugins()) {
        if (ps->state() == PluginSpec::Running) {
            const QStringList pluginOptions = subList(serializedArguments, QLatin1Char(':') + ps->name());
            QObject *socketParent = ps->plugin()->remoteCommand(pluginOptions, workingDirectory,
                                                                arguments);
            if (socketParent && socket) {
                socket->setParent(socketParent);
                socket = 0;
            }
        }
    }
    if (socket)
        delete socket;
}

/*!
    Takes the list of command line options in \a args and parses them.
    The plugin manager itself might process some options itself directly (-noload <plugin>), and
    adds options that are registered by plugins to their plugin specs.
    The caller (the application) may register itself for options via the \a appOptions list, containing pairs
    of "option string" and a bool that indicates if the option requires an argument.
    Application options always override any plugin's options.

    \a foundAppOptions is set to pairs of ("option string", "argument") for any application options that were found.
    The command line options that were not processed can be retrieved via the arguments() function.
    If an error occurred (like missing argument for an option that requires one), \a errorString contains
    a descriptive message of the error.

    Returns if there was an error.
 */
bool PluginManager::parseOptions(const QStringList &args,
                                 const QMap<QString, bool> &appOptions,
                                 QMap<QString, QString> *foundAppOptions,
                                 QString *errorString)
{
    OptionsParser options(args, appOptions, foundAppOptions, errorString, d);
    return options.parse();
}

static inline void indent(QTextStream &str, int indent)
{
    const QChar blank = QLatin1Char(' ');
    for (int i = 0; i < indent; i++)
        str << blank;
}

static inline void formatOption(QTextStream &str,
                                const QString &opt, const QString &parm, const QString &description,
                                int optionIndentation, int descriptionIndentation)
{
    int remainingIndent = descriptionIndentation - optionIndentation - opt.size();
    indent(str, optionIndentation);
    str << opt;
    if (!parm.isEmpty()) {
        str << " <" << parm << '>';
        remainingIndent -= 3 + parm.size();
    }
    if (remainingIndent >= 1) {
        indent(str, remainingIndent);
    } else {
        str << '\n';
        indent(str, descriptionIndentation);
    }
    str << description << '\n';
}

/*!
    Formats the startup options of the plugin manager for command line help.
*/

void PluginManager::formatOptions(QTextStream &str, int optionIndentation, int descriptionIndentation)
{
    formatOption(str, QLatin1String(OptionsParser::LOAD_OPTION),
                 QLatin1String("plugin"), QLatin1String("Load <plugin> and all plugins that it requires"),
                 optionIndentation, descriptionIndentation);
    formatOption(str, QLatin1String(OptionsParser::LOAD_OPTION) + QLatin1String(" all"),
                 QString(), QLatin1String("Load all available plugins"),
                 optionIndentation, descriptionIndentation);
    formatOption(str, QLatin1String(OptionsParser::NO_LOAD_OPTION),
                 QLatin1String("plugin"), QLatin1String("Do not load <plugin> and all plugins that require it"),
                 optionIndentation, descriptionIndentation);
    formatOption(str, QLatin1String(OptionsParser::NO_LOAD_OPTION) + QLatin1String(" all"),
                 QString(), QString::fromLatin1("Do not load any plugin (useful when "
                                                "followed by one or more \"%1\" arguments)")
                                .arg(QLatin1String(OptionsParser::LOAD_OPTION)),
                 optionIndentation, descriptionIndentation);
    formatOption(str, QLatin1String(OptionsParser::PROFILE_OPTION),
                 QString(), QLatin1String("Profile plugin loading"),
                 optionIndentation, descriptionIndentation);
}

/*!
    Formats the plugin options of the plugin specs for command line help.
*/

void PluginManager::formatPluginOptions(QTextStream &str, int optionIndentation, int descriptionIndentation)
{
    // Check plugins for options
    foreach (PluginSpec *ps, d->pluginSpecs) {
        const PluginSpec::PluginArgumentDescriptions pargs = ps->argumentDescriptions();
        if (!pargs.empty()) {
            str << "\nPlugin: " << ps->name() << '\n';
            foreach (PluginArgumentDescription pad, pargs)
                formatOption(str, pad.name, pad.parameter, pad.description, optionIndentation, descriptionIndentation);
        }
    }
}

/*!
    Formats the version of the plugin specs for command line help.
*/
void PluginManager::formatPluginVersions(QTextStream &str)
{
    foreach (PluginSpec *ps, d->pluginSpecs)
        str << "  " << ps->name() << ' ' << ps->version() << ' ' << ps->description() << '\n';
}

/*!
 * \internal
 */
bool PluginManager::testRunRequested()
{
    return !d->testSpecs.isEmpty();
}

/*!
    Creates a profiling entry showing the elapsed time if profiling is
    activated.
*/

void PluginManager::profilingReport(const char *what, const PluginSpec *spec)
{
    d->profilingReport(what, spec);
}

/*!
    Returns a list of plugins in load order.
*/
QList<PluginSpec *> PluginManager::loadQueue()
{
    return d->loadQueue();
}

//============PluginManagerPrivate===========

PluginSpec *PluginManagerPrivate::createSpec()
{
    return new PluginSpec();
}

void PluginManagerPrivate::setSettings(QSettings *s)
{
    if (settings)
        delete settings;
    settings = s;
    if (settings)
        settings->setParent(this);
}

void PluginManagerPrivate::setGlobalSettings(QSettings *s)
{
    if (globalSettings)
        delete globalSettings;
    globalSettings = s;
    if (globalSettings)
        globalSettings->setParent(this);
}

PluginSpecPrivate *PluginManagerPrivate::privateSpec(PluginSpec *spec)
{
    return spec->d;
}

void PluginManagerPrivate::nextDelayedInitialize()
{
    while (!delayedInitializeQueue.isEmpty()) {
        PluginSpec *spec = delayedInitializeQueue.takeFirst();
        profilingReport(">delayedInitialize", spec);
        bool delay = spec->d->delayedInitialize();
        profilingReport("<delayedInitialize", spec);
        if (!delay)
            break;  // do next delayedInitialize after a delay
    }
    if (delayedInitializeQueue.isEmpty()) {
        m_isInitializationDone = true;
        delete delayedInitializeTimer;
        delayedInitializeTimer = 0;
        profilingSummary();
        emit q->initializationDone();
    } else {
        delayedInitializeTimer->start();
    }
}

PluginManagerPrivate::PluginManagerPrivate(PluginManager *pluginManager) :
    delayedInitializeTimer(0),
    shutdownEventLoop(0),
    m_profileElapsedMS(0),
    m_profilingVerbosity(0),
    settings(0),
    globalSettings(0),
    q(pluginManager)
{
}

PluginManagerPrivate::~PluginManagerPrivate()
{
    qDeleteAll(pluginSpecs);
    qDeleteAll(pluginCategories);
}

void PluginManagerPrivate::writeSettings()
{
    if (!settings)
        return;
    QStringList tempDisabledPlugins;
    QStringList tempForceEnabledPlugins;
    foreach (PluginSpec *spec, pluginSpecs) {
        if (spec->isEnabledByDefault() && !spec->isEnabledBySettings())
            tempDisabledPlugins.append(spec->name());
        if (!spec->isEnabledByDefault() && spec->isEnabledBySettings())
            tempForceEnabledPlugins.append(spec->name());
    }

    settings->setValue(QLatin1String(C_IGNORED_PLUGINS), tempDisabledPlugins);
    settings->setValue(QLatin1String(C_FORCEENABLED_PLUGINS), tempForceEnabledPlugins);
}

void PluginManagerPrivate::readSettings()
{
    if (globalSettings) {
        defaultDisabledPlugins = globalSettings->value(QLatin1String(C_IGNORED_PLUGINS)).toStringList();
        defaultEnabledPlugins = globalSettings->value(QLatin1String(C_FORCEENABLED_PLUGINS)).toStringList();
    }
    if (settings) {
        disabledPlugins = settings->value(QLatin1String(C_IGNORED_PLUGINS)).toStringList();
        forceEnabledPlugins = settings->value(QLatin1String(C_FORCEENABLED_PLUGINS)).toStringList();
    }
}

void PluginManagerPrivate::stopAll()
{
    if (delayedInitializeTimer && delayedInitializeTimer->isActive()) {
        delayedInitializeTimer->stop();
        delete delayedInitializeTimer;
        delayedInitializeTimer = 0;
    }
    QList<PluginSpec *> queue = loadQueue();
    foreach (PluginSpec *spec, queue) {
        loadPlugin(spec, PluginSpec::Stopped);
    }
}

void PluginManagerPrivate::deleteAll()
{
    QList<PluginSpec *> queue = loadQueue();
    QListIterator<PluginSpec *> it(queue);
    it.toBack();
    while (it.hasPrevious()) {
        loadPlugin(it.previous(), PluginSpec::Deleted);
    }
}

void PluginManagerPrivate::addObject(QObject *obj)
{
    {
        QWriteLocker lock(&m_lock);
        if (obj == 0) {
            qWarning() << "PluginManagerPrivate::addObject(): trying to add null object";
            return;
        }
        if (allObjects.contains(obj)) {
            qWarning() << "PluginManagerPrivate::addObject(): trying to add duplicate object";
            return;
        }

        if (debugLeaks)
            qDebug() << "PluginManagerPrivate::addObject" << obj << obj->objectName();

        if (m_profilingVerbosity && !m_profileTimer.isNull()) {
            // Report a timestamp when adding an object. Useful for profiling
            // its initialization time.
            const int absoluteElapsedMS = m_profileTimer->elapsed();
            qDebug("  %-43s %8dms", obj->metaObject()->className(), absoluteElapsedMS);
        }
        allObjects.append(obj);
    }
    emit q->objectAdded(obj);
}

void PluginManagerPrivate::removeObject(QObject *obj)
{
    if (obj == 0) {
        qWarning() << "PluginManagerPrivate::removeObject(): trying to remove null object";
        return;
    }

    if (!allObjects.contains(obj)) {
        qWarning() << "PluginManagerPrivate::removeObject(): object not in list:"
                   << obj << obj->objectName();
        return;
    }
    if (debugLeaks)
        qDebug() << "PluginManagerPrivate::removeObject" << obj << obj->objectName();

    emit q->aboutToRemoveObject(obj);
    QWriteLocker lock(&m_lock);
    allObjects.removeAll(obj);
}

void PluginManagerPrivate::loadPlugins()
{
    QList<PluginSpec *> queue = loadQueue();
    SplashScreen::instance()->setinitAndDelayPluginSum(queue.size());
    SplashScreen::instance()->setFinshCount(0);
    foreach (PluginSpec *spec, queue) {
        loadPlugin(spec, PluginSpec::Loaded);
    }
#ifdef QT_DEBUG
    QList<QPair<QString, int>> recordTime;
    QDateTime last = QDateTime::currentDateTime();
    foreach (PluginSpec *spec, queue) {
        // qDebug()<<"spec object name is"<<spec->plugin()->objectName();
        loadPlugin(spec, PluginSpec::Initialized);
        SplashScreen::instance()->updateFinshCount();
        QDateTime current = QDateTime::currentDateTime();
        recordTime << QPair<QString, int>(spec->plugin()->metaObject()->className(), last.msecsTo(current));
        last = current;
    }
    std::sort(recordTime.begin(), recordTime.end(), [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
        return a.second > b.second;
    });
    qDebug() << "Plugin init time cost";
    for (auto &i : recordTime)
        qDebug() << i.first << i.second;
#else
    foreach (PluginSpec *spec, queue) {
        loadPlugin(spec, PluginSpec::Initialized);
        SplashScreen::instance()->updateFinshCount();
    }
#endif
    QListIterator<PluginSpec *> it(queue);
    it.toBack();
    isAllowResigterDelayInit = true;
    while (it.hasPrevious()) {
        PluginSpec *spec = it.previous();
        loadPlugin(spec, PluginSpec::Running);
        if (spec->state() == PluginSpec::Running) {
            hashPluginNameToPluginAddress[spec->plugin()->objectName()] = spec->plugin();
        } else {
            spec->d->kill();
        }
    }
    isAllowResigterDelayInit = false;
    emit q->pluginsChanged();
    delayedInitializeTimer = new QTimer;
    delayedInitializeTimer->setInterval(DELAYED_INITIALIZE_INTERVAL);
    delayedInitializeTimer->setSingleShot(true);
    connect(delayedInitializeTimer, SIGNAL(timeout()),
            this, SLOT(nextDelayedInitialize()));
    delayedInitializeTimer->start();
}

bool PluginManagerPrivate::registerDelayInit(PluginSpec *spec)
{
    if (isAllowResigterDelayInit)
        delayedInitializeQueue.push_back(spec);
    return isAllowResigterDelayInit;
}

bool PluginManagerPrivate::registerAddXmlConfigToActiveProjectWhenSaveProject(PluginSpec *spec)
{
    m_registerAddXmlConfigToActiveProjectWhenSaveProjectQueue.push_back(spec);
    return true;
}

bool PluginManagerPrivate::registerConditionNameToPlugin(const QString &name, IPlugin *spec)
{
    if(spec)
        hashConditionTypeToPlugin[name] = spec;
    return true;
}

void PluginManagerPrivate::shutdown()
{
    stopAll();
    if (!asynchronousPlugins.isEmpty()) {
        shutdownEventLoop = new QEventLoop;
        shutdownEventLoop->exec();
    }
    deleteAll();
    if (!allObjects.isEmpty()) {
        qDebug() << "There are" << allObjects.size() << "objects left in the plugin manager pool.";
        // Intentionally split debug info here, since in case the list contains
        // already deleted object we get at least the info about the number of objects;
        qDebug() << "The following objects left in the plugin manager pool:" << allObjects;
    }
}

void PluginManagerPrivate::asyncShutdownFinished()
{
    IPlugin *plugin = qobject_cast<IPlugin *>(sender());
    Q_ASSERT(plugin);
    asynchronousPlugins.removeAll(plugin->pluginSpec());
    if (asynchronousPlugins.isEmpty())
        shutdownEventLoop->exit();
}

QList<PluginSpec *> PluginManagerPrivate::loadQueue()
{
    QList<PluginSpec *> queue;
    foreach (PluginSpec *spec, pluginSpecs) {
        QList<PluginSpec *> circularityCheckQueue;
        loadQueue(spec, queue, circularityCheckQueue);
    }
    return queue;
}

bool PluginManagerPrivate::loadQueue(PluginSpec *spec, QList<PluginSpec *> &queue,
                                     QList<PluginSpec *> &circularityCheckQueue)
{
    if (queue.contains(spec))
        return true;
    // check for circular dependencies
    if (circularityCheckQueue.contains(spec)) {
        spec->d->hasError = true;
        spec->d->errorString = PluginManager::tr("Cyclic dependencies detected:");
        spec->d->errorString += QLatin1Char('\n');
        int index = circularityCheckQueue.indexOf(spec);
        for (unsigned int i = index; i < circularityCheckQueue.size(); ++i) {
            spec->d->errorString.append(PluginManager::tr("%1(%2) depends on")
                                            .arg(circularityCheckQueue.at(i)->name())
                                            .arg(circularityCheckQueue.at(i)->version()));
            spec->d->errorString += QLatin1Char('\n');
        }
        spec->d->errorString.append(PluginManager::tr("%1(%2)").arg(spec->name()).arg(spec->version()));
        return false;
    }
    circularityCheckQueue.append(spec);
    // check if we have the dependencies
    if (spec->state() == PluginSpec::Invalid || spec->state() == PluginSpec::Read) {
        queue.append(spec);
        return false;
    }

    // add dependencies
    QHashIterator<PluginDependency, PluginSpec *> it(spec->dependencySpecs());
    while (it.hasNext()) {
        it.next();
        // Skip test dependencies since they are not real dependencies but just force-loaded
        // plugins when running tests
        if (it.key().type == PluginDependency::Test)
            continue;
        PluginSpec *depSpec = it.value();
        if (!loadQueue(depSpec, queue, circularityCheckQueue)) {
            spec->d->hasError = true;

            spec->d->errorString = PluginManager::tr("Cannot load plugin because dependencies cannot be loaded: %1(%2)")
                                       .arg(depSpec->name())
                                       .arg(depSpec->version())
                                 + "\r\n"
                                 + tr("Cause: %1").arg(depSpec->errorString());
            return false;
        }
    }
    // add self
    queue.append(spec);
    return true;
}

void PluginManagerPrivate::loadPlugin(PluginSpec *spec, PluginSpec::State destState)
{
    if (spec->hasError() || spec->state() != destState - 1)
        return;

    // don't load disabled plugins.
    if (!spec->isEffectivelyEnabled() && destState == PluginSpec::Loaded)
        return;

    switch (destState) {
    case PluginSpec::Running:
        profilingReport(">initializeExtensions", spec);
        spec->d->initializeExtensions();
        profilingReport("<initializeExtensions", spec);
        return;
    case PluginSpec::Deleted:
        profilingReport(">delete", spec);
        spec->d->kill();
        profilingReport("<delete", spec);
        return;
    default:
        break;
    }
    // check if dependencies have loaded without error
    QHashIterator<PluginDependency, PluginSpec *> it(spec->dependencySpecs());
    while (it.hasNext()) {
        it.next();
        if (it.key().type != PluginDependency::Required)
            continue;
        PluginSpec *depSpec = it.value();
        if (depSpec->state() != destState) {
            spec->d->hasError = true;
            spec->d->errorString = PluginManager::tr("Cannot load plugin because dependency failed to load: %1(%2)")
                                       .arg(depSpec->name())
                                       .arg(depSpec->version())
                                 + "\r\n"
                                 + tr("Cause: %3").arg(depSpec->errorString());
            return;
        }
    }
    switch (destState) {
    case PluginSpec::Loaded:
        profilingReport(">loadLibrary", spec);
        spec->d->loadLibrary();
        profilingReport("<loadLibrary", spec);
        break;
    case PluginSpec::Initialized:
        profilingReport(">initializePlugin", spec);
        spec->d->initializePlugin();
        profilingReport("<initializePlugin", spec);
        break;
    case PluginSpec::Stopped:
        profilingReport(">stop", spec);
        if (spec->d->stop() == IPlugin::AsynchronousShutdown) {
            asynchronousPlugins << spec;
            connect(spec->plugin(), SIGNAL(asynchronousShutdownFinished()),
                    this, SLOT(asyncShutdownFinished()));
        }
        profilingReport("<stop", spec);
        break;
    default:
        break;
    }
}

void PluginManagerPrivate::setPluginPaths(const QStringList &paths)
{
    qCDebug(pluginLog) << "Plugin search paths:" << paths;
    qCDebug(pluginLog) << "Required IID:" << pluginIID;
    pluginPaths = paths;
    readSettings();
    readPluginPaths();
}

void PluginManagerPrivate::readPluginPaths()
{
    qDeleteAll(pluginCategories);
    qDeleteAll(pluginSpecs);
    pluginSpecs.clear();
    pluginCategories.clear();

    QStringList pluginFiles;
    QStringList searchPaths = pluginPaths;
    while (!searchPaths.isEmpty()) {
        const QDir dir(searchPaths.takeFirst());
        const QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
        foreach (const QFileInfo &file, files) {
            const QString filePath = file.absoluteFilePath();
            if (QLibrary::isLibrary(filePath))
                pluginFiles.append(filePath);
        }
        const QFileInfoList dirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (const QFileInfo &subdir, dirs)
            searchPaths << subdir.absoluteFilePath();
    }

    defaultCollection = new PluginCollection(QString());
    pluginCategories.insert(QString(), defaultCollection);

    QStringList pluginLibEnabledList = QString(PluginsListEnabled).split(",");
    QStringList pluginEnabledList;
    foreach (QString pluginLibEnabled, pluginLibEnabledList) {
        QString plugin = pluginLibEnabled.remove("PluginLib_").remove("_Enabled");
        pluginEnabledList.append(plugin);
    }

    foreach (const QString &pluginFile, pluginFiles) {
        PluginSpec *spec = new PluginSpec;
        if (!spec->d->read(pluginFile)) {  // not a InoCobotTP plugin
            delete spec;
            continue;
        }

        PluginCollection *collection = 0;
        // find correct plugin collection or create a new one
        if (pluginCategories.contains(spec->category())) {
            collection = pluginCategories.value(spec->category());
        } else {
            collection = new PluginCollection(spec->category());
            pluginCategories.insert(spec->category(), collection);
        }
        // defaultDisabledPlugins and defaultEnabledPlugins from install settings
        // is used to override the defaults read from the plugin spec
        if (spec->isEnabledByDefault() && defaultDisabledPlugins.contains(spec->name())) {
            spec->d->setEnabledByDefault(false);
            spec->d->setEnabledBySettings(false);
        } else if (!spec->isEnabledByDefault() && defaultEnabledPlugins.contains(spec->name())) {
            spec->d->setEnabledByDefault(true);
            spec->d->setEnabledBySettings(true);
        }
        if (!spec->isEnabledByDefault() && forceEnabledPlugins.contains(spec->name()))
            spec->d->setEnabledBySettings(true);
        if (spec->isEnabledByDefault() && disabledPlugins.contains(spec->name()))
            spec->d->setEnabledBySettings(false);

        collection->addPlugin(spec);
        if (pluginEnabledList.contains(spec->name())) {
            pluginSpecs.append(spec);
        }
    }

    resolveDependencies();
    // ensure deterministic plugin load order by sorting
    std::sort(pluginSpecs.begin(), pluginSpecs.end(), lessThanByPluginName);
    emit q->pluginsChanged();
}

void PluginManagerPrivate::resolveDependencies()
{
    foreach (PluginSpec *spec, pluginSpecs) {
        spec->d->enabledIndirectly = false;  // reset, is recalculated below
        spec->d->resolveDependencies(pluginSpecs);
    }

    QListIterator<PluginSpec *> it(loadQueue());
    it.toBack();
    while (it.hasPrevious()) {
        PluginSpec *spec = it.previous();
        spec->d->enableDependenciesIndirectly();
    }
}

void PluginManagerPrivate::enableOnlyTestedSpecs()
{
    if (testSpecs.isEmpty())
        return;

    QList<PluginSpec *> specsForTests;
    foreach (const TestSpec &testSpec, testSpecs) {
        QList<PluginSpec *> circularityCheckQueue;
        loadQueue(testSpec.pluginSpec, specsForTests, circularityCheckQueue);
        // add plugins that must be force loaded when running tests for the plugin
        // (aka "test dependencies")
        QHashIterator<PluginDependency, PluginSpec *> it(testSpec.pluginSpec->dependencySpecs());
        while (it.hasNext()) {
            it.next();
            if (it.key().type != PluginDependency::Test)
                continue;
            PluginSpec *depSpec = it.value();
            circularityCheckQueue.clear();
            loadQueue(depSpec, specsForTests, circularityCheckQueue);
        }
    }
    foreach (PluginSpec *spec, pluginSpecs)
        spec->d->setForceDisabled(true);
    foreach (PluginSpec *spec, specsForTests) {
        spec->d->setForceDisabled(false);
        spec->d->setForceEnabled(true);
    }
}

// Look in argument descriptions of the specs for the option.
PluginSpec *PluginManagerPrivate::pluginForOption(const QString &option, bool *requiresArgument) const
{
    // Look in the plugins for an option
    *requiresArgument = false;
    foreach (PluginSpec *ps, pluginSpecs) {
        const PluginSpec::PluginArgumentDescriptions pargs = ps->argumentDescriptions();
        if (!pargs.empty()) {
            foreach (PluginArgumentDescription pad, pargs) {
                if (pad.name == option) {
                    *requiresArgument = !pad.parameter.isEmpty();
                    return ps;
                }
            }
        }
    }
    return 0;
}

PluginSpec *PluginManagerPrivate::pluginByName(const QString &name) const
{
    foreach (PluginSpec *spec, pluginSpecs)
        if (spec->name() == name)
            return spec;
    return 0;
}

void PluginManagerPrivate::initProfiling()
{
    if (m_profileTimer.isNull()) {
        m_profileTimer.reset(new QElapsedTimer);
        m_profileTimer->start();
        m_profileElapsedMS = 0;
        qDebug("Profiling started");
    } else {
        m_profilingVerbosity++;
    }
}

void PluginManagerPrivate::profilingReport(const char *what, const PluginSpec *spec /* = 0 */)
{
    if (!m_profileTimer.isNull()) {
        const int absoluteElapsedMS = m_profileTimer->elapsed();
        const int elapsedMS = absoluteElapsedMS - m_profileElapsedMS;
        m_profileElapsedMS = absoluteElapsedMS;
        if (spec)
            m_profileTotal[spec] += elapsedMS;
        if (spec)
            qDebug("%-22s %-22s %8dms (%8dms)", what, qPrintable(spec->name()), absoluteElapsedMS, elapsedMS);
        else
            qDebug("%-45s %8dms (%8dms)", what, absoluteElapsedMS, elapsedMS);
    }
}

void PluginManagerPrivate::profilingSummary() const
{
    if (!m_profileTimer.isNull()) {
        typedef QMultiMap<int, const PluginSpec *> Sorter;
        Sorter sorter;
        int total = 0;

        QHash<const PluginSpec *, int>::ConstIterator it1 = m_profileTotal.constBegin();
        QHash<const PluginSpec *, int>::ConstIterator et1 = m_profileTotal.constEnd();
        for (; it1 != et1; ++it1) {
            sorter.insert(it1.value(), it1.key());
            total += it1.value();
        }

        Sorter::ConstIterator it2 = sorter.constBegin();
        Sorter::ConstIterator et2 = sorter.constEnd();
        if (total != 0) {
            for (; it2 != et2; ++it2)
                qDebug("%-22s %8dms   ( %5.2f%% )",
                       qPrintable(it2.value()->name()), it2.key(), 100.0 * it2.key() / total);
            qDebug("Total: %8dms", total);
        } else {
            qDebug("Total time calculate error");
        }
    }
}

static inline QString getPlatformName()
{
    return QOperatingSystemVersion::current().name();
}

QString PluginManager::platformName()
{
    static const QString result = getPlatformName();
    return result;
}

bool PluginManager::isInitializationDone()
{
    return d->m_isInitializationDone;
}

bool PluginManager::registerDelayInit(PluginSpec *spec)
{
    return d->registerDelayInit(spec);
}

bool PluginManager::registerAddXmlConfigToActiveProjectWhenSaveProject(PluginSpec *spec)
{
    return d->registerAddXmlConfigToActiveProjectWhenSaveProject(spec);
}

QList<PluginSpec *> PluginManager::getRegisterAddXmlConfigToActiveProjectWhenSaveProject()
{
    return d->m_registerAddXmlConfigToActiveProjectWhenSaveProjectQueue;
}

bool PluginManager::registerConditionTypeToPlugin(const QString &name, IPlugin *spec)
{
    return d->registerConditionNameToPlugin(name, spec);
}

IPlugin * PluginManager::getPluginAddressByConditionType(const QString &name)
{
    if(d->hashConditionTypeToPlugin.contains(name))
        return d->hashConditionTypeToPlugin[name];
    else{
        PRINT_ERROR(tr("No matching plugin for condition type %1").arg(name));
        return nullptr;
    }
    return nullptr;
}

IPlugin * PluginManager::getPluginAddressByPluginName(const QString &name)
{
    if(name.isEmpty()){
        return nullptr;
    }
    if(d->hashPluginNameToPluginAddress.contains(name))
    {
        return d->hashPluginNameToPluginAddress[name];
    }
    else{
        PRINT_ERROR(tr("No matching plugin for plugin name %1").arg(name));
        return nullptr;
    }
    return nullptr;
}

QHash<QString, IPlugin*> PluginManager::gethashConditionTypeToPluginAddress()
{
    return d->hashConditionTypeToPlugin;
}

/*!
    Retrieves one object with \a name from the object pool.
    \sa addObject()
*/

QObject *PluginManager::getObjectByName(const QString &name)
{
    QReadLocker lock(&d->m_lock);
    QList<QObject *> all = allObjects();
    foreach (QObject *obj, all) {
        if (obj->objectName() == name)
            return obj;
    }
    return 0;
}

/*!
    Retrieves one object inheriting a class with \a className from the object
    pool.
    \sa addObject()
*/

QObject *PluginManager::getObjectByClassName(const QString &className)
{
    const QByteArray ba = className.toUtf8();
    QReadLocker lock(&d->m_lock);
    QList<QObject *> all = allObjects();
    foreach (QObject *obj, all) {
        if (obj->inherits(ba.constData()))
            return obj;
    }
    return 0;
}

PluginSpec *PluginManager::pluginByName(const QString &pluginName)
{
    return d->pluginByName(pluginName);
}
