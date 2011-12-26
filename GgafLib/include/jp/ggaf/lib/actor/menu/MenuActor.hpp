#ifndef MENUACTOR_H_
#define MENUACTOR_H_
namespace GgafLib {

enum MenuItemWay {
    ITEM_RELATION_EX_NEXT = 0,
    ITEM_RELATION_EX_PREV,
    ITEM_RELATION_TO_CANCEL,
};

/**
 * メニューGUIテンプレート .
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class MenuActor : public T {

protected:
    /** カーソル移動先アイテムの前フレームのX座標 */
    coord _X_cursor_target_prev;
    /** カーソル移動先アイテムの前フレームのY座標 */
    coord _Y_cursor_target_prev;
    /** カーソル移動先アイテムの前フレームのZ座標 */
    coord _Z_cursor_target_prev;
    /** フェードイン中は true */
    bool _with_rising;
    /** フェードアウト中は true */
    bool _with_sinking;
    /** フェードインが開始した瞬間のフレームだけ true */
    bool _is_just_with_rising;
    /** フェードアウトが開始した瞬間のフレームだけ true */
    bool _is_just_with_sinking;
    /**
     * _lstItems のアクティブ要素を next() へ移動させ、カーソルを移動 .
     */
    virtual void moveCursorNext();

    /**
     * _lstItems のアクティブ要素を prev() へ移動させ、カーソルを移動 .
     */
    virtual void moveCursorPrev();

    /**
     * _lstItems のアクティブ要素を gotoRelation(ITEM_RELATION_EX_NEXT) へ移動させ、カーソルを移動 .
     */
    virtual void moveCursorExNext();

    /**
     * _lstItems のアクティブ要素を gotoRelation(ITEM_RELATION_EX_PREV) へ移動させ、カーソルを移動 .
     */
    virtual void moveCursorExPrev();

    /**
     *  _lstItems のアクティブ要素を gotoRelation(ITEM_RELATION_TO_CANCEL) へ移動させ、カーソルを移動 .
     */
    virtual void moveCursorCancel();

public:

    /** [r]メニューアイテムのリスト */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstItems;
    /** [r]メニューカーソル */
    GgafDxCore::GgafDxDrawableActor* _pCursor;
    /** [r/w]メニューフェイドイン・アウト時のアルファ速度 */
    float _velo_alpha_fade;
    /** [r]カーソルが、メニューアイテム間を移動する際に費やすスフレーム数 */
    int _cursor_move_frames;
    /** [r]カーソルが移動時、アイテム間移動距離の速度０～最高速に達する時点の割合 */
    float _cursor_move_p1;
    /** [r]カーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合 */
    float _cursor_move_p2;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_model モデル識別名
     */
    MenuActor(const char* prm_name, const char* prm_model);

    /**
     * メニューアイテムを追加する .
     * @param prm_pItem メニューアイテム
     * @param prm_X_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_Z_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_X_local, coord prm_Y_local, coord prm_Z_local);
    /**
     * メニューカーソルオブジェクトを設定する .
     * 【注意】<BR>
     * カーソル移動を制御するため、MenuActor<T>::processBehavior() 内で、<BR>
     * _pCursor->_pKurokoA->behave(); <BR>
     * を実行しています。したがって、引数のカーソルクラスで、<BR>
     * _pKurokoA->behave(); <BR>
     * を実行する必要はありません。<BR>
     * @param prm_pCursor カーソル
     */
    virtual void setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor);

    /**
     * メニューの動きを設定する。
     * @param prm_menu_fade_frames メニューのフェードイン（とフェードアウト）のフレーム数
     * @param prm_cursor_move_frames カーソルがアイテム間移動に費やすフレーム(デフォルト8フレーム)
     * @param prm_cursor_move_p1 カーソルが移動時、アイテム間移動距離の速度０～最高速に達する時点の割合(デフォルト0.2)
     * @param prm_cursor_move_p2 カーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合(デフォルト0.7)
     */
    virtual void config(int prm_menu_fade_frames,
                        int prm_cursor_move_frames = 8,
                        float prm_cursor_move_p1 = 0.2,
                        float prm_cursor_move_p2 = 0.7);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(自身がFrom ⇔ To) .
     * addItem(GgafDxCore::GgafDxDrawableActor*) により、追加を行うことで、自動的に<BR>
     * 次、前、の線形オーダーが構築されている。<BR>
     * このメソッドはそれとは別にアイテム間の「次」、「前」、の関係を設定する。<BR>
     * 例えば、「→」キーで「次」、「←」キーで「戻る」という動作にした場合に
     * 「↑」「↓」の移動先を設定するといった使用方法を想定。<BR>
     * @param prm_index_of_fromitem 連結元のメニューアイテムのインデックス
     * @param prm_index_of_toitem 連結元のメニューアイテムのインデックスから
     *                            「次」に対応する連結先のメニューアイテムのインデックス
     */
    virtual void relationItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem);
