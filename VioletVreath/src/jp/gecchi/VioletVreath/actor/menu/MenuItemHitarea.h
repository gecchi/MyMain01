#ifndef MENUITEMHITAREA_H_
#define MENUITEMHITAREA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * ƒƒjƒ…[€–Ú‚Ì“–‚½‚è”»’è .
 * @version 1.00
 * @since 2022/08/08
 * @author Masatoshi Tsuge
 */
class MenuItemHitarea : public GgafLib::DefaultGeometricActor {
public:
    GgafDx::FigureActor* _pItem;


public:
    MenuItemHitarea(GgafDx::FigureActor* prm_pItem);

    void initialize() override;

    void processSettlementBehavior() override;

    void processPreJudgement() override;

    virtual ~MenuItemHitarea();
};

}
#endif /*MENUITEMHITAREA_H_*/

