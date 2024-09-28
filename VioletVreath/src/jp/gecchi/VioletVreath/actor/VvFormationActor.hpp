#ifndef VVFORMATIONACTOR_H_
#define VVFORMATIONACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

namespace VioletVreath {

template<class T>
class VvFormationActor : public T {

public:
    VvFormationActor(const char* prm_name, void* prm_pFuncResetStatus = nullptr)
            : T(prm_name) {

        if (prm_pFuncResetStatus) {
            T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pFuncResetStatus);
#ifdef MY_DEBUG
            //if (!(T::_pChecker->_kind & KIND_FORMATION)) {
            if (!(T::getDefaultKind() & KIND_FORMATION)) {
                throwCriticalException("KIND_FORMATION �ƁA�X�e�[�^�X���قȂ��Ă��܂��Bname="<<prm_name);
            }
#endif
        } else {
            T::getStatus()->reset(StatusReset(Default));
        }
    }

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override {
        //�t�H�[���[�V�����S�Ŕ����G�t�F�N�g
        UTIL::activateExplosionEffectOf(this);
        //�t�H�[���[�V�����S�ŃA�C�e���o��
        UTIL::activateItemOf(this);
        //�t�H�[���[�V�����S�ł������G�t�F�N�g�i�{�[�i�X�\�����j
        UTIL::activateDestroyedEffectOf(this);
        //�ґ��S�Ŏ��{�[�i�X���Z
        GameGlobal::addDestroyedScoreBy(this);
    }

    virtual ~VvFormationActor() {
    }
};

}

#endif /* VVFORMATIONACTOR_H_ */