//    virtual void relationItemExNext(int prm_index_of_fromitem, ...);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(From ⇔ 自身がTo) .
     * addItem(GgafDxCore::GgafDxDrawableActor*) により、追加を行うことで、自動的に<BR>
     * 次、前、の線形オーダーが構築されている。<BR>
     * このメソッドはそれとは別にアイテム間の「前」、「次」、の関係を設定する。<BR>
     * 例えば、「→」キーで「次」、「←」キーで「戻る」という動作にした場合に
     * 「↑」「↓」の移動先を設定するといった使用方法を想定。<BR>
     * @param prm_index_of_fromitem 連結元のメニューアイテムのインデックス
     * @param prm_index_of_toitem 連結元のメニューアイテムのインデックスから
     *                            「前」に対応する連結先のメニューアイテムのインデックス
     */
    virtual void relationItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * キャンセルのメニューアイテムを設定する。
     * @param prm_index_of_cancel_item キャンセルアイテムのインデックス
     */
    virtual void relationItemCancel(int prm_index_of_cancel_item);

    /**
     * カーソルを取得 .
     * @return
     */
    virtual GgafDxCore::GgafDxDrawableActor* getCursor();
    /**
     * 指定のインデックスのメニューアイテムに、カーソルが移動 .
     * 既に指定のインデックス選択中の場合はカーソルは何も移動無し。
     * @param prm_index ターゲットのアイテムインデックス
     * @return アイテムインデックスのアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* setSelectedItemIndex(int prm_index);

    /**
     * 現在カーソルが選択中のアイテムのインデックスを取得 .
     * @return 選択中のアイテムオブジェクト
     */
    virtual int getSelectedItemIndex();

    /**
     * 現在カーソルが選択中のアイテムのオブジェクトを取得 .
     * @return 選択中のアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItem();

    /**
     * カーソルが「次」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、実装してください。
     * @return true:「次」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorNext() = 0;

    /**
     * カーソルが「前」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、実装してください。
     * @return true:「前」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorPrev() = 0;

    /**
     * カーソルが「もう一つの別の次」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、実装してください。
     * @return true:「もう一つの別の次」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorExNext() = 0;


    /**
     * カーソルが「もう一つの別の前」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、実装してください。
     * @return true:「もう一つの別の前」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorExPrev() = 0;

    /**
     * カーソルが「キャンセル」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、実装してください。
     * @return true:「キャンセル」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorCancel() = 0;

    /**
     * カーソル選択中のアイテムで決定であるという条件を実装する .
     * 下位クラスでオーバーライドして、実装してください。
     * @return 「決定」の条件成立 / false:不成立
     */
    virtual bool condDecision() = 0;

    /**
     * カーソルを _lstItems のアクティブ要素へ移動させる .
     * カーソル移動時の効果音を鳴らす場合等は、オーバーライドして再定義してください。<BR>
     * 但し、処理中に上位 moveCursor() を呼び出すのを忘れないように。<BR>
     */
    virtual void moveCursor();


    virtual void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * メニューを表示開始 .
     * 本オブジェクトを生成、タスクに追加後、表示させたいタイミングで実行してください。<BR>
     */
    void rise();

    /**
     * メニューを表示開始時の処理 .
     * rise() 実行時直後、１回だけコールバックされます。<BR>
     * 必要に応じてオーバーライドしてください。<BR>
     */
    virtual void onRisen();

    /**
     * メニュー表示のトランジション処理 .
     * rise() 実行 ～ フェードイン完了までの間コールされ続けます。
     * アルファを加算しフェードイン効果を行い、アルファが1.0になれば終了。
     * というトランジション処理が実装済みです。<BR>
     * トランジションを独自に行いたい場合はオーバーライドし、トランジション完了時に<BR>
     * _with_rising = false;<BR>
     * を実行してください。<BR>
     */
    virtual void processRising();

    /**
     * メニューの振る舞い .
     * カーソルの移動及び、アイテムとカーソルをメニューの母体座標に追従させる
     * 処理が実装済みです。<BR>
     * メニューの振る舞いを追加する場合は、オーバーライドして、<BR>
     * 処理中に上位 moveCursor() を呼び出すのを忘れないように。<BR>
     */
    virtual void processBehavior() override;

    /**
     * メニューを消去開始 .
     * 本オブジェクトを生成、タスクに追加後、表示させたいタイミングで実行してください。<BR>
     */
    void sink();

    bool isJustSink() {
        return _is_just_with_sinking;
    }

    /**
     * メニューを消去開始時の処理 .
     * sink() 実行時直後、１回だけコールバックされます。<BR>
     * 必要に応じてオーバーライドしてください。<BR>
     */
    virtual void onSunk();

    /**
     * メニュー消去のトランジション処理 .
     * sink() 実行 ～ フェードアウト完了までの間コールされ続けます。
     * アルファを減算しフェードアウト効果を行い、アルファが1.0になれば終了
     * というトランジション処理が実装済みです。<BR>
     * トランジションを独自に行いたい場合はオーバーライドし、トランジション完了時に<BR>
     * _with_sinking = false;<BR>
     * T::inactivateTreeImmed();<BR>
     * を実行してください。<BR>
     */
    virtual void processSinking();



    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model, NULL),_lstItems(3) { //枝を３つ
    T::_class_name = "MenuActor";
    _pCursor = NULL;
    _velo_alpha_fade = 1.0;
    _cursor_move_frames = 10;
    _cursor_move_p1 = 0.2;
    _cursor_move_p2 = 0.7;
    _X_cursor_target_prev = T::_X;
    _Y_cursor_target_prev = T::_Y;
    _Z_cursor_target_prev = T::_Z;
    _with_rising = false;
    _with_sinking = false;
    _is_just_with_rising = false;
    _is_just_with_sinking = false;
    T::inactivateImmed();
}


