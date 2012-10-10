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
    /** [r]その他表示アイテムのリスト */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstDispActors;
    /** [r]メニューアイテムインデックスのヒストリー */
    GgafCore::GgafLinkedListRing<int> _lstMoveHistory;
    /** [r/w]メニューフェイドイン・アウト時のアルファ速度 */
    float _velo_alpha_fade;
    /** [r]カーソルが、メニューアイテム間を移動する際に費やすスフレーム数 */
    int _cursor_move_frames;
    /** [r]カーソルが移動時、アイテム間移動距離の速度０～最高速に達する時点の割合 */
    float _cursor_move_p1;
    /** [r]カーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合 */
    float _cursor_move_p2;
    MenuActor<T>* _pActiveSubMenu;

    /**
     * コンストラクタ .
     * 【注意】生成直後非活動状態をデフォルトとしています。<BR>
     * 具体的には T::inactivateImmed(); をコールしています。
     * @param prm_name
     * @param prm_model モデル識別名
     */
    MenuActor(const char* prm_name, const char* prm_model);

    /**
     * メニューフェイドイン・アウト時のアルファ速度を設定 .
     * @param prm_menu_fade_frames フェードフレーム時間
     */
    virtual void setFadeFrames(frame prm_menu_fade_frames) {
        _velo_alpha_fade = 1.0 / prm_menu_fade_frames;
    }

    /**
     * 選択可能メニューアイテムを追加する .
     * 追加されたアイテムはメニューオブジェクト(this)のサブに登録されるため、
     * メニューオブジェクトがタスクツリーに登録されるならば delete する必要はない。
     * @param prm_pItem メニューアイテム
     * @param prm_X_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_Z_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addSelectItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                               coord prm_X_local, coord prm_Y_local, coord prm_Z_local);
    /**
     * 選択可能メニューアイテム追加する .
     * 追加されたアイテムはメニューオブジェクト(this)のサブに登録されるため、
     * メニューオブジェクトがタスクツリーに登録されるならば delete する必要はない。<BR>
     * 【注意】Z座標は、オフセット0が設定される。つまりアイテムの絶対Z座標は、現在のメニューのZ座標と一致する。
     * もしメニューが2Dで、アイテムの表示プライオリティの考慮が必要な場合は、オフセットを-1等に明示設定したほうが良い。
     * @param prm_pItem メニューアイテム
     * @param prm_X_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void addSelectItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                               coord prm_X_local, coord prm_Y_local) {
        addSelectItem(prm_pItem, prm_X_local, prm_Y_local, 0);
    }

    /**
     * 選択不可の表示用メニューアイテムを追加する .
     * @param prm_pItem 表示用アイテム
     * @param prm_X_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_Z_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addDispItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                              coord prm_X_local, coord prm_Y_local, coord prm_Z_local);
    /**
     * 選択不可の表示用メニューアイテムを追加する .
     * 【注意】Z座標は、オフセット0が設定される。つまり表示用アクターの絶対Z座標は、現在のメニューのZ座標と一致する。
     * もしメニューが2Dで、アイテムの表示プライオリティの考慮が必要な場合は、オフセットを-1等に明示設定したほうが良い。
     * @param prm_pItem 表示用アイテム
     * @param prm_X_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_Y_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void addDispItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                              coord prm_X_local, coord prm_Y_local) {
        addDispItem(prm_pItem, prm_X_local, prm_Y_local, 0);
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
     * addSelectItem(GgafDxCore::GgafDxDrawableActor*) により、追加を行うことで、自動的に<BR>
     * 次、前、の線形オーダーが構築されている。<BR>
     * このメソッドはそれとは別にアイテム間の「次」、「前」、の関係を追加設定する。<BR>
     * 例えば、「→」キーで「次」、「←」キーで「戻る」という動作にした場合に
     * 「↑」「↓」の移動先を設定するといった使用方法を想定。<BR>
     * @param prm_index_of_fromitem 連結元のメニューアイテムのインデックス
     * @param prm_index_of_toitem 連結元のメニューアイテムのインデックスから
     *                            「次」に対応する連結先のメニューアイテムのインデックス
     */
    virtual void relateItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(From ⇔ To) .
     * @param prm_index_of_item1 拡張連結するメニューアイテムのインデックス1
     * @param prm_index_of_item2 拡張連結するメニューアイテムのインデックス2
     * @param prm_index_of_item3 拡張連結するメニューアイテムのインデックス3
     */
    virtual void relateItemExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3);
    /**
     * メニューアイテム間のオーダー連結を拡張設定(From ⇔ To) .
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
     * メニューアイテム間のオーダー連結を拡張設定(From ⇔ To) .
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
     * addSelectItem(GgafDxCore::GgafDxDrawableActor*) により、追加を行うことで、自動的に<BR>
     * 次、前、の線形オーダーが構築されている。<BR>
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
     * 内部で moveCursor() がコールバックされ、カーソルが移動することになる。
     * 既に指定のインデックス選択中の場合はカーソルは何も移動無し。
     * @param prm_index ターゲットのアイテムインデックス
     * @return アイテムインデックスのアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* setSelectedItemIndex(int prm_index);

    /**
     * 現在カーソルが選択中のアイテムのインデックスを取得 .
     * @return 選択中のアイテムオブジェクトのインデックス
     */
    virtual int getSelectedIndex();

    /**
     * 過去にカーソルが選択中だったアイテムのインデックスを取得 .
     * getSelectedPrevIndex(0) は getSelectedIndex() と同じです。
     * @param prm_n 幾つ過去のカーソル位置か(0 ～)
     * @return 選択中だったのアイテムオブジェクトのインデックス
     */
    virtual int getSelectedPrevIndex(int prm_n);

    /**
     * 「決定（振る舞い）」が行われた時に、決定されたメニューアイテムのインデックスを返します .
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getDecidedIndex() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return 決定された時：そのアイテムのインデックス(>=0)／何も決定されていない場合：常に -1
     */
    virtual int getDecidedIndex();

    /**
     * 「キャンセル（振る舞い）」が行われた時に、決定されたメニューアイテムのインデックスを返します .
     * ＜メニューの選択項目がキャンセルされた場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getCancelledIndex() の戻り値を毎フレーム調べることで、キャンセル時の処理を記述することが可能。<BR>
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return キャンセルされた時：そのアイテムのインデックス(>=0)／何もキャンセルされていない場合：常に -1
     */
    virtual int getCancelledIndex();

    /**
     * 現在カーソルが選択中のアイテムのオブジェクトを取得 .
     * @return 選択中のアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItem();


    virtual MenuActor<T>* getSubMenu();

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
    virtual bool condMoveCursorNext() = 0;

    /**
     * カーソルが「前のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「前のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorPrev() = 0;

    /**
     * カーソルが「もう一つの別の次のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「もう一つの別の次のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorExNext() = 0;

    /**
     * カーソルが「もう一つの別の前のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「もう一つの別の前のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorExPrev() = 0;

    /**
     * カーソルが「キャンセルのメニューアイテム」へ飛ぶ条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「キャンセルのメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condMoveCursorCancel() = 0;


    /**
     * 「決定（振る舞い）」された場合に呼び出されるコールバック。
     * 動作をオーバーライドして実装してください。<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で、getDecidedIndex() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。
     * @param prm_pItem 決定されたのアイテム
     * @param prm_item_index 決定されたのアイテムのインデックス
     */
    virtual void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * 「キャンセル（振る舞い）」された場合に呼び出されるコールバック。
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
     * カーソルを _lstItems のアクティブ要素へ移動させる .
     * カーソル移動時の効果音を鳴らす場合等は、オーバーライドして再定義してください。<BR>
     * 但し、その処理中に上位 moveCursor() を呼び出すのを忘れないように。<BR>
     */
    virtual void moveCursor();

    /**
     * メニューを表示開始 .
     * 本オブジェクトを生成、タスクに追加後、表示させたいタイミングで実行してください。<BR>
     */
    virtual void rise();

    /**
     * サブメニューを表示する .
     * サブメニューを表示すると、サブメニューを閉じる(sinkSub()) まで、
     * 呼び出し元メニューは操作不可能になります。
     * @param prm_pSubMenu
     */
    virtual void riseSub(MenuActor<T>* prm_pSubMenu);

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
     * メニューを消去開始 .
     * 本オブジェクトを生成、タスクに追加後、表示させたいタイミングで実行してください。<BR>
     */
    virtual void sink();

    virtual void sinkSub();
    /**
     * rise()が実行された直後か否か .
     * @return
     */
    virtual bool isJustRise() {
        return _is_just_risen;
    }

    /**
     * sink()が実行された直後か否か .
     * @return
     */
    virtual bool isJustSink() {
        return _is_just_sunk;
    }

    virtual bool isJustDecided() {
        return _is_just_decided;
    }

    virtual bool isJustCancelled() {
        return _is_just_cancelled;
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
  T(prm_name, prm_model, NULL),_lstItems(3) { //全アイテム枝を３つ追加：「その他次」「その他前」「キャンセル」の３つ
    T::_class_name = "MenuActor";
    _pCursor = NULL;
    _X_cursor_adjust = 0;
    _Y_cursor_adjust = 0;
    _Z_cursor_adjust = 0;
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
    _pActiveSubMenu = NULL;
    for (int i = 0; i < 10; i++) {
        _lstMoveHistory.addLast(new int(0), true);
    }
    T::inactivateImmed(); //メニューなので、初期状態は非活動状態をデフォルトとする
}
template<class T>
void MenuActor<T>::riseSub(MenuActor<T>* prm_pSubMenu) {
    _pActiveSubMenu = prm_pSubMenu;
    _pActiveSubMenu->rise();
    _will_be_able_to_controll = false;
}
template<class T>
void MenuActor<T>::sinkSub() {
    _pActiveSubMenu->sink();
    _pActiveSubMenu = NULL;
    _will_be_able_to_controll = true;
}

template<class T>
void MenuActor<T>::nextFrame() {
    T::nextFrame();
    _is_just_risen = false;
    if (_will_be_rising_next_frame) {
        _with_rising = true;
        _is_just_risen = true;
        onRisen();
        _will_be_rising_next_frame = false;
    }

    _is_just_sunk = false;
    if (_will_be_sinking_next_frame) {
        _with_sinking = true;
        _is_just_sunk = true;
        onSunk();
        _will_be_sinking_next_frame = false;
    }

    _is_just_decided = false;
    if (_will_be_just_decided_next_frame) {
        onDecision(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
        _is_just_decided = true;
        _will_be_just_decided_next_frame = false;
    }

    _is_just_cancelled = false;
    if (_will_be_just_cancelled_next_frame) {
        onCancel(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
        _is_just_cancelled = true;
        _will_be_just_cancelled_next_frame = false;
    }

    _can_controll = _will_be_able_to_controll;
}

template<class T>
void MenuActor<T>::addSelectItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
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
void MenuActor<T>::addDispItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                                coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pItem->_X_local = prm_X_local;
    prm_pItem->_Y_local = prm_Y_local;
    prm_pItem->_Z_local = prm_Z_local;
    prm_pItem->_alpha = T::_alpha; //半透明αを共有させる。
    prm_pItem->inactivateImmed();
    _lstDispActors.addLast(prm_pItem);
    T::addSubLast(prm_pItem);
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
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::setSelectedItemIndex(int prm_index) {
    int n = getSelectedIndex();
    if (n == prm_index) {
        return _lstItems.getCurrent();
    } else {
#ifdef MY_DEBUG
        if (_lstItems.length() <= prm_index) {
            throwGgafCriticalException("MenuActor<T>::setSelectedItemIndex() メニューアイテム要素数オーバー name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
        }
#endif
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.current(prm_index);
        moveCursor();
        return pTargetItem;
    }
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
    *(_lstMoveHistory.current(0)) = _lstItems.getCurrentIndex();
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
int MenuActor<T>::getSelectedPrevIndex(int prm_n) {
    return (*(_lstMoveHistory.getPrev(prm_n)));
}

template<class T>
int MenuActor<T>::getDecidedIndex() {
    if (_is_just_decided) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}
template<class T>
int MenuActor<T>::getCancelledIndex() {
    if (_is_just_cancelled) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
MenuActor<T>* MenuActor<T>::getSubMenu() {
    return _pActiveSubMenu;
}

template<class T>
void MenuActor<T>::moveCursorNext() {
    if (_pCursor) {
        _pCursor->locateWith(_lstItems.getCurrent());
    }
    _lstItems.next();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorPrev() {
    if (_pCursor) {
        _pCursor->locateWith(_lstItems.getCurrent());
    }
    _lstItems.prev();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorExNext() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
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
            _pCursor->locateWith(_lstItems.getCurrent());
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
            _pCursor->locateWith(_lstItems.getCurrent());
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
        _pCursor->_pKurokoA->setMvAng(
                                pTargetItem->_X + _X_cursor_adjust,
                                pTargetItem->_Y + _Y_cursor_adjust,
                                pTargetItem->_Z + _Z_cursor_adjust
                            );
        _pCursor->_pKurokoA->setMvVelo(0);
        _pCursor->_pKurokoA->setMvAcce(0);
        _pCursor->_pKurokoA->execSmoothMvSequence(
                                 0,
                                 UTIL::getDistance(
                                         _pCursor->_X,
                                         _pCursor->_Y,
                                         _pCursor->_Z,
                                         pTargetItem->_X + _X_cursor_adjust,
                                         pTargetItem->_Y + _Y_cursor_adjust,
                                         pTargetItem->_Z + _Z_cursor_adjust),
                                 _cursor_move_frames,
                                 _cursor_move_p1, _cursor_move_p2);

        _X_cursor_target_prev = pTargetItem->_X;
        _Y_cursor_target_prev = pTargetItem->_Y;
        _Z_cursor_target_prev = pTargetItem->_Z;

        *(_lstMoveHistory.next()) = _lstItems.getCurrentIndex();
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
    _will_be_able_to_controll = true;

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
    GgafDxCore::GgafDxDrawableActor* p;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        p->setAlpha(T::getAlpha());
        pElem = pElem->_pNext;
    }
    //表示アイテムをメニューに追従
    pElem = _lstDispActors.getElemFirst();
    for (int i = 0; i < _lstDispActors.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        p->setAlpha(T::getAlpha());
        pElem = pElem->_pNext;
    }

    //カーソルをメニューアイテムに追従
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursor->_pKurokoA->isRunnigSmoothMvSequence()) {
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
}

template<class T>
void MenuActor<T>::sink() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = true;
    _will_be_able_to_controll = false;
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
        T::inactivateTree();
    }
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
