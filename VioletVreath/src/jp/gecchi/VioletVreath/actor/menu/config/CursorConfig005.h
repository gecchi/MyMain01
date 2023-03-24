#ifndef CURSORCONFIG005_H_
#define CURSORCONFIG005_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * スクリーンコンフィグのカーソル .
 * @version 1.00
 * @since 2013/06/06
 * @author Masatoshi Tsuge
 */
class CursorConfig005 : public GgafLib::DefaultBoardActor {

public:
    CursorConfig005(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorConfig005();
};

}
#endif /*CURSORCONFIG005_H_*/

