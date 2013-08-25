#ifndef MENUBOARDPAUSE_H_
#define MENUBOARDPAUSE_H_
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"


namespace VioletVreath {

/**
 * ポーズ時メニュー .
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
class MenuBoardPause : public MenuBoard {

public:
    enum {
        ITEM_BACK_TO_GAME = 0 ,
        ITEM_CONFIG,
        ITEM_BACK_TO_TITLE,
        ITEM_REBOOT,

        ITEM_DUMMY1,
        ITEM_DUMMY2,
        ITEM_DUMMY3,
        ITEM_DUMMY4,

        ITEM_DUMMY5,
        ITEM_DUMMY6,
        ITEM_DUMMY7,
        ITEM_QUIT_GAME
    };

public:
    MenuBoardPause(const char* prm_name);

    bool condSelectNext() override;

    bool condSelectPrev() override;

    bool condSelectExNext() override;

    bool condSelectrExPrev() override;

    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    void processBehavior() override;

    virtual ~MenuBoardPause();
};

}
#endif /*MENUBOARDPAUSE_H_*/

