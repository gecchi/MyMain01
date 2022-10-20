#ifndef MENUBOARDNAMEENTRY_H_
#define MENUBOARDNAMEENTRY_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

DECLARE_HASHVAL(EVENT_MENU_NAMEENTRY_DONE);

namespace VioletVreath {

/**
 * ネームエントリーの文字選択ボード .
 * @version 1.00
 * @since 2012/10/04
 * @author Masatoshi Tsuge
 */
class MenuBoardNameEntry : public MenuBoard {

public:
    static const char* apInputItemStr_[];

    static int input_item_num_;
    int ITEM_INDEX_OK_;
    int ITEM_INDEX_BS_;
    GgafLib::FontSpriteActor* pLabelInputedName_;
    GgafLib::FontSpriteActor* pLabelSelectedChar_;
    bool _is_input_keyboard;

public:
    MenuBoardNameEntry(const char* prm_name);

    void setNameFontBoard(GgafLib::FontSpriteActor* prm_pInputedName,
                          GgafLib::FontSpriteActor* prm_pSelectedChar);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectExPrev() override;
    bool condDecision() override;
    bool condCancel() override;

    void selectNext(bool prm_smooth = true) override;
    void selectPrev(bool prm_smooth = true) override;
    void selectExNext(bool prm_smooth = true) override;
    void selectExPrev(bool prm_smooth = true) override;

    void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void moveCursor(bool prm_smooth = true) override;
    void onActive() override;
    void processBehavior() override;
    void inputChar(const int prm_c);

    virtual ~MenuBoardNameEntry();
};

}
#endif /*MENUBOARDNAMEENTRY_H_*/

