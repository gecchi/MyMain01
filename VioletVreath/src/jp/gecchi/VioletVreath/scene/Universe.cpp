#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Universe::Universe(const char* prm_name, GgafDxCamera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
    _class_name = "Universe";
    _pWorld = NULL;
    _TRACE_("Universe::Universe()");
    _pCameraWorkerManager = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pDefaultCameraWorkerCon = (CameraWorkerConnection*)_pCameraWorkerManager->connect("DefaultCamWorker");
    _stack_CameraWorkerCon.push(pDefaultCameraWorkerCon);
    _pActiveCameraWorker = pDefaultCameraWorkerCon->use();
    getDirector()->addSubGroup(_pActiveCameraWorker); //基底デフォルトカメラワーク


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
    _pWorld = NEW World("WORLD");
    addSubLast(_pWorld);

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
//    _stack_CameraWorkerCon.dump();
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
    if (pCameraWorker != _pActiveCameraWorker) {
        //現在の CameraWork を非活動へ
        _pActiveCameraWorker->onSwitchToOherCameraWork(); //コールバック
        _pActiveCameraWorker->inactivate();
        //パラメータの CameraWork を活動へ
        pCameraWorker->activate();
        pCameraWorker->onSwitchCameraWork(); //コールバック
        if (getDirector()->getSubFirst()->getSub(pCameraWorker)) {
            //２回目以降の
        } else {
            getDirector()->addSubGroup(pCameraWorker); //初回はツリーに追加
        }
        //スタックに積む
        _stack_CameraWorkerCon.push(pCon);
        _pActiveCameraWorker = pCameraWorker;
    } else {
#ifdef MY_DEBUG
        _stack_CameraWorkerCon.dump();
        _TRACE_("＜警告＞Universe::switchCameraWork("<<prm_pID<<") 同じカメラワークを連続でpush()していますので無視します。_pActiveCameraWorker="<<_pActiveCameraWorker->getName());
#endif
    }
//    _TRACE_("switchCameraWork("<<prm_pID<<") end---");
//    _stack_CameraWorkerCon.dump();
    return pCameraWorker;

}

CameraWorker* Universe::undoCameraWork() {
//    _TRACE_("undoCameraWork begin---");
//    _stack_CameraWorkerCon.dump();
    //    |      |                       |      |
    //    +------+                       |      |
    //    | ConC | ←Active      pop     |      |
    //    +------+           --------->  +------+
    //    | ConB |                       | ConB | ←Active(return)
    //    +------+                       +------+
    //    | ConA |                       | ConA |
    //    +------+                       +------+

    //スタックｋら取り出し
    CameraWorkerConnection* pCon_now = _stack_CameraWorkerCon.pop(); //pCon_nowは上図のConCが返る
    CameraWorkerConnection* pCon = _stack_CameraWorkerCon.getLast(); //pConは上図で言うとConBが返る
    if (pCon) {
        CameraWorker* pCameraWorker = pCon->use();
        if (pCameraWorker != _pActiveCameraWorker) {
            //現在の CameraWork を非活動へ
            _pActiveCameraWorker->inactivate();
            _pActiveCameraWorker->onUndoCameraWork();  //コールバック
            _pActiveCameraWorker = pCameraWorker;
            if (_pActiveCameraWorker) {
                //１つ前の CameraWork を活動へ
                _pActiveCameraWorker->onCameBackFromOtherCameraWork();  //コールバック
                _pActiveCameraWorker->activate();
            } else {
                _stack_CameraWorkerCon.dump();
                throwGgafCriticalException("Universe::undoCameraWork()  _stack_CameraWorker から pop() しすぎ。");
            }
            pCon_now->close();
//            _TRACE_("undoCameraWork end---");
//            _stack_CameraWorkerCon.dump();
            return _pActiveCameraWorker;
        } else {
#ifdef MY_DEBUG
            _stack_CameraWorkerCon.dump();
            _TRACE_("＜警告＞Universe::undoCameraWork() pop()したカメラワークは、pop()前と同じカメラワークです。pCameraWorker="<<pCameraWorker->getName());
#endif
            return _pActiveCameraWorker;
        }
    } else {
        _stack_CameraWorkerCon.dump();
        throwGgafCriticalException("Universe::undoCameraWork()  _stack_CameraWorker から pop() しすぎにも程がある");
    }
}

void Universe::resetCameraWork() {
    //DefaultCamWorkerまでキレイにする
//    _TRACE_("resetCameraWork begin---");
//    _stack_CameraWorkerCon.dump();
    for (int i = 0; i < 30; i++) {
        if (_stack_CameraWorkerCon._p == 1) {
            break;
        } else {
            CameraWorkerConnection* pCon = _stack_CameraWorkerCon.pop();
            pCon->close();
        }
    }
    P_CAM->setDefaultPosition();
    _pActiveCameraWorker = _stack_CameraWorkerCon.getLast()->use();
    _pActiveCameraWorker->setMoveTargetCamBy(P_CAM);
    _pActiveCameraWorker->setMoveTargetCamVpBy(P_CAM->_pViewPoint);
    _pActiveCameraWorker->_angXY_nowCamUp = GgafDxUtil::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
    _pActiveCameraWorker->_move_target_XY_CAM_UP = _pActiveCameraWorker->_angXY_nowCamUp;
    _pActiveCameraWorker->activate();
//    _TRACE_("resetCameraWork end---");
//    _stack_CameraWorkerCon.dump();
}


Universe::~Universe() {
    DELETE_IMPOSSIBLE_NULL(_pCameraWorkerManager);
}
