#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_


#ifdef P_GAME_SCENE
    #define P_COMMON_SCENE (P_GAME_SCENE->pCommonScene_)
#else
    #error P_GAME_SCENE isnt define
#endif

/**
 * 共通オブジェクト取得マクロ
 * EffectExplosion001, EffectTurbo002, MagicPointItem001, MagicPointItem002 のみ可能
 */
#define employFromCommon(X) ((X*)P_COMMON_SCENE->pDepo_##X##_->dispatch())
#define employDelayFromCommon(X, F) ((X*)P_COMMON_SCENE->pDepo_##X##_->dispatch((F)))
#define employForceFromCommon(X) ((X*)P_COMMON_SCENE->pDepo_##X##_->dispatchForce())
#define employForceDelayFromCommon(X, F) ((X*)P_COMMON_SCENE->pDepo_##X##_->dispatchForce((F)))

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
    GgafCore::GgafActorDepository* pDepo_EffectExplosion001_;
    /** 汎用爆発エフェクトその２用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectExplosion002_;
    /** 汎用爆発エフェクトその３用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectExplosion003_;
    /** 汎用爆発エフェクトその４用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectExplosion004_;
    /** ターボエフェクト用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectTurbo002_;
    /** アイテムオブジェクトその１用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_MagicPointItem001_;
    /** アイテムオブジェクトその１用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_MagicPointItem002_;

    /** 汎用出現エフェクトその１用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectEntry001_;
    /** 汎用出現エフェクトその２用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectEntry002_;
    /** 汎用出現エフェクトその３用、常備デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectEntry003_;

    GgafCore::GgafActorDepository* pDepo_SpriteLabelBonus001_;

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
