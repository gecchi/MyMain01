#ifndef LABELRANKINGFONT_H_
#define LABELRANKINGFONT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * �����L���O�\���p�t�H���g .
 * @version 1.00
 * @since 2011/08/02
 * @author Masatoshi Tsuge
 */
class LabelRankingFont : public GgafLib::FontBoardActor {

public:
    LabelRankingFont(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelRankingFont();

};

}
#endif /*LABELRANKINGFONT_H_*/
