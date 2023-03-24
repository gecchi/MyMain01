#ifndef CURSORCONFIG004_H_
#define CURSORCONFIG004_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * サウンドコンフィグのカーソル .
 * @version 1.00
 * @since 2013/02/25
 * @author Masatoshi Tsuge
 */
class CursorConfig004 : public GgafLib::DefaultBoardActor {

public:
    CursorConfig004(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorConfig004();
};

}
#endif /*CURSORCONFIG004_H_*/

