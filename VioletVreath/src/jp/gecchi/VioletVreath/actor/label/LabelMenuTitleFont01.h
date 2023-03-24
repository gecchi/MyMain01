#ifndef LABELMENUTITLEFONT01_H_
#define LABELMENUTITLEFONT01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * メニューのタイトル用フォント .
 * @version 1.00
 * @since 2013/03/26
 * @author Masatoshi Tsuge
 */
class LabelMenuTitleFont01 : public GgafLib::FontBoardActor {

public:
    LabelMenuTitleFont01(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelMenuTitleFont01();

};

}
#endif /*LABELFIX16FONT01_H_*/
