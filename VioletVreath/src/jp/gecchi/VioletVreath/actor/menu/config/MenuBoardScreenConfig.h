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

        ITEM_SCREEN_MODE_FULL_SCREEN,
        ITEM_SCREEN_MODE_WINDOW_MODE,
        ITEM_VIEW_NUM_SINGLE,
        ITEM_VIEW_NUM_DUAL,
        ITEM_VIEW_ASPECT_TYPE_FIX,
        ITEM_VIEW_ASPECT_TYPE_STRETCH,
    };

    enum {
        SUPCUR_SCREEN_MODE,
        SUPCUR_VIEW_NUM,
        SUPCUR_VIEW_ASPECT,
    };
    LabelGecchi16Font* pLabel_Msg_;
public:
    MenuBoardScreenConfig(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectExPrev() override;
    void onRise() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardScreenConfig();
};

}
#endif /*MENUBOARDSCREENCONFIG_H_*/

