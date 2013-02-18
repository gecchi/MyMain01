#ifndef MENUBOARDKEYCONFIG_H_
#define MENUBOARDKEYCONFIG_H_

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
        ITEM_MAIN_SHOT = 0,
        ITEM_SUB_SHOT,
        ITEM_TURBO,
        ITEM_CONTROLL,
        ITEM_MAGIC,
        ITEM_VAM,
        ITEM_SAVE_AND_EXIT,
        ITEM_CANCEL
    };

public:
    MenuBoardKeyConfig(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    bool condMoveCursorExNext() override;
    bool condMoveCursorExPrev() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardKeyConfig();
};

}
#endif /*MENUBOARDKEYCONFIG_H_*/

