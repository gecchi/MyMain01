#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

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
    _Z = 5; //プライオリティ

    //メニューアイテム（選択可）設定
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

    LabelGecchi16Font* pBS = NEW LabelGecchi16Font("[BS]"); //バックスペース(キャンセル扱い)
    pBS->update("[BS]", ALIGN_CENTER, VALIGN_MIDDLE);
    addSelectItem(pBS, PX_C(700), PX_C(100), -1);

    LabelGecchi16Font* pOK = NEW LabelGecchi16Font("[OK]"); //OK
    pOK->update("[OK]", ALIGN_CENTER, VALIGN_MIDDLE);
    addSelectItem(pOK, PX_C(100), PX_C(300), -1);

    //上下オーダーを追加
    for (int i = 0; i < 16; i++) {
        relationItemExNext(i   , i+16);
        relationItemExNext(i+16, i+32);
        relationItemExNext(i+32, i+48);
    }

    for (int i = 48; i < 48+16; i++) {
        //最下段で↓の場合OKへ行く
        relationItemExNext(i, ITEM_OK);
    }
    relationItemExNext(48+8, ITEM_OK); //OKで↑押した場合の戻り先


    //プレイヤー入力のネーム表示
    pLabelInputedName_ = NEW LabelGecchi32Font("InputedName");
    pLabelInputedName_->update("");
    addDispItem(pLabelInputedName_, PX_C(800), PX_C(300), -1);
    pLabelSelectedChar_ = NEW LabelGecchi32Font("SelectedChar");
    pLabelSelectedChar_->_pFader->beat(60, 30, 0, 0, -1); //チカチカ点滅
    addDispItem(pLabelSelectedChar_, PX_C(800), PX_C(300), -1);


    //メニューカーソルを設定
    CursorNameEntryMenu* pCursor = NEW CursorNameEntryMenu("CursorNameEntryMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setCursor(pCursor);

    setSelectedItemIndex('A'-' '); //カーソルの初期選択アイテムを設定
    setTransition(30, PX_C(0), -PX_C(100)); //トランジションを上から下へ少しスライド
    relationAllItemCancel(ITEM_BS); //キャンセル押下時は、[BS]へ移動
    pConfirmMenu_ = NEW MenuBoardConfirm("confirm"); //Yes No 問い合わせメニューを生成
    addSubLast(pConfirmMenu_);                       //サブに追加
}
bool MenuBoardNameEntry::condDecision() {
    if (VB->isPushedDown(VB_UI_EXECUTE)) {
        _TRACE_("condDecision() 通常の決定にしました！");
        _pSeTxer->play(SE_DECIDED_NOMAL);
        return true;
    } else if (VB->isPushedDown(VB_UI_CANCEL) &&
               getSelectedIndex() == ITEM_BS) {
        //特別に[BS]でキャンセルボタン押した場合は。[BS]を「決定（振る舞い）」したことにする
        _TRACE_("condDecision() [BS]でキャンセルなので決定にしました！");
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

    //サブメニュー判定
    StringBoardMenu* pSub = getSubMenu();
    if (pSub) {
        if (pSub->isJustDecided()) {
            if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {
                if (getSelectedIndex() == ITEM_OK) {
                    //ネームエントリー完了OK
                    _TRACE_("ネームエントリー完了OK!!!");
                    std::string s = std::string(pLabelInputedName_->_draw_string);
                    _TRACE_("入力は\""<<s<<"\"でした");
                }
            } else if (pSub->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkSub();
            } else {
            }
        } else {

        }
    }

    //カーソル文字表示
    int item_no = getSelectedIndex();
    int len = strlen(pLabelInputedName_->_draw_string);
    if (' '-' ' <= item_no && item_no <= '_'-' ') {
        //' ' ～ '_' の間の場合
        if (len > 10) {
            //11文字以上の場合
            pLabelSelectedChar_->update(" ");
        } else {
            //通常時、選択文字を表示
            char a[2];
            a[0] = item_no + ' ';
            a[1] = '\0';
            pLabelSelectedChar_->update(a);
        }
    } else if (item_no == ITEM_BS) {
        //[BS]時の表示
        pLabelSelectedChar_->update("<<BS");
    } else if (item_no == ITEM_OK) {
        //[OK]時の表示
        pLabelSelectedChar_->update(" ");
    }
    pLabelSelectedChar_->_X = pLabelInputedName_->_X +
            PX_C(pLabelInputedName_->_chr_width_px * len);
    pLabelSelectedChar_->_pFader->behave();
}

void MenuBoardNameEntry::onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) {
    //決定（振る舞い）の処理
    int item_no = getSelectedIndex();
    int len = strlen(pLabelInputedName_->_draw_string);
    if (prm_item_index == ITEM_BS) {
        //[BS]で決定（振る舞い）の処理
        if (len > 0) {
            //１文字除去する。
            std::string s = std::string(pLabelInputedName_->_draw_string);
            pLabelInputedName_->update(s.substr(0, s.length()-1).c_str());
        } else {
            //除去する文字はもう無い
        }
    } else if (prm_item_index == ITEM_OK) {
        //[OK]で決定（振る舞い）の処理終了
        //確認サブメニュー起動
        riseSub(pConfirmMenu_, getSelectedItem()->_X + PX_C(50), getSelectedItem()->_Y + PX_C(50));
    } else {
        //その他アイテム（入力文字）で決定（振る舞い）の処理
        //文字入力する
        if (len > 10) {
            //11文字以上の場合
            //何もしない
        } else {
            char input_char = item_no + ' '; //入力文字
            std::string s = std::string(pLabelInputedName_->_draw_string) + std::string(1, input_char);
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
