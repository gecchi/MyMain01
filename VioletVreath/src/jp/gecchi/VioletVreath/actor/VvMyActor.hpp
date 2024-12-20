#ifndef VVMYACTOR_H_
#define VVMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

namespace VioletVreath {

template<class T>
class VvMyActor : public VvGeometricActor<T> {

public:
    VvMyActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvGeometricActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_MY)) {
            throwCriticalException("KIND_MY �ƁA�X�e�[�^�X���قȂ��Ă��܂��Bname="<<prm_name);
        }
#endif
    }


//    bool performMyHit(const GgafDx::GeometricActor* prm_pOther) {
//        GgafCore::Status* pThisStatus  = VvGeometricActor<T>::getStatus();
//        if (VvGeometricActor<T>::calcStamina(prm_pOther) <= 0) { //�̗͂������Ȃ�����
//            //���j�󂳂ꂽ�ꍇ��
//            VvGeometricActor<T>::setHitAble(false); //�����蔻�����
//            //�����G�t�F�N�g
//            UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
//            if ((prm_pOther->_pChecker->_kind) & KIND_ENEMY) {
//                //�����ʂ� MY*** �i���@�֘A�j �Ȃ��
//                GameGlobal::addDestroyedScoreBy(prm_pOther);
//                prm_pOther->notifyDestroyed(); //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����A�ƒʒm
//                UTIL::activateMyShipItemOf(prm_pOther);    //�A�C�e���o��
//                //UTIL::activateCommonEffectOf(prm_pOther, STAT_DestroyedEffectKind);  //�ґ��S�Ŕ���ɗL���Ȃ������G�t�F�N�g�i���̂Ƃ���Ȃ��H�j
//                UTIL::activateMyShipEffectOf(prm_pOther, STAT_DestroyedEffectKind);  //���_�\�����i�ґ��̓{�[�i�X���_�j
//                //UTIL::activateRevengeShotOf(this);     //�ł��Ԃ��e
//            }
//            return true;
//        } else {
//            //����j�󎞁A�_���[�W���󂯂��ꍇ��
//            //�_���[�W�G�t�F�N�g
//            UTIL::activateCommonEffectOf(this, STAT_DamagedEffectKind);
//            if ((prm_pOther->_pChecker->_kind) & KIND_ENEMY) {
//                //�����ʂ� MY*** �i���@�֘A�j �Ȃ��
//                GameGlobal::addDamagedScoreBy(prm_pOther); //�_���[�W�����_
//            }
//            if (pThisStatus->get(STAT_FlushAble)) { //�_���[�W�t���b�V�����邩�ǂ���
//                VvGeometricActor<T>::effectFlush(2); //�t���b�V���I
//            }
//            return false;
//        }
//    }



    virtual ~VvMyActor() {
    }
};

}

#endif /* VVMIKATAACTOR_H_ */
