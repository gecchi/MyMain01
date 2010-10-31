#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

////////////////////////////////////////////////////////////////////////////

GroundBoxActor::GroundBoxActor(const char* prm_name) :
    WallActor(prm_name, "g_box001") {
    _class_name = "GroundBoxActor";
    MyStgUtil::resetGroundBoxActorStatus(_pStatus);
    _SX=_SY=_SZ = 2000;
    setBoundingSphereRadiusRate(2.0);
}

void GroundBoxActor::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.2, 3.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(60*20, 60*9, 60*3, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.7;
}


bool GroundBoxActor::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        return false;
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////


GroundBoxScene::GroundBoxScene(const char* prm_name, ScrolledScene* prm_pScrolledScene)
     : WalledSectionScene(prm_name,"scene2_wall.dat", prm_pScrolledScene) {
    _class_name = "GroundBoxScene";
    //    for (int i = 0; i < 4000; i++) {
//        GroundBoxActor* pGroundBoxActor =  NEW GroundBoxActor("GroundBox");
//        pGroundBoxActor->inactivateTreeImmediately();
//        _pDispatcher_Wall->addSubLast(pGroundBoxActor);
//    }
//    getLordActor()->addSubGroup(_pDispatcher_Wall);
//    config( NULL,
//    800000, 200000,200000,
//    5000, 10);
    _bound_alpha = -pCAM->_cameraZ_org*0.7; //背面時カメラは_cameraZ_org*0.6に由来している

    orderActorToFactory(9999999+_id, FormationThalia, "FormationThalia_1");

}

void GroundBoxScene::processBehavior() {
    WalledSectionScene::processBehavior();
    if (_bound_alpha - (-(pMYSHIP->_fDist_VpPlnFront)) < 0) {
        enableFrontAlpha(pMYSHIP);
    } else {
        enableFrontAlpha(NULL); //背面カメラの近さならアルファ無し
    }


    if (getActivePartFrame() == 10) {
    FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(9999999+_id);
    getLordActor()->addSubGroup(pActor);
    }

    if (getActivePartFrame() == 300) {
        pUNIVERSE->pushCameraWork("TestCamWorker");
    }

    if (getActivePartFrame() == 1200) {
        pUNIVERSE->popCameraWork();
    }

}


GroundBoxScene::~GroundBoxScene() {

}
