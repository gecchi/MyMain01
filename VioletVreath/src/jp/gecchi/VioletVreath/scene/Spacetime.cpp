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

Spacetime::CameraWorkerConnectionStack::CameraWorkerConnectionStack() {
    p_ = 0;
    for (int i = 0; i < 30; i++) {
        apCamWorkerConnection_[i] = nullptr;
    }
}
CameraWorkerConnection* Spacetime::CameraWorkerConnectionStack::getLast() {
    if (p_ == 0) {
        return nullptr;
    } else {
        return apCamWorkerConnection_[p_-1];
    }
}
void Spacetime::CameraWorkerConnectionStack::push(CameraWorkerConnection* prm_pCamWorkerCon) {
    if (p_ > 30-1) {
        throwGgafCriticalException("CameraWorkerConnectionStack::push("<<prm_pCamWorkerCon->getIdStr()<<") �X�^�b�N���g���؂�܂����B");
    }
    apCamWorkerConnection_[p_] = prm_pCamWorkerCon;
    p_++;
}
CameraWorkerConnection* Spacetime::CameraWorkerConnectionStack::pop() {
    if (p_ == 0) {
        throwGgafCriticalException("CameraWorkerConnectionStack::pop() �|�b�v�������ł�");
    } else {
        p_--;
        CameraWorkerConnection* r = apCamWorkerConnection_[p_];
        apCamWorkerConnection_[p_] = nullptr;
        return r;
    }
}
void Spacetime::CameraWorkerConnectionStack::clear() {
    p_ = 0;
    for (int i = 0; i < 30; i++) {
        apCamWorkerConnection_[i] = nullptr;
    }
}

void Spacetime::CameraWorkerConnectionStack::dump() {
    _TRACE_("CameraWorkerConnectionStack p_="<<p_);
    for (int i = 0; i < 30; i++) {
        if (apCamWorkerConnection_[i]) {
            _TRACE_("apCamWorkerConnection_["<<i<<"]="<<(apCamWorkerConnection_[i]->getIdStr()));
        }
    }
}
Spacetime::CameraWorkerConnectionStack::~CameraWorkerConnectionStack() {
    clear();
}

/////////////////////////////////////////////////

Spacetime::Spacetime(const char* prm_name, Camera* prm_pCamera) : DefaultSpacetime(prm_name, prm_pCamera) {
    _class_name = "Spacetime";
    pWorld_ = nullptr;
    _TRACE_("Spacetime::Spacetime()");
    pCamWorkerManager_ = NEW CameraWorkerManager("CameraWorkerManager");

    CameraWorkerConnection* pCamWorkerCon = (CameraWorkerConnection*)pCamWorkerManager_->connect("DefaultCamWorker", this);
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
    _TRACE_("Spacetime::initialize()");
}

void Spacetime::processBehavior() {
    if (!pActiveCamWorker_->_was_initialize_flg) {
        pActiveCamWorker_->initialize();
    }
    if (pActiveCamWorker_->isJustChangedToActive()) {
        if (pActiveCamWorker_->frame_of_behaving_since_onSwitch_== 0) {
            pActiveCamWorker_->onSwitchCameraWork(); //�R�[���o�b�N
        } else {
            pActiveCamWorker_->onCameBackFromOtherCameraWork(); //�R�[���o�b�N
        }
    }

    pActiveCamWorker_->frame_of_behaving_since_onSwitch_++;
    DefaultSpacetime::processBehavior();
}

void Spacetime::processJudgement() {
    DefaultSpacetime::processJudgement();
}

CameraWorker* Spacetime::switchCameraWork(const char* prm_pID) {
    _TRACE_("Spacetime::switchCameraWork("<<prm_pID<<") ");
//    stack_CamWorkerConnection_.dump();
    //    |      |                             |      |
    //    |      |                             +------+
    //    |      |            push ConC        | ConC | ��Active(return)
    //    +------+            --------->       +------+
    //    | ConB | ��Active                    | ConB |
    //    +------+                             +------+
    //    | ConA |                             | ConA |
    //    +------+                             +------+

    CameraWorkerConnection* pCon = getConnection_CameraWorkerManager(prm_pID);
    CameraWorker* pCamWorker = pCon->peek();
    if (pCamWorker != pActiveCamWorker_) {
        _TRACE_("��pActiveCamWorker_="<<pActiveCamWorker_->getName()<<" �͈ꎞ�񊈓��őҋ@");
        //���݂� CameraWork ��񊈓���
        pActiveCamWorker_->onSwitchToOtherCameraWork(); //�R�[���o�b�N
        pActiveCamWorker_->inactivate();
        //�p�����[�^�� CameraWork ��������
        pCamWorker->activate();
        pCamWorker->frame_of_behaving_since_onSwitch_ = 0; //switch��t���[���J�E���^���Z�b�g
//        pCamWorker->onSwitchCameraWork(); //�R�[���o�b�N
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
        _TRACE_("���x����Spacetime::switchCameraWork("<<prm_pID<<") �����J�������[�N��A����push()���Ă��܂��̂Ŗ������܂��BpActiveCamWorker_="<<pActiveCamWorker_->getName());
#endif
    }
//    stack_CamWorkerConnection_.dump();
    return pCamWorker;

}

CameraWorker* Spacetime::undoCameraWork() {
    _TRACE_("Spacetime::undoCameraWork()");
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

            pActiveCamWorker_->inactivate();
            pActiveCamWorker_->onUndoCameraWork();  //�R�[���o�b�N
            pActiveCamWorker_ = pCamWorker;
            if (pActiveCamWorker_) {
                //�P�O�� CameraWork ��������
//                pActiveCamWorker_->onCameBackFromOtherCameraWork();  //�R�[���o�b�N
                pActiveCamWorker_->activate();
            } else {
                stack_CamWorkerConnection_.dump();
                throwGgafCriticalException("Spacetime::undoCameraWork()  stack_CameraWorker_ ���� pop() �������B");
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
        throwGgafCriticalException("Spacetime::undoCameraWork()  stack_CameraWorker_ ���� pop() �������ɂ���������");
    }
}

void Spacetime::resetCamWorker() {
    //DefaultCamWorker�܂ŃL���C�ɂ���
   _TRACE_("Spacetime::resetCamWorker()");
//    stack_CamWorkerConnection_.dump();
    for (int i = 0; i < 30; i++) {
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
    GGAF_DELETE(pCamWorkerManager_);
}
