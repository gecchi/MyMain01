#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShip* MyShipScene::_pMyShip = NULL;
VamSysCamWorker* MyShipScene::_pVamSysCamWorker = NULL;

MyShipScene::MyShipScene(const char* prm_name) : DefaultScene(prm_name) {
    pMYSHIP = NEW MyShip("MYSHIP");
    pMYSHIP->inactivateImmediately(); //�z���ɉ��o�^�̃A�N�^�[�����҂Ƃ����邵
    getLordActor()->addSubGroup(KIND_MY_BODY_NOMAL, pMYSHIP);
    pUNIVERSE->pushCameraWork("VamSysCamWorker");
}

void MyShipScene::initialize() {
}

void MyShipScene::processBehavior() {


}

MyShipScene::~MyShipScene() {
}
