#ifndef FORMATIONIDA_H_
#define FORMATIONIDA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/FkFormation.h"

namespace VioletVreath {

/**
 * �G�@�C�[�_�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class FormationIda : public GgafLib::FkFormation {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_spl_id �X�v���C����`ID(XXX.spl �� XXX)
     */
    FormationIda(const char* prm_name) ;

    virtual void onActive() override;

    virtual void onCallUpIda(EnemyIda* pEnemyIda) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual ~FormationIda();
};

}
#endif /*FORMATIONIDA_H_*/
