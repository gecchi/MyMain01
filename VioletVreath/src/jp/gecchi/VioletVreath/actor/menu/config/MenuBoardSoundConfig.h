#ifndef MENUBOARDSOUNDCONFIG_H_
#define MENUBOARDSOUNDCONFIG_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"


namespace VioletVreath {

/**
 * サウンドコンフィグメニュー .
 * @version 1.00
 * @since 2013/02/25
 * @author Masatoshi Tsuge
 */
class MenuBoardSoundConfig : public MenuBoard {

public:
    enum {
        ITEM_SE_VOL = 0,
        ITEM_BGM_VOL  ,
        ITEM_MASTER_VOL,
    };

    int ITEM_INDEX_OK_;
    int ITEM_INDEX_CANCEL_;

    LabelFix16Font01* pLabel_SeVol_;
    LabelFix16Font01* pLabel_BgmVol_;
    LabelFix16Font01* pLabel_MasterVol_;

    LabelGecchi16Font* pLabel_msg_;
public:
    MenuBoardSoundConfig(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    void onRise() override;
    void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardSoundConfig();
};

}
#endif /*MENUBOARDKEYCONFIG_H_*/

