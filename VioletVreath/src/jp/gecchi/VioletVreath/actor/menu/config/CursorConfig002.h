#ifndef CURSORCONFIG002_H_
#define CURSORCONFIG002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * キーコンフィグのカーソル .
 * @version 1.00
 * @since 2013/02/18
 * @author Masatoshi Tsuge
 */
class CursorConfig002 : public GgafLib::DefaultBoardActor {

public:
    CursorConfig002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorConfig002();
};

}
#endif /*CURSORCONFIG002_H_*/

