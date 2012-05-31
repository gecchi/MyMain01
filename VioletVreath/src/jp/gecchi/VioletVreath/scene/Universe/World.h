#ifndef WORLD_H_
#define WORLD_H_
namespace VioletVreath {


#ifdef P_UNIVERSE
    #define P_WORLD ((VioletVreath::World*)(P_UNIVERSE->pWorld_))
#else
    #error P_UNIVERSE isnt define
#endif


/**
 * ���E�V�[���N���X .
 * �A�v����́u���̐�(Universe)�v�̈���̊K�w�Ɉʒu���܂��B<BR>
 */
class World : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1 ,
        PROG_CALM1 ,
        PROG_CALM2 ,
        PROG_MAINLOOP ,
    };


    bool is_create_GameScene_;
    char aBufDebug_[80];
    LabelGecchi16Font* pLabel_Aster_;
    LabelGecchi16Font* pLabel_Title_;
    LabelGecchi16Font* pLabel_Debug_;
    LabelGecchi16Font* pLabel_Wait_;
    PreDrawScene* pPreDrawScene_;
    GameScene* pGameScene_;

    /////////////////////////////////
    LabelGecchi16Font** papTest_;

    /////////////////////////////////

    World(const char* prm_name);

    /**
     * ��������
     */
    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~World();
};

}
#endif /*WORLD_H_*/
