#ifndef GGAFLIB_MENUACTOR_H_
#define GGAFLIB_MENUACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/lib/actor/menu/MenuActor.hpp"
#include "jp/ggaf/lib/actor/StringBoardActor.h"
#include "jp/ggaf/lib/actor/StringSpriteActor.h"


using GgafDxCore::GgafDxUtil;


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


    /** メインカーソルの補正X座標 */
    coord _x_cursor_adjust;
    /** メインカーソルの補正Y座標 */
    coord _y_cursor_adjust;
    /** メインカーソルの補正Z座標 */
    coord _z_cursor_adjust;
    /** メインカーソル移動先アイテムの前フレームのX座標 */
    coord _x_cursor_target_prev;
    /** メインカーソル移動先アイテムの前フレームのY座標 */
    coord _y_cursor_target_prev;
    /** メインカーソル移動先アイテムの前フレームのZ座標 */
    coord _z_cursor_target_prev;
    /** [r]メインカーソルが、メニューアイテム間を移動する際に費やすスフレーム数 */
    int _cursor_move_frames;
    /** [r]メインカーソルが移動時、アイテム間移動距離の速度０〜最高速に達する時点の割合 */
    float _cursor_move_p1;
    /** [r]メインカーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合 */
    float _cursor_move_p2;
    /** [r]メインメニューカーソル */
    GgafDxCore::GgafDxDrawableActor* _pCursorActor;

    /**
     * 補助カーソル .
     */
    class SupCursor {
    public:
        /** [r]補助カーソルアクター */
        GgafDxCore::GgafDxDrawableActor* _pActor;
        /** 選択中インデックス  */
        int _select_index;
        /** 補助カーソルの補正X座標 */
        coord _x_adjust;
        /** 補助カーソルの補正Y座標 */
        coord _y_adjust;
        /** 補助カーソルの補正Z座標 */
        coord _z_adjust;
        /** 補助カーソル移動先アイテムの前フレームのX座標 */
        coord _x_target_prev;
        /** 補助カーソル移動先アイテムの前フレームのY座標 */
        coord _y_target_prev;
        /** 補助カーソル移動先アイテムの前フレームのZ座標 */
        coord _z_target_prev;
        /** [r]補助カーソルが、メニューアイテム間を移動する際に費やすスフレーム数 */
        int _move_frames;
        /** [r]補助カーソルが移動時、アイテム間移動距離の速度０〜最高速に達する時点の割合 */
        float _move_p1;
        /** [r]補助カーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合 */
        float _move_p2;
    public:
        SupCursor() {
            _select_index = 0;
            _move_frames = 10;
            _move_p1 = 0.2;
            _move_p2 = 0.7;
            _x_target_prev = 0;
            _y_target_prev = 0;
            _z_target_prev = 0;
            _pActor = nullptr;
            _x_adjust = 0;
            _y_adjust = 0;
            _z_adjust = 0;
        }
        virtual ~SupCursor() {
        }
    };

protected:
    /**
     * メインカーソルを選択アイテム(_lstItems のアクティブ要素)へ移動させる .
     * 「選択」と「カーソルの移動」は、別々で考えて下さい。<BR>
     * 本メソッドは予め選択済みのアイテムへ「カーソルの移動」だけであり、視覚効果の処理に特化しています。<BR>
     * 「選択」自体を行うものではありません。「選択」は selectItem() で行います。<BR>
     * また、selectItem() 処理内で、この moveCursor() は実行されます。<BR>
     * 従って、moveCursor() 単体で呼び出す事は殆ど想定してないので注意して下さい。<BR>
     * カーソル移動時の効果音を鳴らす場合等は、オーバーライドして再定義することで実現してください。<BR>
     * その処理中に上位 moveCursor() を呼び出すのを忘れないように。<BR>
     * @param prm_smooth スムーズ移動するか否か
     */
    virtual void moveCursor(bool prm_smooth = true);

    /**
     * 補助カーソルを選択アイテムへ移動させる .
     * 「選択」と「カーソルの移動」は、別々で考えて下さい。<BR>
     * 本メソッドは予め選択済みアイテムへ「カーソルの移動」だけであり、視覚効果の処理に特化しています。<BR>
     * 「選択」自体を行うものではありません。「選択」は selectItemBySupCursor() で行います。<BR>
     * また、selectItemBySupCursor() 処理内で、この moveSupCursor() は実行されます。<BR>
     * 従って、moveCursor() 単体で呼び出す事は殆ど想定してないので注意して下さい。<BR>
     * カーソル移動時の効果音を鳴らす場合等は、オーバーライドして再定義することで実現してください。<BR>
     * その処理中に上位 moveSupCursor() を呼び出すのを忘れないように。<BR>
     * @param prm_supcur_no
     * @param prm_smooth
     */
    virtual void moveSupCursor(int prm_supcur_no, bool prm_smooth = true);

