#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

#ifdef pGAME_SCENE
    #define pCOMMON_SCENE (pGAME_SCENE->pCommonScene_)
#else
    #undef pCOMMON_SCENE
#endif

/**
 * 共通オブジェクト取得マクロ
 */
#define pCOMMON_DEPO(X)                   pDepo_##X##_
#define getCommonDepository(X)             (pCOMMON_SCENE->pCOMMON_DEPO(X))
#define dispatchFromCommon(X)              ( (X*)(getCommonDepository(X)->dispatch()) )
#define dispatchDelayFromCommon(X, F)      ( (X*)(getCommonDepository(X)->dispatch((F))) )
#define dispatchForceFromCommon(X)         ( (X*)(getCommonDepository(X)->dispatchForce()) )

#define pCOMMON_DEPO_STORE(X)              pStore_##X##_
#define getCommonDepoStore(X)                  (pCOMMON_SCENE->pCOMMON_DEPO_STORE(X))
#define dispatchFromCommonDepositoryStore(X)         ( (GgafCore::GgafActorDepository*)(getCommonDepoStore(X)->dispatch()) )
namespace VioletVreath {

/**
 * 共通シーンクラス .
 * 主な仕事は次のステージを決定することです。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CommonScene : public GgafLib::DefaultScene {

public:
    /** 汎用爆発エフェクトその１用、常備デポジトリ */

    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectExplosion001);
    /** 汎用爆発エフェクトその２用、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectExplosion002);
    /** 汎用爆発エフェクトその３用、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectExplosion003);
    /** 汎用爆発エフェクトその４用、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectExplosion004);
    /** ターボエフェクト用、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectTurbo002);
    /** アイテムオブジェクト小、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(MagicPointItem001);
    /** アイテムオブジェクト中、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(MagicPointItem002);
    /** アイテムオブジェクト大、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(MagicPointItem003);

    /** 汎用出現エフェクトその１用、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectBlink001);
    /** 汎用出現エフェクトその２用、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectBlink002);
    /** 汎用出現エフェクトその３用、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectBlink003);

    GgafCore::GgafActorDepository* pCOMMON_DEPO(SpriteLabelBonus001);

    /** 汎用出現エフェクトその３用、常備デポジトリ */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(Shot004);

    /**  */
    GgafCore::GgafActorDepositoryStore* pCOMMON_DEPO_STORE(EnemyWateringLaserChip001);
    GgafCore::GgafActorDepositoryStore* pCOMMON_DEPO_STORE(EnemyStraightLaserChip001);

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
     * @param p1 スクロールスピード(_scroll_speedへのポインタ)
     * @param p2 nullptr
     * @param p3 nullptr
     */
    static void scrollX(GgafObject* pThat, void* p1, void* p2, void* p3);

    virtual ~CommonScene();
};

}
#endif /*COMMONSCENE_H_*/
