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
        throwGgafCriticalException("Spacetime::CameraWorkerHistory::pop() POP�������ł�");
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
    bringDirector()->addSubGroup(pActiveCamWorker_); //���f�t�H���g�J�������[�N
    //�y�߂��z
    //������Actor��Scene��NEW�����Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
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
            //changeCameraWork �Ő؂�ւ���Ă����ꍇ
            pActiveCamWorker_->onSwitchCameraWork(); //�R�[���o�b�N
        } else {
            //undoCameraWork�Ő؂�ւ���Ă����ꍇ
            pActiveCamWorker_->onSwitchCameraWork(); //�R�[���o�b�N
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
    //    |      |            push ConC        | ConC | ��Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ��Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+
    CameraWorkerConnection* pCon = (CameraWorkerConnection*)pCamWorkerManager_->connect(prm_pID, getCamera());
    CameraWorker* pCamWorker = pCon->peek();
    if (pCamWorker != pActiveCamWorker_) {
        _TRACE_("��pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" �͈ꎞ�񊈓��őҋ@");
        //���݂� CameraWork ��񊈓���
        pActiveCamWorker_->onChangedToOtherCameraWork(); //�R�[���o�b�N
        pActiveCamWorker_->inactivate();
        //�p�����[�^�� CameraWork ��������
        pCamWorker->activate();
        pCamWorker->frame_of_behaving_since_onSwitch_ = 0; //switch��t���[���J�E���^���Z�b�g
        if (bringDirector()->getSubFirst()->getSub(pCamWorker)) {
            //�Q��ڈȍ~��
        } else {
            bringDirector()->addSubGroup(pCamWorker); //����̓c���[�ɒǉ�
        }
        //�X�^�b�N�ɐς�
        stack_CamWorkerConnection_.push(pCon);
        pActiveCamWorker_ = pCamWorker;
        _TRACE_("�VpActiveCamWorker_="<<pActiveCamWorker_->getName()<<" �͏㏑���Ŋ������");
    } else {
#ifdef MY_DEBUG
        stack_CamWorkerConnection_.dump();
        _TRACE_("���x����Spacetime::changeCameraWork("<<prm_pID<<") �����J�������[�N��A����push()���Ă��܂��̂Ŗ������܂��BpActiveCamWorker_="<<pActiveCamWorker_->getName());
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
    //    | ConC | ��Active      pop     |      |
    //    +------+           --------->  +------+
    //    | ConB |                       | ConB | ��Active(return)
    //    +------+                       +------+
    //    | ConA |                       | ConA |
    //    +------+                       +------+

    //�X�^�b�N������o��
    CameraWorkerConnection* pConn_now = stack_CamWorkerConnection_.pop(); //pConn_now�͏�}��ConC���Ԃ�
    CameraWorkerConnection* pCon = stack_CamWorkerConnection_.getLast(); //pCon�͏�}�Ō�����ConB���Ԃ�
    if (pCon) {
        CameraWorker* pCamWorker = pCon->peek();
        if (pCamWorker != pActiveCamWorker_) {
            //���݂� CameraWork ��񊈓���
            _TRACE_("��pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" �͂����Ȃ�");
            pActiveCamWorker_->onChangedToOtherCameraWork();  //�R�[���o�b�N
            pActiveCamWorker_->inactivate();
            pActiveCamWorker_ = pCamWorker;
            if (pActiveCamWorker_) {
                //�P�O�� CameraWork ��������
                pActiveCamWorker_->activate();
            } else {
                stack_CamWorkerConnection_.dump();
                throwGgafCriticalException("stack_CameraWorker_ ���� pop() �������B");
            }
            pConn_now->close();
//            _TRACE_("undoCameraWork end---");
//            stack_CamWorkerConnection_.dump();
            _TRACE_("���X�^�b�N�� pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" ���A�N�e�B�u��");
            return pActiveCamWorker_;
        } else {
#ifdef MY_DEBUG
            stack_CamWorkerConnection_.dump();
            _TRACE_("���x����Spacetime::undoCameraWork() pop()�����J�������[�N�́Apop()�O�Ɠ����J�������[�N�ł��BpCamWorker="<<pCamWorker->getName());
#endif
            return pActiveCamWorker_;
        }
    } else {
        stack_CamWorkerConnection_.dump();
        throwGgafCriticalException("stack_CameraWorker_ ���� pop() �������ɂ���������");
    }
}

void Spacetime::resetCamWorker() {
    //DefaultCamWorker�܂ŃL���C�ɂ���
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
