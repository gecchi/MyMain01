#ifndef CURSORSCREENCONFIGMENU_H_
#define CURSORSCREENCONFIGMENU_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * スクリーンコンフィグのカーソル .
 * @version 1.00
 * @since 2013/06/06
 * @author Masatoshi Tsuge
 */
class CursorScreenConfigMenu : public GgafLib::DefaultBoardActor {

public:
    CursorScreenConfigMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorScreenConfigMenu();
};

}
#endif /*CURSORSCREENCONFIGMENU_H_*/

