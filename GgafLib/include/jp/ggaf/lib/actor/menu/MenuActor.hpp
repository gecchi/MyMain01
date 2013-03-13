#ifndef MENUACTOR_H_
#define MENUACTOR_H_
namespace GgafLib {

/**
 * メニュー .
 * GUI簡易メニューを簡単に実装するためのテンプレートです。<BR>
 * <b>【まぎらわしい用語の区別】</b><BR>
 * ・キャンセル（メニューアイテム）… 「キャンセル」の動作が期待されるGUI部品の事を指す。（例： [Cancel] や [取り消し] のボタン自体）<BR>
 * ・決定（振る舞い）              … ユーザー操作で、「決定」の意思を表す操作を指す。（例： [ENTER]キーや、[○]ボタンを押す事）<BR>
 * ・キャンセル（振る舞い）        … ユーザー操作で、「キャンセル」の意思を表す操作を指す。（例： [ESC]キーや、[×]ボタンを押す事）<BR>
 * 俗に「キャンセルした」と言われる事について、本稿での説明では、<BR>
 * 『「キャンセル（メニューアイテム）」で、「決定（振る舞い） 」した。』<BR>
 * というめんどくさい表現になっています。<BR>
 * <BR>
 * ＜注意＞<BR>
 * 本クラスは「キャンセル（メニューアイテム）」「決定（振る舞い）」「キャンセル（振る舞い）」を特別扱いし、
 * 様々な機能をサポートしますが、[OK]ボタン等の「決定（メニューアイテム）」についての機能は今のところありません。<BR>
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class MenuActor : public T {

protected:

    enum MenuItemWay {
        ITEM_RELATION_EX_NEXT = 0,
        ITEM_RELATION_EX_PREV,
        ITEM_RELATION_TO_CANCEL,
    };

    /** カーソルの補正X座標 */
    coord _X_cursor_adjust;
    /** カーソルの補正Y座標 */
    coord _Y_cursor_adjust;
    /** カーソルの補正Z座標 */
    coord _Z_cursor_adjust;

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
    bool _is_just_risen;
    /** フェードアウトが開始した瞬間のフレームだけ true */
    bool _is_just_sunk;
    /** 「決定（振る舞い）」した瞬間のフレームだけ true */
    bool _is_just_decided;
    /** 「キャンセル（振る舞い）」した瞬間のフレームだけ true */
    bool _is_just_cancelled;

    bool _will_be_rising_next_frame;

    bool _will_be_sinking_next_frame;

    bool _will_be_just_decided_next_frame;

    bool _will_be_just_cancelled_next_frame;

    bool _can_controll;

    bool _will_be_able_to_controll;

protected:
    /**
     * _lstItems のアクティブ要素を next() へ移動させ、カーソルを移動 .
     */
    virtual void selectNext();

    /**
     * _lstItems のアクティブ要素を prev() へ移動させ、カーソルを移動 .
     */
    virtual void selectPrev();

    /**
     * _lstItems のアクティブ要素を gotoRelation(ITEM_RELATION_EX_NEXT) へ移動させ、カーソルを移動 .
     */
    virtual void selectExNext();

    /**
     * _lstItems のアクティブ要素を gotoRelation(ITEM_RELATION_EX_PREV) へ移動させ、カーソルを移動 .
     */
    virtual void selectExPrev();

    /**
     *  _lstItems のアクティブ要素を gotoRelation(ITEM_RELATION_TO_CANCEL) へ移動させ、カーソルを移動 .
     */
    virtual void selectCancel();

public:
    /** [r]メニューアイテムのリスト */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstItems;
    /** [r]メニューカーソル */
    GgafDxCore::GgafDxDrawableActor* _pCursor;
    /** [r]その他表示アイテムのリスト */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstDispActors;
    /** [r]カーソルが移動したメニューアイテムインデックスのヒストリー(0～N、但し初期は全て -1 ) */
    GgafCore::GgafLinkedListRing<int> _lstMvCursorHistory;
    /** [r]選択したメニューアイテムインデックスのヒストリー(0～N、但し初期は全て -1 ) */
    GgafCore::GgafLinkedListRing<int> _lstMvSelectHistory;

    /** [r]メニューフェイドイン・アウト時のフレーム数 */
    frame _fade_frames;
    /** [r]メニューフェイドイン・アウト時のアルファ速度 */
    float _velo_alpha_fade;
    /** [r]カーソルが、メニューアイテム間を移動する際に費やすスフレーム数 */
    int _cursor_move_frames;
    /** [r]カーソルが移動時、アイテム間移動距離の速度０～最高速に達する時点の割合 */
    float _cursor_move_p1;
    /** [r]カーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合 */
    float _cursor_move_p2;
    /** [r]サブメニューのリスト */
    GgafCore::GgafLinkedListRing<MenuActor<T>> _lstSubMenu;

public:
    /**
     * コンストラクタ .
     * 【注意】生成直後非活動状態をデフォルトとしています。<BR>
     * 具体的には T::inactivateImmed(); をコールしています。
     * @param prm_name
     * @param prm_model モデル識別名
     */
    MenuActor(const char* prm_name, const char* prm_model);

    /**
     * 現在入力が受け付けられている状態かを返す .
     * サブメニューが表示されている間等は、操作不可になり、本メソッドはfalseを返します。
     * @return true:コントロール可能状態/false:コントロール不可能状態
     */
    virtual bool canControll() {
        return _can_controll;
    }

