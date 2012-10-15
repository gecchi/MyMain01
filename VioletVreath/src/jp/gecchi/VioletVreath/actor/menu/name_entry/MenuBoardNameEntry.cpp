#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

char* MenuBoardNameEntry::apInputItemStr_[] = {
     " ", "!", "\"","#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
     "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?",
     "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
     "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\","]", "^", "_"
};
int MenuBoardNameEntry::input_item_num_ = 16*4;

MenuBoardNameEntry::MenuBoardNameEntry(const char* prm_name) :
        MenuBoard(prm_name, "board_bg01") {
    _class_name = "MenuBoardNameEntry";
    //メニューウィンドウ設定
    update("%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'\n"
           ")******************************+\n"
           ")******************************+\n"
           ")******************************+\n"
           ")******************************+\n"
           ")******************************+\n"
           ")******************************+\n"
           "-............................../");
//        update("%&'\n"
//               ")*+\n"
//               "-./");

    _Z = 5; //プライオリティ

    //メニューアイテム（入力文字盤）設定
    for (int i = 0; i < input_item_num_; i++) {
        LabelGecchi16Font* pLabel = NEW LabelGecchi16Font("item");
        pLabel->update(apInputItemStr_[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(10  + ((i%16)*(pLabel->_chr_width_px)*2)  ),
                        PX_C(100 + ((i/16)*(pLabel->_chr_height_px)*2) ),
                        -1);
    }

    LabelGecchi16Font* pBS = NEW LabelGecchi16Font("[BS]"); //バックスペース(キャンセル扱い)
    pBS->update("[BS]", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pBS, PX_C(650), PX_C(100 + (pBS->_chr_height_px * 3 * 2)), -1);
    ITEM_INDEX_BS_ = (input_item_num_+1) - 1; //indexなので-1

    LabelGecchi16Font* pOK = NEW LabelGecchi16Font("[OK]"); //OK
    pOK->update("[OK]", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pOK, PX_C(300), PX_C(300), -1);
    ITEM_INDEX_OK_ = (input_item_num_+2) - 1;

    //上下オーダーを追加
    for (int i = 0; i < 16; i++) {
        relateItemExNext(i, i+16, i+32, i+48, ITEM_INDEX_OK_); //最下段は↓でOKへ行く
    }
    relateItemExNext(ITEM_INDEX_BS_, ITEM_INDEX_OK_); //[BS]から↓もOKへ行く

    //setNameStringBoard()してください
    pLabelInputedName_ = NULL;
    pLabelSelectedChar_ = NULL;

    //メニューカーソルを設定
    CursorNameEntryMenu* pCursor = NEW CursorNameEntryMenu("CursorNameEntryMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    setSelectedIndex(0);          //カーソルの初期選択アイテムを設定
    setTransition(30, PX_C(0), -PX_C(100)); //トランジションを上から下へ少しスライド
    relateAllItemCancel(ITEM_INDEX_BS_);       //キャンセル押下時は、[BS]へ移動
    setSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューを生成
}

void MenuBoardNameEntry::setNameStringBoard(StringSpriteActor* prm_pInputedName,
                                            StringSpriteActor* prm_pSelectedChar) {
    pLabelInputedName_ = prm_pInputedName;
    pLabelSelectedChar_ = prm_pSelectedChar;
}

bool MenuBoardNameEntry::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        _pSeTxer->play(SE_DECIDED_NOMAL);
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               getSelectedIndex() == ITEM_INDEX_BS_) {
        //特別に[BS]でキャンセルボタン押した場合は。[BS]を「決定（振る舞い）」したことにする
        _pSeTxer->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoardNameEntry::condCancel() {
    if (VB->isPushedDown(VB_UI_CANCEL)) {
        //「メニューアイテム：任意」で、VB_UI_CANCEL ボタンの場合は
        //そのアイテムを「キャンセル」した事とする。(当たり前だが)
        _pSeTxer->play(SE_DECIDED_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoardNameEntry::condMoveCursorNext() {
    if (getSelectedIndex() == ITEM_INDEX_BS_) {  //BSから先へ進めなくする
        return false;
    } else {
        return VB->isAutoRepeat(VB_UI_RIGHT);
    }
}
bool MenuBoardNameEntry::condMoveCursorPrev() {
    if (getSelectedIndex() == 0) { //先頭文字からさらに戻れなくする
        return false;
    } else {
        return VB->isAutoRepeat(VB_UI_LEFT);
    }
}
bool MenuBoardNameEntry::condMoveCursorExNext() {
    if (getSelectedIndex() == ITEM_INDEX_OK_) { //OKから下へは進めなくする
        return false;
    } else {
        return VB->isAutoRepeat(VB_UI_DOWN);
    }
}
bool MenuBoardNameEntry::condMoveCursorExPrev() {
    return VB->isAutoRepeat(VB_UI_UP);
}

void MenuBoardNameEntry::moveCursorNext() { //右の時
    if (_pCursor) {
        _pCursor->locateWith(_lstItems.getCurrent());
    }
    if (getSelectedIndex() == ITEM_INDEX_OK_) {
        //[OK]から右で進む場合、最下段(4段目)の一番右のアイテム("_")に進む
        _lstItems.current((16*3 + 16)-1);
    } else {
        _lstItems.next();
    }
    moveCursor();
}
void MenuBoardNameEntry::moveCursorPrev() { //左の時
    if (_pCursor) {
        _pCursor->locateWith(_lstItems.getCurrent());
    }
    if (getSelectedIndex() == ITEM_INDEX_BS_) { //[BS]から左で戻る場合、
        //直前の元の選択アイテムに戻す
        _lstItems.current(getSelectedHistoryIndex(1));
    } else if (getSelectedIndex() == ITEM_INDEX_OK_) { //[OK]から左で戻る場合
        //最下段(4段目)の一番左のアイテム("P")に戻す
        _lstItems.current((16*3 + 1)-1);
    } else {
        _lstItems.prev();
    }
    moveCursor();
}
void MenuBoardNameEntry::moveCursorExNext() { //下の時
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
        moveCursor();
    } else {

    }
}
void MenuBoardNameEntry::moveCursorExPrev() { //上の時
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
        }
        if (getSelectedIndex() == ITEM_INDEX_OK_) { //OKから上で戻る場合、
            //元の選択アイテムに戻す
            _lstItems.current(getSelectedHistoryIndex(1));
        } else {
            _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
        }
        moveCursor();
    } else {
    }
}

void MenuBoardNameEntry::processBehavior() {
#ifdef MY_DEBUG
    if (pLabelInputedName_ == NULL || pLabelSelectedChar_ == NULL) {
        throwGgafCriticalException("MenuBoardNameEntry::processBehavior() 事前に setNameStringBoard() してください。");
    }

#endif
    MenuBoard::processBehavior();
    if (getSelectedIndex() == ITEM_INDEX_OK_) {
        StringBoardMenu* pMenuConfirm = getSubMenu();
        if (pMenuConfirm->isJustDecided()) { //サブメニューで「決定（振る舞い）」の時
            if (pMenuConfirm->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {
                //ネームエントリー完了OK
                throwEventToUpperTree(EVENT_MENU_NAMEENTRY_DONE);
                _TRACE_("MenuBoardNameEntry::processBehavior() おしまい。イベントを投げた throwEventToUpperTree(EVENT_MENU_NAMEENTRY_DONE);");
                sinkSubMenu();
            } else if (pMenuConfirm->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkSubMenu();
            } else {
            }
        } else {
        }
    }

    //カーソル文字表示
    int item_index = getSelectedIndex();
    int len = strlen(pLabelInputedName_->_draw_string);
    if (0 <= item_index && item_index <= (input_item_num_-1)) {
        if (len >= QUERYRANKING_NAME_LEN) {
            //10文字以上の場合カーソル文字表示無し
            pLabelSelectedChar_->update("");
        } else {
            //10文字未満の場合カーソル文字表示として、選択文字を表示
            std::string s = " " + std::string(len, ' ') + std::string(apInputItemStr_[item_index]);
            pLabelSelectedChar_->update(s.c_str());
        }
    } else if (item_index == ITEM_INDEX_BS_) {
        //[BS]時の表示
        std::string s = "      " + std::string(len, ' ') + "<<[BS]";
        pLabelSelectedChar_->update(s.c_str());
    } else if (item_index == ITEM_INDEX_OK_) {
        //[OK]時の表示
        std::string s = "      " + std::string(len, ' ') + " [OK]?";
        pLabelSelectedChar_->update(s.c_str());
    }
    //pLabelSelectedChar_->_X = pLabelInputedName_->_X + PX_C(pLabelInputedName_->_chr_width_px * len);
}

void MenuBoardNameEntry::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    //決定（振る舞い）の処理
    int item_index = getSelectedIndex();
    int len = strlen(pLabelInputedName_->_draw_string);
    if (prm_item_index == ITEM_INDEX_BS_) {
        //[BS]で決定（振る舞い）の処理
        if (len > 0) {
            //１文字除去する。
            std::string s = std::string(pLabelInputedName_->_draw_string);
            pLabelInputedName_->update(s.substr(0, s.length()-1).c_str());
        } else {
            //除去する文字はもう無い
        }
    } else if (prm_item_index == ITEM_INDEX_OK_) {
        //[OK]で決定（振る舞い）の処理終了
        //確認サブメニュー起動
        riseSubMenu(getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y);
    } else {
        //その他アイテム（入力文字）で決定（振る舞い）の処理
        //文字入力する
        if (len >= QUERYRANKING_NAME_LEN) {
            //10文字以上の場合
            //何もしない
        } else {
            std::string s = std::string(pLabelInputedName_->_draw_string) + std::string(apInputItemStr_[item_index]);
            pLabelInputedName_->update(s.c_str());
        }
    }
}

void MenuBoardNameEntry::onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
//    if (prm_item_index == ITEM_BS) {
//        //１文字除去
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
