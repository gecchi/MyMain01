#ifndef MENUBOARDTITLE_H_
#define MENUBOARDTITLE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

namespace VioletVreath {

/**
 * タイトルメニュー .
 * @version 1.00
 * @since 2011/12/27
 * @author Masatoshi Tsuge
 */
class MenuBoardTitle : public MenuBoard {

public:
    enum {
        ITEM_GAME_START = 0 ,
        ITEM_KEY_CONFIG,
        ITEM_SOUND_CONFIG,
        ITEM_SCREEN_CONFIG,
        ITEM_NAME_ENTRY,
        ITEM_REBOOT,
        ITEM_QUIT,
        ITEM_BANPEI,
    };
    enum {
        MENU_CONFIRM = 0 ,
        MENU_KEY_CONFIG,
        MENU_SOUND_CONFIG,
        MENU_SCREEN_CONFIG,
        MENU_NAME_ENTRY,
        MENU_BANPEI,
    };

    MenuBoardTitle(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectExPrev() override;
    void onSelect(int prm_from_index, int prm_selected_index) override;
    void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;

    void processBehavior() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~MenuBoardTitle();
};

}
#endif /*MENUBOARDTITLE_H_*/

