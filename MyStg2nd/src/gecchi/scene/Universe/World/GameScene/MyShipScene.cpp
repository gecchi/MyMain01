#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShipScene::MyShipScene(const char* prm_name) : DefaultScene(prm_name) ,
_pMyShip(NULL),
_pVamSysCamWorker(NULL) {
    _class_name = "MyShipScene";
    _pMyShip = NEW MyShip("MYSHIP");
    _pMyShip->inactivateImmediately(); //配下に仮登録のアクター発送者とかあるし
    getLordActor()->addSubGroup(KIND_MY_BODY_NOMAL, _pMyShip);
    _pVamSysCamWorker = (VamSysCamWorker*)P_UNIVERSE->_pCameraWorkerManager->getConnection("VamSysCamWorker")->refer();
    _pVamSysCamWorker->_pMyShip = _pMyShip;
//    _pVamSysCamWorker = (VamSysCamWorker*)P_UNIVERSE->pushCameraWork("VamSysCamWorker");
//    _pVamSysCamWorker->_pMyShip = _pMyShip;
}

void MyShipScene::initialize() {

}

void MyShipScene::processBehavior() {
}

void MyShipScene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == MY_SHIP_WAS_DESTROYED_BEGIN) {
        fadeoutSceneTree(180);
    } else if (prm_no == MY_SHIP_WAS_DESTROYED_FINISH) {
        //setProgress()
    }
}

MyShipScene::~MyShipScene() {
}
