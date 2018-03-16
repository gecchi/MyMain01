#ifndef FORMATIONGERIA_H_
#define FORMATIONGERIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * ���g�͏o���|�C���g�̒��S
 */
class FormationGeria : public GgafLib::DefaultGeometricActor {


public:
    /** �Q���A�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_;

public:

    FormationGeria(const char* prm_name, int prm_nGeriaStock);


    EnemyGeria* summonGeria();

    virtual ~FormationGeria();
};

}
#endif /*FORMATIONGERIA_H_*/