template<class T>
void MenuActor<T>::addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                           coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pItem->_X_local = prm_X_local;
    prm_pItem->_Y_local = prm_Y_local;
    prm_pItem->_Z_local = prm_Z_local;
    prm_pItem->_fAlpha = T::_fAlpha; //半透明αを共有させる。
    prm_pItem->inactivateImmed();

    _lstItems.addLast(prm_pItem);
    T::addSubLast(prm_pItem);
}

template<class T>
void MenuActor<T>::config(int prm_menu_fade_frames,
                          int prm_cursor_move_frames,
                          float prm_cursor_move_p1,
                          float prm_cursor_move_p2) {
    _velo_alpha_fade = 1.0 / prm_menu_fade_frames;
    _cursor_move_frames = prm_cursor_move_frames;
    _cursor_move_p1 = prm_cursor_move_p1;
    _cursor_move_p2 = prm_cursor_move_p2;
    if (_pCursor) {
        _pCursor->_fAlpha = T::_fAlpha;
        _pCursor->inactivateImmed();
    }
}

template<class T>
void MenuActor<T>::relationItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

//template<class T>
//void MenuActor<T>::relationItemExNext(int prm_index_of_fromitem, ...) {
//    va_list pArg;
//    va_start(pArg, prm_index_of_fromitem);         //可変長引数操作開始
//        va_arg( argptr, int );
//
//
//
//    va_end(pArg);      //可変長引数操作終了
//}


