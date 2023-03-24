#ifndef MENUBOARDSCREENCONFIG_H_
#define MENUBOARDSCREENCONFIG_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

#include "jp/ggaf/core/util/EnumIndex.h"

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
        ITEM_FULL_SCREEN,
        ITEM_DUAL_VIEW,
//        ITEM_FULL_SCREEN1_RESOLUTION,
        ITEM_FULL_SCREEN1_RESOLUTION,
        ITEM_FULL_SCREEN2_RESOLUTION,
        ITEM_SWAP_GAME_VIEW,
        ITEM_FIXED_GAME_VIEW_ASPECT,
//        ITEM_PRESENT_POSITION1,
        ITEM_PRESENT_POSITION1,
        ITEM_PRESENT_POSITION2,

        ITEM_OK, ITEM_OK_REBOOT, ITEM_CANCEL,

        VALUE_FULL_SCREEN_TRUE, VALUE_FULL_SCREEN_FALSE,
        VALUE_DUAL_VIEW_TRUE,  VALUE_DUAL_VIEW_FALSE,
//        VALUE_FULL_SCREEN1_RESOLUTION,
        VALUE_FULL_SCREEN1_RESOLUTION,
        VALUE_FULL_SCREEN2_RESOLUTION,
        VALUE_SWAP_GAME_VIEW_FALSE, VALUE_SWAP_GAME_VIEW_TRUE,
        VALUE_FIXED_GAME_VIEW_TRUE, VALUE_FIXED_GAME_VIEW_FALSE,
//        VALUE_POS_1, VALUE_POS_2, VALUE_POS_3, VALUE_POS_4, VALUE_POS_5, VALUE_POS_6, VALUE_POS_7, VALUE_POS_8, VALUE_POS_9,
        VALUE_POS1_1, VALUE_POS1_2, VALUE_POS1_3, VALUE_POS1_4, VALUE_POS1_5, VALUE_POS1_6, VALUE_POS1_7, VALUE_POS1_8, VALUE_POS1_9,
        VALUE_POS2_1, VALUE_POS2_2, VALUE_POS2_3, VALUE_POS2_4, VALUE_POS2_5, VALUE_POS2_6, VALUE_POS2_7, VALUE_POS2_8, VALUE_POS2_9,

        ITEM_BANPEI,
    };
    enum {
        SUBCUR_FULL_SCREEN  = 0,
        SUBCUR_DUAL_VIEW,
//        SUBCUR_FULL_SCREEN1_RESOLUTION,
        SUBCUR_FULL_SCREEN1_RESOLUTION,
        SUBCUR_FULL_SCREEN2_RESOLUTION,
        SUBCUR_SWAP_GAME_VIEW,
        SUBCUR_FIXED_GAME_VIEW_ASPECT,
//        SUBCUR_PRESENT_POSITION1,
        SUBCUR_PRESENT_POSITION1,
        SUBCUR_PRESENT_POSITION2,
        SUBCUR_BANPEI,
    };

    LabelGecchi16Font* pLabel_msg_;

    bool in_FULL_SCREEN_;
    bool in_DUAL_VIEW_;
    bool in_SWAP_GAME_VIEW_;
    bool in_FIXED_GAME_VIEW_ASPECT_;
    int in_PRESENT_POSITION1_;
    int in_PRESENT_POSITION2_;
//    int in_PRESENT_POSITION1_;


    int rezo_index_;
    int rezo1_index_;
    int rezo2_index_;
    int rezo_num_;
    int rezo1_num_;
    int rezo2_num_;

public:
    MenuBoardScreenConfig(const char* prm_name);

    bool condSelectNext() override;

    bool condSelectPrev() override;

    bool condSelectExNext() override;

    bool condSelectExPrev() override;

    void onRise() override;

    void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;

    void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;

    void processBehavior() override;

    void replaceItem();

    virtual ~MenuBoardScreenConfig();
};

}
#endif /*MENUBOARDSCREENCONFIG_H_*/

