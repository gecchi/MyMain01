#ifndef WORLD_H_
#define WORLD_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe.h"

namespace VioletVreath {

#ifdef P_UNIVERSE
    #undef  P_WORLD
    #define P_WORLD ((VioletVreath::World*)(P_UNIVERSE->pWorld_))
#else
    #undef P_WORLD
#endif


/**
 * ���E�V�[���N���X .
 * �A�v����́u���̐�(Universe)�v�̈���̊K�w�Ɉʒu���܂��B<BR>
 */
class World : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT  ,
        PROG_CALM1 ,
        PROG_CALM2 ,
        PROG_CALM3 ,
        PROG_CALM4 ,
        PROG_MAINLOOP ,
        PROG_BANPEI,
    };

    bool is_create_GameScene_;
    char aBufDebug_[80];
    LabelGecchi16Font* pLabel_aster_;
    LabelGecchi16Font* pLabel_title_;
    LabelGecchi16Font* pLabel_debug_;
    LabelGecchi16Font* pLabel_resolution1_;
    LabelGecchi16Font* pLabel_resolution2_;
    LabelGecchi8Font*  pLabel_warn1_;
    LabelGecchi8Font*  pLabel_warn2_;
    PreDrawScene* pPreDrawScene_;
    GameScene* pGameScene_;

public:
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
