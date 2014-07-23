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
 * 世界シーンクラス .
 * アプリ上の「この世(Universe)」の一つ下の階層に位置します。<BR>
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
    LabelGecchi8Font*  pLabel_warn_dual_view_;

    int need_reboot_;
    int need_reboot_prev_;
    LabelGecchi16Font* pLabel_need_reboot_;
    PreDrawScene* pPreDrawScene_;
    GameScene* pGameScene_;


    InnerTitleBar* pInnerTitleBar01_;
    InnerTitleBar* pInnerTitleBar02_;
    coord close01_x1_, close01_y1_, close01_x2_, close01_y2_;
    coord close02_x1_, close02_y1_, close02_x2_, close02_y2_;
    frame hide_cursor_cnt_;
public:
    World(const char* prm_name);

    /**
     * 初期処理
     */
    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~World();
};

}
#endif /*WORLD_H_*/
