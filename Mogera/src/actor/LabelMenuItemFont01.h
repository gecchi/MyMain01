#ifndef LABELMENUITEMFONT01_H_
#define LABELMENUITEMFONT01_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace Mogera {

/**
 * メニューのタイトル用フォント .
 * @version 1.00
 * @since 2013/03/26
 * @author Masatoshi Tsuge
 */
class LabelMenuItemFont01 : public GgafLib::FontBoardActor {

public:
    LabelMenuItemFont01(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onUpdate() override;

    void processBehavior() override;

    virtual ~LabelMenuItemFont01();

};

}
#endif /*LABELMENUITEMFONT01_H_*/
