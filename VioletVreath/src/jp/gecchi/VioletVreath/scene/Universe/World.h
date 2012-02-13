#ifndef WORLD_H_
#define WORLD_H_
namespace VioletVreath {


#ifdef P_UNIVERSE
    #define P_WORLD ((VioletVreath::World*)(P_UNIVERSE->_pWorld))
#else
    #error P_UNIVERSE isnt define
#endif


/**
 * ���E�V�[���N���X .
 * �A�v����́u���̐�(Universe)�v�̈���̊K�w�Ɉʒu���܂��B<BR>
 */
class World : public GgafLib::DefaultScene {

public:
    bool _is_create_GameScene;
    char _aBufDebug[80];
    LabelGecchi16Font* _pLabel_Title;
    LabelGecchi16Font* _pLabel_Aster;
    LabelGecchi16Font* _pLabel_Debug;
    LabelGecchi16Font* _pLabel_Wait;
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
