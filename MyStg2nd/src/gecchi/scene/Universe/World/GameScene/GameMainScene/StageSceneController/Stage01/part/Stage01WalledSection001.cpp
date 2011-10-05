#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


Stage01WalledSection001::Stage01WalledSection001(const char* prm_name, ScrolledScene* prm_pScrolledScene, const char* prm_data_filename)
     : WalledSectionScene(prm_name, prm_data_filename, prm_pScrolledScene) {
    _class_name = "Stage01WalledSection001";
    _bound_alpha = -P_CAM->_cameraZ_org*0.7; //背面時カメラは_cameraZ_org*0.6に由来している


}

void Stage01WalledSection001::processBehavior() {
    WalledSectionScene::processBehavior();
    if (_bound_alpha - (-(P_MYSHIP->_fDist_VpPlnFront)) < 0) {
        enableFrontAlpha(P_MYSHIP);
    } else {
        enableFrontAlpha(NULL); //背面カメラの近さならアルファ無し
    }


//    if (getActivePartFrame() == 300) {
//        P_UNIVERSE->switchCameraWork("TestCamWorker");
//    }
//
//    if (getActivePartFrame() == 1200) {
//        P_UNIVERSE->undoCameraWork();
//    }

}


Stage01WalledSection001::~Stage01WalledSection001() {

}
