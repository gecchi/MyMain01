#ifndef MENUBOARDTITLE_H_
#define MENUBOARDTITLE_H_



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
        ITEM_CONFIG,
        ITEM_DEBUG,
        ITEM_QUIT,
    };
    MenuBoardConfirm* pConfirmMenu_;


    MenuBoardTitle(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    bool condMoveCursorExNext() override;
    bool condMoveCursorExPrev() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    void riseConfirm();
    void sinkConfirm();

    virtual ~MenuBoardTitle();
};

}
#endif /*MENUBOARDTITLE_H_*/

