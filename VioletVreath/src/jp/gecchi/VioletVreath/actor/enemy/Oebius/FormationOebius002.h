#ifndef FORMATIONOEBIUS002_H_
#define FORMATIONOEBIUS002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス用フォーメーションその002 .
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class FormationOebius002 : public FormationOebius {

public:
    GgafLib::SplineManufactureConnection** papSplManufConn_;
    FormationOebius002(const char* prm_name);

    virtual void processBehavior() override;


    virtual void onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDxCore::GgafDxDrawableActor* prm_pActor) override;

    virtual ~FormationOebius002();
};

}
#endif /*FORMATIONOEBIUS002_H_*/
