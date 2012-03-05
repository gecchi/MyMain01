#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Universe::Universe(const char* prm_name, Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
    _class_name = "Universe";
    pWorld_ = NULL;
    _TRACE_("Universe::Universe()");
    pCameraWorkerManager_ = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pDefaultCameraWorkerCon = (CameraWorkerConnection*)pCameraWorkerManager_->connect("DefaultCamWorker");
    stack_CameraWorkerCon_.push(pDefaultCameraWorkerCon);
    pActiveCameraWorker_ = pDefaultCameraWorkerCon->use();
    getDirector()->addSubGroup(pActiveCameraWorker_); //基底デフォルトカメラワーク


    GgafRepeatSeq::create("CH_bomb1", 0, 20);
    GgafRepeatSeq::create("CH_yume_Sbend", 0, 8);
    GgafRepeatSeq::create("CH_MetisHit", 0, 20);
    GgafRepeatSeq::create("CH_break_glass01", 0, 20);
    GgafRepeatSeq::create("CH_a_shot", 0, 5);
    GgafRepeatSeq::create("CH_laser001", 0, 8); //オプションレーザー
    GgafRepeatSeq::create("CH_cm-22", 0, 8); //Juno発射音
    GgafRepeatSeq::create("CH_MetisDestroy", 0, 20); //Metis爆発
    GgafRepeatSeq::create("CH_explos3", 0, 3); //Vesta爆発
    GgafRepeatSeq::create("CH_humei10", 0, 1); //Lockon
    GgafRepeatSeq::create("CH_fire01", 0, 16); //自機ショット


    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void Universe::initialize() {
    pWorld_ = NEW World("WORLD");
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
//    stack_CameraWorkerCon_.dump();
    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ←Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ←Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+

    CameraWorkerConnection* pCon = connectCameraWorkerManager(prm_pID);
    CameraWorker* pCameraWorker = pCon->use();
    if (pCameraWorker != pActiveCameraWorker_) {
        //現在の CameraWork を非活動へ
        pActiveCameraWorker_->onSwitchToOherCameraWork(); //コールバック
        pActiveCameraWorker_->inactivate();
        //パラメータの CameraWork を活動へ
        pCameraWorker->activate();
        pCameraWorker->onSwitchCameraWork(); //コールバック
        if (getDirector()->getSubFirst()->getSub(pCameraWorker)) {
            //２回目以降の
        } else {
            getDirector()->addSubGroup(pCameraWorker); //初回はツリーに追加
        }
        //スタックに積む
        stack_CameraWorkerCon_.push(pCon);
        pActiveCameraWorker_ = pCameraWorker;
    } else {
#ifdef MY_DEBUG
        stack_CameraWorkerCon_.dump();
        _TRACE_("＜警告＞Universe::switchCameraWork("<<prm_pID<<") 同じカメラワークを連続でpush()していますので無視します。pActiveCameraWorker_="<<pActiveCameraWorker_->getName());
#endif
    }
//    _TRACE_("switchCameraWork("<<prm_pID<<") end---");
//    stack_CameraWorkerCon_.dump();
    return pCameraWorker;

}

CameraWorker* Universe::undoCameraWork() {
//    _TRACE_("undoCameraWork begin---");
//    stack_CameraWorkerCon_.dump();
    //    |      |                       |      |
    //    +------+                       |      |
    //    | ConC | ←Active      pop     |      |
    //    +------+           --------->  +------+
    //    | ConB |                       | ConB | ←Active(return)
    //    +------+                       +------+
    //    | ConA |                       | ConA |
    //    +------+                       +------+

    //スタックｋら取り出し
    CameraWorkerConnection* pCon_now = stack_CameraWorkerCon_.pop(); //pCon_nowは上図のConCが返る
    CameraWorkerConnection* pCon = stack_CameraWorkerCon_.getLast(); //pConは上図で言うとConBが返る
    if (pCon) {
        CameraWorker* pCameraWorker = pCon->use();
        if (pCameraWorker != pActiveCameraWorker_) {
            //現在の CameraWork を非活動へ
            pActiveCameraWorker_->inactivate();
            pActiveCameraWorker_->onUndoCameraWork();  //コールバック
            pActiveCameraWorker_ = pCameraWorker;
            if (pActiveCameraWorker_) {
                //１つ前の CameraWork を活動へ
                pActiveCameraWorker_->onCameBackFromOtherCameraWork();  //コールバック
                pActiveCameraWorker_->activate();
            } else {
                stack_CameraWorkerCon_.dump();
                throwGgafCriticalException("Universe::undoCameraWork()  stack_CameraWorker_ から pop() しすぎ。");
            }
            pCon_now->close();
//            _TRACE_("undoCameraWork end---");
//            stack_CameraWorkerCon_.dump();
            return pActiveCameraWorker_;
        } else {
#ifdef MY_DEBUG
            stack_CameraWorkerCon_.dump();
            _TRACE_("＜警告＞Universe::undoCameraWork() pop()したカメラワークは、pop()前と同じカメラワークです。pCameraWorker="<<pCameraWorker->getName());
#endif
            return pActiveCameraWorker_;
        }
    } else {
        stack_CameraWorkerCon_.dump();
        throwGgafCriticalException("Universe::undoCameraWork()  stack_CameraWorker_ から pop() しすぎにも程がある");
    }
}

void Universe::resetCameraWork() {
    //DefaultCamWorkerまでキレイにする
//    _TRACE_("resetCameraWork begin---");
//    stack_CameraWorkerCon_.dump();
    for (int i = 0; i < 30; i++) {
        if (stack_CameraWorkerCon_.p_ == 1) {
            break;
        } else {
            CameraWorkerConnection* pCon = stack_CameraWorkerCon_.pop();
            pCon->close();
        }
    }
    P_CAM->setDefaultPosition();
    pActiveCameraWorker_ = stack_CameraWorkerCon_.getLast()->use();
    pActiveCameraWorker_->setMoveTargetCamBy(P_CAM);
    pActiveCameraWorker_->setMoveTargetCamVpBy(P_CAM->_pViewPoint);
    pActiveCameraWorker_->angXY_nowCamUp_ = GgafDxUtil::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
    pActiveCameraWorker_->move_target_XY_CAM_UP_ = pActiveCameraWorker_->angXY_nowCamUp_;
    pActiveCameraWorker_->activate();
//    _TRACE_("resetCameraWork end---");
//    stack_CameraWorkerCon_.dump();
}


Universe::~Universe() {
    DELETE_IMPOSSIBLE_NULL(pCameraWorkerManager_);
}
