#ifndef PAUSECAMWORKER_H_
#define PAUSECAMWORKER_H_


namespace VioletVreath {

/**
 * �ꎞ��~���̃J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class PauseCamWorker : public CameraWorker {

public:
    ViewPointGuide* _pVPGuide;

    int _cd;

    int _cam_X,_cam_Y,_cam_Z, _vp_X, _vp_Y, _vp_Z;

    bool _mdz_flg;
    double _mdz_vx, _mdz_vy, _mdz_vz, _mdz_t;
    int _mdz_total;
    PauseCamWorker(const char* prm_name);

    virtual void initialize() override;


    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~PauseCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
