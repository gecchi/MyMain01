#ifndef CURSORPAUSEMENU_H_
#define CURSORPAUSEMENU_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"



namespace VioletVreath {

/**
 * ÉJÅ[É\ÉãÇªÇÃÇP .
 * @version 1.00
 * @since 2011/04/07
 * @author Masatoshi Tsuge
 */
class CursorPauseMenu : public GgafLib::DefaultBoardActor {

public:
    CursorPauseMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorPauseMenu();
};

}
#endif /*CURSORPAUSEMENU_H_*/

