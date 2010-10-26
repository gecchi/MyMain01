#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;



GroundBoxScene::GroundBoxActor::GroundBoxActor(const char* prm_name) :
    WallActor(prm_name, "g_box001") {
    _class_name = "GroundBoxActor";
    MyStgUtil::resetGroundBoxActorStatus(_pStatus);
    _SX=_SY=_SZ = 2000;
    setBoundingSphereRadiusRate(2.0);
}

void GroundBoxScene::GroundBoxActor::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.2, 3.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(60*20, 60*9, 60*3, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.7;
}


bool GroundBoxScene::GroundBoxActor::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        return false;
    }
    return true;
}


GroundBoxScene::GroundBoxScene(const char* prm_name) : WalledSectionScene(prm_name,
                                                                   "scene1_wall.dat",
                                                                   800000, 200000,200000,
                                                                   10000
                                                                   ) {
    for (int i = 0; i < 4000; i++) {
        GroundBoxActor* pGroundBoxActor =  NEW GroundBoxActor("GroundBox");
        pGroundBoxActor->inactivateTreeImmediately();
        _pDispatcher_Wall->addSubLast(pGroundBoxActor);
    }
    getLordActor()->addSubGroup(_pDispatcher_Wall);
    _bound_alpha = -pCAM->_cameraZ_org*0.7; //背面時カメラは_cameraZ_org*0.6に由来している
}

void GroundBoxScene::processBehavior() {
    WalledSectionScene::processBehavior();
    if (_bound_alpha - (-(pMYSHIP->_fDist_VpPlnFront)) < 0) {
        enableFrontAlpha(pMYSHIP);
    } else {
        enableFrontAlpha(NULL); //背面カメラの近さならアルファ無し
    }




    if (getActivePartFrame() == 300) {
        pUNIVERSE->pushCameraWork("TestCamWorker");
    }

    if (getActivePartFrame() == 500) {
        pUNIVERSE->popCameraWork();
    }

    if (getActivePartFrame() == 700) {
        pUNIVERSE->pushCameraWork("TestCamWorker");
    }

    if (getActivePartFrame() == 1000) {
        pUNIVERSE->popCameraWork();
    }

    if (getActivePartFrame() == 1100) {
        _ground_speed = 40000;
    }

    if (getActivePartFrame() == 1300) {
        _ground_speed = 1000;
    }


    if (getActivePartFrame() == 1800) {
        _ground_speed = 10000;
    }


}


GroundBoxScene::~GroundBoxScene() {

}
