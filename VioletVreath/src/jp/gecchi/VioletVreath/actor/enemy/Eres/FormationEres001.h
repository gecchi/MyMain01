#ifndef FORMATIONERES001_H_
#define FORMATIONERES001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 */
class FormationEres001 : public VvFormationActor<GgafLib::TreeFormation> {

public:
    FormationEres001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~FormationEres001();
};

}
#endif /*FORMATIONERES001_H_*/
