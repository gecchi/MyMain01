#ifndef FORMATIONIDA_H_
#define FORMATIONIDA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/FkFormation.h"

namespace VioletVreath {

/**
 * �G�@�C�[�_�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class FormationIda : public VvFormationActor<GgafLib::FkFormation> {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_ldr_id �Ȑ��ړ��̏��ID(XXX.ldr �� XXX)
     */
    FormationIda(const char* prm_name, void* prm_pFuncResetStatus) ;

    virtual void onActive() override;

    virtual void onSummonIda(EnemyIda* pEnemyIda) = 0;

    virtual ~FormationIda();
};

}
#endif /*FORMATIONIDA_H_*/
