#include "stdafx.h"
#include "Universe.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/Camera.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerManager.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Universe::CameraWorkerConnectionStack::CameraWorkerConnectionStack() {
    p_ = 0;
    for (int i = 0; i < 30; i++) {
        apCamWorkerConnection_[i] = nullptr;
    }
}
CameraWorkerConnection* Universe::CameraWorkerConnectionStack::getLast() {
    if (p_ == 0) {
        return nullptr;
    } else {
        return apCamWorkerConnection_[p_-1];
    }
}
void Universe::CameraWorkerConnectionStack::push(CameraWorkerConnection* prm_pCamWorkerCon) {
    if (p_ > 30-1) {
        throwGgafCriticalException("CameraWorkerConnectionStack::push("<<prm_pCamWorkerCon->getIdStr()<<") スタックを使い切りました。");
    }
    apCamWorkerConnection_[p_] = prm_pCamWorkerCon;
    p_++;
}
CameraWorkerConnection* Universe::CameraWorkerConnectionStack::pop() {
    if (p_ == 0) {
        throwGgafCriticalException("CameraWorkerConnectionStack::pop() ポップしすぎです");
    } else {
        p_--;
        CameraWorkerConnection* r = apCamWorkerConnection_[p_];
        apCamWorkerConnection_[p_] = nullptr;
        return r;
    }
}
void Universe::CameraWorkerConnectionStack::clear() {
    p_ = 0;
    for (int i = 0; i < 30; i++) {
        apCamWorkerConnection_[i] = nullptr;
    }
}

void Universe::CameraWorkerConnectionStack::dump() {
    _TRACE_("CameraWorkerConnectionStack p_="<<p_);
    for (int i = 0; i < 30; i++) {
        if (apCamWorkerConnection_[i]) {
            _TRACE_("apCamWorkerConnection_["<<i<<"]="<<(apCamWorkerConnection_[i]->getIdStr()));
        }
    }
}
Universe::CameraWorkerConnectionStack::~CameraWorkerConnectionStack() {
    clear();
}

/////////////////////////////////////////////////

Universe::Universe(const char* prm_name, Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
    _class_name = "Universe";
    pWorld_ = nullptr;
    _TRACE_("Universe::Universe()");
    pCamWorkerManager_ = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pCamWorkerCon = (CameraWorkerConnection*)pCamWorkerManager_->connect("DefaultCamWorker", this);
    stack_CamWorkerConnection_.push(pCamWorkerCon);
    pActiveCamWorker_ = pCamWorkerCon->peek();
    getSceneDirector()->addSubGroup(pActiveCamWorker_); //基底デフォルトカメラワーク

    //【めも】
    //ここでActorやSceneのNEWをあんまししてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void Universe::initialize() {
    pWorld_ = createInFactory(VioletVreath::World, "WORLD");
    addSubLast(pWorld_);
    _TRACE_("Universe::initialize()");
}

void Universe::processBehavior() {
    DefaultUniverse::processBehavior();
}

void Universe::processJudgement() {
    DefaultUniverse::processJudgement();
}

CameraWorker* Universe::switchCameraWork(const char* prm_pID) {
//    _TRACE_("switchCameraWork("<<prm_pID<<") begin---");
//    stack_CamWorkerConnection_.dump();
    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ←Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ←Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+

    CameraWorkerConnection* pCon = connectToCameraWorkerManager(prm_pID);
    CameraWorker* pCamWorker = pCon->peek();
    if (pCamWorker != pActiveCamWorker_) {
        //現在の CameraWork を非活動へ
        pActiveCamWorker_->onSwitchToOtherCameraWork(); //コールバック
        pActiveCamWorker_->inactivate();
        //パラメータの CameraWork を活動へ
        pCamWorker->activate();
        pCamWorker->onSwitchCameraWork(); //コールバック
        if (getSceneDirector()->getSubFirst()->getSub(pCamWorker)) {
            //２回目以降の
        } else {
            getSceneDirector()->addSubGroup(pCamWorker); //初回はツリーに追加
        }
        //スタックに積む
        stack_CamWorkerConnection_.push(pCon);
        pActiveCamWorker_ = pCamWorker;
    } else {
#ifdef MY_DEBUG
        stack_CamWorkerConnection_.dump();
        _TRACE_("＜警告＞Universe::switchCameraWork("<<prm_pID<<") 同じカメラワークを連続でpush()していますので無視します。pActiveCamWorker_="<<pActiveCamWorker_->getName());
#endif
    }
//    stack_CamWorkerConnection_.dump();
    return pCamWorker;

}

