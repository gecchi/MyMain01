#include "Spacetime.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerManager.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Spacetime::CameraWorkerConnectionStack::CameraWorkerConnectionStack() {
    p_ = 0;
    for (int i = 0; i < 30; i++) {
        apCamWorkerConnection_[i] = nullptr;
    }
}
CameraWorkerConnection* Spacetime::CameraWorkerConnectionStack::getLast() {
    if (p_ == 0) {
        return nullptr;
    } else {
        return apCamWorkerConnection_[p_-1];
    }
}
void Spacetime::CameraWorkerConnectionStack::push(CameraWorkerConnection* prm_pCamWorkerCon) {
    if (p_ > 30-1) {
        throwGgafCriticalException("CameraWorkerConnectionStack::push("<<prm_pCamWorkerCon->getIdStr()<<") スタックを使い切りました。");
    }
    apCamWorkerConnection_[p_] = prm_pCamWorkerCon;
    p_++;
}
CameraWorkerConnection* Spacetime::CameraWorkerConnectionStack::pop() {
    if (p_ == 0) {
        throwGgafCriticalException("CameraWorkerConnectionStack::pop() ポップしすぎです");
    } else {
        p_--;
        CameraWorkerConnection* r = apCamWorkerConnection_[p_];
        apCamWorkerConnection_[p_] = nullptr;
        return r;
    }
}
void Spacetime::CameraWorkerConnectionStack::clear() {
    p_ = 0;
    for (int i = 0; i < 30; i++) {
        apCamWorkerConnection_[i] = nullptr;
    }
}

void Spacetime::CameraWorkerConnectionStack::dump() {
    _TRACE_("CameraWorkerConnectionStack p_="<<p_);
    for (int i = 0; i < 30; i++) {
        if (apCamWorkerConnection_[i]) {
            _TRACE_("apCamWorkerConnection_["<<i<<"]="<<(apCamWorkerConnection_[i]->getIdStr()));
        }
    }
}
Spacetime::CameraWorkerConnectionStack::~CameraWorkerConnectionStack() {
    clear();
}

/////////////////////////////////////////////////

Spacetime::Spacetime(const char* prm_name, Camera* prm_pCamera) : DefaultSpacetime(prm_name, prm_pCamera) {
    _class_name = "Spacetime";
    pWorld_ = nullptr;
    _TRACE_("Spacetime::Spacetime()");
    pCamWorkerManager_ = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pCamWorkerCon = (CameraWorkerConnection*)pCamWorkerManager_->connect("DefaultCamWorker", this);
    stack_CamWorkerConnection_.push(pCamWorkerCon);
    pActiveCamWorker_ = pCamWorkerCon->peek();
    bringDirector()->addSubGroup(pActiveCamWorker_); //基底デフォルトカメラワーク
    //【めも】
    //ここでActorやSceneのNEWをしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void Spacetime::initialize() {
    pWorld_ = createInFactory(VioletVreath::World, "WORLD");
    addSubLast(pWorld_);
    _TRACE_("Spacetime::initialize()");
}

void Spacetime::processBehavior() {
    if (!pActiveCamWorker_->_was_initialize_flg) {
        pActiveCamWorker_->initialize();
    }
    if (pActiveCamWorker_->isJustChangedToActive()) {
        if (pActiveCamWorker_->frame_of_behaving_since_onSwitch_== 0) {
            pActiveCamWorker_->onSwitchCameraWork(); //コールバック
        } else {
            pActiveCamWorker_->onCameBackFromOtherCameraWork(); //コールバック
        }
    }

    pActiveCamWorker_->frame_of_behaving_since_onSwitch_++;
    DefaultSpacetime::processBehavior();
}

void Spacetime::processJudgement() {
    DefaultSpacetime::processJudgement();
}

