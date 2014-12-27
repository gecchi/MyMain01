#include "Stage01WalledSection001.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "../Stage01PartController.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Stage01WalledSection001::Stage01WalledSection001(const char* prm_name, WalledScene* prm_pWalledScene, const char* prm_data_filename)
     : WalledSectionScene(prm_name, prm_data_filename, prm_pWalledScene) {
    _class_name = "Stage01WalledSection001";
    bound_alpha_ = -P_CAM->getZOrigin()*0.7; //背面時カメラは_cameraZ_org*0.6に由来している
}

void Stage01WalledSection001::processBehavior() {
    WalledSectionScene::processBehavior();
    MyShip* pMyShip = P_MYSHIP;
    if (pMyShip && pMyShip->isActiveInTheTree()) {
        if (bound_alpha_ - (-(pMyShip->_dest_from_vppln_front)) < 0) {
            enableFrontAlpha(pMyShip);
        } else {
            enableFrontAlpha(nullptr); //背面カメラの近さならアルファ無し
        }
    } else {
        enableFrontAlpha(nullptr); //背面カメラの近さならアルファ無し
    }


//    if (getActiveFrame() == 300) {
//        P_UNIVERSE->switchCameraWork("TestCamWorker");
//    }
//
//    if (getActiveFrame() == 1200) {
//        P_UNIVERSE->undoCameraWork();
//    }

}

void Stage01WalledSection001::onBlockLaunch(int prm_loop_count, int prm_wall_count, coord prm_wall_x) {
    if (prm_wall_count == 1) {
        EnemyHisbe* p = createInFactory(EnemyHisbe,"TTT");
        p->position(prm_wall_x, -PX_C(600), -PX_C(600));
        p->setRyFaceAng(-D90ANG);
        getSceneDirector()->addSubGroup(p);
    }
    if (prm_wall_count == 2) {
        EnemyHisbe* p = createInFactory(EnemyHisbe,"TTT");
        p->position(prm_wall_x, PX_C(600), PX_C(600));
        p->setRzFaceAng(D180ANG);
        p->setRyFaceAng(-D90ANG);
        getSceneDirector()->addSubGroup(p);
    }

}

Stage01WalledSection001::~Stage01WalledSection001() {

}
