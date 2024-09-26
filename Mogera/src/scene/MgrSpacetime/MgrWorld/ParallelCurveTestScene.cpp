#include "ParallelCurveTestScene.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "actor/EnemyIda.h"
#include "actor/EnemyIdaBase.h"
#include "actor/Box.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "actor/camera/MgrCamera.h"
#include "actor/camera/MgrCameraWorker.h"
#include "scene/MgrSpacetime.h"
#include "MgrCaretaker.h"

using namespace GgafLib;
using namespace Mogera;

enum {
    PHASE_INIT ,
    PHASE_MOVE ,
    PHASE_END,
};

ParallelCurveTestScene::ParallelCurveTestScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "ParallelCurveTestScene";
    pTest_ = nullptr;
    pActor_ = nullptr;
    pDepoBox_ = NEW GgafCore::ActorDepository("depo_box");
    pDepoBox_->putn<Box>(5000);
    getSceneChief()->appendChild(pDepoBox_);
    requestActor(1234, EnemyIdaBase, "ParallelCurve_0");
}


void ParallelCurveTestScene::initialize() {
    GgafDx::Input::updateMouseState();
    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
    pActor_ = (EnemyIdaBase*)receiveActor(1234);
    getSceneChief()->appendChild(pActor_);
    pActor_->setPosition(PX_C(-300), PX_C(-200), 0);
    getPhase()->reset(PHASE_INIT);
}

void ParallelCurveTestScene::processBehavior() {
    if (GgafDx::Input::isPushedDownKey(DIK_F1)) {
        MgrSpacetime* pSpacetime = pCARETAKER->getSpacetime();
        MgrCamera* pCam = pSpacetime->getCamera();
        //カメラを初期位置へ
        MgrCameraWorker* pCameraWorker = pSpacetime->pActiveCamWorker_;
        pCameraWorker->slideMvCamTo(0, 0, DX_C(pCam->getZOrigin()), 60);
        pCameraWorker->slideMvVpTo(0, 0, 0, 60);
        pCameraWorker->slideMvUpVecTo(0, DX_C(1), 0, 60);

    }
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            if (GgafDx::Input::isPushedDownKey(DIK_RETURN)) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_MOVE: {
            if (pPhase->hasJustChanged()) {
                pActor_->throwEventLowerTree(EVENT_START_MOVING);
            }
            if (pPhase->getFrame() % 3 == 0) {
                psetAs(pActor_);
                (*pActor_->pOs_) << pActor_->_x << "  " <<  pActor_->_y  << "  " << pActor_->_z << std::endl;

                EnemyIda* pChild = pActor_->_list_child.first();
                while(true) {
                    psetAs(pChild);
                    (*pChild->pOs_) << pChild->_x << "  " <<  pChild->_y  << "  " << pChild->_z << std::endl;
                    pChild =  pActor_->_list_child.next();
                    if (pActor_->_list_child.isFirst()) {
                        break;
                    }
                }
            }
            break;
        }
        case PHASE_END: {
            break;
        }
    }
}

void ParallelCurveTestScene::pset(coord x, coord y, coord z) {
    Box* pBox = (Box*)pDepoBox_->dispatchForce();
    pBox->setPosition(x, y, z);
}

void ParallelCurveTestScene::psetAs(GgafDx::GeometricActor* pActor) {
    pset(pActor->_x, pActor->_y, pActor->_z);
}

ParallelCurveTestScene::~ParallelCurveTestScene() {
}
