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
 */
class World : public GgafDx9LibStg::DefaultScene {

public:
    bool _is_create_GameScene;
    char _aBufDebug[80];
    LabelGecchi16Font* _pFont16_Debug;

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
