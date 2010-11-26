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
    getLordActor()->addSubGroup(_pActiveCameraWorker); //���f�t�H���g�J�������[�N


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
    CameraWorkerConnection* pCon = (CameraWorkerConnection*)_pCameraWorkerManager->getConnection(prm_pID);
    CameraWorker* pCameraWorker = pCon->refer();
    if (pCameraWorker != _pActiveCameraWorker) {
        _pActiveCameraWorker->inactivate();
        if (getLordActor()->getSubFirst()->getSub(pCameraWorker)) {
            pCameraWorker->activate();
        } else {
            pCameraWorker->activate();
            getLordActor()->addSubGroup(pCameraWorker);
        }
        _stack_CameraWorkerCon.push(pCon);
        _pActiveCameraWorker = pCameraWorker;
    } else {
        _stack_CameraWorkerCon.dump();
        throwGgafCriticalException("Universe::pushCameraWork("<<prm_pID<<") �����J�������[�N��A����push()���Ă��܂��B_pActiveCameraWorker="<<_pActiveCameraWorker->getName());
    }
    pCameraWorker->onPushed();
    return pCameraWorker;

}

CameraWorker* Universe::popCameraWork() {
    CameraWorkerConnection* pCon = _stack_CameraWorkerCon.pop();
    if (pCon) {
        CameraWorker* pCameraWorker = pCon->refer();
        if (_stack_CameraWorkerCon.getLast()->refer() != _pActiveCameraWorker) {
            _pActiveCameraWorker->inactivate();
            _pActiveCameraWorker = _stack_CameraWorkerCon.getLast()->refer();
            if (_pActiveCameraWorker) {
                _pActiveCameraWorker->activate();
            } else {
                _stack_CameraWorkerCon.dump();
                throwGgafCriticalException("Universe::popCameraWork()  _stack_CameraWorker ���� pop() �������B");
            }
            pCon->close();
            pCameraWorker->onPoped();
            return pCameraWorker;
        } else {
            _stack_CameraWorkerCon.dump();
            throwGgafCriticalException("Universe::popCameraWork() pop()�����J�������[�N�́Apop()�O�Ɠ����J�������[�N�ł��BpCameraWorker="<<pCameraWorker->getName());
        }
    } else {
        _stack_CameraWorkerCon.dump();
        throwGgafCriticalException("Universe::popCameraWork()  _stack_CameraWorker ���� pop() �������ɂ���������");
    }
}

CameraWorker* Universe::resetCameraWork() {
    //DefaultCamWorker�܂ŃL���C�ɂ���
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
