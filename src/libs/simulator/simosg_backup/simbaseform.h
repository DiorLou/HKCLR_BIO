#pragma once

#include "osghud.h"
#include "osgmodel.h"
#include "osgrobotmodel.h"
#include "osgtrackmodel.h"
#include "osggroundmodel.h"
#include "roadpoint.h"
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osg/Group>
#include "simulator_global.h"

#include "osgmanipulator.h"
#include "pileupinfo.h"
#include <QPoint>
#define SIM_185

class osgBoxModel;
class osgPalletModel;

class QTimer;
class QSignalMapper;
class QPushButton;

class SIMULATOR_EXPORT SimBaseForm : public osgQOpenGLWidget
{
    Q_OBJECT

public:
    explicit SimBaseForm(
        QWidget *parent,
        const bool &isAutoRefreshCurrentRoadPoint = true);
    ~SimBaseForm();
    void setRealtimeRoadPoint(RoadPoint position);
    RoadPoint getRealTimeRoadPoint();
    void setTargetRoadPoint(RoadPoint position);
    RoadPoint getTargetRoadPoint();

    void setCoordIndex(int index);

    void setTool(ToolParams toolParam, bool isNull);
    void setWobj(WobjParams wobjParams, bool isNull);

    void setEnableDrawTrack(bool isDrawTrack);
    void setTrackDuration(const int &trackDuration);

    void clearTrack();

    void enableDrawTargetModel(
        const bool &isDrawTargetModel, const bool &isShowDrawPbn,
        const int &drawPbnIndex);
    void enableDrawCoord(
        const bool &isDrawCoord, const bool &isShowDrawPbn,
        const int &drawPbnIndex);

    bool isDrawCoord() const;

    void initButtons();

    void updateButtons(const QSize &size);

    void enableDrawTargetRoadPoint(bool enable = true);

    void enableDrawRealTimeRoadPoint(bool enable = true);

    void enableDrawGroundModel(bool bEnable);

    void setDHParam(const DHParam &dhParam);

    void setData(int index,bool leftOrRight);

    void setInstallParams(const double &alpha, const double &beta);

    void setTemporaryInstallParams(const double &alpha, const double &beta);

    void enableInstallationMode(bool bEnable);

    void enableDrawInstallationReferenceLocationModel(bool bEnable);

    void enableDrawInstallationRealLocationModel(bool bEnable);

    void enableDrawInstallationGroundModel(bool bEnable);

    void updateViewport();

    void addDePallet(const QString &uuid,const CubeSize &size,const QString& wobj);

    void removeDePallet(const QString &uuid);

    void removeAllDePallet();

    void addPallet(const QString &uuid,const CubeSize &size,const QString& wobj);

    void removePallet(const QString &uuid);

    void removeAllPallet();

    void moveModelFromBaseToTool(osg::ref_ptr<osg::MatrixTransform> child);

    void moveModelFromToolToWobj(osg::ref_ptr<osg::MatrixTransform> child,
                                 const Pos &pos,
                                 const Ori &ori);

    void moveModelFromToolToBase(osg::ref_ptr<osg::MatrixTransform> child,const Pos &pos, const Ori &ori);

    void addDepalletizingBox(const QString &uuid,const int &boxNum, const QString &wobj,
                             const Pos &pos, const Ori &ori, const CubeSize &size,
                             const Ori& rotate,const bool &isVisible = true);

    void *createPalletizingBox(const QString &uuid,const int &boxNum, const QString &wobj,
                             const Pos &pos, const Ori &ori, const CubeSize &size,
                             const Ori& rotate,const bool &isVisible = true);

    void removeDepalletizingBoxs(const QString &uuid);

    void removeAllPalletizingBoxs();

    bool isNeedReCreateModel(const QString &uuid);

    bool isAllowUpdateModel(const QString &uuid, const int &sum);

    void grapPalletizingBox(const QString &uuid, const int &boxNum);
    void grapPalletizingBox(const CubeSize &size, const Ori& rotate);

    void loosePalletizingBox(const QString &uuid, const int &boxNum,
                             const Pos &pos, const Ori &ori, const QString &wobj);
    void loosePalletizingBox();

    void setPalletizingBoxVisible(const QString &uuid, const int &boxNum, bool bEnable);

    void setPalletizingBoxVisible(const QString &uuid, bool bEnable);

    void setAllPalletizingBoxVisible(bool bEnable);

    void translateToPos(const QString &uuid, const int &boxNum, const Pos &pos);

    void rotateToOri(const QString &uuid, const int &boxNum, const Ori &ori);

    void setModelSize(const QString &uuid, const int &boxNum, const CubeSize &size);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
    virtual void paintGL();
private slots:
    void on_pbn_drawRealtimeModel_pressed();
    void on_pbn_drawTargetRoadPoint_pressed();
    void on_pbn_drawCoord_pressed();
    void on_pbn_drawGround_pressed();

