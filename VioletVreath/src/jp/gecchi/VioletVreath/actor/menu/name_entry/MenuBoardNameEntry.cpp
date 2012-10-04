#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardNameEntry::MenuBoardNameEntry(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardNameEntry";
    //���j���[�E�B���h�E�ݒ�
    update("%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'\n"
           ")*******************************************+\n"
           ")*******************************************+\n"
           ")*******************************************+\n"
           ")*******************************************+\n"
           ")*******************************************+\n"
           ")*******************************************+\n"
           ")*******************************************+\n"
           "-.........................................../");
    _Z = 5; //�v���C�I���e�B

    //���j���[�A�C�e���i�I���j�ݒ�
    char* apItemStr[] = {
         " ","!","\"","#","$","%","&","'","(",")","*","+",",","-",".","/",
         "0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","?",
         "@","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
         "P","Q","R","S","T","U","V","W","X","Y","Z","[","\\","]","^","_"
    };
    int item_index = 0;
    for (int i = ' '-' '; i < '_'-' '; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addSelectItem(pLabel, PX_C(100 + ((i/16)*(pLabel->_chr_width_px * 2))),
                              PX_C(100 + ((i%16)*(pLabel->_chr_height_px * 2))),
                              -1);
        item_index++;
    }
    ITEM_BS = item_index; item_index++;
    ITEM_OK = item_index; item_index++;

    LabelGecchi16Font* pBS = NEW LabelGecchi16Font("item"); //�o�b�N�X�y�[�X(�L�����Z������)
    pBS->update("[BS]", ALIGN_CENTER, VALIGN_MIDDLE);
    addSelectItem(pBS, PX_C(700), PX_C(100), -1);

    LabelGecchi16Font* pOK = NEW LabelGecchi16Font("item"); //OK
    pOK->update("[OK]", ALIGN_CENTER, VALIGN_MIDDLE);
    addSelectItem(pOK, PX_C(100), PX_C(300), -1);

    //�㉺�I�[�_�[��ǉ�
    for (int i = 15; i <= 0; i--) {  //OK�Ł���"P"�ɃJ�[�\���������邽�ߋt
        relationItemExNext(i   , i+16);
        relationItemExNext(i+16, i+32);
        relationItemExNext(i+32, i+48);
        relationItemExNext(i+48, i+64);
        relationItemExNext(i+64, ITEM_OK); //�ŉ��i�ŉ���OK��
    }

    //���j���[�J�[�\����ݒ�
    CursorNameEntryMenu* pCursor = NEW CursorNameEntryMenu("CursorNameEntryMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    setSelectedItemIndex(0); //�J�[�\���̏����I���A�C�e����ݒ�
    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�����i�\����\�����̋����j
                                            //�ォ�牺�֏����X���C�h������

    //�L�����Z���������ړ���A�C�e��
    relationItemCancel(ITEM_BS);

    pConfirmMenu_ = NEW MenuBoardConfirm("confirm"); //Yes No �₢���킹���j���[�𐶐�
    addSubLast(pConfirmMenu_);                       //�T�u�ɒǉ�
}
bool MenuBoardNameEntry::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardNameEntry::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}
bool MenuBoardNameEntry::condMoveCursorExNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardNameEntry::condMoveCursorExPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}

void MenuBoardNameEntry::processBehavior() {
    MenuBoard::processBehavior();

    //�T�u���j���[����
    StringBoardMenu* pSub = getSubMenu();
    if (pSub) {
        if (pSub->isJustDecided()) {
            if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {

                if (getSelectedIndex() == ITEM_OK) {
                    //�l�[���G���g���[����OK
                }
            } else if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkSub();
            } else {
            }
        } else {

        }
    }
}

void MenuBoardNameEntry::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BS) {
        sink();
    } else if (prm_item_index == ITEM_OK) {
        riseSub(pConfirmMenu_, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50)); //�T�u���j���[�N��
    }
}

void MenuBoardNameEntry::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    if (prm_item_index == ITEM_BS) {
        //�P���������I
    }
}

MenuBoardNameEntry::~MenuBoardNameEntry() {
}
