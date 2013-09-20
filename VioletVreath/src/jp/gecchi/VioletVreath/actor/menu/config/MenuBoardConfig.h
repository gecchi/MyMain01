#ifndef MENUBOARDCONFIG_H_
#define MENUBOARDCONFIG_H_
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

namespace VioletVreath {

/**
 * �R���t�B�O���j���[ .
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

    bool condSelectNext() override;
    bool condSelectPrev() override;
    void onRise() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardConfig();
};

}
#endif /*MENUBOARDCONFIG_H_*/

