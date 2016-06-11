#ifndef GGAFLIB_CAMERAWORKER_H_
#define GGAFLIB_CAMERAWORKER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace GgafLib {

/**
 * �J�����}�� .
 * �J����(VioletVreath::Camera)�ƁA���_(VioletVreath::CameraViewPoint) �𑀂�A
 * ����� UP�̕����x�N�g�� pUp_ ���Ǘ����܂��B
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

    /** [���J������UP�v�f�x�N�g���̖ʔԍ�][�����̔��΃x�N�g���̖ʔԍ�] = ���̑Ó���UP�v�f�x�N�g���̖ʔԍ�(�A��DIR26_NULL�͈ړ��s�v���Ӗ�����)  �֘A�e�[�u�� */
    static int relation_up_vec_[3*3*3][3*3*3];
    /** relation_up_vec_�A�N�Z�X�p */
    static int (*relation_up_by_vec_)[3*3*3];

private:
    /** ���݂̃J���������_�̕����ԍ� */
    dir26 vcv_dir_;
    /** �O��J���������_�̕����ԍ� */
    dir26 vcv_dir_prev_;

public:
    /** [r]�J�����ւ̎Q�� */
    DefaultCamera* pCam_;
    /** [r]���_�ւ̎Q�� */
    DefaultCameraViewPoint* pVp_;
    /** [r]�J�����̏�����̈ʒu�x�N�g�� */
    DefaultCameraUpVector*  pUp_;
    /** �J�����}���̈ړ��ڕW���W */
    coord t_x_CAM_, t_y_CAM_, t_z_CAM_;
    /** �J�����}���̃r���[�|�C���g�̈ړ��ڕW���W */
    coord t_x_VP_, t_y_VP_, t_z_VP_;
    /** �J�����}���̓��̕����ڕW�ԍ� */
    dir26 t_cam_up_dir_;

    frame frame_of_behaving_since_onSwitch_;

public:
    CameraWorker(const char* prm_name, DefaultCamera* prm_pCamera);

    static bool initStatic();

    virtual void initialize() override;

    virtual void onActive() override;
    /**
     * �X�C�b�`���ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N .
     * ���܂Ŏ��g����A�N�e�B�u�� CameraWorker ���������A
     * Spacetime::changeCameraWork() �ɂ�育�w�����������A
     * ���� Spacetime::undoCameraWork() ���s�ɂ�蕜�A�����A
     * ���Ƃɂ��A�A�N�e�B�u�ɐ؂�ւ�����ŏ��̃t���[����
     * Spacetime::processBehavior() ���ŃR�[���o�b�N�����B
     */
    virtual void onSwitchCameraWork();

    /**
     * ���� CameraWorker �ɐ؂�ւ��ۂ̃R�[���o�b�N .
     * ���܂Ŏ��g���A�N�e�B�u�� CameraWorker ���������A
     * Spacetime::changeCameraWork() ���� Spacetime::undoCameraWork() ���s�ɂ��A
     * ���� CameraWorker �ɐ؂�ւ��̂ŁA���t���[�����玩�g����A�N�e�B�u��
     * �Ȃ��Ă��܂��Ƃ��� inactivate() �����s����钼�O�ɌĂяo�����R�[���o�b�N�B
     */
    virtual void onChangedToOtherCameraWork();

    void targetAutoCamup();

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
    void mvCamTo(coord tx, coord ty, coord tz);

    bool isCamSliding();
    void slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);
    void slideMvVpTo(coord tx, coord ty, coord tz, frame t);

    void slideMvUpVecTo(coord tx, coord ty, coord tz, frame t);
    void slideMvUpVecTo(dir26 prm_up_dir_no, frame t);

    void setUpVec(coord tx, coord ty, coord tz);
//    void stopNaturallyCam(coord distance, frame t);
//    void stopNaturallyVp(coord distance, frame t);

    void stopMvCam();
    void stopMvVp();
//    void behaveAutoCamUp();
    virtual ~CameraWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERAWORKER_H_*/
