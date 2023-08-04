#ifndef FORMATIONERES002_H_
#define FORMATIONERES002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 */
class FormationEres002 : public VvFormationActor<GgafLib::TreeFormation> {

public:
    FormationEres002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~FormationEres002();
};

}
#endif /*FORMATIONERES002_H_*/