public:
    /** [r]メニューアイテムのリスト、アクティブはメインカーソルが選択されている */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstItems;
    /** [r]その他表示アイテムのリスト */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstDispActors;
    /** [r]メインカーソルが移動したメニューアイテムインデックスのヒストリー(0〜N、但し初期は全て -1 ) */
    GgafCore::GgafLinkedListRing<int> _lstMvCursorHistory;
    /** [r]選択したメニューアイテムインデックスのヒストリー(0〜N、但し初期は全て -1 ) */
    GgafCore::GgafLinkedListRing<int> _lstMvSelectHistory;
    /** [r]メニューフェイドイン・アウト時のフレーム数 */
    frame _fade_frames;
    /** [r]メニューフェイドイン・アウト時のアルファ速度 */
    float _velo_alpha_fade;
    /** [r]サブメニューのリスト */
    GgafCore::GgafLinkedListRing<MenuActor<T> > _lstSubMenu;
    /** [r]サブカーソルのリスト */
    GgafCore::GgafLinkedListRing<SupCursor> _lstSupCursor;

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
        if (prm_menu_fade_frames == 0) {
            _velo_alpha_fade = 1.0;
        } else {
            _velo_alpha_fade = 1.0 / prm_menu_fade_frames;
        }
    }

    /**
     * 選択可能メニューアイテムを追加し、メニューアイテム間のオーダーも連結追加する .
     * 追加されたアイテムはメニューオブジェクト(this)のサブに登録されるため、
     * メニューオブジェクトがタスクツリーに登録されるならば delete する必要はない。
     * 【注意】<BR>
     * 同一Z座標ならば、後に addItem() した方が、より手前に表示となる。<BR>
     * @param prm_pItem メニューアイテム
     * @param prm_x_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_z_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * 選択可能メニューアイテム追加し、メニューアイテム間のオーダーも連結追加する .
     * 追加されたアイテムはメニューオブジェクト(this)のサブに登録されるため、
     * メニューオブジェクトがタスクツリーに登録されるならば delete する必要はない。<BR>
     * 【注意】<BR>
     * 同一Z座標ならば、後に addItem() した方が、より手前に表示となる。<BR>
     * Z座標は、オフセット0が設定される。つまりアイテムの絶対Z座標は、現在のメニューのZ座標と一致する。<BR>
     * もしメニューが2Dで、アイテムの表示プライオリティの考慮が必要な場合は、オフセットを-1等に明示設定も可能。
     * @param prm_pItem メニューアイテム
     * @param prm_x_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local メニューオブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_x_local, coord prm_y_local) {
        addItem(prm_pItem, prm_x_local, prm_y_local, 0);
    }

    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem) {
        addItem(prm_pItem, 0, 0, 0);
    }

    virtual void positionItem(int prm_index_of_item,
                              coord prm_x_local, coord prm_y_local, coord prm_z_local);

    virtual void positionItem(int prm_index_of_item,
                              coord prm_x_local, coord prm_y_local) {
        positionItem(prm_index_of_item, prm_x_local, prm_y_local, 0);
    }

    /**
     * 選択不可の表示用メニューアイテム(ラベル)を追加する .
     * 【注意】<BR>
     * 同一Z座標ならば、より後の順に addDisp() した方が、より手前に表示となる。<BR>
     * @param prm_pItem 表示用ラベルのアクター
     * @param prm_x_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_z_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                         coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * 選択不可の表示用メニューラベルを追加する .
     * 【注意】<BR>
     * 同一Z座標ならば、より後の順に addDisp() した方が、より手前に表示となる。<BR>
     * Z座標は、オフセット0が設定される。つまり表示用アクターの絶対Z座標は、現在のメニューのZ座標と一致する。
     * もしメニューが2Dで、アイテムの表示プライオリティの考慮が必要な場合は、オフセットを-1等に明示設定も可能。
     * @param prm_pItem 表示用ラベルのアクター
     * @param prm_x_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                         coord prm_x_local, coord prm_y_local) {
        addDisp(prm_pDisp, prm_x_local, prm_y_local, 0);
    }


    virtual void addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp) {
        addDisp(prm_pDisp, 0, 0, 0);
    }

    virtual void positionDisp(int prm_index_of_disp,
                              coord prm_x_local, coord prm_y_local, coord prm_z_local);

    virtual void positionDisp(int prm_index_of_disp,
                              coord prm_x_local, coord prm_y_local) {
        positionItem(prm_index_of_disp, prm_x_local, prm_y_local, 0);
    }

    /**
     * メインカーソルオブジェクトを設定する .
     * 【注意】<BR>
     * カーソル移動を制御するため、MenuActor<T>::processBehavior() 内で、<BR>
     * _pCursorActor->getKuroko()->behave(); <BR>
     * を実行しています。したがって、引数のカーソルクラスで、<BR>
     * getKuroko()->behave(); <BR>
     * を実行する必要はありません。<BR>
     * @param prm_pCursorActor メインカーソル
     * @param prm_x_cursor_adjust アイテムとの重なりを補正するための加算される差分X座標
     * @param prm_y_cursor_adjust アイテムとの重なりを補正するための加算される差分Y座標
     * @param prm_z_cursor_adjust アイテムとの重なりを補正するための加算される差分Z座標
     * @param prm_cursor_move_frames メインカーソルがアイテム間移動に費やすフレーム(デフォルト8フレーム)
     * @param prm_cursor_move_p1 メインカーソルが移動時、アイテム間移動距離の速度０〜最高速に達する時点の割合(デフォルト0.2)
     * @param prm_cursor_move_p2 メインカーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合(デフォルト0.7)
     */
    virtual void setMainCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursorActor,
                               coord prm_x_cursor_adjust = 0,
                               coord prm_y_cursor_adjust = 0,
                               coord prm_z_cursor_adjust = 0,
                               int prm_cursor_move_frames = 10,
                               float prm_cursor_move_p1 = 0.2,
                               float prm_cursor_move_p2 = 0.6);

    /**
     * 補助カーソルオブジェクトを設定する .
     * 【注意】<BR>
     * カーソル移動を制御するため、MenuActor<T>::processBehavior() 内で、<BR>
     * _lstSupCursor.getFromFirst(i)->_pActor->getKuroko()->behave(); <BR>
     * を実行しています。したがって、引数のカーソルクラスで、<BR>
     * getKuroko()->behave(); <BR>
     * を実行する必要はありません。<BR>
     * @param prm_pCursorActor 補助カーソル
     * @param prm_x_cursor_adjust アイテムとの重なりを補正するための加算される差分X座標
     * @param prm_y_cursor_adjust アイテムとの重なりを補正するための加算される差分Y座標
     * @param prm_z_cursor_adjust アイテムとの重なりを補正するための加算される差分Z座標
     * @param prm_cursor_move_frames 補助カーソルがアイテム間移動に費やすフレーム(デフォルト8フレーム)
     * @param prm_cursor_move_p1 補助カーソルが移動時、アイテム間移動距離の速度０〜最高速に達する時点の割合(デフォルト0.2)
     * @param prm_cursor_move_p2 補助カーソルが移動時、アイテム間移動距離の最高速から減速を開始する割合(デフォルト0.7)
     */
    virtual void addSupCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursorActor,
                              coord prm_x_cursor_adjust = 0,
                              coord prm_y_cursor_adjust = 0,
                              coord prm_z_cursor_adjust = 0,
                              int prm_cursor_move_frames = 10,
                              float prm_cursor_move_p1 = 0.2,
                              float prm_cursor_move_p2 = 0.6);

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
    virtual void relateItemToExNext(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(item1 ⇔ item2  ⇔ item3) .
     * @param prm_index_of_item1 拡張連結するメニューアイテムのインデックス1
     * @param prm_index_of_item2 拡張連結するメニューアイテムのインデックス2
     * @param prm_index_of_item3 拡張連結するメニューアイテムのインデックス3
     */
    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3 );
    /**
     * メニューアイテム間のオーダー連結を拡張設定(item1 ⇔ item2  ⇔ item3 ⇔ item4) .
     * @param prm_index_of_item1 拡張連結するメニューアイテムのインデックス1
     * @param prm_index_of_item2 拡張連結するメニューアイテムのインデックス2
     * @param prm_index_of_item3 拡張連結するメニューアイテムのインデックス3
     * @param prm_index_of_item4 拡張連結するメニューアイテムのインデックス4
     */
    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4 );
    /**
     * メニューアイテム間のオーダー連結を拡張設定(item1 ⇔ item2  ⇔ item3 ⇔ item4 ⇔ item5).
     * @param prm_index_of_item1 拡張連結するメニューアイテムのインデックス1
     * @param prm_index_of_item2 拡張連結するメニューアイテムのインデックス2
     * @param prm_index_of_item3 拡張連結するメニューアイテムのインデックス3
     * @param prm_index_of_item4 拡張連結するメニューアイテムのインデックス4
     * @param prm_index_of_item5 拡張連結するメニューアイテムのインデックス5
     */
    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4,
                                    int prm_index_of_item5 );


