#ifndef MENUBOARDTITLE_H_
#define MENUBOARDTITLE_H_
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

namespace VioletVreath {

/**
 * �^�C�g�����j���[ .
 * @version 1.00
 * @since 2011/12/27
 * @author Masatoshi Tsuge
 */
class MenuBoardTitle : public MenuBoard {

public:
    enum {
        ITEM_GAME_START = 0 ,
        ITEM_CONFIG,
        ITEM_REBOOT,
        ITEM_QUIT,
    };
    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader** papItemAFader_;

public:
    MenuBoardTitle(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectExPrev() override;
    void onSelect(int prm_from, int prm_to) override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    void processBehavior() override;

    virtual ~MenuBoardTitle();
};

}
#endif /*MENUBOARDTITLE_H_*/

