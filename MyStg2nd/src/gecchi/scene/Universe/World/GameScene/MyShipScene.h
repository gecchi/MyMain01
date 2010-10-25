#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_

#define pMYSHIP (MyStg2nd::MyShipScene::_pMyShip)
#define pVAM (MyStg2nd::MyShipScene::_pVamSysCamWorker)
namespace MyStg2nd {

/**
 * 共通シーンクラス .
 * 2008/9/8
 */
class MyShipScene : public GgafDx9LibStg::DefaultScene {

public:
    static MyShip* _pMyShip;
    static VamSysCamWorker* _pVamSysCamWorker;

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
