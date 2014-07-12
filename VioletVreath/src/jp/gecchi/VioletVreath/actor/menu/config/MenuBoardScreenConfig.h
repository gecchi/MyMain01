#ifndef MENUBOARDSCREENCONFIG_H_
#define MENUBOARDSCREENCONFIG_H_
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

#include "jp/ggaf/core/util/GgafEnumIndex.h"

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
        ITEM_SCREEN_RESOLUTION,
        ITEM_SCREEN1_RESOLUTION, ITEM_SCREEN2_RESOLUTION,
        ITEM_SWAP_GAME_VIEW,
        ITEM_VIEW_ASPECT_TYPE   ,
        ITEM_VIEW_POSITION,
        ITEM_VIEW_POSITION1 , ITEM_VIEW_POSITION2 ,

        ITEM_OK, ITEM_OK_REBOOT, ITEM_CANCEL,

        ITEM_SCREEN_MODE_FULL_SCREEN,  ITEM_SCREEN_MODE_WINDOW_MODE,
        ITEM_VIEW_NUM_SINGLE        ,  ITEM_VIEW_NUM_DUAL,
        ITEM_SCREEN_RESOLUTION_VALUE,
        ITEM_SCREEN1_RESOLUTION_VALUE, ITEM_SCREEN2_RESOLUTION_VALUE,
        ITEM_SWAP_GAME_VIEW_NO      ,  ITEM_SWAP_GAME_VIEW_YES,
        ITEM_VIEW_ASPECT_TYPE_FIX   ,  ITEM_VIEW_ASPECT_TYPE_STRETCH,
        ITEM_POS_1, ITEM_POS_2, ITEM_POS_3, ITEM_POS_4, ITEM_POS_5, ITEM_POS_6, ITEM_POS_7, ITEM_POS_8, ITEM_POS_9,
        ITEM_POS1_1, ITEM_POS1_2, ITEM_POS1_3, ITEM_POS1_4, ITEM_POS1_5, ITEM_POS1_6, ITEM_POS1_7, ITEM_POS1_8, ITEM_POS1_9,
        ITEM_POS2_1, ITEM_POS2_2, ITEM_POS2_3, ITEM_POS2_4, ITEM_POS2_5, ITEM_POS2_6, ITEM_POS2_7, ITEM_POS2_8, ITEM_POS2_9,

        ITEM_BANPEI,
    };
    GgafCore::GgafEnumIndex itm;

    enum {
        SUPCUR_SCREEN_MODE = 0,
        SUPCUR_VIEW_NUM,
        SUPCUR_SCREEN_RESOLUTION,
        SUPCUR_SCREEN1_RESOLUTION,
        SUPCUR_SCREEN2_RESOLUTION,
        SUPCUR_SWAP_GAME_VIEW,
        SUPCUR_VIEW_ASPECT,
        SUPCUR_VIEW_POSITION,
        SUPCUR_VIEW_POSITION1,
        SUPCUR_VIEW_POSITION2,
        SUPCUR_BANPEI,
    };
    GgafCore::GgafEnumIndex cur;

    LabelGecchi16Font* pLabel_Msg_;


    bool in_FULL_SCREEN_;
    bool in_DUAL_VIEW_;
    bool in_SWAP_GAME_VIEW_;
    bool in_FIXED_GAME_VIEW_ASPECT_;
    int in_DUAL_VIEW_DRAW_POSITION1_;
    int in_DUAL_VIEW_DRAW_POSITION2_;
    int in_SINGLE_VIEW_DRAW_POSITION_;

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

