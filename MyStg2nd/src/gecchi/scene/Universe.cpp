#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
CameraWorker* Universe::_pActiveCameraWorker = NULL;


Universe::Universe(const char* prm_name, GgafDx9Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
    _TRACE_("Universe::Universe()");
    _pCameraWorkerManager = NEW CameraWorkerManager("CameraWorkerManager");
    GgafResourceConnection<CameraWorker>* pCameraWorkerCon = _pCameraWorkerManager->getConnection("DefaultCamWorker");
    _stack_CameraWorkerCon.push(pCameraWorkerCon);
    _pActiveCameraWorker = pCameraWorkerCon->refer();
    getLordActor()->addSubGroup(_pActiveCameraWorker);


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

void Universe::pushCameraWork(const char* prm_pID) {
    GgafResourceConnection<CameraWorker>* pCameraWorkerCon = _pCameraWorkerManager->getConnection(prm_pID);
    CameraWorker* pCameraWorker = pCameraWorkerCon->refer();
    if (pCameraWorker != _pActiveCameraWorker) {
        if (getLordActor()->getSubFirst()->getSub(pCameraWorker)) {
            _pActiveCameraWorker->inactivate();
            pCameraWorker->activate();
            _pActiveCameraWorker = pCameraWorker;
        } else {
            _pActiveCameraWorker->inactivate();
            getLordActor()->addSubGroup(pCameraWorker);
            _pActiveCameraWorker = pCameraWorker;
        }
    } else {
        _TRACE_("同じカメラワークをpush()しています"<<pCameraWorker->getName());
    }
    _stack_CameraWorkerCon.push(pCameraWorkerCon);
}

void Universe::popCameraWork() {
    GgafResourceConnection<CameraWorker>* pCameraWorkerCon = _stack_CameraWorkerCon.pop();
    if (pCameraWorkerCon) {
        CameraWorker* pCameraWorker = pCameraWorkerCon->refer();
        if (pCameraWorker != _pActiveCameraWorker) {
            _pActiveCameraWorker->inactivate();
            pCameraWorker->activate();
            _pActiveCameraWorker = pCameraWorker;
        } else {
            _TRACE_("Universe::popCameraWork() pop()したカメラワークは現在と同じです。"<<pCameraWorker->getName());
        }
    } else {
        //popしすぎ
        throwGgafCriticalException("Universe::popCameraWork()  _stack_CameraWorkerCon から pop() しすぎ");
    }
}



Universe::~Universe() {
    _pActiveCameraWorker->extract();
    DELETE_IMPOSSIBLE_NULL(_pCameraWorkerManager);
}
