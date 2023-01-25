#ifndef GGAF_LIB_MENUACTOR_H_
#define GGAF_LIB_MENUACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/lib/actor/DefaultFramedBoardActor.h"
#include "jp/ggaf/lib/actor/menu/MenuActor.hpp"
#include "jp/ggaf/lib/actor/FontBoardActor.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"


namespace GgafLib {

/**
 * メニュー .
 * GUI簡易メニューを簡単に実装するためのテンプレートです。<BR>
 * <b>【用語】</b><BR>
 * ・メニューアイテム              … カーソルで選択が可能なオブジェクト（ボタン等のGUI部品）を指します。
 * ・メニューラベル                … カーソルで選択が不可の表示用オブジェクト（ボタン等のGUI部品）を指します。
 * ・キャンセル（メニューアイテム）… 「キャンセル」の動作が期待されるGUI部品の事を指す。（例： [Cancel] や [取り消し] 、[×] ボタン自体）<BR>
 * ・決定（振る舞い）              … ユーザー操作で、メニューアイテムの「決定」の意思を表す操作を指す。（例： [ENTER]キーを押す事）<BR>
 * ・キャンセル（振る舞い）        … ユーザー操作で、メニューアイテムの「キャンセル」の意思を表す操作を指す。（例： [ESC]キー押す事）<BR>
 * 俗に「キャンセルした」と言われる事について、本稿での説明では、<BR>
 * 『「キャンセル（メニューアイテム）」で、「決定（振る舞い） 」した。』<BR>
 * という表現になります。<BR>
 * また、例えば [Yes][No] ボタンがあり、[Yes] ボタンを選択した状態で、ESC入力で[No]ボタンにカーソル選択が移動する場合、<BR>
 *『Yesのメニューアイテムで、「キャンセル（振る舞い）」したので、「キャンセル（メニューアイテム）」にカーソル選択が移動する』
 * という表現になります。<BR>
 * 本クラスは「キャンセル（メニューアイテム）」「決定（振る舞い）」「キャンセル（振る舞い）」を特別扱いし、
 * これらについて機能をサポートします。<BR>
 * （※[OK]ボタン等の「決定（メニューアイテム）」について特別扱いしていません）<BR>
 * @tparam T 母体のメニュー板となるアクターの型
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
    /** メインカーソル移動先メニューアイテムの前フレームのX座標 */
    coord _x_cursor_target_prev;
    /** メインカーソル移動先メニューアイテムの前フレームのY座標 */
    coord _y_cursor_target_prev;
    /** メインカーソル移動先メニューアイテムの前フレームのZ座標 */
    coord _z_cursor_target_prev;
    /** [r]メインカーソルが、メニューアイテム間を移動する際に費やすスフレーム数 */
    int _cursor_move_frames;
    /** [r]メインカーソルが移動時、メニューアイテム間移動距離の速度０～最高速に達する時点の割合 */
    float _cursor_move_p1;
    /** [r]メインカーソルが移動時、メニューアイテム間移動距離の最高速から減速を開始する割合 */
    float _cursor_move_p2;
    /** [r]メインメニューカーソル */
    GgafDx::FigureActor* _pCursorActor;

    /**
     * 補助カーソル .
     */
    class SubCursor {
    public:
        /** [r]補助カーソルアクター */
        GgafDx::FigureActor* _pActor;
        /** 選択中インデックス  */
        int _select_index;
        /** 補助カーソルの補正X座標 */
        coord _x_adjust;
        /** 補助カーソルの補正Y座標 */
        coord _y_adjust;
        /** 補助カーソルの補正Z座標 */
        coord _z_adjust;
        /** 補助カーソル移動先メニューアイテムの前フレームのX座標 */
        coord _x_target_prev;
        /** 補助カーソル移動先メニューアイテムの前フレームのY座標 */
        coord _y_target_prev;
        /** 補助カーソル移動先メニューアイテムの前フレームのZ座標 */
        coord _z_target_prev;
        /** [r]補助カーソルが、メニューアイテム間を移動する際に費やすスフレーム数 */
        int _move_frames;
        /** [r]補助カーソルが移動時、メニューアイテム間移動距離の速度０～最高速に達する時点の割合 */
        float _move_p1;
        /** [r]補助カーソルが移動時、メニューアイテム間移動距離の最高速から減速を開始する割合 */
        float _move_p2;
    public:
        SubCursor() {
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
        virtual ~SubCursor() {
        }
    };

protected:
    /**
     * メインカーソルを選択メニューアイテム(_lstItems のアクティブ要素)へ移動させる .
     * 「選択」と「カーソルの移動」は、別々で考えて下さい。<BR>
     * 本メソッドは予め選択済みのメニューアイテムへ「カーソルの移動」だけであり、視覚効果の処理に特化しています。<BR>
     * 「選択」自体を行うものではありません。「選択」は selectItem() で行います。<BR>
     * また、selectItem() 処理内で、この moveCursor() は実行されます。<BR>
     * 従って、moveCursor() 単体で呼び出す事は殆ど想定してないので注意して下さい。<BR>
     * カーソル移動時の効果音を鳴らす場合等は、オーバーライドして再定義することで実現してください。<BR>
     * その処理中に上位 moveCursor() を呼び出すのを忘れないように。<BR>
     * @param prm_smooth スムーズ移動するか否か
     */
    virtual void moveCursor(bool prm_smooth = true);

