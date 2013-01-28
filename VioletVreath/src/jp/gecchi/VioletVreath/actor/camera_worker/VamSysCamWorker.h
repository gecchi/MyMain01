#ifndef VAMSYSCAMWORKER_H_
#define VAMSYSCAMWORKER_H_

#define VAM_POS_RIGHT 1
#define VAM_POS_LEFT 2
#define VAM_POS_TOP 3
#define VAM_POS_BOTTOM 4
#define VAM_POS_TO_BEHIND 10
#define VAM_POS_BEHIND_RIGHT 11
#define VAM_POS_BEHIND_LEFT 12
#define VAM_POS_BEHIND_TOP 13
#define VAM_POS_BEHIND_BOTTOM 14

namespace VioletVreath {

/**
 * VamSystem�̃J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public CameraWorker {

public:
    MyShip* pMyShip_;
    /** ���_���珉���J����Z�ʒu�̋��� */
//    int dZ_camera_init_;

    /** �J����Y���W��� */
    coord lim_CAM_top_;
    /** �J����Y���W���� */
    coord lim_CAM_bottom_;
    /** �J����X���W��� */
    coord lim_CAM_front_;
    /** �J����X���W���� */
    coord lim_CAM_behaind_;
    /** �J����Z���W��� */
    coord lim_CAM_zleft_;
    /** �J����Z���W���� */
    coord lim_CAM_zright_;
    /** �r���[�|�C���gY���W��� */
    coord lim_VP_top_;
    /** �r���[�|�C���gY���W���� */
    coord lim_VP_bottom_;
    /** �r���[�|�C���gX���W��� */
    coord lim_VP_front_;
    /** �r���[�|�C���gX���W���� */
    coord lim_VP_behaind_;
    /** �r���[�|�C���gZ���W��� */
    coord lim_VP_zleft_;
    /** �r���[�|�C���gZ���W���� */
    coord lim_VP_zright_;

//    /** ���݂̃J������UP�̃A���O���l */
//    angle angXY_nowCamUp_;
    /** ��ʔw�㎞�pZ���␳�͈͍��� */
    coord correction_width_;
    /** ��ʔw�㎞�pY���␳�͈͍��� */
    coord correction_height_;
    /** �J�����̍ō����x�i����A�����ŉ����j */
//    int cam_velo_renge_;
    /** �J�����̑��x���A���x���@�̒ʏ�ړ����x��1.0�{�ƂȂ�J�����ڕW���W����̋����B */
//    int stop_renge_; //�J�����ڕW���W�������A�����菬�����ƁA     1.0�{��茸
//                     //�J�����ڕW���W�������A������傫���Ƃ����� 1.0�{��蒴
    /** �J�����ڕW���W�ɉ�������Z�����W�I�t�Z�b�g�␳�l */
    coord stop_dZ_;
    /** �J�����ڕW���W�ɉ�������Y�����W�I�t�Z�b�g�␳�l */
    coord stop_dY_;
    /** �J�����̓I�v�V�����w�ʒ��ł���ꍇtrue */
    bool is_cam_pos_option_back_;

public:
    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual ~VamSysCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