    void on_pbn_frontView_pressed();
    void on_pbn_upMove_pressed();
    void on_pbn_downMove_pressed();
    void on_pbn_leftMove_pressed();
    void on_pbn_rightMove_pressed();
    void on_pbn_leftRotate_pressed();
    void on_pbn_rightRotate_pressed();
    void on_pbn_zoomOut_pressed();
    void on_pbn_zoomIn_pressed();
    void slot_updateRealTimeRoadPoint(RoadPoint rp);
    void initOsg();
    void initOsgEnvironment();
    void initOsgRobot();

    void slot_refreshDHParams(QObject *obj,const QList<double> &data);

private:
    void calculateWobjTransform(const QString &wobj,osg::Matrix &transform);

    void calculateBasePose(const osg::Matrix &transform,
                           const Pos &pos, const Ori &ori,
                           Pos &base_pos,
                           Ori &base_ori);

    void quaternionToEulerZYX(const osg::Quat& q,Ori &ori);

    void clearRobotModel();

private:
    void initLights();

    bool m_isAutoRefreshCurrentRoadPoint;

    QList<RoadPoint> m_trackRoadPointList;

    osgGroundModel m_osgGroundModel;
    osgTrackModel m_osgTrackModel;
    bool m_isDrawTrack;
    int m_trackDuration;

    RoadPoint m_realtimeRoadPoint;
    RoadPoint m_targetRoadPoint;

    QPushButton *m_pbnFrontView;
    QPushButton *m_pbnUpMove;
    QPushButton *m_pbnDownMove;
    QPushButton *m_pbnLeftMove;
    QPushButton *m_pbnRightMove;
    QPushButton *m_pbnLeftRotate;
    QPushButton *m_pbnRightRotate;
    QPushButton *m_pbnZoomOut;
    QPushButton *m_pbnZoomIn;
    QPushButton *m_pbnDrawGround;
    QPushButton *m_pbnDrawRealtimeModel;
    QPushButton *m_pbnDrawTargetModel;
    QPushButton *m_pbnDrawCoord;

    bool m_isDrawGround;
    bool m_isDrawRealtimeModel;
    bool m_isDrawTargetModel;
    bool m_isDrawCoord;

    bool m_isInstallationMode;
    bool m_isDrawInstallationReferenceLocationModel;
    bool m_isDrawInstallationRealLocationModel;
    bool m_isDrawInstallationGroundModel;

    QTimer *m_timerRender;

    QSharedPointer<osgRobotModel> m_realtimeRoadPointModelptr = nullptr;
    QSharedPointer<osgRobotModel> m_targetRoadPointModelptr = nullptr;

    QSharedPointer<osgRobotModel> m_installationReferenceLocationModelptr = nullptr;
    QSharedPointer<osgRobotModel> m_installationRealLocationModelptr = nullptr;

    osgGroundModel m_installationGroundModel;

    double m_endMat[16];

    int m_coordIndex;

    QPushButton *creatButton(
        int x, int y, int w, int h, bool isFlat,
        bool isAutoRepeat, QIcon icon, bool isShow);

    osg::ref_ptr<osg::Group> m_root;
    osg::ref_ptr<osg::MatrixTransform> m_rootTrans;
    osg::ref_ptr<osg::MatrixTransform> m_rootInstallationRealTrans;

    OsgManipulator *m_Manipulator;

    osgHUD m_HudCameraManager;

    QMap<QString ,osg::ref_ptr<osgPalletModel>> m_palletizingUuidAndPalletsMap;

    QMap<QString ,osg::ref_ptr<osgPalletModel>> m_depalletizingUuidAndPalletsMap;

    QMap<QString ,QMap<int, osg::ref_ptr<osgBoxModel>>> m_depalletizingUuidAndBoxsMap;

    QMap<QString ,QMap<int, QMap<int,osg::ref_ptr<osgBoxModel>>>> m_palletizingUuidAndBoxsMap;

    QMap<QString ,QList<QList<osg::ref_ptr<osgBoxModel>>>> m_depalletizingUuidAndBoxsList;
    QMap<QString ,QList<QList<osg::ref_ptr<osgBoxModel>>>> m_palletizingUuidAndBoxsList;

    osg::ref_ptr<osgBoxModel> m_grapBox;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    bool is_leftPress;
    QPoint m_lastPos;  // mouse position
    bool m_isConnected = false;

    //安装参数
    double m_alpha;
    double m_beta;

    //临时安装参数
    double m_temporary_alpha;
    double m_temporary_beta;

    bool m_isEnvironmentInited = false;
    bool m_isRobotInited = false;

    QString m_robotType;
};
