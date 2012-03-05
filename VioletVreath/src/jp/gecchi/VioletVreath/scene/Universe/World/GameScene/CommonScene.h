#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_


#ifdef P_GAME_SCENE
    #define P_COMMON_SCENE (P_GAME_SCENE->pCommonScene_)
#else
    #error P_GAME_SCENE isnt define
#endif

namespace VioletVreath {

/**
 * 共通シーンクラス .
 * 2008/9/8
 */
class CommonScene : public GgafLib::DefaultScene {


public:
    /** 汎用爆発 */
    GgafCore::GgafActorDepository* pDP_EffectExplosion001_;
    GgafCore::GgafActorDepository* pDepo_EffectTurbo002_;
    GgafCore::GgafActorDepository* pDP_MagicPointItem001_;
    GgafCore::GgafActorDepository* pDP_MagicPointItem002_;

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
