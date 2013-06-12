#ifndef SUPCURSORSCREENCONFIGMENU_H_
#define SUPCURSORSCREENCONFIGMENU_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * スクリーンコンフィグのカーソル .
 * @version 1.00
 * @since 2013/06/06
 * @author Masatoshi Tsuge
 */
class SupCursorScreenConfigMenu : public GgafLib::DefaultBoardActor {

public:
    SupCursorScreenConfigMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~SupCursorScreenConfigMenu();
};

}
#endif /*SUPCURSORSCREENCONFIGMENU_H_*/

