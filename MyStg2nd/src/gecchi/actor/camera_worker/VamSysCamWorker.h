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

namespace MyStg2nd {

/**
 * VamSystem�̃J�����}�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public CameraWorker {

public:
    MyShip* _pMyShip;

    /** ���_���珉���J����Z�ʒu�̋��� */
//    int _dZ_camera_init;

    /** �J����Y���W��� */
    appcoord _lim_CAM_top;
    /** �J����Y���W���� */
    appcoord _lim_CAM_bottom;
    /** �J����X���W��� */
    appcoord _lim_CAM_front;
    /** �J����X���W���� */
    appcoord _lim_CAM_behaind;
    /** �J����Z���W��� */
    appcoord _lim_CAM_zleft;
    /** �J����Z���W���� */
    appcoord _lim_CAM_zright;
    /** �r���[�|�C���gY���W��� */
    appcoord _lim_VP_top;
    /** �r���[�|�C���gY���W���� */
    appcoord _lim_VP_bottom;
    /** �r���[�|�C���gX���W��� */
    appcoord _lim_VP_front;
    /** �r���[�|�C���gX���W���� */
    appcoord _lim_VP_behaind;
    /** �r���[�|�C���gZ���W��� */
    appcoord _lim_VP_zleft;
    /** �r���[�|�C���gZ���W���� */
    appcoord _lim_VP_zright;

//    /** ���݂̃J������UP�̃A���O���l */
//    appangle _angXY_nowCamUp;
    /** ��ʔw�㎞�pZ���␳�͈͍��� */
    appcoord _correction_width;
    /** ��ʔw�㎞�pY���␳�͈͍��� */
    appcoord _correction_height;
    /** �J�����̍ō����x�i����A�����ŉ����j */
//    int _cam_velo_renge;
    /** �J�����̑��x���A���x���@�̒ʏ�ړ����x��1.0�{�ƂȂ�J�����ڕW���W����̋����B */
//    int _stop_renge; //�J�����ڕW���W�������A�����菬�����ƁA     1.0�{��茸
//                     //�J�����ڕW���W�������A������傫���Ƃ����� 1.0�{��蒴
    /** �J�����ڕW���W�ɉ�������Z�����W�I�t�Z�b�g�␳�l */
    appcoord _stop_dZ;
    /** �J�����ڕW���W�ɉ�������Y�����W�I�t�Z�b�g�␳�l */
    appcoord _stop_dY;


    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual ~VamSysCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
