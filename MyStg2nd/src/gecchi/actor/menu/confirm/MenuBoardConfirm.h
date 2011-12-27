#ifndef MENUBOARDCONFIRM_H_
#define MENUBOARDCONFIRM_H_


enum {
    CONFIRM_MENU_ITEM_OK = 0 ,
    CONFIRM_MENU_ITEM_CANCEL ,
};


namespace MyStg2nd {

/**
 * 確認メニュー .
 * @version 1.00
 * @since 2011/12/27
 * @author Masatoshi Tsuge
 */
class MenuBoardConfirm : public MenuBoard {

public:
    MenuBoardConfirm(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    bool condMoveCursorExNext() override;
    bool condMoveCursorExPrev() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    virtual ~MenuBoardConfirm();
};

}
#endif /*MENUBOARDCONFIRM_H_*/

