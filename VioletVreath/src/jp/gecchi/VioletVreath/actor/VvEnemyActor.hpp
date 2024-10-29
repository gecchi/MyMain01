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

    /**
     * �G�L�����q�b�g���̕W���I�ȏ��� .
     * ���j�󂳂ꂽ�ꍇ��<br>
     * �E�j�󎞓��_���Z<br>
     * �E�����N���Z<br>
     * �E�A�C�e���o��             activateItemOf()<br>
     * �E���Ŏ�����G�t�F�N�g�J�n activateDestroyedEffectOf()<br>
     * �E�ł��Ԃ��e�o��           activateRevengeShotOf()<br>
     * �E�����G�t�F�N�g�o��       activateExplosionEffectOf()<br>
     * �E�ґ��S�Ŕ���<br>
     * �E�ґ��S�Ŏ��A�C�e���o��(STAT_ItemKind)<br>
     * ���j�󂳂�Ȃ������ꍇ��<br>
     * �E�_���[�W��^�������_���Z<br>
     * �E�_���[�W�t���b�V���\��       STAT_FlushAble<br>
     * �E�_���[�W������G�t�F�N�g�o�� activateDamagedEffectOf()<br>
     * @param prm_pOther �q�b�g��������̃A�N�^�[��n��
     * @return true:�X�^�~�i0(�j�󂳂ꂽ)/false:�X�^�~�i�c����(�j�󂳂�ĂȂ�)
     */
    bool performEnemyHit(const GgafDx::GeometricActor* prm_pOther) {
        GgafCore::Status* pThisStatus  = VvGeometricActor<T>::getStatus();
        if (VvGeometricActor<T>::calcStamina(prm_pOther) <= 0) { //�̗͂������Ȃ�����
            //���j�󂳂ꂽ�ꍇ��
            VvGeometricActor<T>::setHitAble(false); //�����蔻�����
            if ((prm_pOther->_pChecker->_kind) & KIND_MY) {
                //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
                GameGlobal::addDestroyedScoreBy(prm_pOther);
                VvGeometricActor<T>::notifyDestroyed(); //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����A�ƒʒm
                UTIL::activateItemOf(this);    //�A�C�e���o��
                UTIL::activateEffectOf(this, STAT_DestroyedEffectKind);  //�������G�t�F�N�g�i�{�[�i�X�\�����j
            }
            UTIL::activateRevengeShotOf(this);     //�ł��Ԃ��e
            UTIL::activateEffectOf(this, STAT_ExplosionEffectKind); //�����G�t�F�N�g
            return true;
        } else {
            //����j�󎞁A�_���[�W���󂯂��ꍇ��
            if ((prm_pOther->_pChecker->_kind) & KIND_MY) { //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
                GameGlobal::addDamagedScoreBy(prm_pOther); //�_���[�W�����_
            }
            if (pThisStatus->get(STAT_FlushAble)) { //�_���[�W�t���b�V�����邩�ǂ���
                VvGeometricActor<T>::effectFlush(2); //�t���b�V���I
            }
            UTIL::activateEffectOf(this, STAT_DamagedEffectKind); //�_���[�W�G�t�F�N�g
            return false;
        }
    }

    virtual ~VvEnemyActor() {
    }
};

}

#endif /* VVTEKIACTOR_H_ */
