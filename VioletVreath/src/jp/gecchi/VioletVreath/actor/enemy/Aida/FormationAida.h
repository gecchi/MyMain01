#ifndef FORMATIONAIDA_H_
#define FORMATIONAIDA_H_
#include "jp/ggaf/lib/actor/FkFormation.h"

namespace VioletVreath {

/**
 * �G�@�A�C�[�_�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationAida : public GgafLib::FkFormation {
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_spl_id �X�v���C����`ID(XXX.spl �� XXX)
     */
    FormationAida(const char* prm_name) ;

    virtual void onActive() override;

    virtual void onCallUpAida(EnemyAida* pEnemyAida) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationAida();
};

}
#endif /*FORMATIONAIDA_H_*/