    /**
     * 補助カーソルを選択メニューアイテムへ移動させる .
     * 「選択」と「カーソルの移動」は、別々で考えて下さい。<BR>
     * 本メソッドは予め選択済みメニューアイテムへ「カーソルの移動」だけであり、視覚効果の処理に特化しています。<BR>
     * 「選択」自体を行うものではありません。「選択」は selectItemBySubCursor() で行います。<BR>
     * また、selectItemBySubCursor() 処理内で、この moveSubCursor() は実行されます。<BR>
     * 従って、moveCursor() 単体で呼び出す事は殆ど想定してないので注意して下さい。<BR>
     * カーソル移動時の効果音を鳴らす場合等は、オーバーライドして再定義することで実現してください。<BR>
     * その処理中に上位 moveSubCursor() を呼び出すのを忘れないように。<BR>
     * @param prm_subcur_no
     * @param prm_smooth
     */
    virtual void moveSubCursor(int prm_subcur_no, bool prm_smooth = true);

public:
    /** [r]メニューアイテムのリスト、アクティブはメインカーソルが選択されている */
    GgafCore::RingLinkedList<GgafDx::FigureActor> _lstItems;
    /** [r]その他表示メニューアイテムのリスト */
    GgafCore::RingLinkedList<GgafDx::FigureActor> _lstLabelActors;
    /** [r]メインカーソルが移動したメニューアイテムインデックスのヒストリー(0～N、但し初期は全て -1 ) */
    GgafCore::RingLinkedList<int> _lstMvCursorHistory;
    /** [r]選択したメニューアイテムインデックスのヒストリー(0～N、但し初期は全て -1 ) */
    GgafCore::RingLinkedList<int> _lstMvSelectHistory;
    /** [r]メニューフェイドイン・アウト時のフレーム数 */
    frame _fade_frames;
    /** [r]メニューフェイドイン・アウト時のアルファ速度 */
    float _velo_alpha_fade;
    /** [r]サブメニューのリスト */
    GgafCore::RingLinkedList<MenuActor<T> > _lstSubMenu;
    /** [r]サブカーソルのリスト */
    GgafCore::RingLinkedList<SubCursor> _lstSubCursor;

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
     * 選択可能なメニューアイテムを追加し、メニューアイテム間のオーダーも連結追加する .
     * 追加されたメニューアイテムはメニューアイテム(this)の子に登録されるため、
     * メニューアイテムがタスクツリーに登録されるならば delete する必要はない。
     * 【注意】<BR>
     * 同一Z座標ならば、後に addItem() した方が、より手前に表示となる。<BR>
     * @param prm_pItem メニューアイテム
     * @param prm_x_local メニューアイテムのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local メニューアイテムのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_z_local メニューアイテムのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addItem(GgafDx::FigureActor* prm_pItem,
                         coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * 選択可能メニューアイテム追加し、メニューアイテム間のオーダーも連結追加する .
     * 追加されたメニューアイテムはメニューアイテム(this)の子に登録されるため、
     * メニューアイテムがタスクツリーに登録されるならば delete する必要はない。<BR>
     * 【注意】<BR>
     * 同一Z座標ならば、後に addItem() した方が、より手前に表示となる。<BR>
     * Z座標は、オフセット0が設定される。つまりメニューアイテムの絶対Z座標は、現在のメニューのZ座標と一致する。<BR>
     * もしメニューが2Dで、メニューアイテムの表示プライオリティの考慮が必要な場合は、オフセットを-1等に明示設定も可能。
     * @param prm_pItem メニューアイテム
     * @param prm_x_local メニューアイテムのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local メニューアイテムのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void addItem(GgafDx::FigureActor* prm_pItem,
                         coord prm_x_local, coord prm_y_local) {
        addItem(prm_pItem, prm_x_local, prm_y_local, 0);
    }

    /**
     * 選択可能メニューアイテム追加する .
     * 位置は後から setPositionItem() で変更できる。
     * @param prm_pItem メニューアイテム
     */
    virtual void addItem(GgafDx::FigureActor* prm_pItem) {
        addItem(prm_pItem, 0, 0, 0);
    }

    /**
     * 追加された選択可能メニューアイテムの座標位置を設定 .
     * @param prm_index_of_item メニューアイテムのインデックス
     * @param prm_x_local メニューアイテムのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local メニューアイテムのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_z_local メニューアイテムのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void setPositionItem(int prm_index_of_item, coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * 追加されたメニューアイテムの座標位置を設定 .
     * @param prm_index_of_item メニューアイテムのインデックス
     * @param prm_x_local メニューアイテムのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local メニューアイテムのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void setPositionItem(int prm_index_of_item, coord prm_x_local, coord prm_y_local) {
        setPositionItem(prm_index_of_item, prm_x_local, prm_y_local, 0);
    }

    /**
     * 選択不可の表示用メニューラベル(メニューラベル)を追加する .
     * 【注意】<BR>
     * 同一Z座標ならば、より後の順に addLabel() した方が、より手前に表示となる。<BR>
     * @param prm_pItem 表示用メニューラベルのアクター
     * @param prm_x_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_z_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void addLabel(GgafDx::FigureActor* prm_pLabel,
                          coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * 選択不可の表示用メニューラベルを追加する .
     * 【注意】<BR>
     * 同一Z座標ならば、より後の順に addLabel() した方が、より手前に表示となる。<BR>
     * Z座標は、オフセット0が設定される。つまり表示用アクターの絶対Z座標は、現在のメニューのZ座標と一致する。
     * もしメニューが2Dで、メニューアイテムの表示プライオリティの考慮が必要な場合は、オフセットを-1等に明示設定も可能。
     * @param prm_pItem 表示用メニューラベルのアクター
     * @param prm_x_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local 表示用オブジェクトのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void addLabel(GgafDx::FigureActor* prm_pLabel,
                          coord prm_x_local, coord prm_y_local) {
        addLabel(prm_pLabel, prm_x_local, prm_y_local, 0);
    }

    /**
     * 選択不可の表示用メニューラベル追加する .
     * 位置は後から setPositionLabel() で変更できる。
     * @param prm_pLabel 表示用メニューラベルのアクター
     */
    virtual void addLabel(GgafDx::FigureActor* prm_pLabel) {
        addLabel(prm_pLabel, 0, 0, 0);
    }

    /**
     * 追加された選択不可の表示用メニューラベルの座標位置を設定 .
     * @param prm_index_of_label メニューラベルのインデックス
     * @param prm_x_local メニューラベルのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local メニューラベルのローカル座標(0,0,0)からの相対位置Y座標
     * @param prm_z_local メニューラベルのローカル座標(0,0,0)からの相対位置Z座標
     */
    virtual void setPositionLabel(int prm_index_of_label, coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * 追加された選択不可の表示用メニューラベルの座標位置を設定 .
     * @param prm_index_of_label メニューラベルのインデックス
     * @param prm_x_local メニューラベルのローカル座標(0,0,0)からの相対位置X座標
     * @param prm_y_local メニューラベルのローカル座標(0,0,0)からの相対位置Y座標
     */
    virtual void setPositionLabel(int prm_index_of_label, coord prm_x_local, coord prm_y_local) {
        setPositionLabel(prm_index_of_label, prm_x_local, prm_y_local, 0);
    }

    /**
     * メインカーソルオブジェクトを設定する .
     * 【注意】<BR>
     * カーソル移動を制御するため、MenuActor<T>::processBehavior() 内で、<BR>
     * _pCursorActor->getVecVehicle()->behave(); <BR>
     * を実行しています。したがって、引数のカーソルクラスで、<BR>
     * getVecVehicle()->behave(); <BR>
     * を実行する必要はありません。<BR>
     * @param prm_pCursorActor メインカーソル
     * @param prm_x_cursor_adjust メニューアイテムとの重なりを補正するための加算される差分X座標
     * @param prm_y_cursor_adjust メニューアイテムとの重なりを補正するための加算される差分Y座標
     * @param prm_z_cursor_adjust メニューアイテムとの重なりを補正するための加算される差分Z座標
     * @param prm_cursor_move_frames メインカーソルがメニューアイテム間移動に費やすフレーム(デフォルト8フレーム)
     * @param prm_cursor_move_p1 メインカーソルが移動時、メニューアイテム間移動距離の速度０～最高速に達する時点の割合(デフォルト0.2)
     * @param prm_cursor_move_p2 メインカーソルが移動時、メニューアイテム間移動距離の最高速から減速を開始する割合(デフォルト0.6)
     */
    virtual void setMainCursor(GgafDx::FigureActor* prm_pCursorActor,
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
     * _lstSubCursor.getFromFirst(i)->_pActor->getVecVehicle()->behave(); <BR>
     * を実行しています。したがって、引数のカーソルクラスで、<BR>
     * getVecVehicle()->behave(); <BR>
     * を実行する必要はありません。<BR>
     * @param prm_pCursorActor 補助カーソル
     * @param prm_x_cursor_adjust メニューアイテムとの重なりを補正するための加算される差分X座標
     * @param prm_y_cursor_adjust メニューアイテムとの重なりを補正するための加算される差分Y座標
     * @param prm_z_cursor_adjust メニューアイテムとの重なりを補正するための加算される差分Z座標
     * @param prm_cursor_move_frames 補助カーソルがメニューアイテム間移動に費やすフレーム(デフォルト8フレーム)
     * @param prm_cursor_move_p1 補助カーソルが移動時、メニューアイテム間移動距離の速度０～最高速に達する時点の割合(デフォルト0.2)
     * @param prm_cursor_move_p2 補助カーソルが移動時、メニューアイテム間移動距離の最高速から減速を開始する割合(デフォルト0.6)
     */
    virtual void addSubCursor(GgafDx::FigureActor* prm_pCursorActor,
                              coord prm_x_cursor_adjust = 0,
                              coord prm_y_cursor_adjust = 0,
                              coord prm_z_cursor_adjust = 0,
                              int prm_cursor_move_frames = 10,
                              float prm_cursor_move_p1 = 0.2,
                              float prm_cursor_move_p2 = 0.6);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(自身がFrom ⇔ To) .
     * addItem(GgafDx::FigureActor*) により、追加を行うことで、自動的に<BR>
     * 次、前、の線形オーダーが構築されているが、<BR>
     * このメソッドはそれとは別にメニューアイテム間の「次」、「前」、の関係を追加設定する。<BR>
     * 例えば、「→」キーで「次」、「←」キーで「戻る」という動作になっているところに、
     * さらに「↑」「↓」の移動先を別途設定するといった使用方法を想定。<BR>
     * @param prm_index_of_from_item 連結元のメニューアイテムのインデックス
     * @param prm_index_of_to_item 連結元のメニューアイテムのインデックスから
     *                            「次」に対応する連結先のメニューアイテムのインデックス
     */
    virtual void relateItemToExNext(int prm_index_of_from_item, int prm_index_of_to_item);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(item1 ⇔ item2  ⇔ item3) .
     * @param prm_index_of_item1 拡張連結するメニューアイテムのインデックス1
     * @param prm_index_of_item2 拡張連結するメニューアイテムのインデックス2
     * @param prm_index_of_item3 拡張連結するメニューアイテムのインデックス3
     */
    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3 );

    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4 );

    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4,
                                    int prm_index_of_item5 );

    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4,
                                    int prm_index_of_item5,
                                    int prm_index_of_item6 );

//    virtual void relateItemToExNext(int prm_index_of_fromitem, ...);

