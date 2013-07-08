#ifndef FORMATIONETIS001_H_
#define FORMATIONETIS001_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

#define NUM_ETIS_FORMATION001 10
/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 */
class FormationEtis001 : public GgafLib::TreeFormation {

    EnemyEtis* apEnemyEtis_[NUM_ETIS_FORMATION001];

public:
    FormationEtis001(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationEtis001();
};

}
#endif /*FORMATIONETIS001_H_*/
