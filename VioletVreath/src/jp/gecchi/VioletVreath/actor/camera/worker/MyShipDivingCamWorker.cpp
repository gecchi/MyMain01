#include "MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

#include "jp/ggaf/lib/util/Direction26Util.h"


using namespace GgafLib;
using namespace VioletVreath;

MyShipDivingCamWorker::MyShipDivingCamWorker(const char* prm_name, Camera* prm_pCamera) : DefaultCamWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "MyShipDivingCamWorker";
}
void MyShipDivingCamWorker::initialize() {
    CameraWorker::initialize();
}

void MyShipDivingCamWorker::onActive() {
    CameraWorker::onActive();
    MyShip* pMyShip = pMYSHIP;
    slideMvCamTo(-PX_C(300), pMyShip->_y, pMyShip->_z , 60);
    slideMvVpTo(pMyShip, 60);
    slideMvUpVecTo(0,DX_C(1),0, 120);
}
void MyShipDivingCamWorker::processBehavior() {
    if (getActiveFrame() > 30) {
        Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
        MyShip* pMyShip = pMYSHIP;
        coord dx = ABS(pMYSHIP->_x);
        static const coord dc = ABS(pSpacetime->_x_bound_left);
        static const coord r = DX_C(ABS(_pCam->_cameraZ_org));

        double t = RCNV(dc, 0, dx, 0.0, 1.0);  // dx = dc Å® 0 ÅAt = 0.0 Å® 1.0
        angle a = UTIL::simplifyAng((D360ANG)*t); //ÉJÉÅÉâÇ™ÇÆÇÈÅ[ÇÒÇ∆âÒÇ∑
        coord y = ANG_SIN(a) * r;
        coord z = -ANG_COS(a) * r;
        slideMvCamTo(-PX_C(300), y , z, 10);
        slideMvVpTo(pMyShip, 10);
    }
}

MyShipDivingCamWorker::~MyShipDivingCamWorker() {
}
