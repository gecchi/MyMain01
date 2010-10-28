#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
CameraWorker* Universe::_pActiveCameraWorker = NULL;


Universe::Universe(const char* prm_name, GgafDx9Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
    _class_name = "Universe";

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

CameraWorker* Universe::pushCameraWork(const char* prm_pID) {
    CameraWorker* pCameraWorker = _pCameraWorkerManager->getConnection(prm_pID)->refer();
    if (pCameraWorker != _pActiveCameraWorker) {
        if (getLordActor()->getSubFirst()->getSub(pCameraWorker)) {
            pCameraWorker->activate();
        } else {
            getLordActor()->addSubGroup(pCameraWorker);
        }
        _pActiveCameraWorker->inactivate();
        _stack_CameraWorker.push(_pActiveCameraWorker);
        _pActiveCameraWorker = pCameraWorker;
    } else {
        _TRACE_("�����J�������[�N��push()���Ă��܂�"<<pCameraWorker->getName()<<" _class_name="<<_class_name);
    }
    pCameraWorker->onPushed();
    return pCameraWorker;

}

CameraWorker* Universe::popCameraWork() {
    CameraWorker* pCameraWorker = _stack_CameraWorker.pop();
    if (pCameraWorker) {
        if (pCameraWorker != _pActiveCameraWorker) {
            _pActiveCameraWorker->inactivate();
            pCameraWorker->activate();
            _pActiveCameraWorker = pCameraWorker;
        } else {
            _TRACE_("Universe::popCameraWork() pop()�����J�������[�N�͌��݂Ɠ����ł��B"<<pCameraWorker->getName()<<" _class_name="<<_class_name);
        }
    } else {
        //pop������
        throwGgafCriticalException("Universe::popCameraWork()  _stack_CameraWorker ���� pop() �������B_class_name="<<_class_name);
    }
    pCameraWorker->onPoped();
    return pCameraWorker;
}



Universe::~Universe() {
    DELETE_IMPOSSIBLE_NULL(_pCameraWorkerManager);
}
