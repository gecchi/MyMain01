#ifndef FORMATIONOEBIUS001_H_
#define FORMATIONOEBIUS001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス用フォーメーションその001 .
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class FormationOebius001 : public FormationOebius {

    /** 隣の列との間隔 */
    double d_next_col_;

public:
    GgafLib::SplineManufactureConnection** papSplManufConn_;

    FormationOebius001(const char* prm_name);

    virtual void processBehavior() override;
    virtual void onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDxCore::GgafDxDrawableActor* prm_pActor) override;

    virtual ~FormationOebius001();
};

}
#endif /*FORMATIONOEBIUS001_H_*/
