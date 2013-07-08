#ifndef FORMATIONERES002_H_
#define FORMATIONERES002_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 */
class FormationEres002 : public GgafLib::TreeFormation {

public:
    FormationEres002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationEres002();
};

}
#endif /*FORMATIONERES002_H_*/
