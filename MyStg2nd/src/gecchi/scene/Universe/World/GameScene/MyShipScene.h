#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_


#ifdef P_GAME_SCENE
    #define P_MYSHIP_SCENE (P_GAME_SCENE->_pMyShipScene)
    #define P_MYSHIP (P_MYSHIP_SCENE->_pMyShip)
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
    MyShip* _pMyShip;
    VamSysCamWorker* _pVamSysCamWorker;

    MyShipScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