    /**
     * 入力を受け付けを無効 .
     * 選択完了後に呼び出す、等の使用を想定。
     */
    virtual void disableControll() {
        _will_be_able_to_controll = false;
    }

    /**
     * 入力を受け付けを有効 .
     */
    virtual void enableControll() {
        _will_be_able_to_controll = true;
    }

    /**
     * メニューフェイドイン・アウト時のアルファ速度を設定 .
     * @param prm_menu_fade_frames フェードフレーム時間
     */
    virtual void setFadeFrames(frame prm_menu_fade_frames) {
        _fade_frames = prm_menu_fade_frames;
        _velo_alpha_fade = 1.0 / prm_menu_fade_frames;
    }

    /**
     * 選択可能メニューアイテムを追加し、メニューアイテム間のオーダーも連結追加する .
     * 追加されたアイテムはメニューオブジェクト(this)のサブに登録されるため、
     * メニューオブジェクトがタスクツリーに登録されるならば delete する必要はない。
     * 【注意】<BR>
     * 同一Z座標ならば、後に addItem() した方が、より手前に表示となる。<BR>
     * @param prm_pItem メニューアイテム
     * @param prm_X_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_Z_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_X_local, coord prm_Y_local, coord prm_Z_local);
    /**
     * 選択可能メニューアイテム追加し、メニューアイテム間のオーダーも連結追加する .
     * 追加されたアイテムはメニューオブジェクト(this)のサブに登録されるため、
     * メニューオブジェクトがタスクツリーに登録されるならば delete する必要はない。<BR>
     * 【注意】<BR>
     * 同一Z座標ならば、後に addItem() した方が、より手前に表示となる。<BR>
     * Z座標は、オフセット0が設定される。つまりアイテムの絶対Z座標は、現在のメニューのZ座標と一致する。<BR>
     * もしメニューが2Dで、アイテムの表示プライオリティの考慮が必要な場合は、オフセットを-1等に明示設定も可能。
     * @param prm_pItem メニューアイテム
     * @param prm_X_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_X_local, coord prm_Y_local) {
        addItem(prm_pItem, prm_X_local, prm_Y_local, 0);
    }

    /**
     * 選択不可の表示用メニューアイテム(ラベル)を追加する .
     * 【注意】<BR>
     * 同一Z座標ならば、より後の順に addDisp() した方が、より手前に表示となる。<BR>
     * @param prm_pItem 表示用ラベルのアクター
     * @param prm_X_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_Z_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                         coord prm_X_local, coord prm_Y_local, coord prm_Z_local);

    /**
     * 選択不可の表示用メニューラベルを追加する .
     * 【注意】<BR>
     * 同一Z座標ならば、より後の順に addDisp() した方が、より手前に表示となる。<BR>
     * Z座標は、オフセット0が設定される。つまり表示用アクターの絶対Z座標は、現在のメニューのZ座標と一致する。
     * もしメニューが2Dで、アイテムの表示プライオリティの考慮が必要な場合は、オフセットを-1等に明示設定も可能。
     * @param prm_pItem 表示用ラベルのアクター
     * @param prm_X_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                         coord prm_X_local, coord prm_Y_local) {
        addDisp(prm_pDisp, prm_X_local, prm_Y_local, 0);
    }

    /**
     * メニューカーソルオブジェクトを設定する .
     * 【注意】<BR>
     * カーソル移動を制御するため、MenuActor<T>::processBehavior() 内で、<BR>
     * _pCursor->_pKurokoA->behave(); <BR>
     * を実行しています。したがって、引数のカーソルクラスで、<BR>
     * _pKurokoA->behave(); <BR>
     * を実行する必要はありません。<BR>
     * @param prm_pCursor カーソル
     * @param prm_X_cursor_adjust アイテムとの重なりを補正するための加算される差分X座標
     * @param prm_Y_cursor_adjust アイテムとの重なりを補正するための加算される差分Y座標
     * @param prm_Z_cursor_adjust アイテムとの重なりを補正するための加算される差分Z座標
     * @param prm_cursor_move_frames カーソルがアイテム間移動に費やすフレーム(デフォルト8フレーム)
     * @param prm_cursor_move_p1 カーソルが移動時、アイテム間移動距離の速度０～最高速に達する時点の割合(デフォルト0.2)
     * @param prm_cursor_move_p2 カーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合(デフォルト0.7)
     */
    virtual void setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor,
                           coord prm_X_cursor_adjust = 0,
                           coord prm_Y_cursor_adjust = 0,
                           coord prm_Z_cursor_adjust = 0,
                           int prm_cursor_move_frames = 8,
                           float prm_cursor_move_p1 = 0.2,
                           float prm_cursor_move_p2 = 0.7);
    /**
     * メニューアイテム間のオーダー連結を拡張設定(自身がFrom ⇔ To) .
     * addItem(GgafDxCore::GgafDxDrawableActor*) により、追加を行うことで、自動的に<BR>
     * 次、前、の線形オーダーが構築されているが、<BR>
     * このメソッドはそれとは別にアイテム間の「次」、「前」、の関係を追加設定する。<BR>
     * 例えば、「→」キーで「次」、「←」キーで「戻る」という動作になっているところに、
     * さらに「↑」「↓」の移動先を別途設定するといった使用方法を想定。<BR>
     * @param prm_index_of_fromitem 連結元のメニューアイテムのインデックス
     * @param prm_index_of_toitem 連結元のメニューアイテムのインデックスから
     *                            「次」に対応する連結先のメニューアイテムのインデックス
     */
    virtual void relateItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(item1 ⇔ item2  ⇔ item3) .
     * @param prm_index_of_item1 拡張連結するメニューアイテムのインデックス1
     * @param prm_index_of_item2 拡張連結するメニューアイテムのインデックス2
     * @param prm_index_of_item3 拡張連結するメニューアイテムのインデックス3
     */
    virtual void relateItemExNext(int prm_index_of_item1,
                                  int prm_index_of_item2,
                                  int prm_index_of_item3);
    /**
     * メニューアイテム間のオーダー連結を拡張設定(item1 ⇔ item2  ⇔ item3 ⇔ item4) .
     * @param prm_index_of_item1 拡張連結するメニューアイテムのインデックス1
     * @param prm_index_of_item2 拡張連結するメニューアイテムのインデックス2
     * @param prm_index_of_item3 拡張連結するメニューアイテムのインデックス3
     * @param prm_index_of_item4 拡張連結するメニューアイテムのインデックス4
     */
    virtual void relateItemExNext(int prm_index_of_item1,
                                  int prm_index_of_item2,
                                  int prm_index_of_item3,
                                  int prm_index_of_item4);
    /**
     * メニューアイテム間のオーダー連結を拡張設定(item1 ⇔ item2  ⇔ item3 ⇔ item4 ⇔ item5).
     * @param prm_index_of_item1 拡張連結するメニューアイテムのインデックス1
     * @param prm_index_of_item2 拡張連結するメニューアイテムのインデックス2
     * @param prm_index_of_item3 拡張連結するメニューアイテムのインデックス3
     * @param prm_index_of_item4 拡張連結するメニューアイテムのインデックス4
     * @param prm_index_of_item5 拡張連結するメニューアイテムのインデックス5
     */
    virtual void relateItemExNext(int prm_index_of_item1,
                                  int prm_index_of_item2,
                                  int prm_index_of_item3,
                                  int prm_index_of_item4,
                                  int prm_index_of_item5);


