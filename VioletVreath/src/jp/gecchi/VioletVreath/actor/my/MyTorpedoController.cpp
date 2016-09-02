#include "MyTorpedoController.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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
        GgafDestructActor(prm_name, nullptr) {
    _class_name = "MyTorpedoController";
    firing_num_ = 0;
    in_firing_ = false;
    pOrg_ = prm_pOrg;
    pLockonCtrler_ = prm_pLockonCtrler;
    papTorpedo_ = NEW MyTorpedo*[max_torpedo_num_];
    for (int i = 0; i < max_torpedo_num_; i++) {
        std::string name = std::string(prm_pOrg->getName())+"'s Torpedo("+XTOS(i)+")";
        papTorpedo_[i] = NEW MyTorpedo(name.c_str(), this);
        papTorpedo_[i]->inactivate();
        addSubGroup(papTorpedo_[i]);
    }

    pDepo_TorpedoBlast_ = NEW GgafActorDepository("DP_TorpedoBlast");
    for (int i = 0; i < max_torpedo_num_*2; i++) {
        std::string name = std::string(prm_pOrg->getName())+"'s TorpedoBlast("+XTOS(i)+")";
        pDepo_TorpedoBlast_->put(NEW MyTorpedoBlast(name.c_str()));
    }
    addSubGroup(pDepo_TorpedoBlast_);
}

void MyTorpedoController::initialize() {
}

void MyTorpedoController::onActive() {
    in_firing_ = false;
    for (int i = 0; i < max_torpedo_num_; i++) {
        papTorpedo_[i]->pTarget_ = nullptr;
        papTorpedo_[i]->inactivate();
    }
    pDepo_TorpedoBlast_->reset();
}

void MyTorpedoController::processBehavior() {
    in_firing_ = false;
    for (int i = 0; i < firing_num_; i++) {
        if (papTorpedo_[i]->isActive()) {
            in_firing_ = true;
            break;
        }
    }
}

void MyTorpedoController::processJudgement() {
}

void MyTorpedoController::onInactive() {
    in_firing_ = false;
    for (int i = 0; i < max_torpedo_num_; i++) {
        papTorpedo_[i]->pTarget_ = nullptr;
        papTorpedo_[i]->inactivate();
    }
    pDepo_TorpedoBlast_->reset();
}

bool MyTorpedoController::fire() {
    if (!in_firing_ && MyTorpedoController::torpedo_num_ > 0) {
        in_firing_ = true;
        int target_num = pLockonCtrler_->pRingTarget_->length(); //���b�N�I�����̃^�[�Q�b�g��
        firing_num_ = MyTorpedoController::torpedo_num_; //target_num < 4 ? 4 : target_num;

        static const coord r = PX_C(20);              //���ˏ󋛗��o�����A�I�v�V�����Ƃ̔��a����

        if (MyTorpedoController::torpedo_num_ == 1) {
            //�������ˉ\�� �� 1�̏ꍇ�̂݁A���ʂɑO���i���[�U�[���˕����j�ɔ���
            float vx, vy, vz;
            UTIL::convRzRyToVector(pOrg_->_rz, pOrg_->_ry, vx, vy, vz);
            papTorpedo_[0]->place(pOrg_->_x + (vx * r),
                                     pOrg_->_y + (vy * r),
                                     pOrg_->_z + (vz * r));
            if (target_num == 0) {
                papTorpedo_[0]->pTarget_ = nullptr;
            } else {
                papTorpedo_[0]->pTarget_ = pLockonCtrler_->pRingTarget_->getNext(0);
            }
            papTorpedo_[0]->getKuroko()->setRzRyMvAng(pOrg_->_rz, pOrg_->_ry); //��ԕ���
            papTorpedo_[0]->activate();

        } else {
            static const angle expanse = D_ANG(90);       //���ˏƎ˔͈͊p�x(���}�̊p��)
            //
            //      :
            //      :      ����
            //      :    �^
            //      :  �^
            //      :�^
            //     ��  ��   �c �����pexpanse        ���O��
            //      :�_
            //      :  �_
            //      :    �_
            //      :      ����
            //      :
            //
            static const angle expanse_rz = (D180ANG - expanse)/2;

            angle ang_way = D0ANG;                        //���ˏ󋛗��̈�ڂ̊J�n�A���O�� 0=�^������,90=�E����,180=�ォ��
            angle ang_way_offset = D360ANG / firing_num_; //���ˏ󋛗��Ƌ����̊Ԃ̂Ȃ��A���O��
            D3DXMATRIX matRotZ; //���݂̃I�v�V�����̌�������90�x���Ɍ�����]�s��
            UTIL::setWorldMatrix_RzRy(UTIL::simplifyAng(pOrg_->_rz - D90ANG), pOrg_->_ry,
                                      matRotZ);
            float vx, vy, vz;
            coord x1, y1, z1, x2, y2, z2;
            coord rz,ry;
            for (int i = 0; i < firing_num_; i++) {
                UTIL::convRzRyToVector(expanse_rz, ang_way, vx, vy, vz);
                x1 = vx * r;
                y1 = vy * r;
                z1 = vz * r;
                //(x1,y1,z1) �̓I�v�V�����̓��̏�̃��K�z����̍��W�A
                //�����RZ��-90�x��]�������K�z�����I�v�V�����̑O���Ɍ����遨(x2,y2,z2)
                x2 = x1*matRotZ._11 + y1*matRotZ._21 + z1*matRotZ._31;
                y2 = x1*matRotZ._12 + y1*matRotZ._22 + z1*matRotZ._32;
                z2 = x1*matRotZ._13 + y1*matRotZ._23 + z1*matRotZ._33;
                papTorpedo_[i]->place(pOrg_->_x + x2,
                                         pOrg_->_y + y2,
                                         pOrg_->_z + z2);
                if (target_num == 0) {
                    papTorpedo_[i]->pTarget_ = nullptr;
                } else {
                    papTorpedo_[i]->pTarget_ = pLockonCtrler_->pRingTarget_->getNext(i);
                }
                UTIL::convVectorToRzRy(x2, y2, z2, rz, ry);
                papTorpedo_[i]->getKuroko()->setRzRyMvAng(rz, ry); //��ԕ���
                papTorpedo_[i]->activate();
                ang_way = UTIL::addAng(ang_way, ang_way_offset); //���̕��ˏ�̋�����
            }
        }

        return true;
    } else {
        return false;
    }
}

MyTorpedoController::~MyTorpedoController() {
    GGAF_DELETEARR(papTorpedo_);
}
