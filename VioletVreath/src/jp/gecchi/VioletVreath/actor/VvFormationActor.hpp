#ifndef VVFORMATIONACTOR_H_
#define VVFORMATIONACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "VvGeometricActor.hpp"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

namespace VioletVreath {

template<class T>
class VvFormationActor : public VvGeometricActor<T> {

public:
    VvFormationActor(const char* prm_name, void* prm_pFuncResetStatus)
            : VvGeometricActor<T>(prm_name, prm_pFuncResetStatus) {
#ifdef MY_DEBUG
        if (!(T::_pChecker->_kind == KIND_FORMATION)) {
            throwCriticalException("KIND_FORMATION �ƁA�X�e�[�^�X���قȂ��Ă��܂��Bname="<<prm_name);
        }
#endif
        GgafCore::Status* pStatus = T::getStatus();
        GgafDx::SeTransmitterForActor* pSeXmtr = T::getSeXmtr();
    }

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafDx::GeometricActor* prm_pActor_last_destroyed) override {
        //�t�H�[���[�V�����S�Ŕ����G�t�F�N�g
        UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
        //�t�H�[���[�V�����S�ŃA�C�e���o��
        UTIL::activateCommonItemOf(this);
        //�t�H�[���[�V�����S�ł������G�t�F�N�g�i�{�[�i�X�\�����j
        UTIL::activateCommonEffectOf(this, STAT_DestroyedEffectKind);
        //�ґ��S�Ŏ��{�[�i�X���Z
        GameGlobal::addDestroyedScoreBy(this);
    }

    virtual ~VvFormationActor() {
    }
};

}

#endif /* VVFORMATIONACTOR_H_ */
