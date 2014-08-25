#ifndef MENUBOARDPAUSE_H_
#define MENUBOARDPAUSE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"


namespace VioletVreath {

/**
 * �|�[�Y�����j���[ .
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
class MenuBoardPause : public MenuBoard {

public:
    enum {
        ITEM_BACK_TO_GAME = 0 ,
        ITEM_GO_TO_TITLE,
        ITEM_HIDE_MENU,
        ITEM_DUMMY1,

        ITEM_KEY_CONFIG,
        ITEM_SOUND_CONFIG,
        ITEM_REBOOT,
        ITEM_QUIT_GAME,

        ITEM_BANPEI,
    };

    enum {
        MENU_CONFIRM = 0 ,
        MENU_KEY_CONFIG,
        MENU_SOUND_CONFIG,
        MENU_BANPEI,
    };

    bool toggle_HIDE_MENU_;

public:
    MenuBoardPause(const char* prm_name);

    void onRise() override;

    bool condSelectNext() override;

    bool condSelectPrev() override;

    bool condSelectExNext() override;

    bool condSelectExPrev() override;

    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    void processBehavior() override;

    virtual ~MenuBoardPause();
};

}
#endif /*MENUBOARDPAUSE_H_*/

