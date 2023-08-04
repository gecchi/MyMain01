#ifndef FORMATIONDRASTEA001_H_
#define FORMATIONDRASTEA001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機アドラステアのフォーメーションその１ .
 * @version 1.00
 * @since 2012/08/06
 * @author Masatoshi Tsuge
 */
class FormationDrastea001 : public VvFormationActor<GgafLib::TreeFormation> {

public:
    FormationDrastea001(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~FormationDrastea001();
};

}
#endif /*FORMATIONDRASTEA001_H_*/
