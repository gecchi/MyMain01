#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyShipDivingCamWorker::MyShipDivingCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "MyShipDivingCamWorker";
//    pMyShip_ = NULL; //MyShipSceneに設定してもらう
}
void MyShipDivingCamWorker::initialize() {
}

MyShipDivingCamWorker::~MyShipDivingCamWorker() {
}
