#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MenuBoardNameEntry::MenuBoardNameEntry(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardNameEntry";
    //���j���[�E�B���h�E�ݒ�
    update("%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'\n"
           ")******************************+\n"
           ")******************************+\n"
           ")******************************+\n"
           ")******************************+\n"
           ")******************************+\n"
           ")******************************+\n"
           "-............................../");
    _Z = 5; //�v���C�I���e�B

    //���j���[�A�C�e���i�I���j�ݒ�
    char* apItemStr[] = {
         " ", "!", "\"","#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
         "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?",
         "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
         "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\","]", "^", "_"
    };


    int item_index = 0;
    for (int i = ' '-' '; i <= '_'-' '; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apItemStr[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addSelectItem(pLabel, PX_C(10 + ((i%16)*(pLabel->_chr_width_px * 2))),
                              PX_C(200 + ((i/16)*(pLabel->_chr_height_px * 2))),
                              -1);
        item_index++;
    }
    ITEM_BS = item_index; item_index++;
    ITEM_OK = item_index; item_index++;

    LabelGecchi16Font* pBS = NEW LabelGecchi16Font("[BS]"); //�o�b�N�X�y�[�X(�L�����Z������)
    pBS->update("[BS]", ALIGN_CENTER, VALIGN_MIDDLE);
    addSelectItem(pBS, PX_C(700), PX_C(100), -1);

    LabelGecchi16Font* pOK = NEW LabelGecchi16Font("[OK]"); //OK
    pOK->update("[OK]", ALIGN_CENTER, VALIGN_MIDDLE);
    addSelectItem(pOK, PX_C(100), PX_C(300), -1);

    //�㉺�I�[�_�[��ǉ�
    for (int i = 0; i < 16; i++) {
        relationItemExNext(i   , i+16);
        relationItemExNext(i+16, i+32);
        relationItemExNext(i+32, i+48);
    }

    for (int i = 48; i < 48+16; i++) {
        //�ŉ��i�Ł��̏ꍇOK�֍s��
        relationItemExNext(i, ITEM_OK);
    }
    relationItemExNext(48+8, ITEM_OK); //OK�Ł��������ꍇ�̖߂��


    //�v���C���[���͂̃l�[���\��
    pLabelInputedName_ = NEW LabelGecchi32Font("InputedName");
    pLabelInputedName_->update("");
    addDispItem(pLabelInputedName_, PX_C(800), PX_C(300), -1);
    pLabelSelectedChar_ = NEW LabelGecchi32Font("SelectedChar");
    pLabelSelectedChar_->_pFader->beat(60, 30, 0, 0, -1); //�`�J�`�J�_��
    addDispItem(pLabelSelectedChar_, PX_C(800), PX_C(300), -1);


    //���j���[�J�[�\����ݒ�
    CursorNameEntryMenu* pCursor = NEW CursorNameEntryMenu("CursorNameEntryMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    setSelectedItemIndex('A'-' '); //�J�[�\���̏����I���A�C�e����ݒ�
    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�������ォ�牺�֏����X���C�h
    relationAllItemCancel(ITEM_BS); //�L�����Z���������́A[BS]�ֈړ�
    pConfirmMenu_ = NEW MenuBoardConfirm("confirm"); //Yes No �₢���킹���j���[�𐶐�
    addSubLast(pConfirmMenu_);                       //�T�u�ɒǉ�
}
bool MenuBoardNameEntry::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        _TRACE_("condDecision() �ʏ�̌���ɂ��܂����I");
        _pSeTxer->play(SE_DECIDED_NOMAL);
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               getSelectedIndex() == ITEM_BS) {
        //���ʂ�[BS]�ŃL�����Z���{�^���������ꍇ�́B[BS]���u����i�U�镑���j�v�������Ƃɂ���
        _TRACE_("condDecision() [BS]�ŃL�����Z���Ȃ̂Ō���ɂ��܂����I");
        _pSeTxer->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoardNameEntry::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //�u���j���[�A�C�e���F�C�Ӂv�ŁAVB_UI_CANCEL �{�^���̏ꍇ��
        //���̃A�C�e�����u�L�����Z���v�������Ƃ���B(������O����)
        _pSeTxer->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoardNameEntry::condMoveCursorNext() {
    return VB->isAutoRepeat(VB_UI_RIGHT);
}
bool MenuBoardNameEntry::condMoveCursorPrev() {
    return VB->isAutoRepeat(VB_UI_LEFT);
}
bool MenuBoardNameEntry::condMoveCursorExNext() {
    return VB->isAutoRepeat(VB_UI_DOWN);
}
bool MenuBoardNameEntry::condMoveCursorExPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
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
                    _TRACE_("�l�[���G���g���[����OK!!!");
                    std::string s = std::string(pLabelInputedName_->_draw_string);
                    _TRACE_("���͂�\""<<s<<"\"�ł���");
                }
            } else if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkSub();
            } else {
            }
        } else {

        }
    }

    //�J�[�\�������\��
    int item_no = getSelectedIndex();
    int len = strlen(pLabelInputedName_->_draw_string);
    if (' '-' ' <= item_no && item_no <= '_'-' ') {
        //' ' �` '_' �̊Ԃ̏ꍇ
        if (len > 10) {
            //11�����ȏ�̏ꍇ
            pLabelSelectedChar_->update(" ");
        } else {
            //�ʏ펞�A�I�𕶎���\��
            char a[2];
            a[0] = item_no + ' ';
            a[1] = '\0';
            pLabelSelectedChar_->update(a);
        }
    } else if (item_no == ITEM_BS) {
        //[BS]���̕\��
        pLabelSelectedChar_->update("<<BS");
    } else if (item_no == ITEM_OK) {
        //[OK]���̕\��
        pLabelSelectedChar_->update(" ");
    }
    pLabelSelectedChar_->_X = pLabelInputedName_->_X +
            PX_C(pLabelInputedName_->_chr_width_px * len);
    pLabelSelectedChar_->_pFader->behave();
}

