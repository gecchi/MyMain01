#include "jp/ggaf/lib/actor/camera/CameraWorkerChanger.h"

#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"
#include "jp/ggaf/lib/manager/CameraWorkerManager.h"
#include "jp/ggaf/lib/manager/CameraWorkerConnection.h"
#include "jp/ggaf/core/exception/CriticalException.h"

using namespace GgafLib;

CameraWorkerChanger::History::History() {
    _p = 0;
    for (int i = 0; i < CAM_WORKER_HISTORY_NUM; i++) {
        _apCamWorkerConnection[i] = nullptr;
    }
}
CameraWorkerConnection* CameraWorkerChanger::History::getLast() {
    if (_p == 0) {
        return _apCamWorkerConnection[CAM_WORKER_HISTORY_NUM-1];
    } else {
        return _apCamWorkerConnection[_p-1];
    }
}
void CameraWorkerChanger::History::push(CameraWorkerConnection* prm_pCamWorkerCon) {
    if (_p > CAM_WORKER_HISTORY_NUM-1) {
        _p = 0;
    }
    _apCamWorkerConnection[_p] = prm_pCamWorkerCon;
    _p++;
}
CameraWorkerConnection* CameraWorkerChanger::History::pop() {
    if (_p == 0) {
        _p = CAM_WORKER_HISTORY_NUM;
    }
    _p--;
    CameraWorkerConnection* r = _apCamWorkerConnection[_p];
#ifdef MY_DEBUG
    if (r == nullptr) {
        throwCriticalException("CameraWorkerChanger::pop() POPしすぎです");
    }
#endif
    _apCamWorkerConnection[_p] = nullptr;
    return r;
}

void CameraWorkerChanger::History::dump() {
    _TRACE_("CameraWorkerHistory Active _p="<<_p);
    for (int i = 0; i < CAM_WORKER_HISTORY_NUM; i++) {
        if (_apCamWorkerConnection[i]) {
            _TRACE_("_apCamWorkerConnection["<<i<<"]="<<(_apCamWorkerConnection[i]->getIdStr()));
        }
    }
}
CameraWorkerChanger::History::~History() {
    for (int i = 0; i < CAM_WORKER_HISTORY_NUM; i++) {
        _apCamWorkerConnection[i] = nullptr;
    }
    _p = 0;
}


///////////////////////////////////
CameraWorkerChanger::CameraWorkerChanger(const char* prm_name, DefaultCamera* prm_pCamera) : GgafCore::MainActor(prm_name) {
    _class_name = "CameraWorkerChanger";
    _pCamera = prm_pCamera;
    _pCamWorkerManager = NEW CameraWorkerManager("CameraWorkerManager", this);

    CameraWorkerConnection* pCamWorkerCon = (CameraWorkerConnection*)_pCamWorkerManager->connect("DefaultCamWorker", this);
    _stack_CamWorkerConnection.push(pCamWorkerCon);
    _pActiveCamWorker = pCamWorkerCon->peek();
    appendChild(_pActiveCamWorker); //基底デフォルトカメラワーク

    static volatile bool is_init = CameraWorkerChanger::initStatic(); //静的メンバ初期化
    (void)is_init;
    //注意：Cameraはまだ生成されていないためここでP_CAMは使用不可
}

bool CameraWorkerChanger::initStatic() {
    return true;
}

void CameraWorkerChanger::initialize() {
}

void CameraWorkerChanger::processBehavior() {
    if (!_pActiveCamWorker->_was_initialize_flg) {
        _pActiveCamWorker->initialize();
    }
    if (_pActiveCamWorker->hasJustChangedToActive()) {
        if (_pActiveCamWorker->_frame_of_behaving_since_onSwitch== 0) {
            //changeCameraWork で切り替わってきた場合
            _pActiveCamWorker->onSwitchCameraWork(); //コールバック
        } else {
            //undoCameraWorkで切り替わってきた場合
            _pActiveCamWorker->onSwitchCameraWork(); //コールバック
        }
    }

    _pActiveCamWorker->_frame_of_behaving_since_onSwitch++;
}

CameraWorker* CameraWorkerChanger::changeCameraWork(const char* prm_pID) {
    _TRACE_("CameraWorkerChanger::changeCameraWork("<<prm_pID<<") ");
//    _stack_CamWorkerConnection.dump();
    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ←Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ←Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+
    CameraWorkerConnection* pCon = (CameraWorkerConnection*)_pCamWorkerManager->connect(prm_pID, _pCamera);
    CameraWorker* pCamWorker = pCon->peek();
    if (pCamWorker == _pActiveCamWorker) {
#ifdef MY_DEBUG
        _stack_CamWorkerConnection.dump();
        _TRACE_("【警告】CameraWorkerChanger::changeCameraWork("<<prm_pID<<") 同じカメラワークを連続でpush()していますので無視します。_pActiveCamWorker="<<_pActiveCamWorker->getName());
#endif
        pCon->close();
    } else {
        _TRACE_("現_pActiveCamWorker="<<_pActiveCamWorker->getName()<<" は一時非活動で待機");
        //現在の CameraWork を非活動へ
        _pActiveCamWorker->onChangedToOtherCameraWork(); //コールバック
        _pActiveCamWorker->inactivate();
        //パラメータの CameraWork を活動へ
        pCamWorker->activate();
        pCamWorker->_frame_of_behaving_since_onSwitch = 0; //switch後フレームカウンタリセット
        if (getChildFirst()->getChild(pCamWorker)) {
            //２回目以降の
        } else {
            appendChild(pCamWorker); //初回はツリーに追加
        }
        //スタックに積む
        _stack_CamWorkerConnection.push(pCon);
        _pActiveCamWorker = pCamWorker;
        _TRACE_("新_pActiveCamWorker="<<_pActiveCamWorker->getName()<<" は上書きで活動状態");
    }
    return pCamWorker;
}

