#ifndef MENUBOARDKEYCONFIG_H_
#define MENUBOARDKEYCONFIG_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

namespace VioletVreath {

/**
 * キーコンフィグメニュー .
 * @version 1.00
 * @since 2013/02/18
 * @author Masatoshi Tsuge
 */
class MenuBoardKeyConfig : public MenuBoard {

public:
    enum {
        ITEM_UP = 0,
        ITEM_DOWN,
        ITEM_LEFT,
        ITEM_RIGHT,
        ITEM_VIEW_UP,
        ITEM_VIEW_DOWN,
        ITEM_VIEW_LEFT,
        ITEM_VIEW_RIGHT,
        ITEM_MAIN_SHOT,
        ITEM_SUB_SHOT  ,
        ITEM_TURBO     ,
        ITEM_CONTROLL  ,
        ITEM_MAGIC     ,
        ITEM_VIEW       ,
        ITEM_PAUSE     ,
        ITEM_BANPEI    ,
    };
    int ITEM_INDEX_OK_;
    int ITEM_INDEX_CANCEL_;

    struct VBProperty {
        LabelFix16Font01* pKey;
        LabelFix16Font01* pJoy;
    };
    VBProperty* paVBConfig;

    /** 0:メニュー移動、1:KEY割り当て入力待ち状態、2:JOY割り当て入力待ち状態 */
    int input_mode_;
    int input_target_item_;
public:
    MenuBoardKeyConfig(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    void onRise() override;
    void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardKeyConfig();
};

}
#endif /*MENUBOARDKEYCONFIG_H_*/

