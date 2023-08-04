#ifndef FORMATIONETIS001_H_
#define FORMATIONETIS001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

#define NUM_ETIS_FORMATION001 10
/**
 * フォーメーションアクタークラス .
 */
class FormationEtis001 : public VvFormationActor<GgafLib::TreeFormation> {

    EnemyEtis* apEnemyEtis_[NUM_ETIS_FORMATION001];

public:
    FormationEtis001(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationEtis001();
};

}
#endif /*FORMATIONETIS001_H_*/
