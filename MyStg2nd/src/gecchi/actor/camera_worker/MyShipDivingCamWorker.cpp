#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MyShipDivingCamWorker::MyShipDivingCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "MyShipDivingCamWorker";
//    _pMyShip = NULL; //MyShipSceneに設定してもらう
}
void MyShipDivingCamWorker::initialize() {
}

MyShipDivingCamWorker::~MyShipDivingCamWorker() {
}
