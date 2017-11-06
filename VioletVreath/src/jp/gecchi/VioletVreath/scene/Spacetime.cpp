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

Spacetime::CameraWorkerHistory::CameraWorkerHistory() {
    p_ = 0;
    for (int i = 0; i < CAM_WORKER_STACK_NUM; i++) {
        apCamWorkerConnection_[i] = nullptr;
    }
}
CameraWorkerConnection* Spacetime::CameraWorkerHistory::getLast() {
    if (p_ == 0) {
        return apCamWorkerConnection_[CAM_WORKER_STACK_NUM-1];
    } else {
        return apCamWorkerConnection_[p_-1];
    }
}
void Spacetime::CameraWorkerHistory::push(CameraWorkerConnection* prm_pCamWorkerCon) {
    if (p_ > CAM_WORKER_STACK_NUM-1) {
        p_ = 0;
    }
    apCamWorkerConnection_[p_] = prm_pCamWorkerCon;
    p_++;
}
CameraWorkerConnection* Spacetime::CameraWorkerHistory::pop() {
    if (p_ == 0) {
        p_ = CAM_WORKER_STACK_NUM;
    }
    p_--;
    CameraWorkerConnection* r = apCamWorkerConnection_[p_];
#ifdef MY_DEBUG
    if (r == nullptr) {
        throwGgafCriticalException("Spacetime::CameraWorkerHistory::pop() POPしすぎです");
    }
#endif
    apCamWorkerConnection_[p_] = nullptr;
    return r;
}

void Spacetime::CameraWorkerHistory::dump() {
    _TRACE_("CameraWorkerHistory Active p_="<<p_);
    for (int i = 0; i < CAM_WORKER_STACK_NUM; i++) {
        if (apCamWorkerConnection_[i]) {
            _TRACE_("apCamWorkerConnection_["<<i<<"]="<<(apCamWorkerConnection_[i]->getIdStr()));
        }
    }
}
Spacetime::CameraWorkerHistory::~CameraWorkerHistory() {
    for (int i = 0; i < CAM_WORKER_STACK_NUM; i++) {
        apCamWorkerConnection_[i] = nullptr;
    }
    p_ = 0;
}

/////////////////////////////////////////////////

Spacetime::Spacetime(const char* prm_name, Camera* prm_pCamera) : DefaultSpacetime(prm_name, prm_pCamera) {
    _class_name = "Spacetime";
    pWorld_ = nullptr;
    _TRACE_(FUNC_NAME<<"");
    pCamWorkerManager_ = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pCamWorkerCon = (CameraWorkerConnection*)pCamWorkerManager_->connect("DefaultCamWorker", prm_pCamera);
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
    _TRACE_(FUNC_NAME<<"");
}

void Spacetime::processBehavior() {
    if (!pActiveCamWorker_->_was_initialize_flg) {
        pActiveCamWorker_->initialize();
    }
    if (pActiveCamWorker_->hasJustChangedToActive()) {
        if (pActiveCamWorker_->frame_of_behaving_since_onSwitch_== 0) {
            //changeCameraWork で切り替わってきた場合
            pActiveCamWorker_->onSwitchCameraWork(); //コールバック
        } else {
            //undoCameraWorkで切り替わってきた場合
            pActiveCamWorker_->onSwitchCameraWork(); //コールバック
        }
    }

    pActiveCamWorker_->frame_of_behaving_since_onSwitch_++;
    DefaultSpacetime::processBehavior();
}

void Spacetime::processJudgement() {
    DefaultSpacetime::processJudgement();
}

CameraWorker* Spacetime::changeCameraWork(const char* prm_pID) {
    _TRACE_("Spacetime::changeCameraWork("<<prm_pID<<") ");
//    stack_CamWorkerConnection_.dump();
    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ←Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ←Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+
    CameraWorkerConnection* pCon = (CameraWorkerConnection*)pCamWorkerManager_->connect(prm_pID, getCamera());
    CameraWorker* pCamWorker = pCon->peek();
    if (pCamWorker != pActiveCamWorker_) {
        _TRACE_("現pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" は一時非活動で待機");
        //現在の CameraWork を非活動へ
        pActiveCamWorker_->onChangedToOtherCameraWork(); //コールバック
        pActiveCamWorker_->inactivate();
        //パラメータの CameraWork を活動へ
        pCamWorker->activate();
        pCamWorker->frame_of_behaving_since_onSwitch_ = 0; //switch後フレームカウンタリセット
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
        _TRACE_("＜警告＞Spacetime::changeCameraWork("<<prm_pID<<") 同じカメラワークを連続でpush()していますので無視します。pActiveCamWorker_="<<pActiveCamWorker_->getName());
#endif
        pCon->close();
    }
    return pCamWorker;

}

CameraWorker* Spacetime::undoCameraWork() {
    _TRACE_(FUNC_NAME<<"");
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
            pActiveCamWorker_->onChangedToOtherCameraWork();  //コールバック
            pActiveCamWorker_->inactivate();
            pActiveCamWorker_ = pCamWorker;
            if (pActiveCamWorker_) {
                //１つ前の CameraWork を活動へ
                pActiveCamWorker_->activate();
            } else {
                stack_CamWorkerConnection_.dump();
                throwGgafCriticalException("stack_CameraWorker_ から pop() しすぎ。");
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
        throwGgafCriticalException("stack_CameraWorker_ から pop() しすぎにも程がある");
    }
}

void Spacetime::resetCamWorker() {
    //DefaultCamWorkerまでキレイにする
   _TRACE_(FUNC_NAME<<"");
//    stack_CamWorkerConnection_.dump();
    for (int i = 0; i < CAM_WORKER_STACK_NUM; i++) {
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
    for (int i = 0; i < CAM_WORKER_STACK_NUM; i++) {
        CameraWorkerConnection* pCon = stack_CamWorkerConnection_.apCamWorkerConnection_[i];
        if (pCon) {
            pCon->close();
        }
        stack_CamWorkerConnection_.apCamWorkerConnection_[i] = nullptr;
    }
    stack_CamWorkerConnection_.p_ = 0;
    GGAF_DELETE(pCamWorkerManager_);
}
