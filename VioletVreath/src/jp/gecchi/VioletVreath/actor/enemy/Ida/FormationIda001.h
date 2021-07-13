#ifndef FORMATIONIDA001_H_
#define FORMATIONIDA001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/FormationIda.h"

namespace VioletVreath {

/**
 * �G�@�C�[�_�p�t�H�[���[�V����001 .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class FormationIda001 : public FormationIda {

public:
    FormationIda001(const char* prm_name);

    void onCalledUpIda(EnemyIda* pEnemyIda) override;

    virtual void processBehavior() override;

    virtual ~FormationIda001();
};

}
#endif /*FORMATIONIDA001_H_*/
