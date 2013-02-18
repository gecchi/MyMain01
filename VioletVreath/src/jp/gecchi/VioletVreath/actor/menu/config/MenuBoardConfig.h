#ifndef MENUBOARDCONFIG_H_
#define MENUBOARDCONFIG_H_

namespace VioletVreath {

/**
 * コンフィグメニュー .
 * @version 1.00
 * @since 2013/02/18
 * @author Masatoshi Tsuge
 */
class MenuBoardConfig : public MenuBoard {

public:
    enum {
        ITEM_KEY_CONFIG = 0 ,
        ITEM_SOUND_CONFIG,
        ITEM_SCREEN_CONFIG,
        ITEM_BACK,
    };

public:
    MenuBoardConfig(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardConfig();
};

}
#endif /*MENUBOARDCONFIG_H_*/

