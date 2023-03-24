#ifndef LABELGECCHI32FONT_H_
#define LABELGECCHI32FONT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * オリジナル32x32ドットフォントのラベル .
 * @version 1.00
 * @since 2012/10/12
 * @author Masatoshi Tsuge
 */
class LabelGecchi32Font : public GgafLib::FontBoardActor {

public:
    LabelGecchi32Font(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelGecchi32Font();

};

}
#endif /*LABELGECCHI32FONT_H_*/
