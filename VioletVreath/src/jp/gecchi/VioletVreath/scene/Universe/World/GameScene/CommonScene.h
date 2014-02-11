#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene.h"

#ifdef P_GAME_SCENE
    #define P_COMMON_SCENE (P_GAME_SCENE->pCommonScene_)
#else
    #undef P_COMMON_SCENE
#endif

/**
 * 共通オブジェクト取得マクロ
 */
#define P_COMMON_DEPO(X)                   pDepo_##X##_
#define getCommonDepository(X)             (P_COMMON_SCENE->P_COMMON_DEPO(X))
#define dispatchFromCommon(X)              ( (X*)(getCommonDepository(X)->dispatch()) )
#define dispatchDelayFromCommon(X, F)      ( (X*)(getCommonDepository(X)->dispatch((F))) )
#define dispatchForceFromCommon(X)         ( (X*)(getCommonDepository(X)->dispatchForce()) )
#define dispatchForceDelayFromCommon(X, F) ( (X*)(getCommonDepository(X)->dispatchForce((F))) )

#define P_COMMON_STORE(X)                   pStore_##X##_

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

    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectExplosion001);
    /** 汎用爆発エフェクトその２用、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectExplosion002);
    /** 汎用爆発エフェクトその３用、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectExplosion003);
    /** 汎用爆発エフェクトその４用、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectExplosion004);
    /** ターボエフェクト用、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectTurbo002);
    /** アイテムオブジェクト小、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(MagicPointItem001);
    /** アイテムオブジェクト中、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(MagicPointItem002);
    /** アイテムオブジェクト大、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(MagicPointItem003);

    /** 汎用出現エフェクトその１用、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectEntry001);
    /** 汎用出現エフェクトその２用、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectEntry002);
    /** 汎用出現エフェクトその３用、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectEntry003);

    GgafCore::GgafActorDepository* const P_COMMON_DEPO(SpriteLabelBonus001);

    /** 汎用出現エフェクトその３用、常備デポジトリ */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(Shot004);

    /**  */
    GgafCore::GgafActorDepositoryStore* const pStore_EnemyWateringLaser001_;
    GgafCore::GgafActorDepositoryStore* const pStore_EnemyStraightLaser001_;

public:
    CommonScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;
    void onReset() override;

    virtual void processBehavior() override;

    virtual ~CommonScene();
};

}
#endif /*COMMONSCENE_H_*/
