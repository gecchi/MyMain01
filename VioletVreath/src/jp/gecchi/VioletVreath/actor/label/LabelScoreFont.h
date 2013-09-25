#ifndef LABELSCOREFONT_H_
#define LABELSCOREFONT_H_
#include "jp/ggaf/lib/actor/StringBoardActor.h"

namespace VioletVreath {

/**
 * オリジナル16x16ドットフォントのラベル .
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class LabelScoreFont : public GgafLib::StringBoardActor {
public:
    static int blur_no_[600];
    static int bn_;
    int num_pno_;
public:
    LabelScoreFont(const char* prm_name);

    void processBehavior() override;

    void processDraw() override;

    virtual ~LabelScoreFont();

};

}
#endif /*LABELSCOREFONT_H_*/
