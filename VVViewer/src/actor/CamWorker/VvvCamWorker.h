#ifndef VVVCAMWORKER_H_
#define VVVCAMWORKER_H_
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VVViewer {

/**
 * VVViewerのカメラマン .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamWorker : public GgafLib::DefaultGeometricActor {

public:
    /** [r]カメラへの参照 */
    VvvCamera* pCam_;
    /** [r]視点への参照 */
    VvvViewPoint* pVp_;
    /** [r]カメラのUPベクトルにコピーされて同期を取るベクトル座標のアクター */
    GgafLib::DefaultGeometricActor* pUp_;
    /** [r]pUp_を滑らかに移動させるためのヘルパー */
    GgafDxCore::GgafDxAxesMover* pAxsMver_Up_;
    /** カメラマンの移動目標座標 */
    coord t_x_CAM_, t_y_CAM_, t_z_CAM_;
    /** カメラマンのビューポイントの移動目標座標 */
    coord t_x_VP_, t_y_VP_, t_z_VP_;
    /** カメラマンの頭の方向番号 */
    int t_cam_up_face_;
    frame frame_of_behaving_since_onSwitch_;

    int cd_;
    bool mdz_flg_;
    double mdz_vx_, mdz_vy_, mdz_vz_, mdz_t_;
    int mdz_total_;
public:
    VvvCamWorker(const char* prm_name);
    void slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvCamTo(coord tx, coord ty, coord tz, frame t);
    void slideMvVpTo(coord tx, coord ty, coord tz, frame t);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~VvvCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
