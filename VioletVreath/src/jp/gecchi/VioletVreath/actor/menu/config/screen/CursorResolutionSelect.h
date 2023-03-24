#ifndef CURSORRESOLUTIONSELECT_H_
#define CURSORRESOLUTIONSELECT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * ÉJÅ[É\ÉãÇªÇÃÇP .
 * @version 1.00
 * @since 2011/04/07
 * @author Masatoshi Tsuge
 */
class CursorResolutionSelect : public GgafLib::DefaultBoardActor {

public:
    CursorResolutionSelect(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorResolutionSelect();
};

}
#endif /*CURSORRESOLUTIONSELECT_H_*/