CameraWorker* CameraWorkerChanger::undoCameraWork() {
    _TRACE_(FUNC_NAME<<"");
//    _stack_CamWorkerConnection.dump();
    //    |      |                       |      |
    //    +------+                       |      |
    //    | ConC | ←Active      pop     |      |
    //    +------+           --------->  +------+
    //    | ConB |                       | ConB | ←Active(return)
    //    +------+                       +------+
    //    | ConA |                       | ConA |
    //    +------+                       +------+

    //スタックｋら取り出し
    CameraWorkerConnection* pConn_now = _stack_CamWorkerConnection.pop(); //pConn_nowは上図のConCが返る
    CameraWorkerConnection* pCon = _stack_CamWorkerConnection.getLast(); //pConは上図で言うとConBが返る
    if (pCon) {
        CameraWorker* pCamWorker = pCon->peek();
        if (pCamWorker != _pActiveCamWorker) {
            //現在の CameraWork を非活動へ
            _TRACE_("現_pActiveCamWorker="<<_pActiveCamWorker->getName()<<" はさいなら");
            _pActiveCamWorker->onChangedToOtherCameraWork();  //コールバック
            _pActiveCamWorker->inactivate();
            _pActiveCamWorker = pCamWorker;
            if (_pActiveCamWorker) {
                //１つ前の CameraWork を活動へ
                _pActiveCamWorker->activate();
            } else {
                _stack_CamWorkerConnection.dump();
                throwCriticalException("stack_CameraWorker_ から pop() しすぎ。");
            }
            pConn_now->close();
//            _TRACE_("undoCameraWork end---");
//            _stack_CamWorkerConnection.dump();
            _TRACE_("次スタックの _pActiveCamWorker="<<_pActiveCamWorker->getName()<<" がアクティブへ");
            return _pActiveCamWorker;
        } else {
#ifdef MY_DEBUG
            _stack_CamWorkerConnection.dump();
            _TRACE_("【警告】CameraWorkerChanger::undoCameraWork() pop()したカメラワークは、pop()前と同じカメラワークです。pCamWorker="<<pCamWorker->getName());
#endif
            return _pActiveCamWorker;
        }
    } else {
        _stack_CamWorkerConnection.dump();
        throwCriticalException("stack_CameraWorker_ から pop() しすぎにも程がある");
    }
}

void CameraWorkerChanger::cleanCamWorker() {
    //DefaultCamWorkerまでキレイにする
   _TRACE_(FUNC_NAME<<"");
//    _stack_CamWorkerConnection.dump();
    for (int i = 0; i < CAM_WORKER_HISTORY_NUM; i++) {
        if (_stack_CamWorkerConnection._p == 1) {
            //DefaultCamWorkerだけ残す
            break;
        } else {
            CameraWorkerConnection* pCon = _stack_CamWorkerConnection.pop();
            CameraWorker* pCamWorker = pCon->peek();
            pCamWorker->sayonara();
            pCon->close();
        }
    }
    DefaultCamera* pCam = _pCamera;
    pCam->setDefaultPosition();
    _pActiveCamWorker = _stack_CamWorkerConnection.getLast()->peek();//DefaultCamWorkerが入ることになる
    _pActiveCamWorker->slideMvCamTo(pCam, 60);
    _pActiveCamWorker->slideMvVpTo(pCam->getCameraViewPoint(), 60);
    _pActiveCamWorker->slideMvUpVecTo(0, PX_C(1), 0, 60);
//    _pActiveCamWorker->angXY_nowCamU_p = UTIL::getAngle2D((double)(pCam->_pVecCamUp->z), (double)(pCam->_pVecCamUp->y));
//    _pActiveCamWorker->move_target_ZY_CAM_UP_ = _pActiveCamWorker->angXY_nowCamU_p;
    _pActiveCamWorker->activate();
//    _TRACE_("cleanCamWorker end---");
//    _stack_CamWorkerConnection.dump();
}


CameraWorkerChanger::~CameraWorkerChanger() {
    for (int i = 0; i < CAM_WORKER_HISTORY_NUM; i++) {
        CameraWorkerConnection* pCon = _stack_CamWorkerConnection._apCamWorkerConnection[i];
        if (pCon) {
            pCon->close();
        }
        _stack_CamWorkerConnection._apCamWorkerConnection[i] = nullptr;
    }
    _stack_CamWorkerConnection._p = 0;
    GGAF_DELETE(_pCamWorkerManager);
}
