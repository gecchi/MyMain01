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
        ITEM_DUAL_SCREEN,
//        ITEM_PRIMARY_SCREEN_FULL_SCREEN_RESOLUTION,
        ITEM_PRIMARY_SCREEN_FULL_SCREEN_RESOLUTION,
        ITEM_SECONDARY_SCREEN_FULL_SCREEN_RESOLUTION,
        ITEM_SWAP_SCREEN,
        ITEM_PRIMARY_SCREEN_ASPECT_RATIO_FIXED,
//        ITEM_PRIMARY_SCREEN_PRESENT_POSITION,
        ITEM_PRIMARY_SCREEN_PRESENT_POSITION,
        ITEM_SECONDARY_SCREEN_PRESENT_POSITION,

        ITEM_OK, ITEM_OK_REBOOT, ITEM_CANCEL,

        VALUE_FULL_SCREEN_TRUE, VALUE_FULL_SCREEN_FALSE,
        VALUE_DUAL_SCREEN_TRUE,  VALUE_DUAL_SCREEN_FALSE,
//        VALUE_PRIMARY_SCREEN_FULL_SCREEN_RESOLUTION,
        VALUE_PRIMARY_SCREEN_FULL_SCREEN_RESOLUTION,
        VALUE_SECONDARY_SCREEN_FULL_SCREEN_RESOLUTION,
        VALUE_SWAP_SCREEN_FALSE, VALUE_SWAP_SCREEN_TRUE,
        VALUE_FIXED_SCREEN_TRUE, VALUE_FIXED_SCREEN_FALSE,
//        VALUE_POS_1, VALUE_POS_2, VALUE_POS_3, VALUE_POS_4, VALUE_POS_5, VALUE_POS_6, VALUE_POS_7, VALUE_POS_8, VALUE_POS_9,
        VALUE_POS1_1, VALUE_POS1_2, VALUE_POS1_3, VALUE_POS1_4, VALUE_POS1_5, VALUE_POS1_6, VALUE_POS1_7, VALUE_POS1_8, VALUE_POS1_9,
        VALUE_POS2_1, VALUE_POS2_2, VALUE_POS2_3, VALUE_POS2_4, VALUE_POS2_5, VALUE_POS2_6, VALUE_POS2_7, VALUE_POS2_8, VALUE_POS2_9,

        ITEM_BANPEI,
    };
    enum {
        SUBCUR_FULL_SCREEN  = 0,
        SUBCUR_DUAL_SCREEN,
//        SUBCUR_PRIMARY_SCREEN_FULL_SCREEN_RESOLUTION,
        SUBCUR_PRIMARY_SCREEN_FULL_SCREEN_RESOLUTION,
        SUBCUR_SECONDARY_SCREEN_FULL_SCREEN_RESOLUTION,
        SUBCUR_SWAP_SCREEN,
        SUBCUR_PRIMARY_SCREEN_ASPECT_RATIO_FIXED,
//        SUBCUR_PRIMARY_SCREEN_PRESENT_POSITION,
        SUBCUR_PRIMARY_SCREEN_PRESENT_POSITION,
        SUBCUR_SECONDARY_SCREEN_PRESENT_POSITION,
        SUBCUR_BANPEI,
    };

    LabelGecchi16Font* pLabel_msg_;

    bool in_FULL_SCREEN_;
    bool in_NUMBER_OF_SCREENS_USED_;
    bool in_SWAP_SCREEN_;
    bool in_PRIMARY_SCREEN_ASPECT_RATIO_FIXED_;
    int in_PRIMARY_SCREEN_PRESENT_POSITION_;
    int in_SECONDARY_SCREEN_PRESENT_POSITION_;
//    int in_PRIMARY_SCREEN_PRESENT_POSITION_;


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