void MenuBoardNameEntry::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    //����i�U�镑���j�̏���
    int item_no = getSelectedIndex();
    int len = strlen(pLabelInputedName_->_draw_string);
    if (prm_item_index == ITEM_BS) {
        //[BS]�Ō���i�U�镑���j�̏���
        if (len > 0) {
            //�P������������B
            std::string s = std::string(pLabelInputedName_->_draw_string);
            pLabelInputedName_->update(s.substr(0, s.length()-1).c_str());
        } else {
            //�������镶���͂�������
        }
    } else if (prm_item_index == ITEM_OK) {
        //[OK]�Ō���i�U�镑���j�̏����I��
        //�m�F�T�u���j���[�N��
        riseSub(pConfirmMenu_, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50));
    } else {
        //���̑��A�C�e���i���͕����j�Ō���i�U�镑���j�̏���
        //�������͂���
        if (len > 10) {
            //11�����ȏ�̏ꍇ
            //�������Ȃ�
        } else {
            char input_char = item_no + ' '; //���͕���
            std::string s = std::string(pLabelInputedName_->_draw_string) + std::string(1, input_char);
            pLabelInputedName_->update(s.c_str());
        }
    }

}

void MenuBoardNameEntry::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
//    if (prm_item_index == ITEM_BS) {
//        //�P��������
//        std::string s = std::string(pLabelInputedName_->_draw_string);
//        if (s.length() > 0) {
//            pLabelInputedName_->update(s.substr(0, s.length()-1).c_str());
//        }
//    }
}

MenuBoardNameEntry::~MenuBoardNameEntry() {
}


