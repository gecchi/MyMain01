#ifndef LABELSCOREFONT_H_
#define LABELSCOREFONT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * オリジナル16x16ドットフォントのラベル .
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class LabelScoreFont : public GgafLib::FontBoardActor {
public:
    static int blur_no_[600];
    static int bn_;
    int* bk_draw_string_;
    int num_pno_;
public:
    LabelScoreFont(const char* prm_name);

    void processBehavior() override;

    void processPreDraw() override;
    void processAfterDraw() override;

    virtual ~LabelScoreFont();

};

}
#endif /*LABELSCOREFONT_H_*/
