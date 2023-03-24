#ifndef FORMATIONERES001_H_
#define FORMATIONERES001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 */
class FormationEres001 : public GgafLib::TreeFormation {

public:
    FormationEres001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual ~FormationEres001();
};

}
#endif /*FORMATIONERES001_H_*/