/*
    mapDIK2CHR_[DIK_SPACE     ] =  ' ';
//    mapDIK2CHR_[              ] =  '!';
//    mapDIK2CHR_[              ] =  '"';
//    mapDIK2CHR_[              ] =  '#';
//    mapDIK2CHR_[              ] =  '$';
//    mapDIK2CHR_[              ] =  '%';
//    mapDIK2CHR_[              ] =  '&';
    mapDIK2CHR_[DIK_APOSTROPHE] =  '\'';
//    mapDIK2CHR_[              ] =  '(';
//    mapDIK2CHR_[              ] =  ')';
//    mapDIK2CHR_[              ] =  '*';
//    mapDIK2CHR_[              ] =  '+';
    mapDIK2CHR_[DIK_COMMA     ] =  ',';
    mapDIK2CHR_[DIK_MINUS     ] =  '-';
    mapDIK2CHR_[DIK_PERIOD    ] =  '.';
    mapDIK2CHR_[DIK_SLASH     ] =  '/';
    mapDIK2CHR_[DIK_0         ] =  '0';
    mapDIK2CHR_[DIK_1         ] =  '1';
    mapDIK2CHR_[DIK_2         ] =  '2';
    mapDIK2CHR_[DIK_3         ] =  '3';
    mapDIK2CHR_[DIK_4         ] =  '4';
    mapDIK2CHR_[DIK_5         ] =  '5';
    mapDIK2CHR_[DIK_6         ] =  '6';
    mapDIK2CHR_[DIK_7         ] =  '7';
    mapDIK2CHR_[DIK_8         ] =  '8';
    mapDIK2CHR_[DIK_9         ] =  '9';
    mapDIK2CHR_[DIK_SEMICOLON ] =  ':';
//    mapDIK2CHR_[              ] =  ';';
//    mapDIK2CHR_[              ] =  '<';
    mapDIK2CHR_[DIK_EQUALS    ] =  '=';
//    mapDIK2CHR_[              ] =  '>';
//    mapDIK2CHR_[              ] =  '?';
//    mapDIK2CHR_[              ] =  '@';
    mapDIK2CHR_[DIK_A         ] =  'A';
    mapDIK2CHR_[DIK_B         ] =  'B';
    mapDIK2CHR_[DIK_C         ] =  'C';
    mapDIK2CHR_[DIK_D         ] =  'D';
    mapDIK2CHR_[DIK_E         ] =  'E';
    mapDIK2CHR_[DIK_F         ] =  'F';
    mapDIK2CHR_[DIK_G         ] =  'G';
    mapDIK2CHR_[DIK_H         ] =  'H';
    mapDIK2CHR_[DIK_I         ] =  'I';
    mapDIK2CHR_[DIK_J         ] =  'J';
    mapDIK2CHR_[DIK_K         ] =  'K';
    mapDIK2CHR_[DIK_L         ] =  'L';
    mapDIK2CHR_[DIK_M         ] =  'M';
    mapDIK2CHR_[DIK_N         ] =  'N';
    mapDIK2CHR_[DIK_O         ] =  'O';
    mapDIK2CHR_[DIK_P         ] =  'P';
    mapDIK2CHR_[DIK_Q         ] =  'Q';
    mapDIK2CHR_[DIK_R         ] =  'R';
    mapDIK2CHR_[DIK_S         ] =  'S';
    mapDIK2CHR_[DIK_T         ] =  'T';
    mapDIK2CHR_[DIK_U         ] =  'U';
    mapDIK2CHR_[DIK_V         ] =  'V';
    mapDIK2CHR_[DIK_W         ] =  'W';
    mapDIK2CHR_[DIK_X         ] =  'X';
    mapDIK2CHR_[DIK_Y         ] =  'Y';
    mapDIK2CHR_[DIK_Z         ] =  'Z';
    mapDIK2CHR_[DIK_LBRACKET  ] =  '[';
    mapDIK2CHR_[DIK_BACKSLASH ] =  '\\';
//    mapDIK2CHR_[              ] =  ']';
//    mapDIK2CHR_[              ] =  '^';
    mapDIK2CHR_[DIK_UNDERLINE ] =  '_';


*/
