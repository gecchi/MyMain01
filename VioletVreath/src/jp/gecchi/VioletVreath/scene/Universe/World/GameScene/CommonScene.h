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
#define getFromCommon(X) ((X*)P_COMMON_SCENE->pDepo_##X##_->dispatch())

namespace VioletVreath {

/**
 * 共通シーンクラス .
 * 2008/9/8
 */
class CommonScene : public GgafLib::DefaultScene {


public:
    /** 汎用爆発エフェクト用デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectExplosion001_;
    /** ターボエフェクト用デポジトリ */
    GgafCore::GgafActorDepository* pDepo_EffectTurbo002_;
    /** アイテムオブジェクトその１用デポジトリ */
    GgafCore::GgafActorDepository* pDepo_MagicPointItem001_;
    /** アイテムオブジェクトその１用デポジトリ */
    GgafCore::GgafActorDepository* pDepo_MagicPointItem002_;

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
