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
    //メニューアイテム（入力文字盤）設定
    for (int i = 0; i < input_item_num_; i++) {
        LabelFont16x32* pLabel = NEW LabelFont16x32("item");
        pLabel->update(apInputItemStr_[i], ALIGN_CENTER, VALIGN_MIDDLE);
        addItem(pLabel, PX_C(10  + ((i%16)*(pLabel->_chr_base_width_px )*1.2)),
                        PX_C(100 + ((i/16)*(pLabel->_chr_base_height_px)*1.2))  );
    }

    LabelFont16x32* pBS = NEW LabelFont16x32("[BS]"); //バックスペース(キャンセル扱い)
    pBS->update("[BS]", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pBS, PX_C(650), PX_C(100 + (pBS->_chr_base_height_px * 3 * 2)));
    ITEM_INDEX_BS_ = (input_item_num_+1) - 1; //indexなので-1

    LabelFont16x32* pOK = NEW LabelFont16x32("[OK]"); //OK
    pOK->update("[OK]", ALIGN_CENTER, VALIGN_MIDDLE);
    addItem(pOK, PX_C(300), PX_C(300));
    ITEM_INDEX_OK_ = (input_item_num_+2) - 1;

    //上下オーダーを追加
    for (int i = 0; i < 16; i++) {
        relateItemToExNext(i, i+16, i+32, i+48, i+64, i+80);
    }
    for (int i = 0; i < 15; i++) {
        relateItemToExNext(i+80, ITEM_INDEX_OK_); //最下段は↓でOKへ行く
    }
    relateItemToExNext(ITEM_INDEX_BS_, ITEM_INDEX_OK_); //[BS]から↓もOKへ行く

    //setNameFontBoard()してください
    pLabelInputedName_ = nullptr;
    pLabelSelectedChar_ = nullptr;

    //メニューカーソルを設定
    CursorNameEntryMenu* pCursor = NEW CursorNameEntryMenu("CursorNameEntryMenu");
    pCursor->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setMainCursor(pCursor);

    selectItem(0);          //カーソルの初期選択アイテムを設定
    setTransition(30, PX_C(0), -PX_C(100)); //トランジションを上から下へ少しスライド
    relateAllItemToCancel(ITEM_INDEX_BS_);       //キャンセル押下時は、[BS]へ移動
    addSubMenu(NEW MenuBoardConfirm("confirm")); //Yes No 問い合わせメニューを生成
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
        //特別に[BS]でキャンセルボタン押した場合は。[BS]を「決定（振る舞い）」したことにする
        getSeTransmitter()->play(SE_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoardNameEntry::condCancel() {
    if (VVB->isPushedDown(0, VVB_UI_CANCEL)) {
        //「メニューアイテム：任意」で、VVB_UI_CANCEL ボタンの場合は
        //そのアイテムを「キャンセル」した事とする。(当たり前だが)
        getSeTransmitter()->play(SE_CANCEL);
        return true;
    } else {
        return false;
    }
}

bool MenuBoardNameEntry::condSelectNext() {
    if (getSelectedIndex() == ITEM_INDEX_BS_) {  //BSから先へ進めなくする
        return false;
    } else {
        return VVB->isAutoRepeat(0, VVB_UI_RIGHT);
    }
}
bool MenuBoardNameEntry::condSelectPrev() {
    if (getSelectedIndex() == 0) { //先頭文字からさらに戻れなくする
        return false;
    } else {
        return VVB->isAutoRepeat(0, VVB_UI_LEFT);
    }
}
bool MenuBoardNameEntry::condSelectExNext() {
    if (getSelectedIndex() == ITEM_INDEX_OK_) { //OKから下へは進めなくする
        return false;
    } else {
        return VVB->isAutoRepeat(0, VVB_UI_DOWN);
    }
}
bool MenuBoardNameEntry::condSelectExPrev() {
    return VVB->isAutoRepeat(0, VVB_UI_UP);
}

void MenuBoardNameEntry::selectNext(bool prm_smooth) { //右の時
    getMainCursor()->setPositionAt(_lstItems.getCurrent());
    if (getSelectedIndex() == ITEM_INDEX_OK_) {
        //[OK]から右で進む場合、最下段(4段目)の一番右のアイテム("_")に進む
        _lstItems.current((16*3 + 16)-1);
    } else {
        _lstItems.next();
    }
    moveCursor(prm_smooth);
}

void MenuBoardNameEntry::selectPrev(bool prm_smooth) { //左の時
    getMainCursor()->setPositionAt(_lstItems.getCurrent());
    if (getSelectedIndex() == ITEM_INDEX_BS_) { //[BS]から左で戻る場合、
        int prev_item_index = getMvCursorHistoryIndex(1);
        if (prev_item_index < 0) {
            _lstItems.current(getMvCursorHistoryIndex(15));  //"/"
        } else {
            //直前の元の選択アイテムに戻す
            _lstItems.current(getMvCursorHistoryIndex(1));
        }
    } else if (getSelectedIndex() == ITEM_INDEX_OK_) { //[OK]から左で戻る場合
        //最下段(4段目)の一番左のアイテム("P")に戻す
        _lstItems.current((16*3 + 1)-1);
    } else {
        _lstItems.prev();
    }
    moveCursor(prm_smooth);
}
void MenuBoardNameEntry::selectExNext(bool prm_smooth) { //下の時
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        getMainCursor()->setPositionAt(_lstItems.getCurrent());
        _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
        moveCursor(prm_smooth);
    } else {

    }
}
void MenuBoardNameEntry::selectExPrev(bool prm_smooth) { //上の時
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        getMainCursor()->setPositionAt(_lstItems.getCurrent());
        if (getSelectedIndex() == ITEM_INDEX_OK_) { //OKから上で戻る場合、
            int prev_item_index = getMvCursorHistoryIndex(1);
            if (prev_item_index < 0) {
                _lstItems.current((16*3 + 1)-1); //"P"
            } else {
                //元の選択アイテムに戻す
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
    _is_input_keyboard = false; //上下左右で文字を選んでいる。RETEUN押下の挙動は文字決定
}

void MenuBoardNameEntry::onActive() {
    WMKeyInput::init(); //状態クリア
}

void MenuBoardNameEntry::processBehavior() {
#ifdef MY_DEBUG
    if (pLabelInputedName_ == nullptr || pLabelSelectedChar_ == nullptr) {
        throwCriticalException("事前に setNameFontBoard() してください。");
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
        //[BS]で決定（振る舞い）の処理
        int len = pLabelInputedName_->_len;
        if (len > 0) {
            //１文字除去する。
            pLabelInputedName_->deleteUpdate(1);
        } else {
            //除去する文字はもう無い
        }
    }

    if (getSelectedIndex() == ITEM_INDEX_OK_) {
        DefaultFramedBoardMenu* pMenuConfirm = getSubMenu();
        if (pMenuConfirm->hasJustDecided()) { //サブメニューで「決定（振る舞い）」の時
            if (pMenuConfirm->getSelectedIndex() == MenuBoardConfirm::ITEM_OK) {
                //ネームエントリー完了OK
                throwEventUpperTree(EVENT_MENU_NAMEENTRY_DONE);
                _TRACE_(FUNC_NAME<<" おしまい。イベントを投げた throwEventUpperTree(EVENT_MENU_NAMEENTRY_DONE);");
                sinkCurrentSubMenu();
            } else if (pMenuConfirm->getSelectedIndex() == MenuBoardConfirm::ITEM_CANCEL) {
                sinkCurrentSubMenu();
            } else {
            }
        } else {
        }
    }

    //カーソル文字表示
    pixcoord name_width = pLabelInputedName_->_px_row_width[0];
    int len = pLabelInputedName_->_len;
    pLabelSelectedChar_->_x = pLabelInputedName_->_x + PX_C(name_width);
    if (_is_input_keyboard) {
        if (len >= RANKINGTABLE_NAME_LEN) {
            //10文字以上の場合カーソル文字表示無し
            pLabelSelectedChar_->update("");
        } else {
            pLabelSelectedChar_->update("_");
        }
    } else {
        int item_index = getSelectedIndex();

        if (0 <= item_index && item_index <= (input_item_num_-1)) {
            if (len >= RANKINGTABLE_NAME_LEN) {
                //10文字以上の場合カーソル文字表示無し
                pLabelSelectedChar_->update("");
            } else {
                //10文字未満の場合カーソル文字表示として、選択文字を表示
                pLabelSelectedChar_->update(apInputItemStr_[item_index]);
            }
        } else if (item_index == ITEM_INDEX_BS_) {
            //[BS]時の表示
            pLabelSelectedChar_->update("<<[BS]");
        } else if (item_index == ITEM_INDEX_OK_) {
            //[OK]時の表示
            pLabelSelectedChar_->update(" [OK]?");
        }
    }
}

void MenuBoardNameEntry::onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
    if (_is_input_keyboard) {
        //キー入力中ならば確認サブメニュー起動
        selectItem(ITEM_INDEX_OK_);
        riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y);
    } else {
        //決定（振る舞い）の処理
        int item_index = getSelectedIndex();
        int len = pLabelInputedName_->_len;
        if (prm_item_index == ITEM_INDEX_BS_) {
            //[BS]で決定（振る舞い）の処理
            if (len > 0) {
                //１文字除去する。
                char cstr[RANKINGTABLE_NAME_LEN+1];
                pLabelInputedName_->getDrawString(cstr);
                cstr[len-1] = '\0';
                pLabelInputedName_->update(cstr);
            } else {
                //除去する文字はもう無い
            }
        } else if (prm_item_index == ITEM_INDEX_OK_) {
            //[OK]で決定（振る舞い）の処理終了
            //確認サブメニュー起動
            riseSubMenu(0, getSelectedItem()->_x + PX_C(50), getSelectedItem()->_y);
        } else {
            //その他アイテム（入力文字）で決定（振る舞い）の処理
            if (len >= RANKINGTABLE_NAME_LEN) {
                //10文字以上の場合
                //何もしない
            } else {
                //文字入力する
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
        //10文字以上の場合
        getSeTransmitter()->play(SE_WRONG);
    } else {
        if (32 <= prm_c && prm_c <= 255) {
            if (pLabelInputedName_->isDispChr(prm_c)) {
                pLabelInputedName_->appendUpdate(prm_c);
            } else {
                //表示範囲外文字
                pLabelInputedName_->appendUpdate('?');
            }
        } else {
            getSeTransmitter()->play(SE_WRONG);
        }
    }
}
void MenuBoardNameEntry::onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) {
//    if (prm_item_index == ITEM_BS) {
//        //１文字除去
//        std::string s = getDrawString();
//        if (s.length() > 0) {
//            pLabelInputedName_->update(s.substr(0, s.length()-1).c_str());
//        }
//    }
}

MenuBoardNameEntry::~MenuBoardNameEntry() {
}

