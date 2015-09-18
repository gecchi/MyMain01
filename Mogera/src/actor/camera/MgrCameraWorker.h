#ifndef MGRCAMERAWORKER_H_
#define MGRCAMERAWORKER_H_
#include "Mogera.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace Mogera {

/**
 * カメラマン .
 * カメラ(Mogera::MgrCamera)と、視点(Mogera::MgrCameraViewPoint) を操り、
 * さらに UPの方向ベクトル pUp_ を管理します。
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MgrCameraWorker : public GgafCore::GgafMainActor {

    /** カメラのUP要素ベクトルの面番号と、視線の反対ベクトルの面番号との関連テーブル */
    static int relation_up_vec_[3*3*3][3*3*3];
    /** relation_up_vec_アクセス用 */
    static int (*relation_up_by_vec_)[3*3*3];

private:
    /** 現在のカメラ→視点の方向番号 */
    dir26 vcv_dir_;
    /** 前回カメラ→視点の方向番号 */
    dir26 vcv_dir_prev_;

public:
    /** [r]カメラへの参照 */
    MgrCamera* pCam_;
    /** [r]視点への参照 */
    MgrCameraViewPoint* pVp_;
    /** [r]カメラの上方向の位置ベクトル */
    MgrCameraUpVector*  pUp_;
    /** カメラマンの移動目標座標 */
    coord t_x_CAM_, t_y_CAM_, t_z_CAM_;
    /** カメラマンのビューポイントの移動目標座標 */
    coord t_x_VP_, t_y_VP_, t_z_VP_;
    /** カメラマンの頭の方向目標番号 */
    dir26 t_cam_up_dir_;

    frame frame_of_behaving_since_onSwitch_;

public:
    MgrCameraWorker(const char* prm_name);

    static bool initStatic();

    virtual void initialize() override;
    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processFinal() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    inline frame getSwitchedFrame() {
        return frame_of_behaving_since_onSwitch_;
    }

    void slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t,
                      float prm_x_p1, float prm_y_p1, float prm_z_p1);
    void slideMvCamTo(coord tx, coord ty, coord tz, frame t);
    void slideMvCamTo(coord tx, coord ty, coord tz, frame t,
                      float prm_x_p1, float prm_y_p1, float prm_z_p1);


    void slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvVpTo(coord tx, coord ty, coord tz, frame t);

    void slideMvUpVecTo(dir26 prm_up_dir_no, frame t);
//    void stopNaturallyCam(coord distance, frame t);
//    void stopNaturallyVp(coord distance, frame t);

    void stopMvCam();
    void stopMvVp();
//    void behaveAutoCamUp();
    virtual ~MgrCameraWorker(); //デストラクタ
};

}
#endif /*MGRCAMERAWORKER_H_*/
