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
 * �J����.
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class VamSysCamWorker : public CameraWorker {

public:
    MyShip* _pMyShip;

    /** ���_���珉���J����Z�ʒu�̋��� */
    int _dZ_camera_init;

    /** �J����Y���W��� */
    int _lim_CAM_top;
    /** �J����Y���W���� */
    int _lim_CAM_bottom;
    /** �J����X���W��� */
    int _lim_CAM_front;
    /** �J����X���W���� */
    int _lim_CAM_behaind;
    /** �J����Z���W��� */
    int _lim_CAM_zleft;
    /** �J����Z���W���� */
    int _lim_CAM_zright;
    /** �r���[�|�C���gY���W��� */
    int _lim_VP_top;
    /** �r���[�|�C���gY���W���� */
    int _lim_VP_bottom;
    /** �r���[�|�C���gX���W��� */
    int _lim_VP_front;
    /** �r���[�|�C���gX���W���� */
    int _lim_VP_behaind;
    /** �r���[�|�C���gZ���W��� */
    int _lim_VP_zleft;
    /** �r���[�|�C���gZ���W���� */
    int _lim_VP_zright;

    /** ���݂̃J������UP�̃A���O���l */
    angle _angXY_nowCamUp;
    /** ��ʔw�㎞�pZ���␳�͈͍��� */
    int _correction_width;
    /** ��ʔw�㎞�pY���␳�͈͍��� */
    int _correction_height;
    /** �J�����̍ō����x�i����A�����ŉ����j */
    int _cam_velo_renge;
    /** �J�����̑��x���A���x���@�̒ʏ�ړ����x��1.0�{�ƂȂ�J�����ڕW���W����̋����B */
    int _stop_renge; //�J�����ڕW���W�������A�����菬�����ƁA     1.0�{��茸
                     //�J�����ڕW���W�������A������傫���Ƃ����� 1.0�{��蒴
    /** �J�����ڕW���W�ɉ�������Z�����W�I�t�Z�b�g�␳�l */
    int _stop_dZ;
    /** �J�����ڕW���W�ɉ�������Y�����W�I�t�Z�b�g�␳�l */
    int _stop_dY;


    VamSysCamWorker(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }
    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }
    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }
    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }
    virtual ~VamSysCamWorker(); //�f�X�g���N�^
};

}
#endif /*CAMERA_H_*/
