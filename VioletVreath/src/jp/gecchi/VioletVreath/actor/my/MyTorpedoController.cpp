#include "stdafx.h"
#include "MyTorpedoController.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "MyTorpedo.h"
#include "MyTorpedoBlast.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;
int MyTorpedoController::max_torpedo_num_ = 8;
int MyTorpedoController::torpedo_num_ = 0;

MyTorpedoController::MyTorpedoController(const char* prm_name,
                                         GgafDxCore::GgafDxGeometricActor* prm_pOrg,
                                         MyLockonController* prm_pLockonCtrler) :
        GgafDummyActor(prm_name, nullptr) {
    _class_name = "MyTorpedoController";
    firing_num_ = 0;
    in_firing_ = false;
    pOrg_ = prm_pOrg;
    pLockonCtrler_ = prm_pLockonCtrler;
    papTorpedo_ = NEW MyTorpedo*[max_torpedo_num_];
    for (int i = 0; i < max_torpedo_num_; i++) {
        std::string name = std::string(prm_pOrg->getName())+"'s Torpedo("+XTOS(i)+")";
        papTorpedo_[i] = NEW MyTorpedo(name.c_str(), this);
        papTorpedo_[i]->inactivateImmed();
        addSubGroup(papTorpedo_[i]);
    }

    pDepo_TorpedoBlast_ = NEW GgafActorDepository("DP_TorpedoBlast");
    for (int i = 0; i < max_torpedo_num_*2; i++) {
        std::string name = std::string(prm_pOrg->getName())+"'s TorpedoBlast("+XTOS(i)+")";
        MyTorpedoBlast* pTorpedoBlast = NEW MyTorpedoBlast(name.c_str());
        pTorpedoBlast->inactivateImmed();
        pDepo_TorpedoBlast_->addSubLast(pTorpedoBlast);
    }
    addSubGroup(pDepo_TorpedoBlast_);
}

void MyTorpedoController::initialize() {
}

void MyTorpedoController::onActive() {
    in_firing_ = false;
    for (int i = 0; i < max_torpedo_num_; i++) {
        papTorpedo_[i]->pTarget_ = nullptr;
        papTorpedo_[i]->inactivateImmed();
    }
    pDepo_TorpedoBlast_->reset();
}

void MyTorpedoController::processBehavior() {
    if (in_firing_) {
        in_firing_ = false;
        for (int i = 0; i < firing_num_; i++) {
            if (papTorpedo_[i]->isActiveInTheTree()) {
                in_firing_ = true;
                break;
            }
        }
    }
}

void MyTorpedoController::processJudgement() {
}

void MyTorpedoController::onInactive() {
    in_firing_ = false;
    for (int i = 0; i < max_torpedo_num_; i++) {
        papTorpedo_[i]->pTarget_ = nullptr;
        papTorpedo_[i]->inactivateImmed();
    }
    pDepo_TorpedoBlast_->reset();
}

bool MyTorpedoController::fire() {
    if (!in_firing_ && MyTorpedoController::torpedo_num_ > 0) {
        //
        //      :
        //      :      ����
        //      :    �^
        //      :  �^
        //      :�^
        //     �I  �� �c �����pexpanse        ���O��
        //      :�_
        //      :  �_
        //      :    �_
        //      :      ����
        //      :
        //
        in_firing_ = true;
        int target_num = pLockonCtrler_->pRingTarget_->length(); //���b�N�I�����̃^�[�Q�b�g��
        firing_num_ = MyTorpedoController::torpedo_num_; //target_num < 4 ? 4 : target_num;
        static const angle expanse = D_ANG(90);       //���ˏƎ˔͈͊p�x(��}�̊p��)
        static const angle expanse_rz = (D180ANG - expanse)/2;
        angle ang_way = D0ANG;                        //���ˏ󋛗��̈�ڂ̊J�n�A���O�� 0=�^������,90=�E����,180=�ォ��
        angle ang_way_offset = D360ANG / firing_num_; //���ˏ󋛗��Ƌ����̊Ԃ̂Ȃ��A���O��
        static const coord r = PX_C(20);              //���ˏ󋛗��o�����A�I�v�V�����Ƃ̔��a����
        D3DXMATRIX matRotZ; //���݂̃I�v�V�����̌�������90�x���Ɍ�����]�s��
        UTIL::setWorldMatrix_RzRy(UTIL::simplifyAng(pOrg_->_RZ - D90ANG), pOrg_->_RY,
                                  matRotZ);
        float vx, vy, vz;
        coord X1,Y1,Z1, X2, Y2, Z2;
        coord RZ,RY;
        for (int i = 0; i < firing_num_; i++) {
            UTIL::convRzRyToVector(expanse_rz, ang_way, vx, vy, vz);
            X1 = vx * r;
            Y1 = vy * r;
            Z1 = vz * r;
            //(X1,Y1,Z1) �̓I�v�V�����̓��̏�̃��K�z����̍��W�A
            //�����RZ��-90�x��]�������K�z�����I�v�V�����̑O���Ɍ����遨(X2,Y2,Z2)
            X2 = X1*matRotZ._11 + Y1*matRotZ._21 + Z1*matRotZ._31;
            Y2 = X1*matRotZ._12 + Y1*matRotZ._22 + Z1*matRotZ._32;
            Z2 = X1*matRotZ._13 + Y1*matRotZ._23 + Z1*matRotZ._33;
            papTorpedo_[i]->locate(pOrg_->_X + X2,
                                   pOrg_->_Y + Y2,
                                   pOrg_->_Z + Z2);
            if (target_num == 0) {
                papTorpedo_[i]->pTarget_ = nullptr;
            } else {
                papTorpedo_[i]->pTarget_ = pLockonCtrler_->pRingTarget_->getNext(i);
            }
            UTIL::convVectorToRzRy(X2, Y2, Z2, RZ, RY);
            papTorpedo_[i]->_pKurokoA->setRzRyMvAng(RZ, RY); //��ԕ���
            papTorpedo_[i]->activate();
            ang_way = UTIL::addAng(ang_way, ang_way_offset); //���̕��ˏ�̋�����
        }
        return true;
    } else {
        return false;
    }
}

MyTorpedoController::~MyTorpedoController() {
    GGAF_DELETEARR(papTorpedo_);
}
