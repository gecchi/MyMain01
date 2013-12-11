#ifndef LABELRANKINGFONT_H_
#define LABELRANKINGFONT_H_
#include "jp/ggaf/lib/actor/StringBoardActor.h"

namespace VioletVreath {

/**
 * ランキング表示用フォント .
 * @version 1.00
 * @since 2011/08/02
 * @author Masatoshi Tsuge
 */
class LabelRankingFont : public GgafLib::StringBoardActor {

public:
    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

public:
    LabelRankingFont(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelRankingFont();

};

}
#endif /*LABELRANKINGFONT_H_*/