//    virtual void relateItemExNext(int prm_index_of_fromitem, ...);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(From ⇔ 自身がTo) .
     * addItem(GgafDxCore::GgafDxDrawableActor*) により、追加を行うことで、自動的に<BR>
     * 次、前、の線形オーダーが構築されているが、<BR>
     * このメソッドはそれとは別にアイテム間の「前」、「次」、の関係を追加設定する。<BR>
     * 例えば、「→」キーで「次」、「←」キーで「戻る」という動作にした場合に
     * 「↑」「↓」の移動先を設定するといった使用方法を想定。<BR>
     * @param prm_index_of_fromitem 連結元のメニューアイテムのインデックス
     * @param prm_index_of_toitem 連結元のメニューアイテムのインデックスから
     *                            「前」に対応する連結先のメニューアイテムのインデックス
     */
    virtual void relateItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * 既存アイテム全てに対し、「キャンセル（メニューアイテム）」へのオーダー連結を拡張設定する .
     * @param prm_index_of_cancel_item キャンセルアイテムへのアイテムインデックス
     */
    virtual void relateAllItemCancel(int prm_index_of_cancel_item);

    /**
     * メニューに設定されているカーソルを取得 .
     * @return カーソルオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getCursor();

    /**
     * 指定のインデックスのメニューアイテムへ、カーソルをセット .
     * 内部で moveCursor() がコールバックされ、カーソルが移動することになる。<BR>
     * 既に指定のインデックス選択中の場合はカーソルは何も移動無し。<BR>
     * ついでに、引数インデックスのアイテムオブジェクトもゲット出来る。<BR>
     * @param prm_index ターゲットのアイテムインデックス
     * @return prm_indexのアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* selectItem(int prm_index);

    /**
     * 指定のメニューアイテムへ、カーソルをセット .
     * 内部で moveCursor() がコールバックされ、カーソルが移動することになる。<BR>
     * 既に指定のインデックス選択中の場合はカーソルは何も移動無し。<BR>
     * ついでに、引数アイテムオブジェクトのインデックスもゲット出来る。<BR>
     * @param prm_item ターゲットのアイテム
     * @return ターゲットのアイテムインデックス
     */
    virtual int selectItem(GgafDxCore::GgafDxDrawableActor* prm_item);

    /**
     * 現在カーソルが選択中のアイテムのインデックスを取得 .
     * @return 選択中のアイテムオブジェクトのインデックス
     */
    virtual int getSelectedIndex();

    /**
     * 現在カーソルが選択中のアイテムのオブジェクトを取得 .
     * @return 選択中のアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItem();

    /**
     * 過去にカーソルが選択中だったアイテムのインデックスを取得 .
     * getMvCursorHistoryIndex(0) は getSelectedIndex() と同じです。
     * 指定の過去がない場合は -1 を返します。
     * @param prm_n 幾つ過去のカーソル位置か(0 ～)
     * @return 選択中だったのアイテムオブジェクトのインデックス（無い場合は -1）
     */
    virtual int getMvCursorHistoryIndex(int prm_n);

    /**
     * 「決定（振る舞い）」が行われた時に、そのメニューアイテムのインデックスを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnDecidedIndex() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return 決定された時：そのアイテムのインデックス(>=0)／何も決定されていない場合：常に -1
     */
    virtual int getOnDecidedIndex();

    /**
     * 「決定（振る舞い）」が行われた時に、そのメニューアイテムを返します .
     * それ以外の時は 常に nullptr を返します<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnDecidedItem() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return 決定された時：そのアイテム／何も決定されていない場合：常に nullptr
     */
    virtual GgafDxCore::GgafDxDrawableActor* getOnDecidedItem();

    /**
     * 「キャンセル（振る舞い）」が行われた時に、そのメニューアイテムのインデックスを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目がキャンセルされた場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnCancelledIndex() の戻り値を毎フレーム調べることで、キャンセル時の処理を記述することが可能。<BR>
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return キャンセルされた時：そのアイテムのインデックス(>=0)／何もキャンセルされていない場合：常に -1
     */
    virtual int getOnCancelledIndex();

    /**
     * 「キャンセル（振る舞い）」が行われた時に、そのメニューアイテムを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目がキャンセルされた場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnCancelledItem() の戻り値を毎フレーム調べることで、キャンセル時の処理を記述することが可能。<BR>
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return キャンセルされた時：そのアイテム／何もキャンセルされていない場合：常に nullptr
     */
    virtual GgafDxCore::GgafDxDrawableActor* getOnCancelledItem();

    /**
     * 選択対象アイテムのオブジェクトを取得 .
     * @param prm_index 取得したい選択対象アイテムのインデックス(0～)
     * @return アイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getItem(int prm_index);

    /**
     * その他表示用アイテムのオブジェクトを取得 .
     * @param prm_index 取得したい表示用アイテムのインデックス(0～)
     * @return 表示用アイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getDisp(int prm_index);

    /**
     * 「決定（振る舞い）」した、という事の成立条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。 <BR>
     * 同一フレームで condDecision() と condCancel() の条件成立はどちらか一方が成立し、
     * 判定優先順位は、condDecision() の方が先です。<BR>
     * @return 「決定（振る舞い）」の条件成立 / false:不成立
     */
    virtual bool condDecision() = 0;

    /**
     * 「キャンセル（振る舞い）」した、という事の成立条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。<BR>
     * 同一フレームで condDecision() と condCancel() の条件成立はどちらか一方が成立し、
     * 判定優先順位は、condDecision() の方が先です。<BR>
     * @return 「キャンセル（振る舞い）」の条件成立 / false:不成立
     */
    virtual bool condCancel() = 0;
    /**
     * カーソルが「次のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「次のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectNext() = 0;

    /**
     * カーソルが「前のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「前のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectPrev() = 0;

    /**
     * カーソルが「もう一つの別の次のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「もう一つの別の次のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectExNext() = 0;

    /**
     * カーソルが「もう一つの別の前のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「もう一つの別の前のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectrExPrev() = 0;

    /**
     * カーソルが「キャンセルのメニューアイテム」へ飛ぶ条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「キャンセルのメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectCancel() = 0;

    /**
     * 「決定（振る舞い）」された場合に呼び出されるコールバック。
     * 動作をオーバーライドして実装してください。<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で、getOnDecidedIndex() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。
     * @param prm_pItem 決定されたのアイテム
     * @param prm_item_index 決定されたのアイテムのインデックス
     */
    virtual void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * 「キャンセル（振る舞い）」された場合に呼び出されるコールバック。 .
     * 動作をオーバーライドして実装してください。<BR>
     * ＜メニューの選択項目がキャンセルされた場合の処理記述コードの場所について＞<BR>
     * processBehavior() で、getCancelIndex() の戻り値を毎フレーム調べることで、キャンセル時の処理を記述することが可能。<BR>
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。
     * @param prm_pItem
     * @param prm_item_index
     */
    virtual void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * カーソルが移動した場合に呼び出されるコールバック。 .
     * 動作をオーバーライドして実装してください。<BR>
     * 【捕捉】<BR>
     * onMoveCursor(int,int) と onSelect(int,int) のコールバックタイミングの差について。<BR>
     * onSelect(int,int) は、selectXxxxx 系 のメソッドを実行時に、もれなく呼び出されます。<BR>
     * onMoveCursor(int,int) は、selectXxxxx 系のメソッド実行の際、カーソルが移動した場合のみ呼び出されます。<BR>
     * 呼び出される順序は、onMoveCursor(int,int)  → onSelect(int,int) の順です。<BR>
     * @param prm_from 移動元のアイテムのインデックス（無い（初期の）場合は -1）
     * @param prm_to   移動先のアイテムのインデックス
     */
    virtual void onMoveCursor(int prm_from, int prm_to) = 0;


    /**
     * アイテムが選択された場合に呼び出されるコールバック。 .
     * 動作をオーバーライドして実装してください。<BR>
     * 【捕捉】<BR>
     * onMoveCursor(int,int) と onSelect(int,int) のコールバックタイミングの差について。<BR>
     * onSelect(int,int) は、selectXxxxx 系のメソッドを実行時に、もれなく呼び出されます。<BR>
     * onMoveCursor(int,int) は、selectXxxxx 系のメソッド実行の際、カーソルが移動した場合のみ呼び出されます。<BR>
     * 呼び出される順序は、onMoveCursor(int,int)  → onSelect(int,int) の順です。<BR>
     * @param prm_from 選択元（今回選択される前）のアイテムのインデックス（無い（初期の）場合は -1）
     * @param prm_to   選択先のアイテムのインデックス
     */
    virtual void onSelect(int prm_from, int prm_to) = 0;

    /**
     * カーソルを _lstItems のアクティブ要素へ移動させる .
     * カーソル移動時の効果音を鳴らす場合等は、オーバーライドして再定義してください。<BR>
     * 但し、その処理中に上位 moveCursor() を呼び出すのを忘れないように。<BR>
     * @param prm_smooth スムーズ移動するか否か
     */
    virtual void moveCursor(bool prm_smooth = true);

    /**
     * メニューを表示開始する .
     * 本オブジェクトを生成、タスクに追加後、表示させたいタイミングで実行してください。<BR>
     */
    virtual void rise();

    /**
     * メニュー表示開始時のコールバック .
     * rise() 実行時直後、１回だけコールバックされます。<BR>
     * 必要に応じてオーバーライドしてください。<BR>
     */
    virtual void onRise();

    /**
     * メニュー表示中トランジション処理 .
     * rise() 実行 ～ フェードイン完了までの間コールされ続けます。
     * アルファを加算しフェードイン効果を行い、アルファが1.0になれば終了。
     * というトランジション処理が実装済みです。<BR>
     * トランジションを独自に行いたい場合はオーバーライドし、トランジション完了時に<BR>
     * _with_rising = false;<BR>
     * を実行してください。<BR>
     */
    virtual void processRising();

    /**
     * 状態フラグ更新を追加のためオーバーライド .
     * 内部で T::nextFrame(); もコールしています。
     */
    virtual void nextFrame() override;

    /**
     * メニューの振る舞い .
     * カーソルの移動及び、アイテムとカーソルをメニューの母体座標に追従させる
     * 処理が実装済みです。<BR>
     * メニューの振る舞いを追加する場合は、オーバーライドして、
     * 処理中に上位 processBehavior() を呼び出すのを忘れないように。<BR>
     */
    virtual void processBehavior() override;

    /**
     * メニューを閉じて終了させる .
     */
    virtual void sink();

    /**
     * rise()が実行された直後か否かを返す .
     * @return true:今丁度 rise()が 実行された直後である/false:そうではない
     */
    virtual bool isJustRisen() {
        return _is_just_risen;
    }

    /**
     * sink() が実行された直後か否かを返す .
     * @return true:今丁度 sink() が実行された直後である/false:そうではない
     */
    virtual bool isJustSunk() {
        return _is_just_sunk;
    }

    /**
     * 「決定（振る舞い）」が行われた直後か否かを返す .
     * @return rue:今丁度 「決定（振る舞い）」 が実行された直後である/false:そうではない
     */
    virtual bool isJustDecided() {
        if (_is_just_decided && _can_controll) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * 「キャンセル（振る舞い）」が行われた直後か否かを返す .
     * @return rue:今丁度 「キャンセル（振る舞い）」 が実行された直後である/false:そうではない
     */
    virtual bool isJustCancelled() {
        if (_is_just_cancelled && _can_controll) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * メニューを消去開始時のコールバック .
     * sink() 実行時直後、１回だけコールバックされます。<BR>
     * 必要に応じてオーバーライドしてください。<BR>
     */
    virtual void onSink();

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

    /**
     * サブメニューを追加する。
     * @param prm_pSubMenu サブメニュー
     */
    virtual void addSubMenu(MenuActor<T>* prm_pSubMenu);

    /**
     * 親メニューを返す .
     * @return 親メニュー
     */
    virtual MenuActor<T>* getParentMenu();

    /**
     * サブメニューを取得 .
     * 事前に addSubMenu() でサブメニューを設定する必要があります。<BR>
     * @param prm_index サブメニューのインデックス
     * @return
     */
    virtual MenuActor<T>* getSubMenu(int prm_index);

    /**
     * 現在アクティブなサブメニューを取得 .
     * サブメニューが未登録の場合。或いは登録していても、アクティブではない場合は nullptr を返す。
     * @return アクティブなサブメニュー/nullptr
     */
    virtual MenuActor<T>* getRisingSubMenu();

    /**
     * サブメニューをアクティブにして表示する .
     * 事前に addSubMenu() でサブメニューを設定する必要があります。<BR>
     * また、本メソッドにより現在アクティブなサブメニュー(getRisingSubMenu())は、
     * 引数インデックスのメニューに変更されます。
     * サブメニューを表示すると、サブメニューを閉じる(sinkSubMenu()) まで、
     * 呼び出し元メニューは操作不可能になります。
     * @param prm_index アクティブにするサブメニューのインデックス
     */
    virtual void riseSubMenu(int prm_index);

    /**
     * 現在アクティブなサブメニューを閉じて終了させる .
     * 事前に addSubMenu() でサブメニューを設定する必要があります。<BR>
     */
    virtual void sinkSubMenu();

    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model, nullptr),_lstItems(3) { //全アイテム枝を３つ追加：「その他次」「その他前」「キャンセル」の３つ
    T::_class_name = "MenuActor";
    _pCursor = nullptr;
    _X_cursor_adjust = 0;
    _Y_cursor_adjust = 0;
    _Z_cursor_adjust = 0;
    _fade_frames = 0;
    _velo_alpha_fade = 1.0;
    _cursor_move_frames = 10;
    _cursor_move_p1 = 0.2;
    _cursor_move_p2 = 0.7;
    _X_cursor_target_prev = T::_X;
    _Y_cursor_target_prev = T::_Y;
    _Z_cursor_target_prev = T::_Z;
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _is_just_decided = false;
    _is_just_cancelled = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = false;
    _will_be_just_decided_next_frame = false;
    _will_be_just_cancelled_next_frame = false;
    _can_controll = false;
    _will_be_able_to_controll = false;
    for (int i = 0; i < 10; i++) {
        _lstMvCursorHistory.addLast(new int(-1), true);
        _lstMvSelectHistory.addLast(new int(-1), true);
    }
    T::inactivateImmed(); //メニューなので、初期状態は非活動状態をデフォルトとする
}

template<class T>
void MenuActor<T>::nextFrame() {
    T::nextFrame();
    _is_just_risen = false;
    if (_will_be_rising_next_frame) {
        _with_rising = true;
        _is_just_risen = true;
        _will_be_rising_next_frame = false;
        onRise();
    }

    _is_just_sunk = false;
    if (_will_be_sinking_next_frame) {
        _with_sinking = true;
        _is_just_sunk = true;
        _will_be_sinking_next_frame = false;
        onSink();
    }


    if (_will_be_just_decided_next_frame && _can_controll) {
        _is_just_decided = true;
        _will_be_just_decided_next_frame = false;
        onDecision(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
    } else {
        _is_just_decided = false;
        _will_be_just_decided_next_frame = false;
    }

    if (_will_be_just_cancelled_next_frame && _can_controll) {
        _is_just_cancelled = true;
        _will_be_just_cancelled_next_frame = false;
        onCancel(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
    } else {
        _is_just_cancelled = false;
        _will_be_just_cancelled_next_frame = false;
    }

    _can_controll = _will_be_able_to_controll;

}

template<class T>
void MenuActor<T>::addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                           coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pItem->_X_local = prm_X_local;
    prm_pItem->_Y_local = prm_Y_local;
    prm_pItem->_Z_local = prm_Z_local;
    prm_pItem->_alpha = T::_alpha; //半透明αを共有させる。
    prm_pItem->inactivateImmed();
    _lstItems.addLast(prm_pItem, false);
    T::addSubLast(prm_pItem);
}

template<class T>
void MenuActor<T>::addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                           coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pDisp->_X_local = prm_X_local;
    prm_pDisp->_Y_local = prm_Y_local;
    prm_pDisp->_Z_local = prm_Z_local;
    prm_pDisp->_alpha = T::_alpha; //半透明αを共有させる。
    prm_pDisp->inactivateImmed();
    _lstDispActors.addLast(prm_pDisp, false);
    T::addSubLast(prm_pDisp);
}

template<class T>
void MenuActor<T>::relateItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relateItemExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3 ) {
    relateItemExNext(prm_index_of_item1, prm_index_of_item2);
    relateItemExNext(prm_index_of_item2, prm_index_of_item3);
}

