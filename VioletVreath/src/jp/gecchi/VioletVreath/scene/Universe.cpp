#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Universe::Universe(const char* prm_name, Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
    _class_name = "Universe";
    pWorld_ = NULL;
    _TRACE_("Universe::Universe()");
    pCamWorkerManager_ = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pCamWorkerCon = (CameraWorkerConnection*)pCamWorkerManager_->connect("DefaultCamWorker");
    stack_CamWorkerCon_.push(pCamWorkerCon);
    pActiveCamWorker_ = pCamWorkerCon->fetch();
    getDirector()->addSubGroup(pActiveCamWorker_); //���f�t�H���g�J�������[�N

    //�y�߂��z
    //������Actor��Scene��NEW������܂����Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void Universe::initialize() {
    pWorld_ = createInFactory(World, "WORLD");
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
//    stack_CamWorkerCon_.dump();
    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ��Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ��Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+

    CameraWorkerConnection* pCon = connectToCameraWorkerManager(prm_pID);
    CameraWorker* pCamWorker = pCon->fetch();
    if (pCamWorker != pActiveCamWorker_) {
        //���݂� CameraWork ��񊈓���
        pActiveCamWorker_->onSwitchToOherCameraWork(); //�R�[���o�b�N
        pActiveCamWorker_->inactivate();
        //�p�����[�^�� CameraWork ��������
        pCamWorker->activate();
        pCamWorker->onSwitchCameraWork(); //�R�[���o�b�N
        if (getDirector()->getSubFirst()->getSub(pCamWorker)) {
            //�Q��ڈȍ~��
        } else {
            getDirector()->addSubGroup(pCamWorker); //����̓c���[�ɒǉ�
        }
        //�X�^�b�N�ɐς�
        stack_CamWorkerCon_.push(pCon);
        pActiveCamWorker_ = pCamWorker;
    } else {
#ifdef MY_DEBUG
        stack_CamWorkerCon_.dump();
        _TRACE_("���x����Universe::switchCameraWork("<<prm_pID<<") �����J�������[�N��A����push()���Ă��܂��̂Ŗ������܂��BpActiveCamWorker_="<<pActiveCamWorker_->getName());
#endif
    }
//    _TRACE_("switchCameraWork("<<prm_pID<<") end---");
//    stack_CamWorkerCon_.dump();
    return pCamWorker;

}

CameraWorker* Universe::undoCameraWork() {
//    _TRACE_("undoCameraWork begin---");
//    stack_CamWorkerCon_.dump();
    //    |      |                       |      |
    //    +------+                       |      |
    //    | ConC | ��Active      pop     |      |
    //    +------+           --------->  +------+
    //    | ConB |                       | ConB | ��Active(return)
    //    +------+                       +------+
    //    | ConA |                       | ConA |
    //    +------+                       +------+

    //�X�^�b�N������o��
    CameraWorkerConnection* pConn_now = stack_CamWorkerCon_.pop(); //pConn_now�͏�}��ConC���Ԃ�
    CameraWorkerConnection* pCon = stack_CamWorkerCon_.getLast(); //pCon�͏�}�Ō�����ConB���Ԃ�
    if (pCon) {
        CameraWorker* pCamWorker = pCon->fetch();
        if (pCamWorker != pActiveCamWorker_) {
            //���݂� CameraWork ��񊈓���
            pActiveCamWorker_->inactivate();
            pActiveCamWorker_->onUndoCameraWork();  //�R�[���o�b�N
            pActiveCamWorker_ = pCamWorker;
            if (pActiveCamWorker_) {
                //�P�O�� CameraWork ��������
                pActiveCamWorker_->onCameBackFromOtherCameraWork();  //�R�[���o�b�N
                pActiveCamWorker_->activate();
            } else {
                stack_CamWorkerCon_.dump();
                throwGgafCriticalException("Universe::undoCameraWork()  stack_CameraWorker_ ���� pop() �������B");
            }
            pConn_now->close();
//            _TRACE_("undoCameraWork end---");
//            stack_CamWorkerCon_.dump();
            return pActiveCamWorker_;
        } else {
#ifdef MY_DEBUG
            stack_CamWorkerCon_.dump();
            _TRACE_("���x����Universe::undoCameraWork() pop()�����J�������[�N�́Apop()�O�Ɠ����J�������[�N�ł��BpCamWorker="<<pCamWorker->getName());
#endif
            return pActiveCamWorker_;
        }
    } else {
        stack_CamWorkerCon_.dump();
        throwGgafCriticalException("Universe::undoCameraWork()  stack_CameraWorker_ ���� pop() �������ɂ���������");
    }
}

void Universe::resetCamWorker() {
    //DefaultCamWorker�܂ŃL���C�ɂ���
//    _TRACE_("resetCamWorker begin---");
//    stack_CamWorkerCon_.dump();
    for (int i = 0; i < 30; i++) {
        if (stack_CamWorkerCon_.p_ == 1) {
            break;
        } else {
            CameraWorkerConnection* pCon = stack_CamWorkerCon_.pop();
            pCon->close();
        }
    }
    P_CAM->setDefaultPosition();
    pActiveCamWorker_ = stack_CamWorkerCon_.getLast()->fetch();
    pActiveCamWorker_->setMoveTargetCamBy(P_CAM);
    pActiveCamWorker_->setMoveTargetCamVpBy(P_CAM->_pViewPoint);
    pActiveCamWorker_->angXY_nowCamUp_ = UTIL::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
    pActiveCamWorker_->move_target_XY_CAM_UP_ = pActiveCamWorker_->angXY_nowCamUp_;
    pActiveCamWorker_->activate();
//    _TRACE_("resetCamWorker end---");
//    stack_CamWorkerCon_.dump();
}


Universe::~Universe() {
    DELETE_IMPOSSIBLE_NULL(pCamWorkerManager_);
}
