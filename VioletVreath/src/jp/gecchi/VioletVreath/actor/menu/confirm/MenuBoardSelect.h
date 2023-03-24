#ifndef MENUBOARDSELECT_H_
#define MENUBOARDSELECT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

namespace VioletVreath {

/**
 * 選択メニュー（作成中）
 * @version 1.00
 * @since 2022/08/04
 * @author Masatoshi Tsuge
 */
class MenuBoardSelect : public MenuBoard {

public:
    enum {
        ITEM_OK = 0 ,
        ITEM_CANCEL ,
    };

    MenuBoardSelect(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectExPrev() override;

    void onRise() override;

    void onSelect(int prm_from_index, int prm_selected_index) override;


    void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;

    bool hasJustDecidedOk();
    bool hasJustDecidedCancel();

    virtual ~MenuBoardSelect();
};

}
#endif /*MENUBOARDSELECT_H_*/