CameraWorker* Spacetime::switchCameraWork(const char* prm_pID) {
    _TRACE_("Spacetime::switchCameraWork("<<prm_pID<<") ");
//    stack_CamWorkerConnection_.dump();
    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ←Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ←Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+

    CameraWorkerConnection* pCon = getConnection_CameraWorkerManager(prm_pID);
    CameraWorker* pCamWorker = pCon->peek();
    if (pCamWorker != pActiveCamWorker_) {
        _TRACE_("現pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" は一時非活動で待機");
        //現在の CameraWork を非活動へ
        pActiveCamWorker_->onSwitchToOtherCameraWork(); //コールバック
        pActiveCamWorker_->inactivate();
        //パラメータの CameraWork を活動へ
        pCamWorker->activate();
        pCamWorker->frame_of_behaving_since_onSwitch_ = 0; //switch後フレームカウンタリセット
//        pCamWorker->onSwitchCameraWork(); //コールバック
        if (bringDirector()->getSubFirst()->getSub(pCamWorker)) {
            //２回目以降の
        } else {
            bringDirector()->addSubGroup(pCamWorker); //初回はツリーに追加
        }
        //スタックに積む
        stack_CamWorkerConnection_.push(pCon);
        pActiveCamWorker_ = pCamWorker;
        _TRACE_("新pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" は上書きで活動状態");
    } else {
#ifdef MY_DEBUG
        stack_CamWorkerConnection_.dump();
        _TRACE_("＜警告＞Spacetime::switchCameraWork("<<prm_pID<<") 同じカメラワークを連続でpush()していますので無視します。pActiveCamWorker_="<<pActiveCamWorker_->getName());
#endif
    }
//    stack_CamWorkerConnection_.dump();
    return pCamWorker;

}

CameraWorker* Spacetime::undoCameraWork() {
    _TRACE_("Spacetime::undoCameraWork()");
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
    CameraWorkerConnection* pConn_now = stack_CamWorkerConnection_.pop(); //pConn_nowは上図のConCが返る
    CameraWorkerConnection* pCon = stack_CamWorkerConnection_.getLast(); //pConは上図で言うとConBが返る
    if (pCon) {
        CameraWorker* pCamWorker = pCon->peek();
        if (pCamWorker != pActiveCamWorker_) {
            //現在の CameraWork を非活動へ
            _TRACE_("現pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" はさいなら");

            pActiveCamWorker_->inactivate();
            pActiveCamWorker_->onUndoCameraWork();  //コールバック
            pActiveCamWorker_ = pCamWorker;
            if (pActiveCamWorker_) {
                //１つ前の CameraWork を活動へ
//                pActiveCamWorker_->onCameBackFromOtherCameraWork();  //コールバック
                pActiveCamWorker_->activate();
            } else {
                stack_CamWorkerConnection_.dump();
                throwGgafCriticalException("Spacetime::undoCameraWork()  stack_CameraWorker_ から pop() しすぎ。");
            }
            pConn_now->close();
//            _TRACE_("undoCameraWork end---");
//            stack_CamWorkerConnection_.dump();
            _TRACE_("次スタックの pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" がアクティブへ");
            return pActiveCamWorker_;
        } else {
#ifdef MY_DEBUG
            stack_CamWorkerConnection_.dump();
            _TRACE_("＜警告＞Spacetime::undoCameraWork() pop()したカメラワークは、pop()前と同じカメラワークです。pCamWorker="<<pCamWorker->getName());
#endif
            return pActiveCamWorker_;
        }
    } else {
        stack_CamWorkerConnection_.dump();
        throwGgafCriticalException("Spacetime::undoCameraWork()  stack_CameraWorker_ から pop() しすぎにも程がある");
    }
}

void Spacetime::resetCamWorker() {
    //DefaultCamWorkerまでキレイにする
   _TRACE_("Spacetime::resetCamWorker()");
//    stack_CamWorkerConnection_.dump();
    for (int i = 0; i < 30; i++) {
        if (stack_CamWorkerConnection_.p_ == 1) {
            break;
        } else {
            CameraWorkerConnection* pCon = stack_CamWorkerConnection_.pop();
            pCon->close();
        }
    }
    Camera* pCam = getCamera();
    pCam->setDefaultPosition();
    pActiveCamWorker_ = stack_CamWorkerConnection_.getLast()->peek();
    pActiveCamWorker_->slideMvCamTo(pCam, 60);
    pActiveCamWorker_->slideMvVpTo(pCam->getCameraViewPoint(), 60);
//    pActiveCamWorker_->angXY_nowCamUp_ = UTIL::getAngle2D((double)(pCam->_pVecCamUp->z), (double)(pCam->_pVecCamUp->y));
//    pActiveCamWorker_->move_target_ZY_CAM_UP_ = pActiveCamWorker_->angXY_nowCamUp_;
    pActiveCamWorker_->activate();
//    _TRACE_("resetCamWorker end---");
//    stack_CamWorkerConnection_.dump();
}


Spacetime::~Spacetime() {
    GGAF_DELETE(pCamWorkerManager_);
}
