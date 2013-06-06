#ifndef MENUBOARDSCREENCONFIG_H_
#define MENUBOARDSCREENCONFIG_H_
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"


namespace VioletVreath {

/**
 * スクリーンコンフィグメニュー .
 * @version 1.00
 * @since 2013/06/06
 * @author Masatoshi Tsuge
 */
class MenuBoardScreenConfig : public MenuBoard {

public:
    enum {
        ITEM_SCREEN_MODE = 0,
        ITEM_VIEW_NUM    ,
        ITEM_VIEW_ASPECT_TYPE   ,
        ITEM_VIEW_POSITION ,
        ITEM_OK,
        ITEM_CANCEL,
    };

    int SUB_SCREEN_MODE_, SUB_VIEW_NUM_, SUB_VIEW_ASPECT_TYPE_, SUB_VIEW_POSITION_, SUB_CONFIRM_;

    LabelGecchi16Font* pLabel_Msg_;
public:
    MenuBoardScreenConfig(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    void onRise() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardScreenConfig();
};

}
#endif /*MENUBOARDSCREENCONFIG_H_*/

