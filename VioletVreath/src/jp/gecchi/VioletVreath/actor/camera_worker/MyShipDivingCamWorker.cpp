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
    CameraWorker::initialize();
}

void MyShipDivingCamWorker::onActive() {
    CameraWorker::onActive();
    MyShip* pMyShip = P_MYSHIP;
    slideMvCamTo(-PX_C(300), pMyShip->_y, pMyShip->_z , 60);
    slideMvVpTo(pMyShip, 60);
    pCam_->slideUpCamTo(Camera::FACE_TOP, 120);
}
void MyShipDivingCamWorker::processBehavior() {
    if (getActiveFrame() > 30) {
        MyShip* pMyShip = P_MYSHIP;
        frame f = getSwitchedFrame();
        coord dx = ABS(P_MYSHIP->_x);
        static const coord dc = ABS(Universe::_x_gone_left);
        static const coord r = PX_C(500);
        double t = (1.0-(1.0*dx / dc)); //t=0.0Å®1.0
        angle a = UTIL::simplifyAng((D180ANG)*t); //180ìxâÒì]ÉJÉÅÉâÇ™ÇÆÇÈÅ[ÇÒÇ∆âÒÇ∑
        coord y = ANG_SIN(a) * r;
        coord z = -ANG_COS(a) * r;
        slideMvCamTo(PX_C(300), y , z, 10);
        slideMvVpTo(pMyShip, 10);
    }
}

MyShipDivingCamWorker::~MyShipDivingCamWorker() {
}
