#ifndef VVVCAMWORKER_H_
#define VVVCAMWORKER_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VVViewer {

/**
 * VVViewer�̃J�����}�� .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamWorker : public GgafLib::DefaultGeometricActor {

public:
    /** [r]�J�����ւ̎Q�� */
    VvvCamera* pCam_;
    /** [r]���_�ւ̎Q�� */
    VvvCameraViewPoint* pVp_;
    /** �J�����}���̈ړ��ڕW���W */
    coord t_x_CAM_, t_y_CAM_, t_z_CAM_;
    /** �J�����}���̃r���[�|�C���g�̈ړ��ڕW���W */
    coord t_x_VP_, t_y_VP_, t_z_VP_;

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


    virtual ~VvvCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
