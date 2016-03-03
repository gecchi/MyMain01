#ifndef MENUBOARDNAMEENTRY_H_
#define MENUBOARDNAMEENTRY_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"


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
//    GgafLib::FontBoardActor* pLabelInputedName_;
//    GgafLib::FontBoardActor* pLabelSelectedChar_;
    GgafLib::StringSpriteActor* pLabelInputedName_;
    GgafLib::StringSpriteActor* pLabelSelectedChar_;

public:
    MenuBoardNameEntry(const char* prm_name);

    void setNameFontBoard(GgafLib::StringSpriteActor* prm_pInputedName,
                            GgafLib::StringSpriteActor* prm_pSelectedChar);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectExPrev() override;
    bool condDecision() override;
    bool condCancel() override;

    void selectNext() override;
    void selectPrev() override;
    void selectExNext() override;
    void selectExPrev() override;

    void onDecision(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxFigureActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardNameEntry();
};

}
#endif /*MENUBOARDNAMEENTRY_H_*/