CameraWorker* Universe::undoCameraWork() {
//    _TRACE_("undoCameraWork begin---");
//    stack_CamWorkerConnection_.dump();
    //    |      |                       |      |
    //    +------+                       |      |
    //    | ConC | ←Active      pop     |      |
    //    +------+           --------->  +------+
    //    | ConB |                       | ConB | ←Active(return)
    //    +------+                       +------+
    //    | ConA |                       | ConA |
    //    +------+                       +------+

    //スタックｋら取り出し
    CameraWorkerConnection* pConnection_now = stack_CamWorkerConnection_.pop(); //pConnection_nowは上図のConCが返る
    CameraWorkerConnection* pCon = stack_CamWorkerConnection_.getLast(); //pConは上図で言うとConBが返る
    if (pCon) {
        CameraWorker* pCamWorker = pCon->peek();
        if (pCamWorker != pActiveCamWorker_) {
            //現在の CameraWork を非活動へ
            pActiveCamWorker_->inactivate();
            pActiveCamWorker_->onUndoCameraWork();  //コールバック
            pActiveCamWorker_ = pCamWorker;
            if (pActiveCamWorker_) {
                //１つ前の CameraWork を活動へ
                pActiveCamWorker_->onCameBackFromOtherCameraWork();  //コールバック
                pActiveCamWorker_->activate();
            } else {
                stack_CamWorkerConnection_.dump();
                throwGgafCriticalException("Universe::undoCameraWork()  stack_CameraWorker_ から pop() しすぎ。");
            }
            pConnection_now->close();
//            _TRACE_("undoCameraWork end---");
//            stack_CamWorkerConnection_.dump();
            return pActiveCamWorker_;
        } else {
#ifdef MY_DEBUG
            stack_CamWorkerConnection_.dump();
            _TRACE_("＜警告＞Universe::undoCameraWork() pop()したカメラワークは、pop()前と同じカメラワークです。pCamWorker="<<pCamWorker->getName());
#endif
            return pActiveCamWorker_;
        }
    } else {
        stack_CamWorkerConnection_.dump();
        throwGgafCriticalException("Universe::undoCameraWork()  stack_CameraWorker_ から pop() しすぎにも程がある");
    }
}

void Universe::resetCamWorker() {
    //DefaultCamWorkerまでキレイにする
//    _TRACE_("resetCamWorker begin---");
//    stack_CamWorkerConnection_.dump();
    for (int i = 0; i < 30; i++) {
        if (stack_CamWorkerConnection_.p_ == 1) {
            break;
        } else {
            CameraWorkerConnection* pCon = stack_CamWorkerConnection_.pop();
            pCon->close();
        }
    }
    P_CAM->setDefaultPosition();
    pActiveCamWorker_ = stack_CamWorkerConnection_.getLast()->peek();
    pActiveCamWorker_->setMoveTargetCamBy(P_CAM);
    pActiveCamWorker_->setMoveTargetCamVpBy(P_CAM->_pViewPoint);
    pActiveCamWorker_->angXY_nowCamUp_ = UTIL::getAngle2D((double)(P_CAM->_pVecCamUp->x), (double)(P_CAM->_pVecCamUp->y));
    pActiveCamWorker_->move_target_XY_CAM_UP_ = pActiveCamWorker_->angXY_nowCamUp_;
    pActiveCamWorker_->activate();
//    _TRACE_("resetCamWorker end---");
//    stack_CamWorkerConnection_.dump();
}


Universe::~Universe() {
    GGAF_DELETE(pCamWorkerManager_);
}
