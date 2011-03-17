#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Universe::Universe(const char* prm_name, GgafDx9Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
    _class_name = "Universe";

    _TRACE_("Universe::Universe()");
    _pCameraWorkerManager = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pDefaultCameraWorkerCon = (CameraWorkerConnection*)_pCameraWorkerManager->getConnection("DefaultCamWorker");
    _stack_CameraWorkerCon.push(pDefaultCameraWorkerCon);
    _pActiveCameraWorker = pDefaultCameraWorkerCon->refer();
    getLordActor()->addSubGroup(_pActiveCameraWorker); //基底デフォルトカメラワーク


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

    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ←Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ←Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+

    CameraWorkerConnection* pCon = (CameraWorkerConnection*)_pCameraWorkerManager->getConnection(prm_pID);
    CameraWorker* pCameraWorker = pCon->refer();
    if (pCameraWorker != _pActiveCameraWorker) {
        //現在の CameraWork を非活動へ
        _pActiveCameraWorker->onSwitchToOherCameraWork(); //コールバック
        _pActiveCameraWorker->inactivate();
        //パラメータの CameraWork を活動へ
        pCameraWorker->activate();
        pCameraWorker->onSwitchCameraWork(); //コールバック
        if (getLordActor()->getSubFirst()->getSub(pCameraWorker)) {
            //２回目以降の
        } else {
            getLordActor()->addSubGroup(pCameraWorker); //初回はツリーに追加
        }
        //スタックに積む
        _stack_CameraWorkerCon.push(pCon);
        _pActiveCameraWorker = pCameraWorker;
    } else {
        _stack_CameraWorkerCon.dump();
        throwGgafCriticalException("Universe::switchCameraWork("<<prm_pID<<") 同じカメラワークを連続でpush()しています。_pActiveCameraWorker="<<_pActiveCameraWorker->getName());
    }
    return pCameraWorker;

}

CameraWorker* Universe::undoCameraWork() {

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
        CameraWorker* pCameraWorker = pCon->refer();
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
            return _pActiveCameraWorker;
        } else {
            _stack_CameraWorkerCon.dump();
            throwGgafCriticalException("Universe::undoCameraWork() pop()したカメラワークは、pop()前と同じカメラワークです。pCameraWorker="<<pCameraWorker->getName());
        }
    } else {
        _stack_CameraWorkerCon.dump();
        throwGgafCriticalException("Universe::undoCameraWork()  _stack_CameraWorker から pop() しすぎにも程がある");
    }
}

void Universe::resetCameraWork() {
    //DefaultCamWorkerまでキレイにする
    for (int i = 0; i < 30; i++) {
        if (_stack_CameraWorkerCon._p == 1) {
            break;
        } else {
            CameraWorkerConnection* pCon = _stack_CameraWorkerCon.pop();
            pCon->close();
        }
    }
}


Universe::~Universe() {
    DELETE_IMPOSSIBLE_NULL(_pCameraWorkerManager);
}
