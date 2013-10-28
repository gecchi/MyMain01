#include "stdafx.h"
#include "MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyShipDivingCamWorker::MyShipDivingCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "MyShipDivingCamWorker";
}
void MyShipDivingCamWorker::initialize() {
}

void MyShipDivingCamWorker::onSwitchCameraWork() {
    CameraWorker::onSwitchCameraWork();
    MyShip* pMyShip = P_MYSHIP;
    setMoveTargetCam(-PX_C(300), pMyShip->_y, pMyShip->_z);
    setMoveTargetCamVpBy(pMyShip);
}
void MyShipDivingCamWorker::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    frame f = getSwitchedFrame();
    coord dx = ABS(P_MYSHIP->_x);
    static coord dc = ABS(Universe::_x_gone_left);
    static coord r = PX_C(500);
    double t = (1.0-(1.0*dx / dc)); //t=0.0Å®1.0
    angle a = UTIL::simplifyAng(D180ANG*t);
    coord Y = ANG_SIN(a) * r;
    coord Z = -ANG_COS(a) * r;
    setMoveTargetCam(-PX_C(300), Y , Z);
    setMoveTargetCamVpBy(pMyShip);

    CameraWorker::processBehavior();
}

MyShipDivingCamWorker::~MyShipDivingCamWorker() {
}