//    virtual void relateItemToExNext(int prm_index_of_fromitem, ...);

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
    virtual void relateItemToExPrev(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * 既存アイテム全てに対し、「キャンセル（メニューアイテム）」へのオーダー連結を拡張設定する .
     * @param prm_index_of_cancel_item キャンセルアイテムへのアイテムインデックス
     */
    virtual void relateAllItemToCancel(int prm_index_of_cancel_item);

    /**
     * メニューに設定されているメインカーソルを取得 .
     * @return メインカーソルオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getMainCursor();

    /**
     * メニューに設定されている補助カーソルを取得 .
     * @param prm_supcur_no 補助カーソル番号
     * @return 補助カーソルオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSupCursor(int prm_supcur_no);

    /**
     * メインカーソルで「次」のアイテム(但しisActive())選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectNext();

    /**
     * メインカーソルで「前」のアイテム(但しisActive())選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectPrev();

    /**
     * メインカーソルで「（別の）次」のアイテム(但しisActive())選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectExNext();

    /**
     * メインカーソルで「（別の）前」のアイテム(但しisActive())選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectExPrev();

    /**
     * メインカーソルで「キャンセル」アイテム選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectCancel();

    /**
     * メインカーソルで指定のインデックスのメニューアイテムを「選択」し、メインカーソルを移動させる .
     * onSelect() コールバックは必ず発生します。<BR>
     * 内部で moveCursor() がコールバックされ、メインカーソルが移動することになる。<BR>
     * 既に指定のインデックス選択中の場合はメインカーソルは何も移動無し。<BR>
     * ついでに、引数インデックスのアイテムオブジェクトもゲット出来る。<BR>
     * @param prm_index ターゲットのアイテムインデックス
     * @return prm_indexのアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* selectItem(int prm_index, bool prm_smooth = true);

    /**
     * 補助カーソルで指定のインデックスのメニューアイテムを「選択」し、補助カーソルを移動させる .
    * onSelect() コールバックは発生しません。<BR>
     * 内部で moveSupCursor() がコールバックされ、メインカーソルが移動することになる。<BR>
     * 既に指定のインデックス選択中の場合はメインカーソルは何も移動無し。<BR>
     * ついでに、引数インデックスのアイテムオブジェクトもゲット出来る。<BR>
     * @param prm_index ターゲットのアイテムインデックス
     * @param prm_supcur_no 補助カーソル番号
     * @return prm_indexのアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* selectItemBySupCursor(int prm_supcur_no, int prm_item_index, bool prm_smooth = true);

    /**
     * メインカーソルで指定のメニューアイテムを「選択」し、メインカーソルを移動させる .
     * 引数のターゲットアイテムのインデックスを調べて、selectItem(index); を実行します。
     * @param prm_item ターゲットアイテム
     * @return ターゲットのアイテムインデックス
     */
    virtual int selectItem(GgafDxCore::GgafDxDrawableActor* prm_item, bool prm_smooth = true);

    /**
     * 補助カーソルで指定のメニューアイテムを「選択」し、補助カーソルを移動させる .
     * 内部で moveSupCursor() がコールバックされ、カーソルが移動することになる。<BR>
     * 既に指定のインデックス選択中の場合はカーソルは何も移動無し。<BR>
     * ついでに、引数アイテムオブジェクトのインデックスもゲット出来る。<BR>
     * @param prm_item ターゲットのアイテム
     * @param prm_supcur_no 補助カーソル番号
     * @return
     */
    virtual int selectItemBySupCursor(int prm_supcur_no, GgafDxCore::GgafDxDrawableActor* prm_item, bool prm_smooth = true);

    /**
     * 現在メインカーソルが選択中のアイテムのインデックスを取得 .
     * @return 選択中のアイテムのインデックス
     */
    virtual int getSelectedIndex();

    /**
     * 現在補助カーソルが選択中のアイテムのインデックスを取得 .
     * @param prm_supcur_no 補助カーソル番号
     * @return 選択中のアイテムのインデックス
     */
    virtual int getSelectedIndexOnSupCursor(int prm_supcur_no);

    /**
     * 現在メインカーソルが選択中のアイテムのオブジェクトを取得 .
     * @return 選択中のアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItem();

    /**
     * 現在補助カーソルが選択中のアイテムのオブジェクトを取得 .
     * @param prm_supcur_no 補助カーソル番号
     * @return 選択中のアイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItemOnSupCursor(int prm_supcur_no);

    /**
     * 過去にメインカーソルが選択中だったアイテムのインデックスを取得 .
     * getMvCursorHistoryIndex(0) は getSelectedIndex() と同じです。
     * 指定の過去がない場合は -1 を返します。
     * @param prm_n 幾つ過去のカーソル位置か(0 〜)
     * @return 選択中だったのアイテムオブジェクトのインデックス（無い場合は -1）
     */
    virtual int getMvCursorHistoryIndex(int prm_n);

    /**
     * 「決定（振る舞い）」が行われた時に、そのメニューアイテムのインデックスを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnDecidedIndex() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith〜case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return 決定された時：そのアイテムのインデックス(>=0)／何も決定されていない場合：常に -1
     */
    virtual int getOnDecidedIndex();

    /**
     * 「決定（振る舞い）」が行われた時に、そのメニューアイテムを返します .
     * それ以外の時は 常に nullptr を返します<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnDecidedItem() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith〜case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return 決定された時：そのアイテム／何も決定されていない場合：常に nullptr
     */
    virtual GgafDxCore::GgafDxDrawableActor* getOnDecidedItem();

    /**
     * 「キャンセル（振る舞い）」が行われた時に、そのメニューアイテムのインデックスを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目がキャンセルされた場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnCancelledIndex() の戻り値を毎フレーム調べることで、キャンセル時の処理を記述することが可能。<BR>
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith〜case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return キャンセルされた時：そのアイテムのインデックス(>=0)／何もキャンセルされていない場合：常に -1
     */
    virtual int getOnCancelledIndex();

    /**
     * 「キャンセル（振る舞い）」が行われた時に、そのメニューアイテムを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目がキャンセルされた場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnCancelledItem() の戻り値を毎フレーム調べることで、キャンセル時の処理を記述することが可能。<BR>
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith〜case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return キャンセルされた時：そのアイテム／何もキャンセルされていない場合：常に nullptr
     */
    virtual GgafDxCore::GgafDxDrawableActor* getOnCancelledItem();

    /**
     * 選択対象アイテムのオブジェクトを取得 .
     * @param prm_index 取得したい選択対象アイテムのインデックス(0〜)
     * @return アイテムオブジェクト
     */
    virtual GgafDxCore::GgafDxDrawableActor* getItem(int prm_index);

    /**
     * その他表示用アイテムのオブジェクトを取得 .
     * @param prm_index 取得したい表示用アイテムのインデックス(0〜)
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
     * メインカーソルが「次のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「次のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectNext() = 0;

    /**
     * メインカーソルが「前のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「前のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectPrev() = 0;

    /**
     * メインカーソルが「もう一つの別の次のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「もう一つの別の次のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectExNext() = 0;

    /**
     * メインカーソルが「もう一つの別の前のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「もう一つの別の前のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectExPrev() = 0;

    /**
     * メインカーソルが「キャンセルのメニューアイテム」へ飛ぶ条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「キャンセルのメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectCancel() = 0;

    /**
     * 「決定（振る舞い）」された場合に呼び出されるコールバック。
     * 動作をオーバーライドして実装してください。<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で、getOnDecidedIndex() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith〜case を記述しても良い。<BR>
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
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith〜case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。
     * @param prm_pItem
     * @param prm_item_index
     */
    virtual void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * メインカーソルが移動した場合に呼び出されるコールバック。 .
     * 動作をオーバーライドして実装してください。<BR>
     * 【捕捉】<BR>
     * onMoveCursor(int,int) と onSelect(int,int) のコールバックタイミングの差について。<BR>
     * onMoveCursor(int,int) は、selectXxxxx 系のメソッド実行の際、カーソルが移動した場合のみ呼び出されます。<BR>
     * onSelect(int,int) は、selectXxxxx 系 のメソッドを実行時に、もれなく呼び出されます(たとえ、カーソルが移動しなくても)<BR>
     * 呼び出される順序は、onMoveCursor(int,int)  → onSelect(int,int) の順です。<BR>
     * @param prm_from 移動元のアイテムのインデックス（無い（初期の）場合は -1）
     * @param prm_to   移動先のアイテムのインデックス
     */
    virtual void onMoveCursor(int prm_from, int prm_to) = 0;

    /**
     * メインカーソルがアイテムを選択された場合に呼び出されるコールバック。 .
     * 動作をオーバーライドして実装してください。<BR>
     * 【捕捉】<BR>
     * onMoveCursor(int,int) と onSelect(int,int) のコールバックタイミングの差について。<BR>
     * onMoveCursor(int,int) は、selectXxxxx 系のメソッド実行の際、カーソルが移動した場合のみ呼び出されます。<BR>
     * onSelect(int,int) は、selectXxxxx 系 のメソッドを実行時に、もれなく呼び出されます(たとえ、カーソルが移動しなくても)<BR>
     * 呼び出される順序は、onMoveCursor(int,int)  → onSelect(int,int) の順です。<BR>
     * @param prm_from 選択元（今回選択される前）のアイテムのインデックス（無い（初期の）場合は -1）
     * @param prm_to   選択先のアイテムのインデックス
     */
    virtual void onSelect(int prm_from, int prm_to) = 0;


    /**
     * メニューを表示開始する .
     * 本オブジェクトを生成、タスクに追加後、表示させたいタイミングで実行してください。<BR>
     */
    virtual void riseMe();

    /**
     * メニュー表示開始時のコールバック .
     * riseMe() 実行時直後、１回だけコールバックされます。<BR>
     * 必要に応じてオーバーライドしてください。<BR>
     */
    virtual void onRise();

    /**
     * メニュー表示中トランジション処理 .
     * riseMe() 実行 〜 フェードイン完了までの間コールされ続けます。
     * アルファを加算しフェードイン効果を行い、アルファが1.0になれば終了。
     * というトランジション処理が実装済みです。<BR>
     * トランジションを独自に行いたい場合はオーバーライドし、トランジション完了時に<BR>
     * _with_rising = false;<BR>
     * を実行してください。<BR>
     */
    virtual void processRising();

    /**
     * メニュー表示完了時のコールバック .
     * 必要に応じてオーバーライドしてください。<BR>
     */
    virtual void onRiseDone();

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
    virtual void sinkMe();

    /**
     * riseMe()が実行された直後か否かを返す .
     * @return true:今丁度 riseMe()が 実行された直後である/false:そうではない
     */
    virtual bool isJustRisen() {
        return _is_just_risen;
    }

    /**
     * sinkMe() が実行された直後か否かを返す .
     * @return true:今丁度 sinkMe() が実行された直後である/false:そうではない
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
     * sinkMe() 実行時直後、１回だけコールバックされます。<BR>
     * 必要に応じてオーバーライドしてください。<BR>
     */
    virtual void onSink();

    /**
     * メニュー消去のトランジション処理 .
     * sinkMe() 実行 〜 フェードアウト完了までの間コールされ続けます。
     * アルファを減算しフェードアウト効果を行い、アルファが1.0になれば終了
     * というトランジション処理が実装済みです。<BR>
     * トランジションを独自に行いたい場合はオーバーライドし、トランジション完了時に<BR>
     * _with_sinking = false;<BR>
     * T::inactivateTreeImmed();<BR>
     * を実行してください。<BR>
     */
    virtual void processSinking();

    /**
     * メニューを消去完了時のコールバック .
     * processSinking()中、_with_sinking = false; になった瞬間にコールされます。
     * 必要に応じてオーバーライドしてください。<BR>
     */
    virtual void onSinkDone();

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
     * サブメニューを表示すると、サブメニューを閉じる(sinkCurrentSubMenu()) まで、
     * 呼び出し元メニューは操作不可能になります。
     * @param prm_index アクティブにするサブメニューのインデックス
     */
    virtual void riseSubMenu(int prm_index);

    /**
     * 現在アクティブなサブメニューを閉じて終了させる .
     * 事前に addSubMenu() でサブメニューを設定する必要があります。<BR>
     */
    virtual void sinkCurrentSubMenu();

    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model),_lstItems(3) { //全アイテム枝を３つ追加：「その他次」「その他前」「キャンセル」の３つ
    T::_class_name = "MenuActor";

    _fade_frames = 0;
    _velo_alpha_fade = 1.0;

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

    _cursor_move_frames = 10;
    _cursor_move_p1 = 0.2;
    _cursor_move_p2 = 0.7;
    _x_cursor_target_prev = T::_x;
    _y_cursor_target_prev = T::_y;
    _z_cursor_target_prev = T::_z;
    _pCursorActor = nullptr;
    _x_cursor_adjust = 0;
    _y_cursor_adjust = 0;
    _z_cursor_adjust = 0;

    for (int i = 0; i < 10; i++) {
        _lstMvCursorHistory.addLast(new int(-1), true);
        _lstMvSelectHistory.addLast(new int(-1), true);
    }
    T::inactivate(); //メニューなので、初期状態は非活動状態をデフォルトとする
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
                           coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    prm_pItem->_x_local = prm_x_local;
    prm_pItem->_y_local = prm_y_local;
    prm_pItem->_z_local = prm_z_local;
    prm_pItem->setAlpha(T::_alpha); //半透明αを共有させる。
    prm_pItem->inactivate();
    _lstItems.addLast(prm_pItem, false);
    T::addSubLast(prm_pItem);
}

