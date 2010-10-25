#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_


#define CAM_POS_RIGHT 1
#define CAM_POS_LEFT 2
#define CAM_POS_TOP 3
#define CAM_POS_BOTTOM 4
#define CAM_POS_TO_BEHIND 10
#define CAM_POS_BEHIND_RIGHT 11
#define CAM_POS_BEHIND_LEFT 12
#define CAM_POS_BEHIND_TOP 13
#define CAM_POS_BEHIND_BOTTOM 14

namespace MyStg2nd {

/**
 * カメラ.
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public GgafCore::GgafMainActor {

public:
    MyShip* _pMyShip;

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
    /** カメラの最高速度（上限、負数で下限） */
    int _cam_velo_renge;
    /** カメラの速度が、丁度自機の通常移動速度の1.0倍となるカメラ目標座標からの距離。 */
    int _stop_renge; //カメラ目標座標距離が、これより小さいと、     1.0倍より減
                     //カメラ目標座標距離が、これより大きいとさいと 1.0倍より超
    /** カメラ目標座標に加えられるZ軸座標オフセット補正値 */
    int _stop_dZ;
    /** カメラ目標座標に加えられるY軸座標オフセット補正値 */
    int _stop_dY;


    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }
    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }
    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }
    virtual ~VamSysCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
