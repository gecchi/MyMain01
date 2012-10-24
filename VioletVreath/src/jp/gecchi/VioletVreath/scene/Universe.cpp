#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Universe::Universe(const char* prm_name, Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
    _class_name = "Universe";
    pWorld_ = NULL;
    _TRACE_("Universe::Universe()");
    pCamWorkerManager_ = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pCamWorkerCon = (CameraWorkerConnection*)pCamWorkerManager_->connect("DefaultCamWorker");
    stack_CamWorkerCon_.push(pCamWorkerCon);
    pActiveCamWorker_ = pCamWorkerCon->fetch();
    getDirector()->addSubGroup(pActiveCamWorker_); //基底デフォルトカメラワーク

    //【めも】
    //ここでActorやSceneのNEWをあんまししてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void Universe::initialize() {
    pWorld_ = createInFactory(World, "WORLD");
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
//    stack_CamWorkerCon_.dump();
    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ←Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ←Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+

    CameraWorkerConnection* pCon = connectToCameraWorkerManager(prm_pID);
    CameraWorker* pCamWorker = pCon->fetch();
    if (pCamWorker != pActiveCamWorker_) {
        //現在の CameraWork を非活動へ
        pActiveCamWorker_->onSwitchToOherCameraWork(); //コールバック
        pActiveCamWorker_->inactivate();
        //パラメータの CameraWork を活動へ
        pCamWorker->activate();
        pCamWorker->onSwitchCameraWork(); //コールバック
        if (getDirector()->getSubFirst()->getSub(pCamWorker)) {
            //２回目以降の
        } else {
            getDirector()->addSubGroup(pCamWorker); //初回はツリーに追加
        }
        //スタックに積む
        stack_CamWorkerCon_.push(pCon);
        pActiveCamWorker_ = pCamWorker;
    } else {
#ifdef MY_DEBUG
        stack_CamWorkerCon_.dump();
        _TRACE_("＜警告＞Universe::switchCameraWork("<<prm_pID<<") 同じカメラワークを連続でpush()していますので無視します。pActiveCamWorker_="<<pActiveCamWorker_->getName());
#endif
    }
//    _TRACE_("switchCameraWork("<<prm_pID<<") end---");
//    stack_CamWorkerCon_.dump();
    return pCamWorker;

}

CameraWorker* Universe::undoCameraWork() {
//    _TRACE_("undoCameraWork begin---");
//    stack_CamWorkerCon_.dump();
    //    |      |                       |      |
    //    +------+                       |      |
    //    | ConC | ←Active      pop     |      |
    //    +------+           --------->  +------+
    //    | ConB |                       | ConB | ←Active(return)
    //    +------+                       +------+
    //    | ConA |                       | ConA |
    //    +------+                       +------+

    //スタックｋら取り出し
    CameraWorkerConnection* pConn_now = stack_CamWorkerCon_.pop(); //pConn_nowは上図のConCが返る
    CameraWorkerConnection* pCon = stack_CamWorkerCon_.getLast(); //pConは上図で言うとConBが返る
    if (pCon) {
        CameraWorker* pCamWorker = pCon->fetch();
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
                stack_CamWorkerCon_.dump();
                throwGgafCriticalException("Universe::undoCameraWork()  stack_CameraWorker_ から pop() しすぎ。");
            }
            pConn_now->close();
//            _TRACE_("undoCameraWork end---");
//            stack_CamWorkerCon_.dump();
            return pActiveCamWorker_;
        } else {
#ifdef MY_DEBUG
            stack_CamWorkerCon_.dump();
            _TRACE_("＜警告＞Universe::undoCameraWork() pop()したカメラワークは、pop()前と同じカメラワークです。pCamWorker="<<pCamWorker->getName());
#endif
            return pActiveCamWorker_;
        }
    } else {
        stack_CamWorkerCon_.dump();
        throwGgafCriticalException("Universe::undoCameraWork()  stack_CameraWorker_ から pop() しすぎにも程がある");
    }
}

void Universe::resetCamWorker() {
    //DefaultCamWorkerまでキレイにする
//    _TRACE_("resetCamWorker begin---");
//    stack_CamWorkerCon_.dump();
    for (int i = 0; i < 30; i++) {
        if (stack_CamWorkerCon_.p_ == 1) {
            break;
        } else {
            CameraWorkerConnection* pCon = stack_CamWorkerCon_.pop();
            pCon->close();
        }
    }
    P_CAM->setDefaultPosition();
    pActiveCamWorker_ = stack_CamWorkerCon_.getLast()->fetch();
    pActiveCamWorker_->setMoveTargetCamBy(P_CAM);
    pActiveCamWorker_->setMoveTargetCamVpBy(P_CAM->_pViewPoint);
    pActiveCamWorker_->angXY_nowCamUp_ = UTIL::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
    pActiveCamWorker_->move_target_XY_CAM_UP_ = pActiveCamWorker_->angXY_nowCamUp_;
    pActiveCamWorker_->activate();
//    _TRACE_("resetCamWorker end---");
//    stack_CamWorkerCon_.dump();
}


Universe::~Universe() {
    DELETE_IMPOSSIBLE_NULL(pCamWorkerManager_);
}
