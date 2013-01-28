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
    static char* apInputItemStr_[];
    static int input_item_num_;
    int ITEM_INDEX_OK_;
    int ITEM_INDEX_BS_;
//    GgafLib::StringBoardActor* pLabelInputedName_;
//    GgafLib::StringBoardActor* pLabelSelectedChar_;
    GgafLib::StringSpriteActor* pLabelInputedName_;
    GgafLib::StringSpriteActor* pLabelSelectedChar_;

public:
    MenuBoardNameEntry(const char* prm_name);

    void setNameStringBoard(GgafLib::StringSpriteActor* prm_pInputedName,
                            GgafLib::StringSpriteActor* prm_pSelectedChar);

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