    /**
     * メニューアイテム間のオーダー連結を拡張設定(From ⇔ 自身がTo) .
     * addItem(GgafDx::FigureActor*) により、追加を行うことで、自動的に<BR>
     * 次、前、の線形オーダーが構築されているが、<BR>
     * このメソッドはそれとは別にメニューアイテム間の「前」、「次」、の関係を追加設定する。<BR>
     * 例えば、「→」キーで「次」、「←」キーで「戻る」という動作にした場合に
     * 「↑」「↓」の移動先を設定するといった使用方法を想定。<BR>
     * @param prm_index_of_fromitem 連結元のメニューアイテムのインデックス
     * @param prm_index_of_toitem 連結元のメニューアイテムのインデックスから
     *                            「前」に対応する連結先のメニューアイテムのインデックス
     */
    virtual void relateItemToExPrev(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * 既存メニューアイテム全てに対し、「キャンセル（メニューアイテム）」へのオーダー連結を拡張設定する .
     * @param prm_index_of_cancel_item キャンセル（メニューアイテム）へのメニューアイテムインデックス
     */
    virtual void relateAllItemToCancel(int prm_index_of_cancel_item);

    /**
     * メニューに設定されているメインカーソルを取得 .
     * @return メインカーソルオブジェクト
     */
    virtual GgafDx::FigureActor* getMainCursor();

    /**
     * メニューに設定されている補助カーソルを取得 .
     * @param prm_subcur_no 補助カーソル番号
     * @return 補助カーソルオブジェクト
     */
    virtual GgafDx::FigureActor* getSubCursor(int prm_subcur_no);

    /**
     * メインカーソルで「次」のメニューアイテム(但しisActive())選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectNext(bool prm_smooth = true);

    /**
     * メインカーソルで「前」のメニューアイテム(但しisActive())選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectPrev(bool prm_smooth = true);

    /**
     * メインカーソルで「（別の）次」のメニューアイテム(但しisActive())選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectExNext(bool prm_smooth = true);

    /**
     * メインカーソルで「（別の）前」のメニューアイテム(但しisActive())選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectExPrev(bool prm_smooth = true);

    /**
     * メインカーソルで「キャンセル」メニューアイテム選択＆メインカーソルを移動 .
     * onSelect() コールバックは必ず発生します。<BR>
     */
    virtual void selectCancel(bool prm_smooth = true);

    /**
     * メインカーソルで指定のインデックスのメニューアイテムを「選択」し、メインカーソルを移動させる .
     * onSelect() コールバックは必ず発生します。<BR>
     * 内部で moveCursor() がコールバックされ、メインカーソルが移動することになる。<BR>
     * 既に指定のインデックス選択中の場合はメインカーソルは何も移動無し。<BR>
     * ついでに、引数インデックスのメニューアイテムオブジェクトもゲット出来る。<BR>
     * @param prm_index ターゲットのメニューアイテムインデックス
     * @return prm_indexのメニューアイテムオブジェクト
     */
    virtual GgafDx::FigureActor* selectItem(int prm_index, bool prm_smooth = true);

    /**
     * 補助カーソルで指定のインデックスのメニューアイテムを「選択」し、補助カーソルを移動させる .
    * onSelect() コールバックは発生しません。<BR>
     * 内部で moveSubCursor() がコールバックされ、メインカーソルが移動することになる。<BR>
     * 既に指定のインデックス選択中の場合はメインカーソルは何も移動無し。<BR>
     * ついでに、引数インデックスのメニューアイテムオブジェクトもゲット出来る。<BR>
     * @param prm_subcur_no 補助カーソル番号
     * @param prm_index ターゲットのメニューアイテムインデックス
     * @return prm_indexのメニューアイテムオブジェクト
     */
    virtual GgafDx::FigureActor* selectItemBySubCursor(int prm_subcur_no, int prm_item_index, bool prm_smooth = true);

    /**
     * メインカーソルで指定のメニューアイテムを「選択」し、メインカーソルを移動させる .
     * 引数のターゲットメニューアイテムのインデックスを調べて、selectItem(index); を実行します。
     * @param prm_item ターゲットメニューアイテム
     * @return ターゲットのメニューアイテムインデックス
     */
    virtual int selectItem(GgafDx::FigureActor* prm_item, bool prm_smooth = true);

    virtual int selectItemIfPossible(GgafDx::FigureActor* prm_item, bool prm_smooth = true);

    /**
     * 補助カーソルで指定のメニューアイテムを「選択」し、補助カーソルを移動させる .
     * 内部で moveSubCursor() がコールバックされ、カーソルが移動することになる。<BR>
     * 既に指定のインデックス選択中の場合はカーソルは何も移動無し。<BR>
     * ついでに、引数メニューアイテムオブジェクトのインデックスもゲット出来る。<BR>
     * @param prm_subcur_no 補助カーソル番号
     * @param prm_item ターゲットのメニューアイテム
     * @return
     */
    virtual int selectItemBySubCursor(int prm_subcur_no, GgafDx::FigureActor* prm_item, bool prm_smooth = true);

    /**
     * 現在メインカーソルが選択中のメニューアイテムのインデックスを取得 .
     * @return 選択中のメニューアイテムのインデックス
     */
    virtual int getSelectedIndex();

    /**
     * 現在補助カーソルが選択中のメニューアイテムのインデックスを取得 .
     * @param prm_subcur_no 補助カーソル番号
     * @return 選択中のメニューアイテムのインデックス
     */
    virtual int getSelectedIndexOnSubCursor(int prm_subcur_no);

    /**
     * 現在メインカーソルが選択中のメニューアイテムのオブジェクトを取得 .
     * @return 選択中のメニューアイテムオブジェクト
     */
    virtual GgafDx::FigureActor* getSelectedItem();

    /**
     * 現在補助カーソルが選択中のメニューアイテムのオブジェクトを取得 .
     * @param prm_subcur_no 補助カーソル番号
     * @return 選択中のメニューアイテムオブジェクト
     */
    virtual GgafDx::FigureActor* getSelectedItemOnSubCursor(int prm_subcur_no);

    /**
     * 過去にメインカーソルが選択中だったメニューアイテムのインデックスを取得 .
     * getMvCursorHistoryIndex(0) は getSelectedIndex() と同じです。
     * 指定の過去がない場合は -1 を返します。
     * @param prm_n 幾つ過去のカーソル位置か(0 ～)
     * @return 選択中だったのメニューアイテムオブジェクトのインデックス（無い場合は -1）
     */
    virtual int getMvCursorHistoryIndex(int prm_n);

    /**
     * 「決定（振る舞い）」が行われた時に、そのメニューアイテムのインデックスを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnDecidedIndex() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return 決定された時：そのメニューアイテムのインデックス(>=0)／何も決定されていない場合：常に -1
     */
    virtual int getOnDecidedIndex();

    /**
     * 「決定（振る舞い）」が行われた時に、そのメニューアイテムを返します .
     * それ以外の時は 常に nullptr を返します<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnDecidedItem() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return 決定された時：そのメニューアイテム／何も決定されていない場合：常に nullptr
     */
    virtual GgafDx::FigureActor* getOnDecidedItem();

    /**
     * 「キャンセル（振る舞い）」が行われた時に、そのメニューアイテムのインデックスを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目がキャンセルされた場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnCancelledIndex() の戻り値を毎フレーム調べることで、キャンセル時の処理を記述することが可能。<BR>
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return キャンセルされた時：そのメニューアイテムのインデックス(>=0)／何もキャンセルされていない場合：常に -1
     */
    virtual int getOnCancelledIndex();

    /**
     * 「キャンセル（振る舞い）」が行われた時に、そのメニューアイテムを返します .
     * それ以外の時は 常に -1 を返します<BR>
     * ＜メニューの選択項目がキャンセルされた場合の処理記述コードの場所について＞<BR>
     * processBehavior() で getOnCancelledItem() の戻り値を毎フレーム調べることで、キャンセル時の処理を記述することが可能。<BR>
     * もちろん onCancel() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。<BR>
     * @return キャンセルされた時：そのメニューアイテム／何もキャンセルされていない場合：常に nullptr
     */
    virtual GgafDx::FigureActor* getOnCancelledItem();

    /**
     * 選択対象メニューアイテムのオブジェクトを取得 .
     * @param prm_index 取得したい選択対象メニューアイテムのインデックス(0～)
     * @return メニューアイテムオブジェクト
     */
    virtual GgafDx::FigureActor* getItem(int prm_index);

    /**
     * 表示用メニューアイテムのオブジェクトを取得 .
     * @param prm_index 取得したい表示用メニューアイテムのインデックス(0～)
     * @return 表示用メニューアイテムオブジェクト
     */
    virtual GgafDx::FigureActor* getLabel(int prm_index);

    /**
     * 「決定（振る舞い）」した、という事の成立条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。 <BR>
     * (例えば Enterキーが押されたらtrueを返す ロジック等) <BR>
     * 同一フレームで condDecision() と condCancel() の条件成立はどちらか一方が成立し、
     * 判定優先順位は、condDecision() の方が先です。<BR>
     * @return true:「決定（振る舞い）」の条件成立 / false:不成立
     */
    virtual bool condDecision() = 0;

    /**
     * 「キャンセル（振る舞い）」した、という事の成立条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。<BR>
     * (例えば ESCキーが押されたらtrueを返す ロジック等) <BR>
     * 同一フレームで condDecision() と condCancel() の条件成立はどちらか一方が成立し、
     * 判定優先順位は、condDecision() の方が先です。<BR>
     * @return true:「キャンセル（振る舞い）」の条件成立 / false:不成立
     */
    virtual bool condCancel() = 0;

    /**
     * メインカーソルが「次のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * (例えば ↓キーが押されたらtrueを返す ロジック等) <BR>
     * @return true:「次のメニューアイテム」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectNext() = 0;

    /**
     * メインカーソルが「前のメニューアイテム」へ移動する条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * (例えば ↑キーが押されたらtrueを返す ロジック等) <BR>
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
     * メインカーソルが「キャンセル（メニューアイテム）」へ飛ぶ条件を実装する .
     * 下位クラスでオーバーライドして、条件を実装してください。
     * @return true:「キャンセル（メニューアイテム）」へ移動の条件成立 / false:不成立
     */
    virtual bool condSelectCancel() = 0;

    /**
     * 特定の「メニューアイテム」が選択される条件を実装する .
     * マウスポインタで指す、ショートカッキーを押下などで、
     * 特定の条件でメニューアイテムを選択したい場合、ここに実装する。
     * @return 選択されたメニューアイテム。 nullptr の場合は、メニューアイテム選択は実行されない。・
     */
    virtual GgafDx::FigureActor* condSelectItem() {
        return nullptr;
    }


    /**
     * 「決定（振る舞い）」された場合に呼び出されるコールバック。
     * 動作をオーバーライドして実装してください。<BR>
     * ＜メニューの選択項目が決定された場合の処理記述コードの場所について＞<BR>
     * processBehavior() で、getOnDecidedIndex() の戻り値を毎フレーム調べることで、決定時の処理を記述することが可能。<BR>
     * もちろん onDecision() も呼び出されるので、オーバーライドし、ここで swith～case を記述しても良い。<BR>
     * どちらでも良いし、併用も可能。
     * @param prm_pItem 決定されたメニューアイテム
     * @param prm_item_index 決定されたメニューアイテムのインデックス
     */
    virtual void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) = 0;

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
    virtual void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) = 0;

    /**
     * メインカーソルが移動した場合に呼び出されるコールバック。 .
     * 動作をオーバーライドして実装してください。<BR>
     * 【捕捉】<BR>
     * onMoveCursor(int,int) と onSelect(int,int) のコールバックタイミングの差について。<BR>
     * onMoveCursor(int,int) は、selectXxxxx 系のメソッド実行の際、カーソルが移動した場合のみ呼び出されます。<BR>
     * onSelect(int,int) は、selectXxxxx 系 のメソッドを実行時に、もれなく呼び出されます(たとえ、カーソルが移動しなくても)<BR>
     * 呼び出される順序は、onMoveCursor(int,int)  → onSelect(int,int) の順です。<BR>
     * @param prm_from_index 移動元のメニューアイテムのインデックス（無い（初期の）場合は -1）
     * @param prm_selected_index   移動先のメニューアイテムのインデックス
     */
    virtual void onMoveCursor(int prm_from_index, int prm_selected_index) = 0;

    /**
     * メインカーソルがメニューアイテムを選択された場合に呼び出されるコールバック。 .
     * 動作をオーバーライドして実装してください。<BR>
     * 【捕捉】<BR>
     * onMoveCursor(int,int) と onSelect(int,int) のコールバックタイミングの差について。<BR>
     * onMoveCursor(int,int) は、selectXxxxx 系のメソッド実行の際、カーソルが移動した場合のみ呼び出されます。<BR>
     * onSelect(int,int) は、selectXxxxx 系 のメソッドを実行時に、もれなく呼び出されます(たとえ、カーソルが移動しなくても)<BR>
     * 呼び出される順序は、onMoveCursor(int,int)  → onSelect(int,int) の順です。<BR>
     * @param prm_from_index     選択元（今回選択される前）のメニューアイテムのインデックス（無い（初期の）場合は -1）
     * @param prm_selected_index 選択先のメニューアイテムのインデックス
     */
    virtual void onSelect(int prm_from_index, int prm_selected_index) = 0;


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
     * riseMe() 実行 ～ フェードイン完了までの間コールされ続けます。
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
     * 内部で T::processNextFrame(); もコールしています。
     */
    virtual void processNextFrame() override;

    /**
     * メニューの振る舞い .
     * カーソルの移動及び、メニューアイテムとカーソルをメニューの母体座標に追従させる
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
    virtual bool hasJustRisen() {
        return _is_just_risen;
    }

    /**
     * sinkMe() が実行された直後か否かを返す .
     * @return true:今丁度 sinkMe() が実行された直後である/false:そうではない
     */
    virtual bool hasJustSunk() {
        return _is_just_sunk;
    }

    /**
     * 「決定（振る舞い）」が行われた直後か否かを返す .
     * @return rue:今丁度 「決定（振る舞い）」 が実行された直後である/false:そうではない
     */
    virtual bool hasJustDecided() {
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
    virtual bool hasJustCancelled() {
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
     * sinkMe() 実行 ～ フェードアウト完了までの間コールされ続けます。
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
    virtual MenuActor<T>* getSubMenu(int prm_index = 0);

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
     * @param prm_index アクティブにするサブメニューのインデックス(追加した順番。0～)
     */
    virtual void riseSubMenu(int prm_index = 0);

    /**
     * 表示完了位置を指定してサブメニューを起動 .
     * 引数座標はサブメニューがスライドが完了して落ち着く座標を指定。
     * @param prm_index サブメニューインデックス(追加した順番。0～)
     * @param prm_target_x サブメニュー表示完了X座標
     * @param prm_target_y サブメニュー表示完了Y座標
     */
    virtual void riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y);

    /**
     * 現在アクティブなサブメニューを閉じて終了させる .
     * 事前に addSubMenu() でサブメニューを設定する必要があります。<BR>
     */
    virtual void sinkCurrentSubMenu();

    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model),_lstItems(3) { //全メニューアイテム枝を３つ追加：「その他次」「その他前」「キャンセル」の３つ
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
    _lstMvCursorHistory.createIndex();
    _lstMvSelectHistory.createIndex();
    T::inactivate(); //メニューなので、初期状態は非活動状態をデフォルトとする
}

