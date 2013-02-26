#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardSoundConfig::MenuBoardSoundConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardSoundConfig";
    //メニューウィンドウ設定
    update( "%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            ")*******************************+\n"
            "-.............................../");

    //メニューアイテム（選択可）設定
    char* apItemStr[] = {
          "SE  VOLUME",
          "BGM VOLUME",
          "MASTER VOLUME",
    };

    int item_index;
    for (item_index = ITEM_SE_VOL; item_index <= ITEM_MASTER_VOL; item_index++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[item_index], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+(item_index*20)));
    }

    LabelGecchi16Font* pLabel_OK = NEW LabelGecchi16Font("item_Ok");
    pLabel_OK->update("OK & SAVE", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_OK, PX_C(100), PX_C(350));
    ITEM_INDEX_OK_ = item_index;

    LabelGecchi16Font* pLabel_CANCEL = NEW LabelGecchi16Font("item_Cancel");
    pLabel_CANCEL->update("CANCEL", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_CANCEL, PX_C(400), PX_C(350));
    ITEM_INDEX_CANCEL_ = item_index + 1;

    pLabel_SeVol_ = NEW LabelFix16Font01("LABEL_SE_VOL");
    pLabel_SeVol_->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    addDispLabel(pLabel_SeVol_, PX_C(600), PX_C(100+(0*20)));
    pLabel_BgmVol_ = NEW LabelFix16Font01("LABEL_BGM_VOL");
    pLabel_BgmVol_->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    addDispLabel(pLabel_BgmVol_, PX_C(600), PX_C(100+(1*20)));
    pLabel_MasterVol_ = NEW LabelFix16Font01("LABEL_MASTER_VOL");
    pLabel_MasterVol_->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    addDispLabel(pLabel_MasterVol_, PX_C(600), PX_C(100+(2*20)));

    LabelMenuTitleFont01* pLabel_Title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_Title->update("SELECT AND PUSH <- OR ->", ALIGN_CENTER, VALIGN_MIDDLE);
    addDispLabel(pLabel_Title, PX_C(300), PX_C(40));

    //メニューカーソルを設定
    CursorSoundConfigMenu* pCursor = NEW CursorSoundConfigMenu("CursorSoundConfigMenu");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setCursor(pCursor);
    //キャンセルアイテム設定
    relateAllItemCancel(ITEM_INDEX_CANCEL_);

    setTransition(30, PX_C(0), -PX_C(100)); //トランジション（表示非表示時の挙動）
                                            //上から下へ少しスライドさせる
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューをサブメニューに追加

}
bool MenuBoardSoundConfig::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardSoundConfig::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
void MenuBoardSoundConfig::onRisen() {
    setSelectedIndex(ITEM_SE_VOL); //カーソルの初期選択アイテムを設定
    pLabel_SeVol_->update(ITOS(GgafDxSound::_se_volume).c_str());
    pLabel_BgmVol_->update(ITOS(GgafDxSound::_bgm_volume).c_str());
    pLabel_MasterVol_->update(ITOS(GgafDxSound::_master_volume).c_str());
    MenuBoard::onRisen();
}
void MenuBoardSoundConfig::processBehavior() {
    MenuBoard::processBehavior();

    //OK時の確認メニュー判定
    if (getSelectedIndex() == ITEM_INDEX_OK_) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu(0);
        if (pSubConfirm->wasDecidedOk()) { //確認OK!
            //現プロパティをファイルに保存
            GGAF_PROPERTY(SE_VOLUME    ) = GgafDxSound::_se_volume;
            GGAF_PROPERTY(BGM_VOLUME   ) = GgafDxSound::_bgm_volume;
            GGAF_PROPERTY(MASTER_VOLUME) = GgafDxSound::_master_volume;
            VioletVreath::Properties::save(VV_CONFIG_FILE); //保存
            //実行中アプリへも反映
            GgafDxSound::setSeVolume(GGAF_PROPERTY(SE_VOLUME));
            GgafDxSound::setBgmVolume(GGAF_PROPERTY(BGM_VOLUME));
            GgafDxSound::setMasterVolume(GGAF_PROPERTY(MASTER_VOLUME));

            sinkSubMenu();
            sink();
        } else if (pSubConfirm->wasDecidedCancel()) { //確認でキャンセル
            sinkSubMenu();
        } else {

        }
    }

    //キー入力、ボタン入力、反映
    VirtualButton* pVB = VB;
    int index = getSelectedIndex();
    if (index == ITEM_SE_VOL) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            GgafDxSound::addSeVolume(+1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            GgafDxSound::addSeVolume(-1);
        }
        pLabel_SeVol_->update(ITOS(GgafDxSound::_se_volume).c_str());
    } else if (index == ITEM_BGM_VOL) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            GgafDxSound::addBgmVolume(+1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            GgafDxSound::addBgmVolume(-1);
        }
        pLabel_BgmVol_->update(ITOS(GgafDxSound::_bgm_volume).c_str());
    } else if (index == ITEM_MASTER_VOL) {
        if (pVB->isAutoRepeat(VB_UI_RIGHT)) {
            GgafDxSound::addMasterVolume(+1);
        } else if (pVB->isAutoRepeat(VB_UI_LEFT)) {
            GgafDxSound::addMasterVolume(-1);
        }
        pLabel_MasterVol_->update(ITOS(GgafDxSound::_master_volume).c_str());
    }
}

void MenuBoardSoundConfig::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_INDEX_CANCEL_) {
        //リセット
        GgafDxSound::setSeVolume(GGAF_PROPERTY(SE_VOLUME));
        GgafDxSound::setBgmVolume(GGAF_PROPERTY(BGM_VOLUME));
        GgafDxSound::setMasterVolume(GGAF_PROPERTY(MASTER_VOLUME));
        sink();
    } else if (prm_item_index == ITEM_INDEX_OK_) {
        riseSubMenu(0, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y - PX_C(50)); //確認メニュー起動
    } else {

    }
}
void MenuBoardSoundConfig::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
}

MenuBoardSoundConfig::~MenuBoardSoundConfig() {
}
