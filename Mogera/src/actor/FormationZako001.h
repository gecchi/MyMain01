#ifndef FORMATIONZAKO001_H_
#define FORMATIONZAKO001_H_
#include "Mogera.h"
#include <actor/FormationZako.h>

namespace Mogera {

/**
 * 敵機雑魚用フォーメーションその001 .
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class FormationZako001 : public FormationZako {

public:
    GgafDx::CurveManufactureConnection** papCurveManufConn_;

    FormationZako001(const char* prm_name);

    virtual void processBehavior() override;
    virtual void onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) override;

    virtual ~FormationZako001();
};

}
#endif /*FORMFORMATIONZAKO001_H_ATIONURYDIKE001_H_*/
