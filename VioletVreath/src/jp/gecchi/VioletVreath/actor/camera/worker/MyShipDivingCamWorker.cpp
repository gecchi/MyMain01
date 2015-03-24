#include "MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"
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
    slideMvUpTo(GgafDxDirectionUtil::FACE_ZPZ, 120);
}
void MyShipDivingCamWorker::processBehavior() {
    if (getActiveFrame() > 30) {
        Spacetime* pSpacetime =  P_GOD->getSpacetime();
        MyShip* pMyShip = P_MYSHIP;
        frame f = getSwitchedFrame();
        coord dx = ABS(P_MYSHIP->_x);
        static const coord dc = ABS(pSpacetime->_x_gone_left);
        static const coord r = PX_C(500);
        double t = (1.0-(1.0*dx / dc)); //t=0.0¨1.0
        angle a = UTIL::simplifyAng((D180ANG)*t); //180“x‰ñ“]ƒJƒƒ‰‚ª‚®‚é[‚ñ‚Æ‰ñ‚·
        coord y = ANG_SIN(a) * r;
        coord z = -ANG_COS(a) * r;
        slideMvCamTo(PX_C(300), y , z, 10);
        slideMvVpTo(pMyShip, 10);
    }
}

MyShipDivingCamWorker::~MyShipDivingCamWorker() {
}