template<class T>
void MenuActor<T>::processNextFrame() {
    T::processNextFrame();
    if (T::_can_live_flg) {
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
}

template<class T>
void MenuActor<T>::addItem(GgafDx::FigureActor* prm_pItem,
                           coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    prm_pItem->_x_local = prm_x_local;
    prm_pItem->_y_local = prm_y_local;
    prm_pItem->_z_local = prm_z_local;
    prm_pItem->setAlpha(T::_alpha); //半透明αを共有させる。
    prm_pItem->inactivate();
    _lstItems.addLast(prm_pItem, false);
//    T::appendChild(prm_pItem);
    T::appendGroupChild(prm_pItem);

}

template<class T>
void MenuActor<T>::setPositionItem(int prm_index_of_item, coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    GgafDx::FigureActor* p = getItem(prm_index_of_item);
    p->_x_local = prm_x_local;
    p->_y_local = prm_y_local;
    p->_z_local = prm_z_local;
}

template<class T>
void MenuActor<T>::addLabel(GgafDx::FigureActor* prm_pLabel,
                           coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    prm_pLabel->_x_local = prm_x_local;
    prm_pLabel->_y_local = prm_y_local;
    prm_pLabel->_z_local = prm_z_local;
    prm_pLabel->setAlpha(T::_alpha); //半透明αを共有させる。
    prm_pLabel->inactivate();
    _lstLabelActors.addLast(prm_pLabel, false);
    T::appendChild(prm_pLabel);
}

template<class T>
void MenuActor<T>::setPositionLabel(int prm_index_of_label, coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    GgafDx::FigureActor* p = getLabel(prm_index_of_label);
    p->_x_local = prm_x_local;
    p->_y_local = prm_y_local;
    p->_z_local = prm_z_local;
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_from_item, int prm_index_of_to_item) {
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElemFrom =
            _lstItems.getElemFromFirst(prm_index_of_from_item);
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElemTo =
            _lstItems.getElemFromFirst(prm_index_of_to_item);
    pElemFrom->connect(ITEM_RELATION_EX_NEXT, pElemTo);
    pElemTo->connect(ITEM_RELATION_EX_PREV, pElemFrom);
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3 ) {
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem1 =
            _lstItems.getElemFromFirst(prm_index_of_item1);
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem2 =
            _lstItems.getElemFromFirst(prm_index_of_item2);
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem3 =
            _lstItems.getElemFromFirst(prm_index_of_item3);
    pElem1->connect(ITEM_RELATION_EX_NEXT, pElem2);
    pElem2->connect(ITEM_RELATION_EX_NEXT, pElem3);
    pElem3->connect(ITEM_RELATION_EX_PREV, pElem2);
    pElem2->connect(ITEM_RELATION_EX_PREV, pElem1);
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
    relateItemToExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3);
    relateItemToExNext(prm_index_of_item3, prm_index_of_item4, prm_index_of_item5);
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3,
                                      int prm_index_of_item4,
                                      int prm_index_of_item5,
                                      int prm_index_of_item6 ) {
    relateItemToExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3);
    relateItemToExNext(prm_index_of_item3, prm_index_of_item4, prm_index_of_item5);
    relateItemToExNext(prm_index_of_item5, prm_index_of_item6);
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
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pCancelElem =
            _lstItems.getElemFromFirst(prm_index_of_cancel_item);
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem =
            _lstItems.getElemFirst();
    int n = _lstItems.length();
    for (int i = 0; i < n; i++) {
        pElem->connect(ITEM_RELATION_TO_CANCEL, pCancelElem);
        pElem = pElem->_pNext;
    }
}


