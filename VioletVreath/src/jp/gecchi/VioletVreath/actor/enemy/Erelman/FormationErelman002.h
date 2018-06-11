#ifndef FORMATIONERELMAN002_H_
#define FORMATIONERELMAN002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/FormationErelman.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス用フォーメーションその002 .
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class FormationErelman002 : public FormationErelman {

public:
    GgafLib::SplineManufactureConnection** papSplManufConn_;

    FormationErelman002(const char* prm_name, EnemyErelmanController* prm_pController);

    virtual void processBehavior() override;

    virtual void onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) override;

    virtual void onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) override;

    virtual ~FormationErelman002();
};

}
#endif /*FORMATIONERELMAN002_H_*/
