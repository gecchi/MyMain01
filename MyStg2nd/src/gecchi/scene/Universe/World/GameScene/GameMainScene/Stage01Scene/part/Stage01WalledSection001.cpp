#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage01WalledSection001::Stage01WalledSection001(const char* prm_name, ScrolledScene* prm_pScrolledScene, const char* prm_data_filename)
     : WalledSectionScene(prm_name, prm_data_filename, prm_pScrolledScene) {
    _class_name = "Stage01WalledSection001";
    _bound_alpha = -pCAM->_cameraZ_org*0.7; //�w�ʎ��J������_cameraZ_org*0.6�ɗR�����Ă���


}

void Stage01WalledSection001::processBehavior() {
    WalledSectionScene::processBehavior();
    if (_bound_alpha - (-(pMYSHIP->_fDist_VpPlnFront)) < 0) {
        enableFrontAlpha(pMYSHIP);
    } else {
        enableFrontAlpha(NULL); //�w�ʃJ�����̋߂��Ȃ�A���t�@����
    }


//    if (getActivePartFrame() == 300) {
//        pUNIVERSE->pushCameraWork("TestCamWorker");
//    }
//
//    if (getActivePartFrame() == 1200) {
//        pUNIVERSE->popCameraWork();
//    }

}


Stage01WalledSection001::~Stage01WalledSection001() {

}