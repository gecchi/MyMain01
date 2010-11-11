#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_


#ifdef P_GAME_SCENE
    #define P_MYSHIP_SCENE (P_GAME_SCENE->_pMyShipScene)
    #define P_MYSHIP (P_MYSHIP_SCENE->_pMyShip)
    #define P_VAM (P_MYSHIP_SCENE->_pVamSysCamWorker)
#else
    #error P_GAME_SCENE isnt define
#endif

#define MYSHIPSCENE_PROG_INIT   1
#define MYSHIPSCENE_PROG_BEGIN  2
#define MYSHIPSCENE_PROG_APPEARANCE_NOMAL   3
#define MYSHIPSCENE_PROG_PLAY   4
#define MYSHIPSCENE_PROG_DESTROY   5
#define MYSHIPSCENE_PROG_END    6


namespace MyStg2nd {

/**
 * 共通シーンクラス .
 * 2008/9/8
 */
class MyShipScene : public GgafDx9LibStg::DefaultScene {

public:
    MyShip* _pMyShip;
    VamSysCamWorker* _pVamSysCamWorker;
    MyShipDivingCamWorker* _pMyShipDivingCamWorker;

    MyShipScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    void onActive() override;
    void processBehavior() override;

    void catchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
