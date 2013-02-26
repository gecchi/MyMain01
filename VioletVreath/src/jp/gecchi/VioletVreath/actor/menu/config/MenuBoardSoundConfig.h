#ifndef MENUBOARDSOUNDCONFIG_H_
#define MENUBOARDSOUNDCONFIG_H_

namespace VioletVreath {

/**
 * サウンドフィグメニュー .
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
public:
    MenuBoardSoundConfig(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    void onRisen() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardSoundConfig();
};

}
#endif /*MENUBOARDKEYCONFIG_H_*/

