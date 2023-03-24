#ifndef LABELGECCHI16FONT_H_
#define LABELGECCHI16FONT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * オリジナル16x16ドットフォントのラベル .
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class LabelGecchi16Font : public GgafLib::FontBoardActor {

public:
    LabelGecchi16Font(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelGecchi16Font();

};

}
#endif /*LABELGECCHI16FONT_H_*/
