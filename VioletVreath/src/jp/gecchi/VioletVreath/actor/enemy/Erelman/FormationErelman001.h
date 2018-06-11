#ifndef FORMATIONERELMAN001_H_
#define FORMATIONERELMAN001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/FormationErelman.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス用フォーメーションその001 .
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class FormationErelman001 : public FormationErelman {

public:
    GgafLib::SplineManufactureConnection** papSplManufConn_;

    FormationErelman001(const char* prm_name, EnemyErelmanController* prm_pController);

    virtual void processBehavior() override;
    virtual void onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) override;

    virtual ~FormationErelman001();
};

}
#endif /*FORMATIONERELMAN001_H_*/
