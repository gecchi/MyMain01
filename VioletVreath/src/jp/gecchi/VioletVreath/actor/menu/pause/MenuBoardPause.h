#ifndef MENUBOARDPAUSE_H_
#define MENUBOARDPAUSE_H_

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
        ITEM_QUIT_GAME,
        ITEM_DUMMY1,
        ITEM_DUMMY2,
        ITEM_DUMMY3,
        ITEM_DUMMY4,
        ITEM_DUMMY5,
        ITEM_DUMMY6,
        ITEM_DUMMY7,
        ITEM_CANCEL
    };

    MenuBoardConfirm* _pConfirmMenu;

    MenuBoardPause(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    bool condMoveCursorExNext() override;
    bool condMoveCursorExPrev() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    void processBehavior() override;

    virtual ~MenuBoardPause();
};

}
#endif /*MENUBOARDPAUSE_H_*/

