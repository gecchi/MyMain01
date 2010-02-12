#ifndef WORLD_H_
#define WORLD_H_
namespace MyStg2nd {

//getParent getSub ������ �L���X�g�}�N���B
//���L�}�N���g�p����ɂ́A�I�u�W�F�N�g�̎��ʖ����A
//�N���X���̖�����"...Scene"�Ƃ������������苎�������̂ł��邱�Ƃ��O������ł�
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))
#define getParentActor(X) ((X##Actor*)getParent(#X))
#define getSubActor(X) ((X##Actor*)getSub(#X))


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
 * ���E�V�[���N���X .
 * ���̐��ɁA�Ƃ��鐢�E������܂����B<BR>
 * �{�N���X�́A���E�̐U�镑�������������Ă��܂��B<BR>
 * ���C���̏����̓J��������ɂȂ��Ă��܂��Ă���B
 */
class World : public GgafDx9LibStg::DefaultScene {

public:

    int _dZ_camera_init;
    int _lim_CAM_top;
    int _lim_CAM_bottom;
    int _lim_CAM_front;
    int _lim_CAM_behaind;
    int _lim_CAM_zleft;
    int _lim_CAM_zright;

    int _lim_VP_top;
    int _lim_VP_bottom;
    int _lim_VP_front;
    int _lim_VP_behaind;
    int _lim_VP_zleft;
    int _lim_VP_zright;

    int _correction_width;
    int _correction_height;
    int _pos_camera;
    int _renge;
    DWORD _frame_pushdown_zmove;

    World(const char* prm_name);

    /**
     * ��������
     */
    void initialize() override;

     /**
     * ��OverRide �ł���
     */
    void processBehavior() override;

     /**
     * ��OverRide �ł���
     */
    void processJudgement() override;

    virtual ~World();
};

}
#endif /*WORLD_H_*/