template<class T>
void MenuActor<T>::positionItem(int prm_index_of_item,
                                coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    GgafDxCore::GgafDxDrawableActor* p = getItem(prm_index_of_item);
    p->_x_local = prm_x_local;
    p->_y_local = prm_y_local;
    p->_z_local = prm_z_local;
}

template<class T>
void MenuActor<T>::addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                           coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    prm_pDisp->_x_local = prm_x_local;
    prm_pDisp->_y_local = prm_y_local;
    prm_pDisp->_z_local = prm_z_local;
    prm_pDisp->setAlpha(T::_alpha); //半透明αを共有させる。
    prm_pDisp->inactivate();
    _lstDispActors.addLast(prm_pDisp, false);
    T::addSubLast(prm_pDisp);
}

template<class T>
void MenuActor<T>::positionDisp(int prm_index_of_item,
                                coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    GgafDxCore::GgafDxDrawableActor* p = getItem(prm_index_of_item);
    p->_x_local = prm_x_local;
    p->_y_local = prm_y_local;
    p->_z_local = prm_z_local;
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3 ) {
    relateItemToExNext(prm_index_of_item1, prm_index_of_item2);
    relateItemToExNext(prm_index_of_item2, prm_index_of_item3);
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3,
                                      int prm_index_of_item4 ) {
    relateItemToExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3);
    relateItemToExNext(prm_index_of_item3, prm_index_of_item4);
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3,
                                      int prm_index_of_item4,
                                      int prm_index_of_item5 ) {
    relateItemToExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3, prm_index_of_item4);
    relateItemToExNext(prm_index_of_item4, prm_index_of_item5);
}


