#ifndef MENUBOARDNAMEENTRY_H_
#define MENUBOARDNAMEENTRY_H_

namespace VioletVreath {

/**
 * ネームエントリーの文字選択ボード .
 * @version 1.00
 * @since 2012/10/04
 * @author Masatoshi Tsuge
 */
class MenuBoardNameEntry : public MenuBoard {

public:
    int ITEM_NO_OK_;
    int ITEM_NO_BS_;
    MenuBoardConfirm* pConfirmMenu_;
    LabelGecchi32Font* pLabelInputedName_;
    LabelGecchi32Font* pLabelSelectedChar_;

    MenuBoardNameEntry(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    bool condMoveCursorExNext() override;
    bool condMoveCursorExPrev() override;
    bool condDecision() override;
    bool condCancel() override;

    void moveCursorNext() override;
    void moveCursorPrev() override;
    void moveCursorExNext() override;
    void moveCursorExPrev() override;

    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardNameEntry();
};

}
#endif /*MENUBOARDNAMEENTRY_H_*/

