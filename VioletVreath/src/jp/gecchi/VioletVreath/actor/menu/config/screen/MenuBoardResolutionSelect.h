#ifndef MENUBOARDRESOLUTIONSELECT_H_
#define MENUBOARDRESOLUTIONSELECT_H_
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

namespace VioletVreath {

/**
 * 初期選択[OK]の確認メニュー .
 * @version 1.00
 * @since 2011/12/27
 * @author Masatoshi Tsuge
 */
class MenuBoardResolutionSelect : public MenuBoard {

public:
    enum {
        ITEM_OK = 0 ,
        ITEM_CANCEL ,
    };

public:
    MenuBoardResolutionSelect(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectExPrev() override;

    void onRise() override;

    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    bool isJustDecidedOk();
    bool isJustDecidedCancel();

    virtual ~MenuBoardResolutionSelect();
};

}
#endif /*MENUBOARDRESOLUTIONSELECT_H_*/

