#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/VamSysCamWorker.h"

#ifdef P_GAME_SCENE
    #define P_MYSHIP_SCENE (P_GAME_SCENE->pMyShipScene_)
    #define P_MYSHIP (P_MYSHIP_SCENE->pMyShip_)
    #define P_VAM (P_MYSHIP_SCENE->pVamSysCamWorker_)
#else
    #undef P_MYSHIP_SCENE
    #undef P_MYSHIP
    #undef P_VAM
#endif

namespace VioletVreath {

/**
 * 自機関連シーン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MyShipScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT    ,
        PROG_BEGIN   ,
        PROG_PLAY    ,
        PROG_DESTROY ,
        PROG_END     ,
        PROG_BANPEI,
    };

    /** 自機 */
    MyShip* pMyShip_;
    /** 自機オプション部 */
    MyOptionController** papOptionCtrler_;
    /** 自機爆発エフェクト */
    EffectMyShipExplosion* pEffectMyShipExplosion_;
    /** VAMSYSTEM カメラワーク */
    VamSysCamWorker* pVamSysCamWorker_;
    /** 残機表示 */
    LabelGecchi16Font* pLabelZanki_;

public:
    MyShipScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;
    void onReset() override;
    void onActive() override;
    void processBehavior() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
