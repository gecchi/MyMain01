#ifndef WORLD_H_
#define WORLD_H_
namespace MyStg2nd {


#ifdef P_UNIVERSE
    #define P_WORLD ((MyStg2nd::World*)(P_UNIVERSE->_pWorld))
#else
    #error P_UNIVERSE isnt define
#endif


/**
 * ���E�V�[���N���X .
 * �{�N���X�́A�A�v����́u���̐��v�̐U�镑�������������Ă��܂��B<BR>
 */
class World : public GgafDx9LibStg::DefaultScene {

public:
    bool _is_create_GameScene;
    char _aBufDebug[80];
    LabelGecchi16Font* _pFont16_Wait;
    LabelGecchi16Font* _pFont16_Debug;
    LabelGecchi16Font* _pStringBoard01;
    PreDrawScene* _pPreDrawScene;
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
