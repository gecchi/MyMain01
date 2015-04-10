#ifndef MENUBOARDCONFIRM_H_
#define MENUBOARDCONFIRM_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

namespace VioletVreath {

/**
 * 初期選択[OK]の確認メニュー .
 * @version 1.00
 * @since 2011/12/27
 * @author Masatoshi Tsuge
 */
class MenuBoardConfirm : public MenuBoard {

public:
    enum {
        ITEM_OK = 0 ,
        ITEM_CANCEL ,
    };

public:
    MenuBoardConfirm(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectExPrev() override;

    void onRise() override;

    void onDecision(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) override;

    bool hasJustDecidedOk();
    bool hasJustDecidedCancel();

    virtual ~MenuBoardConfirm();
};

}
#endif /*MENUBOARDCONFIRM_H_*/

