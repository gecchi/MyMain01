#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/CameraWorker.h"

#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

#define VAM_POS_NON          DIR26( 0, 0, 0)
#define VAM_POS_ZRIGHT       DIR26( 0, 0,-1)
#define VAM_POS_ZRIGHT_UP    DIR26( 0,+1,-1)
#define VAM_POS_UP           DIR26( 0,+1, 0)
#define VAM_POS_ZLEFT_UP     DIR26( 0,+1,+1)
#define VAM_POS_ZLEFT        DIR26( 0, 0,+1)
#define VAM_POS_ZLEFT_DOWN   DIR26( 0,-1,+1)
#define VAM_POS_DOWN         DIR26( 0,-1, 0)
#define VAM_POS_ZRIGHT_DOWN  DIR26( 0,-1,-1)

namespace VioletVreath {

/**
 * VamSystemのカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public CameraWorker {

    /** [r/w]自機に対してYZ平面に平行で回っているカメラのアングル位置 */
    angle ang_cam_around_;
    /** [r]ang_cam_around_ の初期アングル位置 */
    angle ang_cam_around_base_;
    /** [r]ang_cam_around_が、元のang_cam_around_base_に自動戻り中に、true */
    bool returnning_cam_pos_;
    /** [r]ang_cam_around_が、元のang_cam_around_base_に自動戻り費やす時間(フレーム) */
    frame returnning_cam_pos_frames_;
    /** [r]ang_cam_around_ を８方向の定数で表した方向値(VAM_POS_XXXXX が入る) */
    dir26 pos_camera_;
    /** [r]pos_camera_の１フレーム前の方向値(VAM_POS_XXXXX) */
    dir26 pos_camera_prev_;
    /** [r]カメラの８方向位置が切り替わった（pos_camera_の値が変化した）ならばtrue */
    bool is_just_changed_pos_cam_;
    /** [r/w]カメラがなめらか移動に費やすフレーム数 */
    frame cam_mv_frame_;
    /** [r]カメラがなめらか移動に費やすフレーム数の標準値 */
    frame cam_mv_frame_base_;

    coord DZC_;
    coord DXC_;
    coord DX2_C_;
    coord X_P_C_;


public:
    enum {
        SE_RETURNNING_CAM_POS     ,
    };

    MyShip* pMyShip_;

    /** カメラY座標上限 */
    coord lim_CAM_top_;
    /** カメラY座標下限 */
    coord lim_CAM_bottom_;
    /** カメラX座標上限 */
    coord lim_CAM_infront_;
    /** カメラX座標下限 */
    coord lim_CAM_behaind_;
    /** カメラZ座標上限 */
    coord lim_CAM_zleft_;
    /** カメラZ座標下限 */
    coord lim_CAM_zright_;
    /** ビューポイントY座標上限 */
    coord lim_VP_top_;
    /** ビューポイントY座標下限 */
    coord lim_VP_bottom_;
    /** ビューポイントX座標上限 */
    coord lim_VP_infront_;
    /** ビューポイントX座標下限 */
    coord lim_VP_behaind_;
    /** ビューポイントZ座標上限 */
    coord lim_VP_zleft_;
    /** ビューポイントZ座標下限 */
    coord lim_VP_zright_;

    GgafDxCore::GgafDxSeTransmitter* pSe_;

public:
    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    inline dir26 getPosCam() {
        return pos_camera_;
    }
    inline bool isJustChangedPosCam() {
        return is_just_changed_pos_cam_;
    }
    virtual ~VamSysCamWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
