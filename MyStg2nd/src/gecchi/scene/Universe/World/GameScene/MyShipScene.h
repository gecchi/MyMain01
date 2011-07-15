#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_


#ifdef P_GAME_SCENE
    #define P_MYSHIP_SCENE (P_GAME_SCENE->_pMyShipScene)
    #define P_MYSHIP (P_MYSHIP_SCENE->_pMyShip)
    #define P_MYOPTIONCON (P_MYSHIP_SCENE->_pMyOptionController)
    #define P_VAM (P_MYSHIP_SCENE->_pVamSysCamWorker)
#else
    #error P_GAME_SCENE isnt define
#endif


namespace MyStg2nd {

/**
 * 共通シーンクラス .
 * 2008/9/8
 */
class MyShipScene : public GgafDx9LibStg::DefaultScene {

public:
    /** 自機 */
    MyShip* _pMyShip;
    /** 自機オプション部 */
    MyOptionController* _pMyOptionController;
    /** 自機爆発エフェクト */
    EffectMyShipExplosion* _pEffectMyShipExplosion;
    /** VAMSYSTEM カメラワーク */
    VamSysCamWorker* _pVamSysCamWorker;

    /** 魔法メーター */
    MagicMeter* _pMagicMeter;
    /** エネルギーバー */
    EnagyBar* _pEnagyBar;

    int _zanki;

    MyShipScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;
    void onReset() override;
    void onActive() override;
    void processBehavior() override;

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
