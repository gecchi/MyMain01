#ifndef LABELMENUITEMFONT01_H_
#define LABELMENUITEMFONT01_H_
#include "jp/ggaf/lib/actor/StringBoardActor.h"

namespace VioletVreath {

/**
 * メニューのタイトル用フォント .
 * @version 1.00
 * @since 2013/03/26
 * @author Masatoshi Tsuge
 */
class LabelMenuItemFont01 : public GgafLib::StringBoardActor {

public:
    LabelMenuItemFont01(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelMenuItemFont01();

};

}
#endif /*LABELMENUITEMFONT01_H_*/
