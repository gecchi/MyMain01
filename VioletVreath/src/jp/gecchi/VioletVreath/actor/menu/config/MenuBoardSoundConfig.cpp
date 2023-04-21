#include "MenuBoardSoundConfig.h"

#include "jp/ggaf/dx/sound/Sound.h"
#include "CursorConfig004.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelFix16Font01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuItemFont01.h"



using namespace GgafLib;
using namespace VioletVreath;

MenuBoardSoundConfig::MenuBoardSoundConfig(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardSoundConfig";
    setWidth(PX_C(32*32));
    setHeight(PX_C(12*32));

    //���j���[�A�C�e���i�I���j�ݒ�
    const char* apItemStr[] = {
          "SE  VOLUME",
          "BGM VOLUME",
          "MASTER VOLUME",
    };

    int item_index;
    for (item_index = ITEM_SE_VOL; item_index <= ITEM_MASTER_VOL; item_index++) {
        LabelMenuItemFont01* pLabel = NEW LabelMenuItemFont01("item");
        pLabel->update(apItemStr[item_index], ALIGN_LEFT, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(200), PX_C(100+(item_index*20)));
    }

    LabelMenuItemFont01* pLabel_OK = NEW LabelMenuItemFont01("item_Ok");
    pLabel_OK->update("OK & SAVE", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_OK, PX_C(100), PX_C(350));
    ITEM_INDEX_OK_ = item_index;

    LabelMenuItemFont01* pLabel_CANCEL = NEW LabelMenuItemFont01("item_Cancel");
    pLabel_CANCEL->update("CANCEL", ALIGN_LEFT, VALIGN_MIDDLE);
    addItem(pLabel_CANCEL, PX_C(400), PX_C(350));
    ITEM_INDEX_CANCEL_ = item_index + 1;

    pLabel_SeVol_ = NEW LabelFix16Font01("LABEL_SE_VOL");
    pLabel_SeVol_->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    addLabel(pLabel_SeVol_, PX_C(600), PX_C(100+(0*20)));
    pLabel_BgmVol_ = NEW LabelFix16Font01("LABEL_BGM_VOL");
    pLabel_BgmVol_->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    addLabel(pLabel_BgmVol_, PX_C(600), PX_C(100+(1*20)));
    pLabel_MasterVol_ = NEW LabelFix16Font01("LABEL_MASTER_VOL");
    pLabel_MasterVol_->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    addLabel(pLabel_MasterVol_, PX_C(600), PX_C(100+(2*20)));

    LabelMenuTitleFont01* pLabel_title = NEW LabelMenuTitleFont01("LABEL_TITLE");
    pLabel_title->update("[SOUND CONFIG]", ALIGN_CENTER, VALIGN_MIDDLE);
    addLabel(pLabel_title, PX_C(300), PX_C(40));

    pLabel_msg_ = NEW LabelGecchi16Font("LABEL_MSG");
    pLabel_msg_->update("PRESS <- OR -> TO ADJUST THE VOLUME.", ALIGN_LEFT, VALIGN_MIDDLE);
    addLabel(pLabel_msg_, PX_C(300), PX_C(60));


    //���j���[�J�[�\����ݒ�
    CursorConfig004* pCursor = NEW CursorConfig004("CursorConfig004");
    pCursor->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setMainCursor(pCursor);
    //�L�����Z���A�C�e���ݒ�
    relateAllItemToCancel(ITEM_INDEX_CANCEL_);

    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�����i�\����\�����̋����j
                                            //�ォ�牺�֏����X���C�h������
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No �₢���킹���j���[���T�u���j���[�ɒǉ�

}
bool MenuBoardSoundConfig::condSelectNext() {
    return VVB->isAutoRepeat(0, VV_VB_UI_DOWN);
}
bool MenuBoardSoundConfig::condSelectPrev() {
    return VVB->isAutoRepeat(0, VV_VB_UI_UP);
}
void MenuBoardSoundConfig::onRise() {
    selectItem(ITEM_SE_VOL); //�J�[�\���̏����I���A�C�e����ݒ�
    pLabel_SeVol_->update(XTOS(GgafDx::Sound::getSeMasterVolume()).c_str());
    pLabel_BgmVol_->update(XTOS(GgafDx::Sound::getBgmMasterVolume()).c_str());
    pLabel_MasterVol_->update(XTOS(GgafDx::Sound::getAppMasterVolume()).c_str());
    MenuBoard::onRise();
}
void MenuBoardSoundConfig::processBehavior() {
    MenuBoard::processBehavior();

    //OK���̊m�F���j���[����
    if (getSelectedIndex() == ITEM_INDEX_OK_) {
        MenuBoardConfirm* pSubConfirm = (MenuBoardConfirm*)getSubMenu();
        if (pSubConfirm->hasJustDecidedOk()) { //SAVE�m�FOK!
            //���v���p�e�B�֏�������
            CONFIG::_properties.setValue("SE_VOLUME", GgafDx::Sound::getSeMasterVolume());
            CONFIG::_properties.setValue("BGM_VOLUME", GgafDx::Sound::getBgmMasterVolume());
            CONFIG::_properties.setValue("MASTER_VOLUME", GgafDx::Sound::getAppMasterVolume());
            CONFIG::_properties.write(CONFIG::_load_properties_filename); //�v���p�e�B�ۑ�
//            CONFIG::loadProperties(CONFIG::_load_properties_filename); //�v���p�e�B�Ĕ��f
//            //���s���A�v���ւ��������f
//            GgafDx::Sound::setSeMasterVolume(CONFIG::SE_VOLUME);
//            GgafDx::Sound::setBgmMasterVolume(CONFIG::BGM_VOLUME);
//            GgafDx::Sound::setAppMasterVolume(CONFIG::MASTER_VOLUME);

            sinkCurrentSubMenu();
            sinkMe();
        } else if (pSubConfirm->hasJustDecidedCancel()) { //SAVE�m�F�ŃL�����Z��
            sinkCurrentSubMenu();
        } else {

        }
    }

    //�L�[���́A�{�^�����́A���f
    VirtualButton* pVVB = VVB;
    int index = getSelectedIndex();
    if (index == ITEM_SE_VOL) {
        if (pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT)) {
            GgafDx::Sound::addSeMasterVolume(+10);
        } else if (pVVB->isAutoRepeat(0, VV_VB_UI_LEFT)) {
            GgafDx::Sound::addSeMasterVolume(-10);
        }
    } else if (index == ITEM_BGM_VOL) {
        if (pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT)) {
            GgafDx::Sound::addBgmMasterVolume(+10);
        } else if (pVVB->isAutoRepeat(0, VV_VB_UI_LEFT)) {
            GgafDx::Sound::addBgmMasterVolume(-10);
        }
    } else if (index == ITEM_MASTER_VOL) {
        if (pVVB->isAutoRepeat(0, VV_VB_UI_RIGHT)) {
            GgafDx::Sound::addAppMasterVolume(+10);
        } else if (pVVB->isAutoRepeat(0, VV_VB_UI_LEFT)) {
            GgafDx::Sound::addAppMasterVolume(-10);
        }
    }
    pLabel_SeVol_->update(XTOS(GgafDx::Sound::getSeMasterVolume()).c_str());
    pLabel_BgmVol_->update(XTOS(GgafDx::Sound::getBgmMasterVolume()).c_str());
    pLabel_MasterVol_->update(XTOS(GgafDx::Sound::getAppMasterVolume()).c_str());
}

void MenuBoardSoundConfig::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_INDEX_CANCEL_) {
        //���ʂ����ɖ߂�
        GgafDx::Sound::setSeMasterVolume(CONFIG::SE_VOLUME);
        GgafDx::Sound::setBgmMasterVolume(CONFIG::BGM_VOLUME);
        GgafDx::Sound::setAppMasterVolume(CONFIG::MASTER_VOLUME);
        sinkMe();
    } else if (prm_item_index == ITEM_INDEX_OK_) {
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y - PX_C(50)); //�m�F���j���[�N��
    } else {

    }
}
void MenuBoardSoundConfig::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
}

MenuBoardSoundConfig::~MenuBoardSoundConfig() {
}