template<class T>
void MenuActor<T>::relateItemExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4 ) {
    relateItemExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3);
    relateItemExNext(prm_index_of_item3, prm_index_of_item4);
}

template<class T>
void MenuActor<T>::relateItemExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4,
                                    int prm_index_of_item5 ) {
    relateItemExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3, prm_index_of_item4);
    relateItemExNext(prm_index_of_item4, prm_index_of_item5);
}


//template<class T>
//void MenuActor<T>::relateItemExNext(int prm_index_of_fromitem, ...) {
//    va_list pArg;
//    va_start(pArg, prm_index_of_fromitem);         //可変長引数操作開始
//        va_arg( argptr, int );
//
//
//
//    va_end(pArg);      //可変長引数操作終了
//}


template<class T>
void MenuActor<T>::relateItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relateAllItemCancel(int prm_index_of_cancel_item) {
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pCancelElem =
            _lstItems.getElemFromFirst(prm_index_of_cancel_item);
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem =
            _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pElem->connect(ITEM_RELATION_TO_CANCEL, pCancelElem);
        pElem = pElem->_pNext;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::selectItem(int prm_index) {
    int n = getSelectedIndex();
#ifdef MY_DEBUG
    if (n == -1) {
        throwGgafCriticalException("MenuActor<T>::selectItem() メニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
    }
#endif
    if (n == prm_index) {
        //既に選択している。
        *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
        onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
        return _lstItems.getCurrent();
    } else {
#ifdef MY_DEBUG
        if (_lstItems.length() <= prm_index) {
            throwGgafCriticalException("MenuActor<T>::selectItem() メニューアイテム要素数オーバー name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
        }
#endif
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.current(prm_index);
        if (T::getActivePartFrame() > 1) {
            moveCursor(true);  //スムーズ移動有り
        } else {
            moveCursor(false); //スムーズ移動無し
        }
        *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
        onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
        return pTargetItem;
    }
}

template<class T>
int MenuActor<T>::selectItem(GgafDxCore::GgafDxDrawableActor* prm_item) {
    int index = _lstItems.indexOf(prm_item);
    if (index == -1) {
        throwGgafCriticalException("MenuActor<T>::selectItem() その前にメニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item="<<prm_item->getName());
    }
    selectItem(index);
    return index;
}

template<class T>
void MenuActor<T>::setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor,
                             coord prm_X_cursor_adjust,
                             coord prm_Y_cursor_adjust,
                             coord prm_Z_cursor_adjust,
                             int prm_cursor_move_frames,
                             float prm_cursor_move_p1,
                             float prm_cursor_move_p2) {
    _pCursor = prm_pCursor;
    if (_pCursor) {
        _pCursor->_alpha = T::_alpha;
        _pCursor->inactivateImmed();
    }
    T::addSubLast(_pCursor);
    _X_cursor_adjust = prm_X_cursor_adjust;
    _Y_cursor_adjust = prm_Y_cursor_adjust;
    _Z_cursor_adjust = prm_Z_cursor_adjust;
    _cursor_move_frames = prm_cursor_move_frames;
    _cursor_move_p1 = prm_cursor_move_p1;
    _cursor_move_p2 = prm_cursor_move_p2;
    selectItem(0);
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getCursor() {
    return _pCursor;
}

template<class T>
int MenuActor<T>::getSelectedIndex() {
    return _lstItems.getCurrentIndex();
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
int MenuActor<T>::getMvCursorHistoryIndex(int prm_n) {
    return (*(_lstMvCursorHistory.getPrev(prm_n)));
}

template<class T>
int MenuActor<T>::getOnDecidedIndex() {
    if (_is_just_decided) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}
template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getOnDecidedItem() {
    if (_is_just_decided) {
        return _lstItems.getCurrent();
    } else {
        return nullptr;
    }
}

template<class T>
int MenuActor<T>::getOnCancelledIndex() {
    if (_is_just_cancelled) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getOnCancelledItem() {
    if (_is_just_cancelled) {
        return _lstItems.getCurrent();
    } else {
        return nullptr;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getItem(int prm_index) {
    return _lstItems.getFromFirst(prm_index);
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getDisp(int prm_index) {
    return _lstDispActors.getFromFirst(prm_index);
}

template<class T>
void MenuActor<T>::selectNext() {
    if (_pCursor) {
        _pCursor->locateWith(_lstItems.getCurrent());
    }
    _lstItems.next();
    moveCursor();
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectPrev() {
    if (_pCursor) {
        _pCursor->locateWith(_lstItems.getCurrent());
    }
    _lstItems.prev();
    moveCursor();
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectExNext() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
        moveCursor();
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectExPrev() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
        moveCursor();
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectCancel() {
    if (_lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_TO_CANCEL);
        moveCursor();
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::moveCursor(bool prm_smooth) {
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (prm_smooth) {
            _pCursor->_pKurokoA->setMvAngTwd(
                                    pTargetItem->_X + _X_cursor_adjust,
                                    pTargetItem->_Y + _Y_cursor_adjust,
                                    pTargetItem->_Z + _Z_cursor_adjust
                                );
            _pCursor->_pKurokoA->setMvVelo(0);
            _pCursor->_pKurokoA->setMvAcce(0);
            _pCursor->_pKurokoA->execSmoothMvVeloSequence(
                                     0,
                                     UTIL::getDistance(
                                             _pCursor->_X,
                                             _pCursor->_Y,
                                             _pCursor->_Z,
                                             pTargetItem->_X + _X_cursor_adjust,
                                             pTargetItem->_Y + _Y_cursor_adjust,
                                             pTargetItem->_Z + _Z_cursor_adjust),
                                     _cursor_move_frames,
                                     _cursor_move_p1, _cursor_move_p2
                                 );
            _X_cursor_target_prev = pTargetItem->_X;
            _Y_cursor_target_prev = pTargetItem->_Y;
            _Z_cursor_target_prev = pTargetItem->_Z;
        } else {
            _pCursor->_pKurokoA->stopSmoothMvVeloSequence();
            _pCursor->_pKurokoA->setMvVelo(0);
            _pCursor->_pKurokoA->setMvAcce(0);
            _pCursor->_X = pTargetItem->_X + _X_cursor_adjust;
            _pCursor->_Y = pTargetItem->_Y + _Y_cursor_adjust;
            _pCursor->_Z = pTargetItem->_Z + _Z_cursor_adjust;
        }
        *(_lstMvCursorHistory.next()) = _lstItems.getCurrentIndex();
        onMoveCursor(*(_lstMvCursorHistory.getPrev()), *(_lstMvCursorHistory.getCurrent())); //コールバック
    }
}

template<class T>
void MenuActor<T>::rise() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = true;
    _will_be_sinking_next_frame = false;
    enableControll();

    T::setAlpha(0.0);
    T::activate();
    //メニューアイテム初期配置
    GgafDxCore::GgafDxDrawableActor* p;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        pElem = pElem->_pNext;
    }
    //表示アイテム初期配置
    pElem = _lstDispActors.getElemFirst();
    for (int i = 0; i < _lstDispActors.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        pElem = pElem->_pNext;
    }
    if (_pCursor) {
        _pCursor->activate();
    }
}

template<class T>
void MenuActor<T>::onRise() {
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
        processSinking();
    }
    if (_with_rising) {
        processRising();
    }
    if (_can_controll && T::getActivePartFrame() > 2) {
        if (condDecision()) {
            _will_be_just_decided_next_frame = true;
        } else if (condCancel()) {
            _will_be_just_cancelled_next_frame = true;
        } else if (condSelectNext()) {
            selectNext();
        } else if (condSelectPrev()) {
            selectPrev();
        } else if (condSelectExNext()) {
            selectExNext();
        } else if (condSelectrExPrev()) {
            selectExPrev();
        } else if (condSelectCancel()) {
            selectCancel();
        }
    }
    if (_pCursor) {
        _pCursor->_pKurokoA->behave();
    }

    //メニューアイテムをメニューに追従
    GgafDxCore::GgafDxDrawableActor* p;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        if (_with_sinking || _with_rising) {
            p->setAlpha(T::getAlpha());
        }
        pElem = pElem->_pNext;
    }
    //表示アイテムをメニューに追従
    pElem = _lstDispActors.getElemFirst();
    for (int i = 0; i < _lstDispActors.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        if (_with_sinking || _with_rising) {
            p->setAlpha(T::getAlpha());
        }
        pElem = pElem->_pNext;
    }

    //カーソルをメニューアイテムに追従
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursor->_pKurokoA->isRunnigSmoothMvVeloSequence()) {
            _pCursor->_X += (pTargetItem->_X - _X_cursor_target_prev);
            _pCursor->_Y += (pTargetItem->_Y - _Y_cursor_target_prev);
            _pCursor->_Z += (pTargetItem->_Z - _Z_cursor_target_prev);
            _X_cursor_target_prev = pTargetItem->_X;
            _Y_cursor_target_prev = pTargetItem->_Y;
            _Z_cursor_target_prev = pTargetItem->_Z;
        } else {
            _pCursor->locate(pTargetItem->_X + _X_cursor_adjust,
                             pTargetItem->_Y + _Y_cursor_adjust,
                             pTargetItem->_Z + _Z_cursor_adjust );
        }
        _pCursor->setAlpha(T::getAlpha());
    }

    //サブメニューのrise() sink() 時
    for (int i = 0; i < _lstSubMenu.length(); i++) {
        MenuActor<T>* pSubMenu = _lstSubMenu.getFromFirst(i);
        if (pSubMenu->isJustRisen()) {
            disableControll(); //サブメニューが立ち上がったので、自身は操作不可
            _can_controll = false; //即刻
        }
        if (pSubMenu->isJustSunk()) {
            if (_with_sinking || _is_just_sunk || _will_be_sinking_next_frame) {
                disableControll(); //自身も同時に閉じている場合
                _can_controll = false; //即刻
            } else {
                enableControll(); //サブメニューが消えたので、自身の操作復帰
            }
        }
    }
}

template<class T>
void MenuActor<T>::sink() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = true;
    disableControll();
    _can_controll = false; //即刻
}

template<class T>
void MenuActor<T>::onSink() {
}

template<class T>
void MenuActor<T>::processSinking() {
    T::addAlpha(-_velo_alpha_fade);
    if (T::getAlpha() <= 0.0) {
        T::setAlpha(0.0);
        _with_sinking = false;
        T::inactivateTree();
    }
}

template<class T>
void MenuActor<T>::addSubMenu(MenuActor<T>* prm_pSubMenu) {
    _lstSubMenu.addLast(prm_pSubMenu, false);
    T::addSubLast(prm_pSubMenu); //サブに追加
}

template<class T>
MenuActor<T>* MenuActor<T>::getParentMenu() {
    GgafCore::GgafActor* pActor = T::getParent(); //サブに追加
#ifdef MY_DEBUG
    MenuActor<T>* pMenuActor = dynamic_cast<MenuActor<T>*>(pActor);
    if (pMenuActor == nullptr) {
        throwGgafCriticalException(" MenuActor<T>::getParentMenu 親ノードは同じメニューではありませんでした。name="<<T::getName()<<" this="<<this);
    }
#endif
    return (MenuActor<T>*)pActor;
}

template<class T>
MenuActor<T>* MenuActor<T>::getSubMenu(int prm_index) {
#ifdef MY_DEBUG
    if (_lstSubMenu.length() < prm_index+1) {
        throwGgafCriticalException("MenuActor<T>::getSubMenu() サブメニューアイテム要素数オーバー name="<<T::getName()<<" _lstSubMenu.length()="<<_lstSubMenu.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstSubMenu.getFromFirst(prm_index);
}

template<class T>
MenuActor<T>* MenuActor<T>::getRisingSubMenu() {
    MenuActor<T>* pSub = _lstSubMenu.getCurrent();
    if (pSub) {
        if (pSub->isActiveInTheTree()) {
            return pSub;
        }
    }
    return nullptr;
}


template<class T>
void MenuActor<T>::riseSubMenu(int prm_index) {
#ifdef MY_DEBUG
    if (_lstSubMenu.length() < prm_index+1) {
        throwGgafCriticalException("MenuActor<T>::riseSubMenu() サブメニューアイテム要素数オーバー name="<<T::getName()<<" _lstSubMenu.length()="<<_lstSubMenu.length()<<" prm_index="<<prm_index);
    }
#endif
    _lstSubMenu.current(prm_index)->rise();
}

template<class T>
void MenuActor<T>::sinkSubMenu() {
    _lstSubMenu.getCurrent()->sink();
}

template<class T>
MenuActor<T>::~MenuActor() {
}

/** メニューの母体を GgafLib::DefaultBoardActor とするメニュー */
typedef GgafLib::MenuActor<GgafLib::DefaultBoardActor> DefaultBoardMenu;
/** メニューの母体を GgafLib::DefaultBoardSetActor とするメニュー */
typedef GgafLib::MenuActor<GgafLib::DefaultBoardSetActor> DefaultBoardSetMenu;
/** メニューの母体を GgafLib::DefaultSpriteActor とするメニュー */
typedef GgafLib::MenuActor<GgafLib::DefaultSpriteActor> DefaultSpriteMenu;
/** メニューの母体を GgafLib::DefaultSpriteSetActor とするメニュー */
typedef GgafLib::MenuActor<GgafLib::DefaultSpriteSetActor> DefaultSpriteSetMenu;
/** メニューの母体を GgafLib::StringBoardActor とするメニュー */
typedef GgafLib::MenuActor<GgafLib::StringBoardActor> StringBoardMenu;
/** メニューの母体を GgafLib::StringSpriteActor とするメニュー */
typedef GgafLib::MenuActor<GgafLib::StringSpriteActor> StringSpriteMenu;

}
#endif /*MENUACTOR_H_*/
