#ifndef MENUBOARDCONFIG_H_
#define MENUBOARDCONFIG_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

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

    MenuBoardConfig(const char* prm_name);
    void onActive() override;
    bool condSelectNext() override;
    bool condSelectPrev() override;
    void onRise() override;
    void onRiseDone() override;
    void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;
    void onSinkDone() override;

    virtual ~MenuBoardConfig();
};

}
#endif /*MENUBOARDCONFIG_H_*/

