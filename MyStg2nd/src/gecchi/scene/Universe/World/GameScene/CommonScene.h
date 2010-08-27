#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
namespace MyStg2nd {

#define CAM_POS_RIGHT 1
#define CAM_POS_LEFT 2
#define CAM_POS_TOP 3
#define CAM_POS_BOTTOM 4
#define CAM_POS_TO_BEHIND 10
#define CAM_POS_BEHIND_RIGHT 11
#define CAM_POS_BEHIND_LEFT 12
#define CAM_POS_BEHIND_TOP 13
#define CAM_POS_BEHIND_BOTTOM 14

/**
 * �Q�[���V�[���̋��ʃV�[���N���X .
 */
class CommonScene : public GgafDx9LibStg::DefaultScene {

public:
    MyShip* _pMyShip;

    GgafCore::GgafActorDispatcher* _pDispatcher_EnemyShots001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion003;
    GgafCore::GgafActorDispatcher* _pDispatcher_LaserChipDispatcher;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectTurbo002;




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
    /** �J�����ʒu�ԍ� */
    int _pos_camera;

    int _cam_velo_renge;
    int _stop_renge;
    int _stop_dZ;
    int _stop_dY;
    frame _frame_pushdown_zmove;




    CommonScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~CommonScene();
};

}
#endif /*MYSHIPSCENE_H_*/
