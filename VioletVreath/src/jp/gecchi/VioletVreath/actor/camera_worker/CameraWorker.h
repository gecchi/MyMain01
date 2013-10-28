#ifndef CAMERAWORKER_H_
#define CAMERAWORKER_H_
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace VioletVreath {

/**
 * �J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

public:
    /** �J�����ʒu�ԍ� */
    int pos_camera_;

    GgafDxCore::GgafDxGeometricActor* pLockOnTarget_;

    /** ���_���珉���J����Z�ʒu�̋��� */
    coord dZ_camera_init_;
    //�J�����̈ړ��ڕW���W
    coord move_target_x_CAM_, move_target_y_CAM_, move_target_z_CAM_;
    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W
    coord move_target_x_VP_, move_target_y_VP_, move_target_z_VP_;
    //�J�����̖ڕWUP�A���O���l
    angle move_target_XY_CAM_UP_;
    angle angXY_nowCamUp_;

    /** �J�����̍ō����x�i����A�����ŉ����j */
    velo cam_velo_renge_;
    /** �J�����̑��x���A���x���@�̒ʏ�ړ����x��1.0�{�ƂȂ�J�����ڕW���W����̋����B */
    coord stop_renge_; //�J�����ڕW���W�������A�����菬�����ƁA     1.0�{��茸
                     //�J�����ڕW���W�������A������傫���Ƃ����� 1.0�{��蒴

    /** �����Ńu���Ȃ��X�s�[�h */
    velo burenai_speed_;

    frame frame_of_behaving_since_onSwitch_;

public:
    CameraWorker(const char* prm_name);

    virtual void initialize() override {
    }

    virtual void onSwitchCameraWork();

    virtual void onUndoCameraWork();

    virtual void onSwitchToOtherCameraWork();

    virtual void onCameBackFromOtherCameraWork();

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processFinal() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }


    void setMoveTargetCamBy(GgafDxCore::GgafDxGeometricActor* pTarget);
    void setMoveTargetCamVpBy(GgafDxCore::GgafDxGeometricActor* pTarget);
    void setMoveTargetCam(coord X, coord Y, coord Z);
    void setMoveTargetCamVp(coord X, coord Y, coord Z);
    void lockCamVp(GgafDxCore::GgafDxGeometricActor* pTarget);

    void unlockCamVp();

    inline frame getSwitchedFrame() {
        return frame_of_behaving_since_onSwitch_;
    }
    virtual ~CameraWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERAWORKER_H_*/
