#ifndef FORMATIONURYDIKE002_H_
#define FORMATIONURYDIKE002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "FormationUrydike.h"

namespace VioletVreath {

/**
 * 敵機ウリュディケ用フォーメーションその002 .
 * @version 1.00
 * @since 2015/01/26
 * @author Masatoshi Tsuge
 */
class FormationUrydike002 : public FormationUrydike {

public:
    GgafDx::CurveManufactureConnection** papCurveManufConn_;

    FormationUrydike002(const char* prm_name);

    virtual void processBehavior() override;
    virtual void onCalledUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) override;

    virtual ~FormationUrydike002();
};

}
#endif /*FORMATIONURYDIKE002_H_*/
