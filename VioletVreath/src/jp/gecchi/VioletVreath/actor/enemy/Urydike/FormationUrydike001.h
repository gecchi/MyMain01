#ifndef FORMATIONURYDIKE001_H_
#define FORMATIONURYDIKE001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "FormationUrydike.h"

namespace VioletVreath {

/**
 * 敵機ウリュディケ用フォーメーションその001 .
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class FormationUrydike001 : public FormationUrydike {

public:
    GgafDx::CurveManufactureConnection** papCurveManufConn_;

    FormationUrydike001(const char* prm_name);

    virtual void processBehavior() override;
    virtual void onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) override;

    virtual ~FormationUrydike001();
};

}
#endif /*FORMATIONURYDIKE001_H_*/
