#ifndef FRMINPUT_H
#define FRMINPUT_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
#include "qscreen.h"
#else
#include "qdesktopwidget.h"
#endif
#include "qapplication.h"
#include "qpropertyanimation.h"
#include "qstandarditemmodel.h"
#include "qmutex.h"
#include "qfile.h"
#include "qscrollbar.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "qdebug.h"

#include "abstractwidget.h"
#include "frminputnumber.h"
#include "pinyingoogle.h"
#include "pinyincustom.h"
#include "pinyinchar.h"
#include "pinyinhelper.h"

#pragma execution_character_set("utf-8")

namespace Ui {
class frmInput;
}

class frmInput : public AbstractWidget<Ui::frmInput>
{
    Q_OBJECT

public:
    //定义友元类 方便直接使用本类的私有变量
    friend class frmInputNumber;
    friend class PinYinCustom;
    friend class PinYinChar;
    friend class PinYinHelper;

    //单例模式,保证一个程序只存在一个输入法实例对象
    static frmInput *Instance();
    explicit frmInput(QWidget *parent = 0);
    ~frmInput();

protected:
    //显示的时候更新图标大小等
    void showEvent(QShowEvent *);
    //事件过滤器
    bool eventFilter(QObject *watched, QEvent *event);
    virtual void retranslateUi();
private:
    void setPinYinLabelText(const QString &fullText);
    QString pinYinLabelFullText() const;

    Ui::frmInput *ui;
    static frmInput *self;

    //鼠标按下拖动
    QPoint mousePoint;
    bool mousePressed;

    //繁体模式
    bool fanti;
    //当前大小写状态
    bool upper;    
    //当前字符类型
    quint8 charType;

    //显示硬键盘汉字标签的数量
    int maxCountCh;
    //显示汉字的标签的最大数量
    int maxCountCn;
    //汉字候选面板最大列数
    int columnCount;
    //面板固定尺寸
    int fixedWidth, fixedHeight;

    //按钮长按自动重复
    bool autoRepeat;
    //是否仅仅当做控件使用,后期拓展成支持输入到其他程序
    bool onlyControl;
    //样式是否支持按下
    bool pressedStyle;
    //样式是否支持悬停
    bool hoverStyle;
    //是否自动隐藏没有汉字的标签
    bool hideLabelNoText;
    //是否启用硬键盘同步
    bool useHardKeyBoard;

    //图标宽度+高度
    int iconWidth;
    int iconHeight;

    //字库文件路径
    QString dbPath;
    //当前输入法面板位置类型
    QString position;
    //当前输入法类型
    QString inputType;
    //当前样式颜色
    QString styleName;
    //当前样式对应图标的类型
    QString iconType;

    //使用全键盘的数字面板还是独立的小数字面板
    QString numberType;
    //数字键盘
    frmInputNumber *inputNumber;

    //谷歌拼音内核
    PinYinGoogle pinyinGoogle;
    //自定义拼音内核
    PinYinCustom pinyinCustom;
    //自定义字符 可拓展为多语言输入
    PinYinChar pinyinChar;
    //拼音辅助类 查询及显示汉字
    PinYinHelper pinyinHelper;

    //当前焦点的对象
    QWidget *currentWidget;

    //固定数量汉字标签数组(硬键盘展示用)
    QList<QLabel *>labCh;

    //顶部汉字标签数组
    QList<QLabel *>labCn;

    //更多汉字标签数组
    QList<QLabel *>labMore;

    //所有按钮集合
    QList<QPushButton *> btns;

    //记住颜色用来设置中英切换
    QString mainTextColor;
    QString btnHoveColor;

    //记住最后按下的汉字
    QString lastText;

    //动画滑动
    QPropertyAnimation *animationCn;
    QPropertyAnimation *animationMore;

    //存储本地选中的字库文件,chinese_select.txt
    QStringList selectKey, selectValue;
    //存储本地用户自定义的字库文件,chinese_user.txt
    QStringList userKey, userValue;
    //繁体汉字对照表,chinese_fanti.txt
    QStringList fantiKey, fantiValue;

    //合法的输入控件,如果后面还发现其他控件也需要输入可以自行增加
    QStringList classNames;

private slots:
    //初始化窗体数据
    void initForm();
    //是否需要弹出输入法
    bool needInput();
    //加载下面一堆玩意
    void initServer();

    //初始化按钮和属性
    void initBtn();
    void initBtn(QList<QPushButton *> btns);
    //初始化显示汉字的标签
    void initLab();
    //初始化动画属性用来滑动选择
    void initAnimation();
    //初始化数字键盘
    void initInputNumber();
    //初始化友元类
    void initClass();
    //初始化数据库以及其他
    void initData();
    //初始化图标大小
    void initIconSize();

    //输入法面板按键处理
    void btnClicked();

    //焦点改变事件槽函数处理
    void focusChanged(QWidget *oldWidget, QWidget *nowWidget);

    //插入值到当前焦点控件
    void insertValue(const QString &value);
    //清空值,恢复到初始状态
    void clearValue();
    //删除当前焦点控件的一个字符
    void deleteValue();

    //滚动条恢复初始值
    void clearScroll();
    //显示输入法面板
    void showPanel();
    //隐藏输入法面板
    void hidePanel(bool clear = true);

    //控制面板隐藏显示
    void setWidgetVisible(int indexVisible);
    //通用发送模拟事件
    void sendEvent(quint8 type, const QString &text);

    bool copyQrcFileToShare(const QString &resourcePath, const QString &targetPath);

    void on_pbn_left_cn_clicked();

    void on_pbn_right_cn_clicked();

public:
    //设置字体名称及大小/包括按钮的字体大小和汉字部分的字体大小
    void setFontInfo(const QString &fontName, int btnFontSize, int labFontSize);
    //设置固定尺寸大小
    void setFixedSize2(int fixedWidth, int fixedHeight);
    //设置图标尺寸
    void setIconSize(int iconWidth, int iconHeight);
    //设置空隙间隔/按钮之间和候选词文本之间
    void setSpacing(int btnSpacing, int labSpacing);
    //设置顶部汉字区域高度
    void setTopHeight(int topHeight);

    //设置长按重复执行
    void setAutoRepeat(bool autoRepeat);
    //设置仅仅当做控件使用
    void setOnlyControl(bool onlyControl);
    //设置开启按下样式
    void setPressedStyle(bool pressedStyle);
    //设置开启悬停样式
    void setHoverStyle(bool hoverStyle);
    //设置是否自动隐藏没有汉字的标签
    void setHideLabelNoText(bool hideLabelNoText);
    //设置是否启用硬键盘同步
    void setUseHardKeyBoard(bool useHardKeyBoard);

    //设置汉字面板列数
    void setColumnCount(int columnCount);
    //设置最大汉字标签数量
    void setMaxCount(int maxCountCn);
    //设置数字面板方式
    void setNumberType(const QString &numberType);

    //设置字库路径
    void setDbPath(const QString &dbPath);
    //设置输入法弹出位置
    void setPosition(const QString &position);
    //设置当前输入法类型
    void setInputType(const QString &inputType);
    //改变字母大小写
    void setUpper(bool isUpper);

    //设置输入法颜色样式
    void setStyleName(const QString &styleName);
    //改变输入法面板样式
    void setColor(const QString &mainBackgroundColor, const QString &mainTextColor,
                  const QString &btnBackgroundColor, const QString &btnHoveColor,
                  const QString &btnHoveTextColor, const QString &labHoveColor,
                  const QString &labHoveTextColor);

signals:
    void receiveValue(const QString &value);
};

#endif // FRMINPUT_H
