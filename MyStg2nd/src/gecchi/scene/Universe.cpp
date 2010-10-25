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
    _pActiveCameraWorker = pCameraWorkerCon->refer();
    getLordActor()->addSubGroup(_pActiveCameraWorker);


    GgafRepeatSeq::create("CH_bomb1", 0, 20);
    GgafRepeatSeq::create("CH_yume_Sbend", 0, 8);
    GgafRepeatSeq::create("CH_MetisHit", 0, 20);
    GgafRepeatSeq::create("CH_break_glass01", 0, 20);
    GgafRepeatSeq::create("CH_a_shot", 0, 5);
    GgafRepeatSeq::create("CH_laser001", 0, 8); //�I�v�V�������[�U�[
    GgafRepeatSeq::create("CH_cm-22", 0, 8); //Juno���ˉ�
    GgafRepeatSeq::create("CH_MetisDestroy", 0, 20); //Metis����
    GgafRepeatSeq::create("CH_explos3", 0, 3); //Vesta����
    GgafRepeatSeq::create("CH_humei10", 0, 1); //Lockon
    GgafRepeatSeq::create("CH_fire01", 0, 16); //���@�V���b�g


    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
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
//    _TRACE_("COMMING Universe::pushCameraWork("<<prm_pID<<")");
//    _TRACE_("Now _pActiveCameraWorker="<<_pActiveCameraWorker->getName()<<")");

    CameraWorker* pCameraWorker = _pCameraWorkerManager->getConnection(prm_pID)->refer();
//    _TRACE_("then refer="<<pCameraWorker->getName()<<")");

    if (pCameraWorker != _pActiveCameraWorker) {
//        _TRACE_("then pCameraWorker != _pActiveCameraWorker");
        if (getLordActor()->getSubFirst()->getSub(pCameraWorker)) {
//            _TRACE_("Its known CameraWorker!!");
            pCameraWorker->activate();
        } else {
//            _TRACE_("Its new CameraWorker!!");
            getLordActor()->addSubGroup(pCameraWorker);
        }
//        _TRACE_("then _pActiveCameraWorker="<<_pActiveCameraWorker->getName()<<" was inactivateand push");
        _pActiveCameraWorker->inactivate();
        _stack_CameraWorker.push(_pActiveCameraWorker);
        _pActiveCameraWorker = pCameraWorker;
    } else {
        _TRACE_("�����J�������[�N��push()���Ă��܂�"<<pCameraWorker->getName());
    }

}

void Universe::popCameraWork() {
//    _TRACE_("COMMING Universe::popCameraWork() ");
//    _TRACE_("Now _pActiveCameraWorker="<<_pActiveCameraWorker->getName()<<")");

    CameraWorker* pCameraWorker = _stack_CameraWorker.pop();
    if (pCameraWorker) {
//        _TRACE_("then poped CameraWorker="<<pCameraWorker->getName()<<")");

        if (pCameraWorker != _pActiveCameraWorker) {
//            _TRACE_("yes pCameraWorker != _pActiveCameraWorker");

            _pActiveCameraWorker->inactivate();
            pCameraWorker->activate();
            _pActiveCameraWorker = pCameraWorker;
        } else {
            _TRACE_("Universe::popCameraWork() pop()�����J�������[�N�͌��݂Ɠ����ł��B"<<pCameraWorker->getName());
        }
    } else {
        //pop������
        throwGgafCriticalException("Universe::popCameraWork()  _stack_CameraWorker ���� pop() ������");
    }
}



Universe::~Universe() {
    DELETE_IMPOSSIBLE_NULL(_pCameraWorkerManager);
}
