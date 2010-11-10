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




#ifdef pUNIVERSE
    #define pWORLD ((MyStg2nd::World*)(pUNIVERSE->_pWorld))
    #define pACTIVE_CAMWORKER (pUNIVERSE->_pActiveCameraWorker)
#else
    #error pUNIVERSE isnt define
#endif


/**
 * ���E�V�[���N���X .
 * �{�N���X�́A�A�v����́u���̐��v�̐U�镑�������������Ă��܂��B<BR>
 */
class World : public GgafDx9LibStg::DefaultScene {

public:
    bool _is_create_GameScene;
    char _aBufDebug[80];
    LabelGecchi16Font* _pFont16_Debug;
    GameScene* _pGameScene;

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