//template<class T>
//void MenuActor<T>::relateItemToExNext(int prm_index_of_fromitem, ...) {
//    va_list pArg;
//    va_start(pArg, prm_index_of_fromitem);         //可変長引数操作開始
//        va_arg( argptr, int );
//
//
//
//    va_end(pArg);      //可変長引数操作終了
//}


template<class T>
void MenuActor<T>::relateItemToExPrev(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relateAllItemToCancel(int prm_index_of_cancel_item) {
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pCancelElem =
            _lstItems.getElemFromFirst(prm_index_of_cancel_item);
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem =
            _lstItems.getElemFirst();
    int n = _lstItems.length();
    for (int i = 0; i < n; i++) {
        pElem->connect(ITEM_RELATION_TO_CANCEL, pCancelElem);
        pElem = pElem->_pNext;
    }
}


template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::selectItem(int prm_index, bool prm_smooth) {
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
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.current(prm_index); //これでセレクト！
        if (T::getActiveFrame() > 1) {
            moveCursor(prm_smooth);  //スムーズ移動は引数
        } else {
            moveCursor(false); //スムーズ移動無し(初期選択の為のselectItem)
        }
        *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
        onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
        return pTargetItem;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::selectItemBySupCursor(int prm_supcur_no, int prm_item_index, bool prm_smooth) {
    int n = getSelectedIndexOnSupCursor(prm_supcur_no);
#ifdef MY_DEBUG
    if (n == -1) {
        throwGgafCriticalException("MenuActor<T>::selectItemBySupCursor() メニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item_index="<<prm_item_index);
    }
#endif
    //補助カーソルはコールバックなし
    if (n == prm_item_index) {
        //既に選択している。
        return _lstItems.getFromFirst(n);
    } else {
#ifdef MY_DEBUG
        if (_lstItems.length() <= prm_item_index) {
            throwGgafCriticalException("MenuActor<T>::selectItemBySupCursor() メニューアイテム要素数オーバー name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item_index="<<prm_item_index);
        }
#endif
        _lstSupCursor.getFromFirst(prm_supcur_no)->_select_index = prm_item_index; //これでセレクト！
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getFromFirst(prm_item_index);

        if (T::getActiveFrame() > 1) {
            moveSupCursor(prm_supcur_no, prm_smooth);  //スムーズ移動は引数依存
        } else {
            moveSupCursor(prm_supcur_no, false); //スムーズ移動無し(初期選択の為のselectItem)
        }
        return pTargetItem;
    }
}

template<class T>
int MenuActor<T>::selectItem(GgafDxCore::GgafDxDrawableActor* prm_item, bool prm_smooth) {
    int index = _lstItems.indexOf(prm_item);
    if (index == -1) {
        throwGgafCriticalException("MenuActor<T>::selectItem() その前にメニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item="<<prm_item->getName());
    }
    selectItem(index, prm_smooth);
    return index;
}

template<class T>
int MenuActor<T>::selectItemBySupCursor(int prm_supcur_no, GgafDxCore::GgafDxDrawableActor* prm_item, bool prm_smooth) {
    int index = _lstItems.indexOf(prm_item);
    if (index == -1) {
        throwGgafCriticalException("MenuActor<T>::selectItemBySupCursor() その前にメニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item="<<prm_item->getName());
    }
    selectItemBySupCursor(index, prm_supcur_no, prm_smooth);
    return index;
}

template<class T>
void MenuActor<T>::setMainCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursorActor,
                                 coord prm_x_cursor_adjust,
                                 coord prm_y_cursor_adjust,
                                 coord prm_z_cursor_adjust,
                                 int prm_cursor_move_frames,
                                 float prm_cursor_move_p1,
                                 float prm_cursor_move_p2) {
    _pCursorActor = prm_pCursorActor;
    _pCursorActor->setAlpha(T::_alpha);
    _pCursorActor->inactivate();
    T::addSubLast(_pCursorActor);
    _x_cursor_adjust = prm_x_cursor_adjust;
    _y_cursor_adjust = prm_y_cursor_adjust;
    _z_cursor_adjust = prm_z_cursor_adjust;
    _cursor_move_frames = prm_cursor_move_frames;
    _cursor_move_p1 = prm_cursor_move_p1;
    _cursor_move_p2 = prm_cursor_move_p2;
    selectItem(0);
}

template<class T>
void MenuActor<T>::addSupCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursorActor,
                                 coord prm_x_cursor_adjust,
                                 coord prm_y_cursor_adjust,
                                 coord prm_z_cursor_adjust,
                                 int prm_cursor_move_frames,
                                 float prm_cursor_move_p1,
                                 float prm_cursor_move_p2) {
    MenuActor<T>::SupCursor* pSupCursor = NEW MenuActor<T>::SupCursor();
    pSupCursor->_pActor = prm_pCursorActor;
    pSupCursor->_pActor->setAlpha(T::_alpha);
    pSupCursor->_pActor->inactivate();
    pSupCursor->_select_index = 0;
    pSupCursor->_x_adjust = prm_x_cursor_adjust;
    pSupCursor->_y_adjust = prm_y_cursor_adjust;
    pSupCursor->_z_adjust = prm_z_cursor_adjust;
    pSupCursor->_move_frames = prm_cursor_move_frames;
    pSupCursor->_move_p1 = prm_cursor_move_p1;
    pSupCursor->_move_p2 = prm_cursor_move_p2;
    _lstSupCursor.addLast(pSupCursor, true);
    T::addSubLast(pSupCursor->_pActor);
    selectItemBySupCursor(0, _lstSupCursor.length()-1);
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getMainCursor() {
    return _pCursorActor;
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSupCursor(int prm_supcur_no) {
    return _lstSupCursor.getFromFirst(prm_supcur_no)->_pActor;
}

template<class T>
int MenuActor<T>::getSelectedIndex() {
    return _lstItems.getCurrentIndex();
}

template<class T>
int MenuActor<T>::getSelectedIndexOnSupCursor(int prm_supcur_no) {
    return _lstSupCursor.getFromFirst(prm_supcur_no)->_select_index;
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItemOnSupCursor(int prm_supcur_no) {
    return _lstItems.getFromFirst(getSelectedIndexOnSupCursor(prm_supcur_no));
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
#ifdef MY_DEBUG
    if (_lstItems.length() <= prm_index) {
        throwGgafCriticalException("MenuActor<T>::getItem() メニューアイテム要素数オーバー name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstItems.getFromFirst(prm_index);
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getDisp(int prm_index) {
#ifdef MY_DEBUG
    if (_lstDispActors.length() <= prm_index) {
        throwGgafCriticalException("MenuActor<T>::getDisp() 表示ラベルアイテム要素数オーバー name="<<T::getName()<<" _lstDispActors.length()="<<_lstDispActors.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstDispActors.getFromFirst(prm_index);
}


template<class T>
void MenuActor<T>::selectNext() {
    GgafDxCore::GgafDxDrawableActor* pCurrent = _lstItems.getCurrent();
    if (_pCursorActor) {
        _pCursorActor->positionAs(pCurrent);
    }
    GgafDxCore::GgafDxDrawableActor* pNext;
    while(true) {
        pNext = _lstItems.next();
        if (pNext->isActive()) {
            break;
        } else {
            if (pNext == pCurrent) {
                break;
            }
        }
    }
    moveCursor();
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectPrev() {
    GgafDxCore::GgafDxDrawableActor* pCurrent = _lstItems.getCurrent();
    if (_pCursorActor) {
        _pCursorActor->positionAs(pCurrent);
    }
    GgafDxCore::GgafDxDrawableActor* pPrev;
    while(true) {
        pPrev = _lstItems.prev();
        if (pPrev->isActive()) {
            break;
        } else {
            if (pPrev == pCurrent) {
                break;
            }
        }
    }
    moveCursor();
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectExNext() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        GgafDxCore::GgafDxDrawableActor* pCurrent = _lstItems.getCurrent();
        if (_pCursorActor) {
            _pCursorActor->positionAs(pCurrent);
        }
        GgafDxCore::GgafDxDrawableActor* pRelation;
        while(true) {
            pRelation = _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
            if (pRelation->isActive()) {
                break;
            } else {
                if (pRelation == pCurrent) {
                    break;
                }
            }
        }
        moveCursor();
    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectExPrev() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        GgafDxCore::GgafDxDrawableActor* pCurrent = _lstItems.getCurrent();
        if (_pCursorActor) {
            _pCursorActor->positionAs(pCurrent);
        }
        GgafDxCore::GgafDxDrawableActor* pRelation;
        while(true) {
            pRelation = _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
            if (pRelation->isActive()) {
                break;
            } else {
                if (pRelation == pCurrent) {
                    break;
                }
            }
        }
        moveCursor();
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectCancel() {
    if (_lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        if (_pCursorActor) {
            _pCursorActor->positionAs(_lstItems.getCurrent());
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
    if (_pCursorActor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        GgafDxCore::GgafDxKuroko* pCursorActor_pKuroko = _pCursorActor->getKuroko();
        if (prm_smooth) {
            pCursorActor_pKuroko->setMvAngTwd(
                                    pTargetItem->_x + _x_cursor_adjust,
                                    pTargetItem->_y + _y_cursor_adjust,
                                    pTargetItem->_z + _z_cursor_adjust
                                  );
            pCursorActor_pKuroko->stopMv();
            pCursorActor_pKuroko->asstA()->slideMvByDt(
                                    UTIL::getDistance(_pCursorActor->_x,
                                                      _pCursorActor->_y,
                                                      _pCursorActor->_z,
                                                      pTargetItem->_x + _x_cursor_adjust,
                                                      pTargetItem->_y + _y_cursor_adjust,
                                                      pTargetItem->_z + _z_cursor_adjust ),
                                    _cursor_move_frames,
                                    _cursor_move_p1, _cursor_move_p2, 0 , true
                                  );
            _x_cursor_target_prev = pTargetItem->_x;
            _y_cursor_target_prev = pTargetItem->_y;
            _z_cursor_target_prev = pTargetItem->_z;
        } else {
            pCursorActor_pKuroko->asstA()->stopSlidingMv();
            pCursorActor_pKuroko->stopMv();
            _pCursorActor->_x = pTargetItem->_x + _x_cursor_adjust;
            _pCursorActor->_y = pTargetItem->_y + _y_cursor_adjust;
            _pCursorActor->_z = pTargetItem->_z + _z_cursor_adjust;
        }
        *(_lstMvCursorHistory.next()) = _lstItems.getCurrentIndex();
        onMoveCursor(*(_lstMvCursorHistory.getPrev()), *(_lstMvCursorHistory.getCurrent())); //コールバック
    }
}


template<class T>
void MenuActor<T>::moveSupCursor(int prm_supcur_no, bool prm_smooth) {
    if (_lstSupCursor.length() > 0) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = getSelectedItemOnSupCursor(prm_supcur_no);
        SupCursor* pSupCursor = _lstSupCursor.getFromFirst(prm_supcur_no);
        GgafDxCore::GgafDxDrawableActor* pSupCursorActor = pSupCursor->_pActor;
        GgafDxCore::GgafDxKuroko* pSupCursorActor_pKuroko = pSupCursorActor->getKuroko();
        if (prm_smooth) {
            pSupCursorActor_pKuroko->setMvAngTwd(
                                         pTargetItem->_x + pSupCursor->_x_adjust,
                                         pTargetItem->_y + pSupCursor->_y_adjust,
                                         pTargetItem->_z + pSupCursor->_z_adjust
                                     );
            pSupCursorActor_pKuroko->stopMv();
            pSupCursorActor_pKuroko->asstA()->slideMvByDt(
                                      UTIL::getDistance(pSupCursorActor->_x,
                                                        pSupCursorActor->_y,
                                                        pSupCursorActor->_z,
                                                        pTargetItem->_x + pSupCursor->_x_adjust,
                                                        pTargetItem->_y + pSupCursor->_y_adjust,
                                                        pTargetItem->_z + pSupCursor->_z_adjust ),
                                      pSupCursor->_move_frames,
                                      pSupCursor->_move_p1, pSupCursor->_move_p2, 0 , true
                                    );
            pSupCursor->_x_target_prev = pTargetItem->_x;
            pSupCursor->_y_target_prev = pTargetItem->_y;
            pSupCursor->_z_target_prev = pTargetItem->_z;
        } else {
            pSupCursorActor_pKuroko->asstA()->stopSlidingMv();
            pSupCursorActor_pKuroko->stopMv();
            pSupCursorActor->_x = pTargetItem->_x + pSupCursor->_x_adjust;
            pSupCursorActor->_y = pTargetItem->_y + pSupCursor->_y_adjust;
            pSupCursorActor->_z = pTargetItem->_z + pSupCursor->_z_adjust;
        }
    }
}

template<class T>
void MenuActor<T>::riseMe() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = true;
    _will_be_sinking_next_frame = false;
    enableControll();
    if (_velo_alpha_fade >= 1.0) {
        T::setAlpha(1.0);
    } else {
        T::setAlpha(0.0);
    }
    T::activate();
    //メニューアイテム初期配置
    GgafDxCore::GgafDxDrawableActor* p;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    int n_i = _lstItems.length();
    for (int i = 0; i < n_i; i++) {
        p = pElem->_pValue;
        p->position(T::_x + p->_x_local,
                    T::_y + p->_y_local,
                    T::_z + p->_z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        pElem = pElem->_pNext;
    }
    //表示アイテム初期配置
    pElem = _lstDispActors.getElemFirst();
    int n_da = _lstDispActors.length();
    for (int i = 0; i < n_da; i++) {
        p = pElem->_pValue;
        p->position(T::_x + p->_x_local,
                    T::_y + p->_y_local,
                    T::_z + p->_z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        pElem = pElem->_pNext;
    }

    if (_pCursorActor) {
        _pCursorActor->setAlpha(T::getAlpha());
        _pCursorActor->activate();
    }
    int n_sc = _lstSupCursor.length();
    for (int i = 0; i < n_sc; i++) {
        GgafDxCore::GgafDxDrawableActor* pSupCursorActor = _lstSupCursor.getFromFirst(i)->_pActor;
        pSupCursorActor->setAlpha(T::getAlpha());
        pSupCursorActor->activate();
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
        onRiseDone();
    }
}

template<class T>
void MenuActor<T>::onRiseDone() {
}


template<class T>
void MenuActor<T>::processBehavior() {
    if (_with_sinking) {
        processSinking();
    }
    if (_with_rising) {
        processRising();
    }
    if (_can_controll && T::getActiveFrame() > 2) {
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
        } else if (condSelectExPrev()) {
            selectExPrev();
        } else if (condSelectCancel()) {
            selectCancel();
        }
    }

    if (_pCursorActor) {
        _pCursorActor->getKuroko()->behave();
        //メインカーソル側で、_pKuroko->behave() しないように注意
    }
    int n_sc = _lstSupCursor.length();
    for (int i = 0; i < n_sc; i++) {
        SupCursor* pSupCursor = _lstSupCursor.getFromFirst(i);
        pSupCursor->_pActor->getKuroko()->behave();
        //補助カーソル側で、_pKuroko->behave() しないように注意
    }

    //メニューアイテムをメニューに追従
    GgafDxCore::GgafDxDrawableActor* p;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    int n_i = _lstItems.length();
    for (int i = 0; i < n_i; i++) {
        p = pElem->_pValue;
        p->position(T::_x + p->_x_local,
                    T::_y + p->_y_local,
                    T::_z + p->_z_local);
        if (_with_sinking) {
            if (T::getAlpha() < p->getAlpha()) {
                p->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > p->getAlpha()) {
                p->setAlpha(T::getAlpha());
            }
        }
        pElem = pElem->_pNext;
    }

    //表示アイテムをメニューに追従
    pElem = _lstDispActors.getElemFirst();
    int n_da = _lstDispActors.length();
    for (int i = 0; i < n_da; i++) {
        p = pElem->_pValue;
        p->position(T::_x + p->_x_local,
                    T::_y + p->_y_local,
                    T::_z + p->_z_local);
        if (_with_sinking) {
            if (T::getAlpha() < p->getAlpha()) {
                p->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > p->getAlpha()) {
                p->setAlpha(T::getAlpha());
            }
        }
        pElem = pElem->_pNext;
    }

    //メインカーソルをメニューアイテムに追従
    if (_pCursorActor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursorActor->getKuroko()->asstA()->isSlidingMv()) {
            _pCursorActor->_x += (pTargetItem->_x - _x_cursor_target_prev);
            _pCursorActor->_y += (pTargetItem->_y - _y_cursor_target_prev);
            _pCursorActor->_z += (pTargetItem->_z - _z_cursor_target_prev);
            _x_cursor_target_prev = pTargetItem->_x;
            _y_cursor_target_prev = pTargetItem->_y;
            _z_cursor_target_prev = pTargetItem->_z;
        } else {
            _pCursorActor->position(pTargetItem->_x + _x_cursor_adjust,
                                    pTargetItem->_y + _y_cursor_adjust,
                                    pTargetItem->_z + _z_cursor_adjust );
        }
        if (_with_sinking) {
            if (T::getAlpha() < _pCursorActor->getAlpha()) {
                _pCursorActor->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > _pCursorActor->getAlpha()) {
                _pCursorActor->setAlpha(T::getAlpha());
            }
        }
    }

    //補助カーソルをメニューアイテムに追従
    for (int i = 0; i < n_sc; i++) {
        SupCursor* pSupCursor = _lstSupCursor.getFromFirst(i);
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getFromFirst(pSupCursor->_select_index);
        GgafDxCore::GgafDxDrawableActor* pSupCursorActor = pSupCursor->_pActor;
        if (pSupCursorActor->getKuroko()->asstA()->isSlidingMv()) {
            pSupCursorActor->_x += (pTargetItem->_x - pSupCursor->_x_target_prev);
            pSupCursorActor->_y += (pTargetItem->_y - pSupCursor->_y_target_prev);
            pSupCursorActor->_z += (pTargetItem->_z - pSupCursor->_z_target_prev);
            pSupCursor->_x_target_prev = pTargetItem->_x;
            pSupCursor->_y_target_prev = pTargetItem->_y;
            pSupCursor->_z_target_prev = pTargetItem->_z;
        } else {
            pSupCursorActor->position(pTargetItem->_x + pSupCursor->_x_adjust,
                                      pTargetItem->_y + pSupCursor->_y_adjust,
                                      pTargetItem->_z + pSupCursor->_z_adjust );
        }
        if (_with_sinking) {
            if (T::getAlpha() < pSupCursorActor->getAlpha()) {
                pSupCursorActor->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > pSupCursorActor->getAlpha()) {
                pSupCursorActor->setAlpha(T::getAlpha());
            }
        }
    }

    //サブメニューのriseMe() sinkMe() 時
    int n_sm = _lstSubMenu.length();
    for (int i = 0; i < n_sm; i++) {
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
void MenuActor<T>::sinkMe() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = true;
    disableControll();
    _can_controll = false; //即刻
    if (_velo_alpha_fade >= 1.0) {
        T::setAlpha(0.0);
        T::inactivateTree();
    }
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
        onSinkDone(); //コールバック
    }
}

template<class T>
void MenuActor<T>::onSinkDone() {
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
    _lstSubMenu.current(prm_index)->riseMe();
}

template<class T>
void MenuActor<T>::sinkCurrentSubMenu() {
    _lstSubMenu.getCurrent()->sinkMe();
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
#endif /*GGAFLIB_MENUACTOR_H_*/
