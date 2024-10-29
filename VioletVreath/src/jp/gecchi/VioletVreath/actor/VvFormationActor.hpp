#ifndef VVFORMATIONACTOR_H_
#define VVFORMATIONACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

namespace VioletVreath {

template<class T>
class VvFormationActor : public T {
public:
    GgafDx::SeTransmitterForActor* _pSeTransmitter;
public:
    VvFormationActor(const char* prm_name, void* prm_pFuncResetStatus = nullptr)
            : T(prm_name) {
        _pSeTransmitter = nullptr;
        if (prm_pFuncResetStatus) {
            T::getStatus()->reset((GgafCore::Status* (*)(GgafCore::Status*))prm_pFuncResetStatus);
            _pSeTransmitter = NEW GgafDx::SeTransmitterForActor((GgafCore::Formation*)this);
            t_se_id se_id = T::getStatus()->get(STAT_ExplosionSeKind);
            if (se_id != SE_NOTHING) {
                _pSeTransmitter->set(se_id, MyStgUtil_SeKind::mapSeId[se_id]);
            }


#ifdef MY_DEBUG
//            if (!(T::_pChecker->_kind == KIND_FORMATION)) {
//                throwCriticalException("KIND_FORMATION �ƁA�X�e�[�^�X���قȂ��Ă��܂��Bname="<<prm_name);
//            }
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
        UTIL::activateEffectOf(this, STAT_ExplosionEffectKind);
        //�t�H�[���[�V�����S�Ŏ�����SE
        t_se_id se_id = T::getStatus()->get(STAT_ExplosionSeKind);
        if (se_id != SE_NOTHING) {
            _pSeTransmitter->play3D(se_id);
        }
        //�t�H�[���[�V�����S�ŃA�C�e���o��
        UTIL::activateItemOf(this);
        //�t�H�[���[�V�����S�ł������G�t�F�N�g�i�{�[�i�X�\�����j
        UTIL::activateEffectOf(this, STAT_DestroyedEffectKind);
        //�ґ��S�Ŏ��{�[�i�X���Z
        GameGlobal::addDestroyedScoreBy(this);
    }

    virtual ~VvFormationActor() {
        GGAF_DELETEARR_NULLABLE(_pSeTransmitter);
    }
};

}

#endif /* VVFORMATIONACTOR_H_ */