template<class T>
void MenuActor<T>::relationItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relationItemCancel(int prm_index_of_cancel_item) {
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pCancelElem =
            _lstItems.getElemFromFirst(prm_index_of_cancel_item);

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem =
            _lstItems.getElemFirst();
    GgafDxCore::GgafDxDrawableActor* pItem;
    for (int i = 0; i < _lstItems.length(); i++) {
        pElem->connect(ITEM_RELATION_TO_CANCEL, pCancelElem);
        pElem = pElem->_pNext;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::setSelectedItemIndex(int prm_index) {
    int n = getSelectedItemIndex();
    if (n == prm_index) {
        return _lstItems.getCurrent();
    } else {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.current(prm_index);
        moveCursor();
        return pTargetItem;
    }
}

template<class T>
void MenuActor<T>::setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor) {
    _pCursor = prm_pCursor;
    T::addSubLast(_pCursor);
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getCursor() {
    return _pCursor;
}

template<class T>
int MenuActor<T>::getSelectedItemIndex() {
    return _lstItems.getCurrentIndex();
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
void MenuActor<T>::moveCursorNext() {
    if (_pCursor) {
        _pCursor->locateAs(_lstItems.getCurrent());
    }
    _lstItems.next();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorPrev() {
    if (_pCursor) {
        _pCursor->locateAs(_lstItems.getCurrent());
    }
    _lstItems.prev();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorExNext() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        if (_pCursor) {
            _pCursor->locateAs(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursorExPrev() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        if (_pCursor) {
            _pCursor->locateAs(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursorCancel() {
    if (_lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        if (_pCursor) {
            _pCursor->locateAs(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_TO_CANCEL);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursor() {
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        _pCursor->_pKurokoA->setMvAng(pTargetItem);
        _pCursor->_pKurokoA->setMvVelo(0);
        _pCursor->_pKurokoA->setMvAcce(0);
        _pCursor->_pKurokoA->execSmoothMvVeloSequence(0, GgafDxCore::GgafDxUtil::getDistance(_pCursor, pTargetItem),
                                                    _cursor_move_frames,
                                                    _cursor_move_p1, _cursor_move_p2);
        _X_cursor_target_prev = pTargetItem->_X;
        _Y_cursor_target_prev = pTargetItem->_Y;
        _Z_cursor_target_prev = pTargetItem->_Z;
    }
}

template<class T>
void MenuActor<T>::rise() {
    _with_rising = true;
    _is_just_with_rising = true;
    _with_sinking = false;
    _is_just_with_sinking = false;
    //メニューアイテム初期配置
    T::setAlpha(0.0);
    GgafDxCore::GgafDxDrawableActor* pItem;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pItem = pElem->_pValue;
        pItem->locate(T::_X + pItem->_X_local,
                      T::_Y + pItem->_Y_local,
                      T::_Z + pItem->_Z_local);
        pItem->setAlpha(T::getAlpha());
        pElem = pElem->_pNext;
    }
    T::activateTree();
}

template<class T>
void MenuActor<T>::onRisen() {
}

template<class T>
void MenuActor<T>::processRising() {
    T::addAlpha(_velo_alpha_fade);
    if (T::getAlpha() >= 1.0) {
        T::setAlpha(1.0);
        _with_rising = false;
    }
}

template<class T>
void MenuActor<T>::processBehavior() {

    if (_with_sinking) {
        if (_is_just_with_sinking) {
            onSunk();
            _is_just_with_sinking = false;
        }
        processSinking();
    }
    if (_with_rising) {
        if (_is_just_with_rising) {
            onRisen();
            _is_just_with_rising = false;
        }
        processRising();
    }

    if (!_with_sinking) {
		if (condDecision()) {
            onDecision(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
        } else if (condMoveCursorNext()) {
            moveCursorNext();
        } else if (condMoveCursorPrev()) {
            moveCursorPrev();
        } else if (condMoveCursorExNext()) {
            moveCursorExNext();
        } else if (condMoveCursorExPrev()) {
            moveCursorExPrev();
        } else if (condMoveCursorCancel()) {
            moveCursorCancel();
        }
    }
    if (_pCursor) {
        _pCursor->_pKurokoA->behave();
    }

    //メニューアイテムをメニューに追従
    GgafDxCore::GgafDxDrawableActor* pItem;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pItem = pElem->_pValue;
        pItem->locate(T::_X + pItem->_X_local,
                      T::_Y + pItem->_Y_local,
                      T::_Z + pItem->_Z_local);
        pItem->setAlpha(T::getAlpha());
        pElem = pElem->_pNext;
    }

    //カーソルをメニューアイテムに追従
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursor->_pKurokoA->isMoveingSmooth()) {
            _pCursor->_X += (pTargetItem->_X - _X_cursor_target_prev);
            _pCursor->_Y += (pTargetItem->_Y - _Y_cursor_target_prev);
            _pCursor->_Z += (pTargetItem->_Z - _Z_cursor_target_prev);
            _X_cursor_target_prev = pTargetItem->_X;
            _Y_cursor_target_prev = pTargetItem->_Y;
            _Z_cursor_target_prev = pTargetItem->_Z;
        } else {
            _pCursor->locateAs(pTargetItem);
        }
        _pCursor->setAlpha(T::getAlpha());
    }
}

template<class T>
void MenuActor<T>::sink() {
    _with_rising = false;
    _is_just_with_rising = false;
    _with_sinking = true;
    _is_just_with_sinking = true;
}


template<class T>
void MenuActor<T>::onSunk() {
}

template<class T>
void MenuActor<T>::processSinking() {
    T::addAlpha(-_velo_alpha_fade);
    if (T::getAlpha() <= 0.0) {
        T::setAlpha(0.0);
        _with_sinking = false;
        T::inactivateTreeImmed();
    }
}

template<class T>
MenuActor<T>::~MenuActor() {
}

/** メニューの母体を GgafLib::DefaultBoardActor とするメニュー */
typedef GgafLib::MenuActor<GgafLib::DefaultBoardActor> DefaultBoardMenu;
/** メニューの母体を GgafLib::DefaultBoardSetActor とするメニュー */
typedef GgafLib::MenuActor<GgafLib::DefaultBoardSetActor> DefaultBoardSetMenu;

}
#endif /*MENUACTOR_H_*/
