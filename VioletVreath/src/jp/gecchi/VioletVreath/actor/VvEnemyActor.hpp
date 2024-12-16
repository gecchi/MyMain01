#ifndef VVENEMYACTOR_H_
#define VVENEMYACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
namespace VioletVreath {

template<class T>
class VvEnemyActor : public VvGeometricActor<T> {

public:
    VvEnemyActor(const char* prm_name, const char* prm_model, void* prm_pFuncResetStatus = nullptr)
            : VvGeometricActor<T>(prm_name, prm_model, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind & KIND_ENEMRY)) {
            throwCriticalException("KIND_ENEMRY �ƁA�X�e�[�^�X���قȂ��Ă��܂��Bname="<<prm_name);
        }
#endif
        GgafCore::Status* pStatus = T::getStatus();
        GgafDx::SeTransmitterForActor* pSeXmtr = T::getSeXmtr();

    }

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor)  override {
        bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
        if (is_stamina_zero) {
            //�j�󂳂ꂽ��(�X�^�~�i <= 0)
            VvGeometricActor<T>::sayonara();
        } else {
            //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        }
    }

    /**
     * �G�L�����q�b�g���̕W���I�ȏ��� .
     * �E�j�󂳂ꂽ�ꍇ<br>
     * �E�j�󂳂�Ȃ������ꍇ<br>
     * ���ꂼ��A�����ʂ� MY*** �i���@�֘A�j�ł���ꍇ�ƁA�����łȂ��i�n�`�Ȃǁj�̏ꍇ�̋��ʏ���
     * @param prm_pOther �q�b�g��������̃A�N�^�[��n��
     * @return true:�X�^�~�i0(�j�󂳂ꂽ)/false:�X�^�~�i�c����(�j�󂳂�ĂȂ�)
     */
    bool performEnemyHit(const GgafDx::GeometricActor* prm_pOther) {
        GgafCore::Status* pThisStatus  = VvGeometricActor<T>::getStatus();
        if (VvGeometricActor<T>::calcStamina(prm_pOther) <= 0) { //�̗͂������Ȃ�����
            //���j�󂳂ꂽ�ꍇ��
            VvGeometricActor<T>::setHitAble(false); //�����蔻�����
            //�����G�t�F�N�g
            UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind); 
            if ((prm_pOther->_pChecker->_kind) & KIND_MY) {
                //�����ʂ� MY*** �i���@�֘A�j �Ȃ��
                GameGlobal::addDestroyedScoreBy(this);
                VvGeometricActor<T>::notifyDestroyed(); //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����A�ƒʒm
                UTIL::activateMyShipItemOf(this);    //�A�C�e���o��
                UTIL::activateCommonEffectOf(this, STAT_DestroyedEffectKind);  //�ґ��S�Ŕ���ɗL���Ȃ������G�t�F�N�g�i���̂Ƃ���Ȃ��H�j
                UTIL::activateMyShipEffectOf(this, STAT_DestroyedEffectKind);  //���_�\�����i�ґ��̓{�[�i�X���_�j
                UTIL::activateRevengeShotOf(this);     //�ł��Ԃ��e
            }
            return true;
        } else {
            //����j�󎞁A�_���[�W���󂯂��ꍇ��
            //�_���[�W�G�t�F�N�g
            UTIL::activateCommonEffectOf(this, STAT_DamagedEffectKind); 
            if ((prm_pOther->_pChecker->_kind) & KIND_MY) {
                //�����ʂ� MY*** �i���@�֘A�j �Ȃ��
                GameGlobal::addDamagedScoreBy(this); //�_���[�W�����_
            }
            if (pThisStatus->get(STAT_FlushAble)) { //�_���[�W�t���b�V�����邩�ǂ���
                VvGeometricActor<T>::effectFlush(2); //�t���b�V���I
            }
            return false;
        }
    }

    virtual ~VvEnemyActor() {
    }
};

}

#endif /* VVTEKIACTOR_H_ */
