#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_

#define pMYSHIP (MyStg2nd::MyShipScene::_pMyShip)
#define pVAM (MyStg2nd::MyShipScene::_pVamSysCamWorker)
namespace MyStg2nd {

/**
 * ���ʃV�[���N���X .
 * 2008/9/8
 */
class MyShipScene : public GgafDx9LibStg::DefaultScene {

public:
    static MyShip* _pMyShip;
    static VamSysCamWorker* _pVamSysCamWorker;

    MyShipScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
