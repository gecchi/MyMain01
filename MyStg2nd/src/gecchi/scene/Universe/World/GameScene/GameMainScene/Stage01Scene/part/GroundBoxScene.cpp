#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


GroundBoxScene::GroundBoxScene(const char* prm_name, ScrolledScene* prm_pScrolledScene, const char* prm_data_filename)
     : WalledSectionScene(prm_name, prm_data_filename, prm_pScrolledScene) {
    _class_name = "GroundBoxScene";
    _bound_alpha = -pCAM->_cameraZ_org*0.7; //背面時カメラは_cameraZ_org*0.6に由来している


}

void GroundBoxScene::processBehavior() {
    WalledSectionScene::processBehavior();
    if (_bound_alpha - (-(pMYSHIP->_fDist_VpPlnFront)) < 0) {
        enableFrontAlpha(pMYSHIP);
    } else {
        enableFrontAlpha(NULL); //背面カメラの近さならアルファ無し
    }


//    if (getActivePartFrame() == 300) {
//        pUNIVERSE->pushCameraWork("TestCamWorker");
//    }
//
//    if (getActivePartFrame() == 1200) {
//        pUNIVERSE->popCameraWork();
//    }

}


GroundBoxScene::~GroundBoxScene() {

}
