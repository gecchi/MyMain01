#ifndef PAUSECAMWORKER_H_
#define PAUSECAMWORKER_H_
#include "jp/gecchi/VioletVreath/actor/camera_worker/CameraWorker.h"

namespace VioletVreath {

/**
 * �ꎞ��~���̃J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class PauseCamWorker : public CameraWorker {

public:
    ViewPointGuide* pVPGuide_;

    int cd_;

    int cam_x_, cam_y_, cam_z_, vp_x_, vp_y_, vp_z_;

    bool mdz_flg_;
    double mdz_vx_, mdz_vy_, mdz_vz_, mdz_t_;
    int mdz_total_;

public:
    PauseCamWorker(const char* prm_name);

    virtual void initialize() override;


    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~PauseCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
