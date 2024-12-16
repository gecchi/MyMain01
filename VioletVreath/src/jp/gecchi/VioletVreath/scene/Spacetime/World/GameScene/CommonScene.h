#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "../GameScene.h"

#ifdef pGAME_SCENE
    #define pCOMMON_SCENE (pGAME_SCENE->pCommonScene_)
#else
    #undef pCOMMON_SCENE
#endif

/**
 * 共通オブジェクト取得マクロ
 */
#define CommonScene_pCOMMON_DEPO(X)          pDepo_##X##_
#define CommonScene_getDepository(X)         (pCOMMON_SCENE->CommonScene_pCOMMON_DEPO(X))
#define CommonScene_dispatch(X)              ( (X*)(CommonScene_getDepository(X)->dispatch()) )
#define CommonScene_dispatchDelay(X, F)      ( (X*)(CommonScene_getDepository(X)->dispatch((F))) )
#define CommonScene_dispatchForce(X)         ( (X*)(CommonScene_getDepository(X)->dispatchForce()) )

#define CommonScene_pCOMMON_DEPO_STORE(X)    pStore_##X##_
#define CommonScene_getDepoStore(X)          (pCOMMON_SCENE->CommonScene_pCOMMON_DEPO_STORE(X))
#define CommonScene_dispatchDepoStore(X)     ( (GgafCore::ActorDepository*)(CommonScene_getDepoStore(X)->dispatch()) )

namespace VioletVreath {

/**
 * 共通シーンクラス .
 * 主な仕事は次のステージを決定することです。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CommonScene : public VvScene<GgafLib::DefaultScene> {

public:
    /** 汎用爆発エフェクトその１用、常備デポジトリ */

    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectExplosion001);
    /** 汎用爆発エフェクトその２用、常備デポジトリ */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectExplosion002);
    /** 汎用爆発エフェクトその３用、常備デポジトリ */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectExplosion003);
    /** 汎用爆発エフェクトその４用、常備デポジトリ */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectExplosion004);


    /** 汎用出現エフェクトその１用、常備デポジトリ */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectBlink001);
    /** 汎用出現エフェクトその２用、常備デポジトリ */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectBlink002);
    /** 汎用出現エフェクトその３用、常備デポジトリ */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectBlink003);


    /** 汎用出現エフェクトその３用、常備デポジトリ */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(Shot004);

    /**  */
    GgafCore::ActorDepositoryStore* CommonScene_pCOMMON_DEPO_STORE(EnemyWateringLaserChip001);
    GgafCore::ActorDepositoryStore* CommonScene_pCOMMON_DEPO_STORE(EnemyStraightLaserChip001);

public:
    CommonScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;
    void onReset() override;

    virtual void processBehavior() override;

    /**
     * X軸の負の方向にスクロールさせる関数 .
     * @param pThat アクター
     * @param p1 スクロールスピード(_feature_p1へのポインタ)
     * @param p2 nullptr
     * @param p3 nullptr
     */
    static void scrollX(GgafCore::Object* pThat, void* p1, void* p2, void* p3);

    virtual ~CommonScene();
};

}
#endif /*COMMONSCENE_H_*/
