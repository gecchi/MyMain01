#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_

#ifdef P_GAME_SCENE
    #define P_MYSHIP_SCENE (P_GAME_SCENE->pMyShip_Scene)
    #define P_MYSHIP (P_MYSHIP_SCENE->pMyShip_)
    #define P_VAM (P_MYSHIP_SCENE->pVamSysCamWorker_)
#else
    #error P_GAME_SCENE isnt define
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
        PROG_INIT = 1,
        PROG_BEGIN   ,
        PROG_PLAY    ,
        PROG_DESTROY ,
        PROG_END
    };

    /** 自機 */
    MyShip* pMyShip_;
    /** 自機オプション部 */
    MyOptionController** papOptionCtrler_;
    /** 自機爆発エフェクト */
    EffectMyShipExplosion* pEffectMyShipExplosion_;
    /** VAMSYSTEM カメラワーク */
    VamSysCamWorker* pVamSysCamWorker_;

    int zanki_;

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
