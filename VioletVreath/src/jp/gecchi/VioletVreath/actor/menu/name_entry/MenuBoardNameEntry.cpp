#include "MenuBoardNameEntry.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "CursorNameEntryMenu.h"
#include "jp/ggaf/lib/util/WMKeyInput.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelFont16x32.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/menu/MousePointer.h"


using namespace GgafLib;
using namespace VioletVreath;

const char* MenuBoardNameEntry::apInputItemStr_[] = {
     " ", "!", "\"","#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
     "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?",
     "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
     "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\","]", "^", "_",
     "`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
     "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", "~"
};
int MenuBoardNameEntry::input_item_num_ = (16*6) - 1;

MenuBoardNameEntry::MenuBoardNameEntry(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardNameEntry";
    setWidth(PX_C(24*32));
    setHeight(PX_C(9*32));
    //���j���[�A�C�e���i���͕����Ձj�ݒ�
    for (int i = 0; i < input_item_num_; i++) {
        LabelFont16x32* pLabel = NEW LabelFont16x32("item");
        pLabel->update(apInputItemStr_[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(10  + ((i%16)*(pLabel->_chr_base_width_px )*1.2)),
                        PX_C(100 + ((i/16)*(pLabel->_chr_base_height_px)*1.2))  );
    }

    LabelFont16x32* pBS = NEW LabelFont16x32("[BS]"); //�o�b�N�X�y�[�X(�L�����Z������)
    pBS->update("[BS]", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pBS, PX_C(650), PX_C(100 + (pBS->_chr_base_height_px * 3 * 2)));
    ITEM_INDEX_BS_ = (input_item_num_+1) - 1; //index�Ȃ̂�-1

    LabelFont16x32* pOK = NEW LabelFont16x32("[OK]"); //OK
    pOK->update("[OK]", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pOK, PX_C(300), PX_C(300));
    ITEM_INDEX_OK_ = (input_item_num_+2) - 1;

    //�㉺�I�[�_�[��ǉ�
    for (int i = 0; i < 16; i++) {
        relateItemToExNext(i, i+16, i+32, i+48, i+64, i+80);
    }
    for (int i = 0; i < 15; i++) {
        relateItemToExNext(i+80, ITEM_INDEX_OK_); //�ŉ��i�́���OK�֍s��
    }
    relateItemToExNext(ITEM_INDEX_BS_, ITEM_INDEX_OK_); //[BS]���火��OK�֍s��

    //setNameFontBoard()���Ă�������
    pLabelInputedName_ = nullptr;
    pLabelSelectedChar_ = nullptr;

    //���j���[�J�[�\����ݒ�
    CursorNameEntryMenu* pCursor = NEW CursorNameEntryMenu("CursorNameEntryMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    selectItem(0);          //�J�[�\���̏����I���A�C�e����ݒ�
    setTransition(30, PX_C(0), -PX_C(100)); //�g�����W�V�������ォ�牺�֏����X���C�h
    relateAllItemToCancel(ITEM_INDEX_BS_);       //�L�����Z���������́A[BS]�ֈړ�
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No �₢���킹���j���[�𐶐�
    _is_input_keyboard = false;
}

void MenuBoardNameEntry::setNameFontBoard(FontSpriteActor* prm_pInputedName,
                                          FontSpriteActor* prm_pSelectedChar) {
    pLabelInputedName_ = prm_pInputedName;
    pLabelSelectedChar_ = prm_pSelectedChar;
}

bool MenuBoardNameEntry::condDecision() {
    if (VVB->isPushedDown(0, VVB_UI_EXECUTE)) {
        return true;
    } else if (pMousePointer_ && pMousePointer_->isReleasedUpButton(0)) {
        return true;
    } else if (VVB->isPushedDown(0, VVB_UI_CANCEL) &&
               getSelectedIndex() == ITEM_INDEX_BS_) {
        //���ʂ�[BS]�ŃL�����Z���{�^���������ꍇ�́B[BS]���u����i�U�镑���j�v�������Ƃɂ���
        getSeTransmitter()->play(SE_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoardNameEntry::condCancel() {
    if (VVB->isPushedDown(0, VVB_UI_CANCEL)) {
        //�u���j���[�A�C�e���F�C�Ӂv�ŁAVVB_UI_CANCEL �{�^���̏ꍇ��
        //���̃A�C�e�����u�L�����Z���v�������Ƃ���B(������O����)
        getSeTransmitter()->play(SE_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoardNameEntry::condSelectNext() {
    if (getSelectedIndex() == ITEM_INDEX_BS_) {  //BS�����֐i�߂Ȃ�����
        return false;
    } else {
        return VVB->isAutoRepeat(0, VVB_UI_RIGHT);
    }
}
bool MenuBoardNameEntry::condSelectPrev() {
    if (getSelectedIndex() == 0) { //�擪�������炳��ɖ߂�Ȃ�����
        return false;
    } else {
        return VVB->isAutoRepeat(0, VVB_UI_LEFT);
    }
}
bool MenuBoardNameEntry::condSelectExNext() {
    if (getSelectedIndex() == ITEM_INDEX_OK_) { //OK���牺�ւ͐i�߂Ȃ�����
        return false;
    } else {
        return VVB->isAutoRepeat(0, VVB_UI_DOWN);
    }
}
bool MenuBoardNameEntry::condSelectExPrev() {
    return VVB->isAutoRepeat(0, VVB_UI_UP);
}

void MenuBoardNameEntry::selectNext(bool prm_smooth) { //�E�̎�
    getMainCursor()->setPositionAt(_lstItems.getCurrent());
    if (getSelectedIndex() == ITEM_INDEX_OK_) {
        //[OK]����E�Ői�ޏꍇ�A�ŉ��i(4�i��)�̈�ԉE�̃A�C�e��("_")�ɐi��
        _lstItems.current((16*3 + 16)-1);
    } else {
        _lstItems.next();
    }
    moveCursor(prm_smooth);
}

void MenuBoardNameEntry::selectPrev(bool prm_smooth) { //���̎�
    getMainCursor()->setPositionAt(_lstItems.getCurrent());
    if (getSelectedIndex() == ITEM_INDEX_BS_) { //[BS]���獶�Ŗ߂�ꍇ�A
        int prev_item_index = getMvCursorHistoryIndex(1);
        if (prev_item_index < 0) {
            _lstItems.current(getMvCursorHistoryIndex(15));  //"/"
        } else {
            //���O�̌��̑I���A�C�e���ɖ߂�
            _lstItems.current(getMvCursorHistoryIndex(1));
        }
    } else if (getSelectedIndex() == ITEM_INDEX_OK_) { //[OK]���獶�Ŗ߂�ꍇ
        //�ŉ��i(4�i��)�̈�ԍ��̃A�C�e��("P")�ɖ߂�
        _lstItems.current((16*3 + 1)-1);
    } else {
        _lstItems.prev();
    }
    moveCursor(prm_smooth);
}
void MenuBoardNameEntry::selectExNext(bool prm_smooth) { //���̎�
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        getMainCursor()->setPositionAt(_lstItems.getCurrent());
        _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
        moveCursor(prm_smooth);
    } else {

    }
}
void MenuBoardNameEntry::selectExPrev(bool prm_smooth) { //��̎�
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        getMainCursor()->setPositionAt(_lstItems.getCurrent());
        if (getSelectedIndex() == ITEM_INDEX_OK_) { //OK�����Ŗ߂�ꍇ�A
            int prev_item_index = getMvCursorHistoryIndex(1);
            if (prev_item_index < 0) {
                _lstItems.current((16*3 + 1)-1); //"P"
            } else {
                //���̑I���A�C�e���ɖ߂�
                _lstItems.current(prev_item_index);
            }
        } else {
            _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
        }
        moveCursor(prm_smooth);
    } else {
    }
}
void MenuBoardNameEntry::moveCursor(bool prm_smooth) {
    MenuBoard::moveCursor(prm_smooth);
    _is_input_keyboard = false; //�㉺���E�ŕ�����I��ł���BRETEUN�����̋����͕�������
}

void MenuBoardNameEntry::onActive() {
    WMKeyInput::init(); //��ԃN���A
}

void MenuBoardNameEntry::processBehavior() {
#ifdef MY_DEBUG
    if (pLabelInputedName_ == nullptr || pLabelSelectedChar_ == nullptr) {
        throwCriticalException("���O�� setNameFontBoard() ���Ă��������B");
    }
#endif
    MenuBoard::processBehavior();

    WMKeyInput::updateState();
    int push_down_char[3];
    const int push_down_num = WMKeyInput::getPushedDownKey(3, push_down_char);
    for (int i = 0; i < push_down_num; i++) {
        inputChar(push_down_char[i]);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_BACKSPACE)) {
        //[BS]�Ō���i�U�镑���j�̏���
        int len = pLabelInputedName_->_len;
        if (len > 0) {
            //�P������������B
            pLabelInputedName_->deleteUpdate(1);
        } else {
            //�������镶���͂�������
        }
    }

    if (getSelectedIndex() == ITEM_INDEX_OK_) {
        DefaultFramedBoardMenu* pMenuConfirm = getSubMenu();
        if (pMenuConfirm->hasJustDecided()) { //�T�u���j���[�Łu����i�U�镑���j�v�̎�
            if (pMenuConfirm->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {
                //�l�[���G���g���[����OK
                throwEventUpperTree(EVENT_MENU_NAMEENTRY_DONE);
                _TRACE_(FUNC_NAME<<" �����܂��B�C�x���g�𓊂��� throwEventUpperTree(EVENT_MENU_NAMEENTRY_DONE);");
                sinkCurrentSubMenu();
            } else if (pMenuConfirm->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkCurrentSubMenu();
            } else {
            }
        } else {
        }
    }

    //�J�[�\�������\��
    pixcoord name_width = pLabelInputedName_->_px_row_width[0];
    int len = pLabelInputedName_->_len;
    pLabelSelectedChar_->_x = pLabelInputedName_->_x + PX_C(name_width);
    if (_is_input_keyboard) {
        if (len >= RANKINGTABLE_NAME_LEN) {
            //10�����ȏ�̏ꍇ�J�[�\�������\������
            pLabelSelectedChar_->update("");
        } else {
            pLabelSelectedChar_->update("_");
        }
    } else {
        int item_index = getSelectedIndex();

        if (0 <= item_index && item_index <= (input_item_num_-1)) {
            if (len >= RANKINGTABLE_NAME_LEN) {
                //10�����ȏ�̏ꍇ�J�[�\�������\������
                pLabelSelectedChar_->update("");
            } else {
                //10���������̏ꍇ�J�[�\�������\���Ƃ��āA�I�𕶎���\��
                pLabelSelectedChar_->update(apInputItemStr_[item_index]);
            }
        } else if (item_index == ITEM_INDEX_BS_) {
            //[BS]���̕\��
            pLabelSelectedChar_->update("<<[BS]");
        } else if (item_index == ITEM_INDEX_OK_) {
            //[OK]���̕\��
            pLabelSelectedChar_->update(" [OK]?");
        }
    }
}

void MenuBoardNameEntry::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
    if (_is_input_keyboard) {
        //�L�[���͒��Ȃ�Ίm�F�T�u���j���[�N��
        selectItem(ITEM_INDEX_OK_);
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y);
    } else {
        //����i�U�镑���j�̏���
        int item_index = getSelectedIndex();
        int len = pLabelInputedName_->_len;
        if (prm_item_index == ITEM_INDEX_BS_) {
            //[BS]�Ō���i�U�镑���j�̏���
            if (len > 0) {
                //�P������������B
                char cstr[RANKINGTABLE_NAME_LEN+1];
                pLabelInputedName_->getDrawString(cstr);
                cstr[len-1] = '\0';
                pLabelInputedName_->update(cstr);
            } else {
                //�������镶���͂�������
            }
        } else if (prm_item_index == ITEM_INDEX_OK_) {
            //[OK]�Ō���i�U�镑���j�̏����I��
            //�m�F�T�u���j���[�N��
            riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y);
        } else {
            //���̑��A�C�e���i���͕����j�Ō���i�U�镑���j�̏���
            if (len >= RANKINGTABLE_NAME_LEN) {
                //10�����ȏ�̏ꍇ
                //�������Ȃ�
            } else {
                //�������͂���
                char cstr[RANKINGTABLE_NAME_LEN+1];
                pLabelInputedName_->getDrawString(cstr);
                std::string s = std::string(cstr) + std::string(apInputItemStr_[item_index]);
                pLabelInputedName_->update(s.c_str());
            }
        }
    }
}

void MenuBoardNameEntry::inputChar(const int prm_c) {
    _is_input_keyboard = true;
    int len = pLabelInputedName_->_len;
    if (len >= RANKINGTABLE_NAME_LEN) {
        //10�����ȏ�̏ꍇ
        getSeTransmitter()->play(SE_WRONG);
    } else {
        if (32 <= prm_c && prm_c <= 255) {
            if (pLabelInputedName_->isDispChr(prm_c)) {
                pLabelInputedName_->appendUpdate(prm_c);
            } else {
                //�\���͈͊O����
                pLabelInputedName_->appendUpdate('?');
            }
        } else {
            getSeTransmitter()->play(SE_WRONG);
        }
    }
}
void MenuBoardNameEntry::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
//    if (prm_item_index == ITEM_BS) {
//        //�P��������
//        std::string s = getDrawString();
//        if (s.length() > 0) {
//            pLabelInputedName_->update(s.substr(0, s.length()-1).c_str());
//        }
//    }
}

MenuBoardNameEntry::~MenuBoardNameEntry() {
}

