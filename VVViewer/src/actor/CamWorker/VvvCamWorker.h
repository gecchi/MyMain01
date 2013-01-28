#ifndef VVVCAMWORKER_H_
#define VVVCAMWORKER_H_


namespace VVViewer {

/**
 * VVViewer�̃J�����}�� .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamWorker : public GgafLib::DefaultGeometricActor {

public:
    int cd_;

    int cam_X_, cam_Y_, cam_Z_, vp_X_, vp_Y_, vp_Z_;

    bool mdz_flg_;
    double mdz_vx_, mdz_vy_, mdz_vz_, mdz_t_;
    int mdz_total_;
    /** ���_���珉���J����Z�ʒu�̋��� */
    coord dZ_camera_init_;
    //�J�����̈ړ��ڕW���W
    coord move_target_X_CAM_, move_target_Y_CAM_, move_target_Z_CAM_;
    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W
    coord move_target_X_VP_, move_target_Y_VP_, move_target_Z_VP_;
    //�J�����̖ڕWUP�A���O���l
    angle move_target_XY_CAM_UP_;
    angle angXY_nowCamUp_;
    /** �J�����̑��x���A���x���@�̒ʏ�ړ����x��1.0�{�ƂȂ�J�����ڕW���W����̋����B */
    coord stop_renge_; //�J�����ڕW���W�������A�����菬�����ƁA     1.0�{��茸
                     //�J�����ڕW���W�������A������傫���Ƃ����� 1.0�{��蒴
public:
    VvvCamWorker(const char* prm_name);

    virtual void initialize() override;


    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~VvvCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
