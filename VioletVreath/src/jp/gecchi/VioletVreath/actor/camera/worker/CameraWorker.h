#ifndef CAMERAWORKER_H_
#define CAMERAWORKER_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace VioletVreath {

/**
 * �J�����}�� .
 * �J����(VioletVreath::Camera)�ƁA���_(VioletVreath::CameraViewPoint) �𑀂�A
 * ����� UP�̕����x�N�g�� pUp_ ���Ǘ����܂��B
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

    /** �J������UP�v�f�x�N�g���̖ʔԍ��ƁA�����̔��΃x�N�g���̖ʔԍ��Ƃ̊֘A�e�[�u�� */
    static int relation_up_vec_[3*3*3][3*3*3];
    /** relation_up_vec_�A�N�Z�X�p */
    static int (*relation_up_by_vec_)[3*3*3];

private:
    /** ���݂̃J���������_�̕����ԍ� */
    face26 vcv_face_;
    /** �O��J���������_�̕����ԍ� */
    face26 vcv_face_prev_;

public:
    /** [r]�J�����ւ̎Q�� */
    Camera* pCam_;
    /** [r]���_�ւ̎Q�� */
    CameraViewPoint* pVp_;
    /** [r]�J�����̏�����̈ʒu�x�N�g�� */
    CameraUpVector*  pUp_;
    /** �J�����}���̈ړ��ڕW���W */
    coord t_x_CAM_, t_y_CAM_, t_z_CAM_;
    /** �J�����}���̃r���[�|�C���g�̈ړ��ڕW���W */
    coord t_x_VP_, t_y_VP_, t_z_VP_;
    /** �J�����}���̓��̕����ڕW�ԍ� */
    face26 t_cam_up_face_;

    frame frame_of_behaving_since_onSwitch_;

public:
    CameraWorker(const char* prm_name);

    bool initStatic();

    virtual void initialize() override;
    virtual void onActive() override;
    /**
     * �X�C�b�`���ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N
     */
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

    void slideMvUpTo(face26 prm_up_face_no, frame t);
//    void stopNaturallyCam(coord distance, frame t);
//    void stopNaturallyVp(coord distance, frame t);

    void stopMvCam();
    void stopMvVp();
//    void behaveAutoCamUp();
    virtual ~CameraWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERAWORKER_H_*/