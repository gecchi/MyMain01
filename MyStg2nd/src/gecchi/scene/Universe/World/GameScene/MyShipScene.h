#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_


#ifdef pGAMESCENE
    #define pMYSHIP_SCENE (pGAMESCENE->_pMyShipScene)
    #define pMYSHIP (pMYSHIP_SCENE->_pMyShip)
    #define pVAM (pMYSHIP_SCENE->_pVamSysCamWorker)
#else
    #error pGAMESCENE isnt define
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
