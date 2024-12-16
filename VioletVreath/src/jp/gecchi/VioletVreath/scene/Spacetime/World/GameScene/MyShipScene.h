#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "../GameScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/VamSysCamWorker.h"

#ifdef pGAME_SCENE
    #define pMYSHIP_SCENE (pGAME_SCENE->pMyShipScene_)
    #define pMYSHIP (pMYSHIP_SCENE->pMyShip_)
    #define pVAM (pMYSHIP_SCENE->pVamSysCamWorker_)
#else
    #undef pMYSHIP_SCENE
    #undef pMYSHIP
    #undef pVAM
#endif


#define MyShipScene_pCOMMON_DEPO(X)          pDepo_##X##_
#define MyShipScene_getDepository(X)         (pMYSHIP_SCENE->MyShipScene_pCOMMON_DEPO(X))
#define MyShipScene_dispatch(X)              ( (X*)(MyShipScene_getDepository(X)->dispatch()) )
#define MyShipScene_dispatchDelay(X, F)      ( (X*)(MyShipScene_getDepository(X)->dispatch((F))) )
#define MyShipScene_dispatchForce(X)         ( (X*)(MyShipScene_getDepository(X)->dispatchForce()) )

#define MyShipScene_pCOMMON_DEPO_STORE(X)    pStore_##X##_
#define MyShipScene_getDepoStore(X)          (pMYSHIP_SCENE->MyShipScene_pCOMMON_DEPO_STORE(X))
#define MyShipScene_dispatchDepoStore(X)     ( (GgafCore::ActorDepository*)(MyShipScene_getDepoStore(X)->dispatch()) )


namespace VioletVreath {

/**
 * 自機関連シーン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MyShipScene : public VvScene<GgafLib::DefaultScene> {

public:
    /** 自機 */
    MyShip* pMyShip_;
    /** 自機爆発エフェクト */
    EffectMyShipExplosion* pEffectMyShipExplosion_;
    /** VAMSYSTEM カメラワーク */
    VamSysCamWorker* pVamSysCamWorker_;
    /** 残機表示 */
    LabelGecchi16Font* pLabelZanki_;

    /** 自機分身土台 */
    MyBunshinBase** papBunshinBase_;

    /** ターボエフェクト用、常備デポジトリ */
    GgafCore::ActorDepository* MyShipScene_pCOMMON_DEPO(EffectTurbo002);
    /** アイテムオブジェクト小、常備デポジトリ */
    GgafCore::ActorDepository* MyShipScene_pCOMMON_DEPO(MagicPointItem001);
    /** アイテムオブジェクト中、常備デポジトリ */
    GgafCore::ActorDepository* MyShipScene_pCOMMON_DEPO(MagicPointItem002);
    /** アイテムオブジェクト大、常備デポジトリ */
    GgafCore::ActorDepository* MyShipScene_pCOMMON_DEPO(MagicPointItem003);

    GgafCore::ActorDepository* MyShipScene_pCOMMON_DEPO(SpriteLabelBonus001);
    GgafCore::ActorDepository* MyShipScene_pCOMMON_DEPO(SpriteLabelBonus002);
    GgafCore::ActorDepository* MyShipScene_pCOMMON_DEPO(LabelBonus001);


public:
    MyShipScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;
    void onReset() override;
    void onActive() override;
    void processBehavior() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
