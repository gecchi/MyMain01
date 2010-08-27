#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
namespace MyStg2nd {

#define CAM_POS_RIGHT 1
#define CAM_POS_LEFT 2
#define CAM_POS_TOP 3
#define CAM_POS_BOTTOM 4
#define CAM_POS_TO_BEHIND 10
#define CAM_POS_BEHIND_RIGHT 11
#define CAM_POS_BEHIND_LEFT 12
#define CAM_POS_BEHIND_TOP 13
#define CAM_POS_BEHIND_BOTTOM 14

/**
 * ゲームシーンの共通シーンクラス .
 */
class CommonScene : public GgafDx9LibStg::DefaultScene {

public:
    MyShip* _pMyShip;

    GgafCore::GgafActorDispatcher* _pDispatcher_EnemyShots001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion003;
    GgafCore::GgafActorDispatcher* _pDispatcher_LaserChipDispatcher;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectTurbo002;




    /** 原点から初期カメラZ位置の距離 */
    int _dZ_camera_init;

    /** カメラY座標上限 */
    int _lim_CAM_top;
    /** カメラY座標下限 */
    int _lim_CAM_bottom;
    /** カメラX座標上限 */
    int _lim_CAM_front;
    /** カメラX座標下限 */
    int _lim_CAM_behaind;
    /** カメラZ座標上限 */
    int _lim_CAM_zleft;
    /** カメラZ座標下限 */
    int _lim_CAM_zright;
    /** ビューポイントY座標上限 */
    int _lim_VP_top;
    /** ビューポイントY座標下限 */
    int _lim_VP_bottom;
    /** ビューポイントX座標上限 */
    int _lim_VP_front;
    /** ビューポイントX座標下限 */
    int _lim_VP_behaind;
    /** ビューポイントZ座標上限 */
    int _lim_VP_zleft;
    /** ビューポイントZ座標下限 */
    int _lim_VP_zright;

    /** 現在のカメラのUPのアングル値 */
    angle _angXY_nowCamUp;
    /** 画面背後時用Z軸補正範囲差分 */
    int _correction_width;
    /** 画面背後時用Y軸補正範囲差分 */
    int _correction_height;
    /** カメラ位置番号 */
    int _pos_camera;

    int _cam_velo_renge;
    int _stop_renge;
    int _stop_dZ;
    int _stop_dY;
    frame _frame_pushdown_zmove;




    CommonScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~CommonScene();
};

}
#endif /*MYSHIPSCENE_H_*/