template<class T>
GgafDx::FigureActor* MenuActor<T>::selectItem(int prm_index, bool prm_smooth) {
    int n = getSelectedIndex();
#ifdef MY_DEBUG
    if (n == -1) {
        throwCriticalException("MenuActor<T>::selectItem() メニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
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
            throwCriticalException("MenuActor<T>::selectItem() メニューアイテム要素数オーバー name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
        }
#endif
        GgafDx::FigureActor* pTargetItem = _lstItems.current(prm_index); //これでセレクト！
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
GgafDx::FigureActor* MenuActor<T>::selectItemBySubCursor(int prm_subcur_no, int prm_item_index, bool prm_smooth) {
    int n = getSelectedIndexOnSubCursor(prm_subcur_no);
#ifdef MY_DEBUG
    if (n == -1) {
        throwCriticalException("MenuActor<T>::selectItemBySubCursor() メニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item_index="<<prm_item_index);
    }
#endif
    //補助カーソルはコールバックなし
    if (n == prm_item_index) {
        //既に選択している。
        return _lstItems.getFromFirst(n);
    } else {
#ifdef MY_DEBUG
        if (_lstItems.length() <= prm_item_index) {
            throwCriticalException("MenuActor<T>::selectItemBySubCursor() メニューアイテム要素数オーバー name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item_index="<<prm_item_index);
        }
#endif
        _lstSubCursor.getFromFirst(prm_subcur_no)->_select_index = prm_item_index; //これでセレクト！
        GgafDx::FigureActor* pTargetItem = _lstItems.getFromFirst(prm_item_index);

        if (T::getActiveFrame() > 1) {
            moveSubCursor(prm_subcur_no, prm_smooth);  //スムーズ移動は引数依存
        } else {
            moveSubCursor(prm_subcur_no, false); //スムーズ移動無し(初期選択の為のselectItem)
        }
        return pTargetItem;
    }
}

template<class T>
int MenuActor<T>::selectItem(GgafDx::FigureActor* prm_item, bool prm_smooth) {
    int index = _lstItems.indexOf(prm_item);
    if (index == -1) {
        throwCriticalException("MenuActor<T>::selectItem() その前にメニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item="<<prm_item->getName());
    }
    selectItem(index, prm_smooth);
    return index;
}

template<class T>
int MenuActor<T>::selectItemIfPossible(GgafDx::FigureActor* prm_item, bool prm_smooth) {
    int index = _lstItems.indexOf(prm_item);
    if (index >= 0) {
        selectItem(index, prm_smooth);
    }
    return index;
}

template<class T>
int MenuActor<T>::selectItemBySubCursor(int prm_subcur_no, GgafDx::FigureActor* prm_item, bool prm_smooth) {
    int index = _lstItems.indexOf(prm_item);
    if (index == -1) {
        throwCriticalException("MenuActor<T>::selectItemBySubCursor() その前にメニューアイテムが未登録です name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item="<<prm_item->getName());
    }
    selectItemBySubCursor(index, prm_subcur_no, prm_smooth);
    return index;
}

template<class T>
void MenuActor<T>::setMainCursor(GgafDx::FigureActor* prm_pCursorActor,
                                 coord prm_x_cursor_adjust,
                                 coord prm_y_cursor_adjust,
                                 coord prm_z_cursor_adjust,
                                 int prm_cursor_move_frames,
                                 float prm_cursor_move_p1,
                                 float prm_cursor_move_p2) {
    _pCursorActor = prm_pCursorActor;
    _pCursorActor->setAlpha(T::_alpha);
    _pCursorActor->inactivate();
    T::appendChild(_pCursorActor);
    _x_cursor_adjust = prm_x_cursor_adjust;
    _y_cursor_adjust = prm_y_cursor_adjust;
    _z_cursor_adjust = prm_z_cursor_adjust;
    _cursor_move_frames = prm_cursor_move_frames;
    _cursor_move_p1 = prm_cursor_move_p1;
    _cursor_move_p2 = prm_cursor_move_p2;
    selectItem(0);
}

template<class T>
void MenuActor<T>::addSubCursor(GgafDx::FigureActor* prm_pCursorActor,
                                 coord prm_x_cursor_adjust,
                                 coord prm_y_cursor_adjust,
                                 coord prm_z_cursor_adjust,
                                 int prm_cursor_move_frames,
                                 float prm_cursor_move_p1,
                                 float prm_cursor_move_p2) {
    MenuActor<T>::SubCursor* pSubCursor = NEW MenuActor<T>::SubCursor();
    pSubCursor->_pActor = prm_pCursorActor;
    pSubCursor->_pActor->setAlpha(T::_alpha);
    pSubCursor->_pActor->inactivate();
    pSubCursor->_select_index = 0;
    pSubCursor->_x_adjust = prm_x_cursor_adjust;
    pSubCursor->_y_adjust = prm_y_cursor_adjust;
    pSubCursor->_z_adjust = prm_z_cursor_adjust;
    pSubCursor->_move_frames = prm_cursor_move_frames;
    pSubCursor->_move_p1 = prm_cursor_move_p1;
    pSubCursor->_move_p2 = prm_cursor_move_p2;
    _lstSubCursor.addLast(pSubCursor, true);
    T::appendChild(pSubCursor->_pActor);
    selectItemBySubCursor(0, _lstSubCursor.length()-1);
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getMainCursor() {
    return _pCursorActor;
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getSubCursor(int prm_subcur_no) {
    return _lstSubCursor.getFromFirst(prm_subcur_no)->_pActor;
}

template<class T>
int MenuActor<T>::getSelectedIndex() {
    return _lstItems.getCurrentIndex();
}

template<class T>
int MenuActor<T>::getSelectedIndexOnSubCursor(int prm_subcur_no) {
    return _lstSubCursor.getFromFirst(prm_subcur_no)->_select_index;
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getSelectedItemOnSubCursor(int prm_subcur_no) {
    return _lstItems.getFromFirst(getSelectedIndexOnSubCursor(prm_subcur_no));
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
GgafDx::FigureActor* MenuActor<T>::getOnDecidedItem() {
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
GgafDx::FigureActor* MenuActor<T>::getOnCancelledItem() {
    if (_is_just_cancelled) {
        return _lstItems.getCurrent();
    } else {
        return nullptr;
    }
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getItem(int prm_index) {
#ifdef MY_DEBUG
    if (_lstItems.length() <= prm_index) {
        throwCriticalException("MenuActor<T>::getItem() メニューアイテム要素数オーバー name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstItems.getFromFirst(prm_index);
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getLabel(int prm_index) {
#ifdef MY_DEBUG
    if (_lstLabelActors.length() <= prm_index) {
        throwCriticalException("MenuActor<T>::getLabel() 表示メニューラベルメニューアイテム要素数オーバー name="<<T::getName()<<" _lstLabelActors.length()="<<_lstLabelActors.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstLabelActors.getFromFirst(prm_index);
}


template<class T>
void MenuActor<T>::selectNext(bool prm_smooth) {
    GgafDx::FigureActor* pCurrent = _lstItems.getCurrent();
    if (_pCursorActor) {
        _pCursorActor->setPositionAt(pCurrent);
    }
    GgafDx::FigureActor* pNext;
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
    moveCursor(prm_smooth);
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectPrev(bool prm_smooth) {
    GgafDx::FigureActor* pCurrent = _lstItems.getCurrent();
    if (_pCursorActor) {
        _pCursorActor->setPositionAt(pCurrent);
    }
    GgafDx::FigureActor* pPrev;
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
    moveCursor(prm_smooth);
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectExNext(bool prm_smooth) {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        GgafDx::FigureActor* pCurrent = _lstItems.getCurrent();
        if (_pCursorActor) {
            _pCursorActor->setPositionAt(pCurrent);
        }
        GgafDx::FigureActor* pRelation;
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
        moveCursor(prm_smooth);
    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectExPrev(bool prm_smooth) {
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        GgafDx::FigureActor* pCurrent = _lstItems.getCurrent();
        if (_pCursorActor) {
            _pCursorActor->setPositionAt(pCurrent);
        }
        GgafDx::FigureActor* pRelation;
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
        moveCursor(prm_smooth);
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::selectCancel(bool prm_smooth) {
    if (_lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        if (_pCursorActor) {
            _pCursorActor->setPositionAt(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_TO_CANCEL);
        moveCursor(prm_smooth);
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //コールバック
}

template<class T>
void MenuActor<T>::moveCursor(bool prm_smooth) {
    if (_pCursorActor) {
        GgafDx::FigureActor* pTargetItem = _lstItems.getCurrent();
        GgafDx::VecVehicle* pCursorVecVehicle = _pCursorActor->getVecVehicle();
        if (prm_smooth) {
            pCursorVecVehicle->setMvAngTwd(
                                    pTargetItem->_x + _x_cursor_adjust,
                                    pTargetItem->_y + _y_cursor_adjust,
                                    pTargetItem->_z + _z_cursor_adjust
                              );
            pCursorVecVehicle->stop();
            pCursorVecVehicle->asstMv()->slideByDt(
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
            pCursorVecVehicle->asstMv()->stopSliding();
            pCursorVecVehicle->stop();
            _pCursorActor->_x = pTargetItem->_x + _x_cursor_adjust;
            _pCursorActor->_y = pTargetItem->_y + _y_cursor_adjust;
            _pCursorActor->_z = pTargetItem->_z + _z_cursor_adjust;
        }
        *(_lstMvCursorHistory.next()) = _lstItems.getCurrentIndex();
        onMoveCursor(*(_lstMvCursorHistory.getPrev()), *(_lstMvCursorHistory.getCurrent())); //コールバック
    }
}


template<class T>
void MenuActor<T>::moveSubCursor(int prm_subcur_no, bool prm_smooth) {
    if (_lstSubCursor.length() > 0) {
        GgafDx::FigureActor* pTargetItem = getSelectedItemOnSubCursor(prm_subcur_no);
        SubCursor* pSubCursor = _lstSubCursor.getFromFirst(prm_subcur_no);
        GgafDx::FigureActor* pSubCursorActor = pSubCursor->_pActor;
        GgafDx::VecVehicle* pSubCursorVecVehicle = pSubCursorActor->getVecVehicle();
        if (prm_smooth) {
            pSubCursorVecVehicle->setMvAngTwd(
                                     pTargetItem->_x + pSubCursor->_x_adjust,
                                     pTargetItem->_y + pSubCursor->_y_adjust,
                                     pTargetItem->_z + pSubCursor->_z_adjust
                                 );
            pSubCursorVecVehicle->stop();
            pSubCursorVecVehicle->asstMv()->slideByDt(
                                      UTIL::getDistance(pSubCursorActor->_x,
                                                        pSubCursorActor->_y,
                                                        pSubCursorActor->_z,
                                                        pTargetItem->_x + pSubCursor->_x_adjust,
                                                        pTargetItem->_y + pSubCursor->_y_adjust,
                                                        pTargetItem->_z + pSubCursor->_z_adjust ),
                                      pSubCursor->_move_frames,
                                      pSubCursor->_move_p1, pSubCursor->_move_p2, 0 , true
                                    );
            pSubCursor->_x_target_prev = pTargetItem->_x;
            pSubCursor->_y_target_prev = pTargetItem->_y;
            pSubCursor->_z_target_prev = pTargetItem->_z;
        } else {
            pSubCursorVecVehicle->asstMv()->stopSliding();
            pSubCursorVecVehicle->stop();
            pSubCursorActor->_x = pTargetItem->_x + pSubCursor->_x_adjust;
            pSubCursorActor->_y = pTargetItem->_y + pSubCursor->_y_adjust;
            pSubCursorActor->_z = pTargetItem->_z + pSubCursor->_z_adjust;
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
    GgafDx::FigureActor* p;
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem = _lstItems.getElemFirst();
    int n_i = _lstItems.length();
    for (int i = 0; i < n_i; i++) {
        p = pElem->getValue();
        p->setPosition(T::_x + p->_x_local,
                       T::_y + p->_y_local,
                       T::_z + p->_z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        GgafCore::GroupHead* pH = p->getGroupHead(); //Itemの間には団長が存在する
        if (pH) {
            pH->activate();
        }
        pElem = pElem->_pNext;
    }
    //表示メニューアイテム初期配置
    pElem = _lstLabelActors.getElemFirst();
    int n_da = _lstLabelActors.length();
    for (int i = 0; i < n_da; i++) {
        p = pElem->getValue();
        p->setPosition(T::_x + p->_x_local,
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
    int n_sc = _lstSubCursor.length();
    for (int i = 0; i < n_sc; i++) {
        GgafDx::FigureActor* pSubCursorActor = _lstSubCursor.getFromFirst(i)->_pActor;
        pSubCursorActor->setAlpha(T::getAlpha());
        pSubCursorActor->activate();
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
    frame active_frames = T::getActiveFrame();
    if (active_frames == 1) {
        onSelect(-1, *(_lstMvSelectHistory.getCurrent())); //コールバック
    }
    if (_can_controll && active_frames > 1) {
        GgafDx::FigureActor* pSelected = condSelectItem();
        if (pSelected) {
            selectItemIfPossible(pSelected);
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
        if (condDecision()) {
            _will_be_just_decided_next_frame = true;
        } else if (condCancel()) {
            _will_be_just_cancelled_next_frame = true;
        }

    }

    if (_pCursorActor) {
        _pCursorActor->getVecVehicle()->behave();
        //メインカーソル側で、_pVecVehicle->behave() しないように注意
    }
    int n_sc = _lstSubCursor.length();
    for (int i = 0; i < n_sc; i++) {
        SubCursor* pSubCursor = _lstSubCursor.getFromFirst(i);
        pSubCursor->_pActor->getVecVehicle()->behave();
        //補助カーソル側で、_pVecVehicle->behave() しないように注意
    }

    //メニューアイテムをメニューに追従
    GgafDx::FigureActor* p;
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem = _lstItems.getElemFirst();
    int n_i = _lstItems.length();
    for (int i = 0; i < n_i; i++) {
        p = pElem->getValue();
        p->setPosition(T::_x + p->_x_local,
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

    //表示メニューアイテムをメニューに追従
    pElem = _lstLabelActors.getElemFirst();
    int n_da = _lstLabelActors.length();
    for (int i = 0; i < n_da; i++) {
        p = pElem->getValue();
        p->setPosition(T::_x + p->_x_local,
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
        GgafDx::FigureActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursorActor->getVecVehicle()->asstMv()->isSliding()) {
            _pCursorActor->_x += (pTargetItem->_x - _x_cursor_target_prev);
            _pCursorActor->_y += (pTargetItem->_y - _y_cursor_target_prev);
            _pCursorActor->_z += (pTargetItem->_z - _z_cursor_target_prev);
            _x_cursor_target_prev = pTargetItem->_x;
            _y_cursor_target_prev = pTargetItem->_y;
            _z_cursor_target_prev = pTargetItem->_z;
        } else {
            _pCursorActor->setPosition(pTargetItem->_x + _x_cursor_adjust,
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
        SubCursor* pSubCursor = _lstSubCursor.getFromFirst(i);
        GgafDx::FigureActor* pTargetItem = _lstItems.getFromFirst(pSubCursor->_select_index);
        GgafDx::FigureActor* pSubCursorActor = pSubCursor->_pActor;
        if (pSubCursorActor->getVecVehicle()->asstMv()->isSliding()) {
            pSubCursorActor->_x += (pTargetItem->_x - pSubCursor->_x_target_prev);
            pSubCursorActor->_y += (pTargetItem->_y - pSubCursor->_y_target_prev);
            pSubCursorActor->_z += (pTargetItem->_z - pSubCursor->_z_target_prev);
            pSubCursor->_x_target_prev = pTargetItem->_x;
            pSubCursor->_y_target_prev = pTargetItem->_y;
            pSubCursor->_z_target_prev = pTargetItem->_z;
        } else {
            pSubCursorActor->setPosition(pTargetItem->_x + pSubCursor->_x_adjust,
                                         pTargetItem->_y + pSubCursor->_y_adjust,
                                         pTargetItem->_z + pSubCursor->_z_adjust );
        }
        if (_with_sinking) {
            if (T::getAlpha() < pSubCursorActor->getAlpha()) {
                pSubCursorActor->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > pSubCursorActor->getAlpha()) {
                pSubCursorActor->setAlpha(T::getAlpha());
            }
        }
    }

    //サブメニューのriseMe() sinkMe() 時
    int n_sm = _lstSubMenu.length();
    for (int i = 0; i < n_sm; i++) {
        MenuActor<T>* pSubMenu = _lstSubMenu.getFromFirst(i);
        if (pSubMenu->hasJustRisen()) {
            disableControll(); //サブメニューが立ち上がったので、自身は操作不可
            _can_controll = false; //即刻
        }
        if (pSubMenu->hasJustSunk()) {
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
    T::appendChild(prm_pSubMenu); //子に追加
}

template<class T>
MenuActor<T>* MenuActor<T>::getParentMenu() {
    GgafCore::Actor* pActor = T::getParent(); //子に追加
#ifdef MY_DEBUG
    MenuActor<T>* pMenuActor = dynamic_cast<MenuActor<T>*>(pActor);
    if (pMenuActor == nullptr) {
        throwCriticalException("MenuActor<T>::getParentMenu 親ノードは同じメニューではありませんでした。name="<<T::getName()<<" this="<<this);
    }
#endif
    return (MenuActor<T>*)pActor;
}

template<class T>
MenuActor<T>* MenuActor<T>::getSubMenu(int prm_index) {
#ifdef MY_DEBUG
    if (_lstSubMenu.length() < prm_index+1) {
        throwCriticalException("MenuActor<T>::getSubMenu() サブメニューアイテム要素数オーバー name="<<T::getName()<<" _lstSubMenu.length()="<<_lstSubMenu.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstSubMenu.getFromFirst(prm_index);
}

template<class T>
MenuActor<T>* MenuActor<T>::getRisingSubMenu() {
    MenuActor<T>* pSubMenu = _lstSubMenu.getCurrent();
    if (pSubMenu) {
        if (pSubMenu->isActiveInTheTree()) {
            return pSubMenu;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}


template<class T>
void MenuActor<T>::riseSubMenu(int prm_index) {
#ifdef MY_DEBUG
    if (_lstSubMenu.length() < prm_index+1) {
        throwCriticalException("MenuActor<T>::riseSubMenu() サブメニューアイテム要素数オーバー name="<<T::getName()<<" _lstSubMenu.length()="<<_lstSubMenu.length()<<" prm_index="<<prm_index);
    }
#endif
    MenuActor<T>* pSubMenu = getSubMenu(prm_index);
    pSubMenu->riseMe();
}

template<class T>
void MenuActor<T>::riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y) {
    getSubMenu(prm_index)->setPosition(prm_target_x, prm_target_y); //←によりvoid MenuBoard::riseMe() に来た時にターゲット設定される
    riseSubMenu(prm_index);
}


template<class T>
void MenuActor<T>::sinkCurrentSubMenu() {
    _lstSubMenu.getCurrent()->sinkMe();
}

template<class T>
MenuActor<T>::~MenuActor() {
}

}
#endif /*GGAF_LIB_MENUACTOR_H_*/
