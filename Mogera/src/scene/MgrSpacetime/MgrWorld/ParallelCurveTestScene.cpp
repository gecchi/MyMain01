#include "ParallelCurveTestScene.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "actor/EnemyIda.h"
#include "actor/EnemyIdaBase.h"
#include "actor/Box.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "actor/camera/MgrCamera.h"
#include "actor/camera/MgrCameraWorker.h"
#include "scene/MgrSpacetime.h"
#include "MgrGod.h"

using namespace GgafLib;
using namespace Mogera;

enum {
    PROG_INIT ,
    PROG_MOVE ,
    PROG_END,
};

ParallelCurveTestScene::ParallelCurveTestScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "ParallelCurveTestScene";
    pTest_ = nullptr;
    pActor_ = nullptr;
    pDepoBox_ = NEW GgafCore::ActorDepository("depo_box");
    pDepoBox_->putn<Box>(5000);
    bringSceneMediator()->appendGroupChild(pDepoBox_);
    requestActor(1234, EnemyIdaBase, "ParallelCurve_0");
}


void ParallelCurveTestScene::initialize() {
    GgafDx::Input::updateMouseState();
    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
    pActor_ = (EnemyIdaBase*)receiveActor(1234);
    bringSceneMediator()->appendGroupChild(pActor_);
    pActor_->setPosition(PX_C(-300), PX_C(-200), 0);
    getProgress()->reset(PROG_INIT);
}

void ParallelCurveTestScene::processBehavior() {
    if (GgafDx::Input::isPushedDownKey(DIK_F1)) {
        MgrSpacetime* pSpacetime = pGOD->getSpacetime();
        MgrCamera* pCam = pSpacetime->getCamera();
        //カメラを初期位置へ
        MgrCameraWorker* pCameraWorker = pSpacetime->pActiveCamWorker_;
        pCameraWorker->slideMvCamTo(0, 0, DX_C(pCam->getZOrigin()), 60);
        pCameraWorker->slideMvVpTo(0, 0, 0, 60);
        pCameraWorker->slideMvUpVecTo(0, DX_C(1), 0, 60);

    }
    SceneProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            if (GgafDx::Input::isPushedDownKey(DIK_RETURN)) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE: {
            if (pProg->hasJustChanged()) {
                pActor_->throwEventLowerTree(EVENT_START_MOVING);
            }
            if (pProg->getFrame() % 3 == 0) {
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
        case PROG_END: {
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
