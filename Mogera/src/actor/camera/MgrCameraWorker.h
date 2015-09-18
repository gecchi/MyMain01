#ifndef MGRCAMERAWORKER_H_
#define MGRCAMERAWORKER_H_
#include "Mogera.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace Mogera {

/**
 * �J�����}�� .
 * �J����(Mogera::MgrCamera)�ƁA���_(Mogera::MgrCameraViewPoint) �𑀂�A
 * ����� UP�̕����x�N�g�� pUp_ ���Ǘ����܂��B
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MgrCameraWorker : public GgafCore::GgafMainActor {

    /** �J������UP�v�f�x�N�g���̖ʔԍ��ƁA�����̔��΃x�N�g���̖ʔԍ��Ƃ̊֘A�e�[�u�� */
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
    MgrCamera* pCam_;
    /** [r]���_�ւ̎Q�� */
    MgrCameraViewPoint* pVp_;
    /** [r]�J�����̏�����̈ʒu�x�N�g�� */
    MgrCameraUpVector*  pUp_;
    /** �J�����}���̈ړ��ڕW���W */
    coord t_x_CAM_, t_y_CAM_, t_z_CAM_;
    /** �J�����}���̃r���[�|�C���g�̈ړ��ڕW���W */
    coord t_x_VP_, t_y_VP_, t_z_VP_;
    /** �J�����}���̓��̕����ڕW�ԍ� */
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
    virtual ~MgrCameraWorker(); //�f�X�g���N�^
};

}
#endif /*MGRCAMERAWORKER_H_*/
