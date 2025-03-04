#include "StageDebugPartWallSection001.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/lib/scene/RotateFormationScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;


StageDebugPartWallSection001::StageDebugPartWallSection001(const char* prm_name, WallScene* prm_pWallScene, const char* prm_data_filename)
     : WallSectionScene(prm_name, prm_data_filename, prm_pWallScene) {
    _class_name = "StageDebugPartWallSection001";
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    bound_alpha_ = -pCam->getZOrigin()*0.7; //背面時カメラは_cameraZ_org*0.6に由来している
}

void StageDebugPartWallSection001::processBehavior() {
    WallSectionScene::processBehavior();
}

void StageDebugPartWallSection001::processPreDraw() {
    MyShip* pMyShip = pMYSHIP;
    if (pMyShip && pMyShip->isActiveInTheTree()) {
        if (bound_alpha_ - (-(pMyShip->_dest_from_vppln_infront)) < 0) {
            enableInfrontAlpha(pMyShip);
        } else {
            enableInfrontAlpha(nullptr); //背面カメラの近さならアルファ無し
        }
    } else {
        enableInfrontAlpha(nullptr); //背面カメラの近さならアルファ無し
    }

//    if (getActiveFrame() == 300) {
//        P_SPACETIME->changeCameraWork("TestCamWorker");
//    }
//
//    if (getActiveFrame() == 1200) {
//        P_SPACETIME->undoCameraWork();
//    }

}

void StageDebugPartWallSection001::onBlockLaunch(int prm_loop_count, int prm_wall_count, coord prm_wall_x) {
//    if (prm_wall_count == 1) {
//        EnemyHisbe* p = desireActor(EnemyHisbe);
//        p->setPosition(pCARETAKER->getSpacetime()->_x_bound_right, -PX_C(900), -PX_C(900));
//        p->setRyFaceAng(-D90ANG);
//        getSceneChief()->appendChild(p);
//    }
}

StageDebugPartWallSection001::~StageDebugPartWallSection001() {

}
