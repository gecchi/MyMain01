#ifndef MENUBOARD_H_
#define MENUBOARD_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/menu/MenuActor.hpp"

namespace VioletVreath {

typedef GgafLib::MenuActor<GgafLib::DefaultFramedBoardActor> DefaultFramedBoardMenu;

/**
 * 本アプリのメニューボード標準実装 .
 * スライドのトランジション実装。
 * キャンセルの実装。
 * @version 1.00
 * @since 2011/12/26
 * @author Masatoshi Tsuge
 */
class MenuBoard : public DefaultFramedBoardMenu {

public:
    enum {
        SE_ON_RISEN      ,
        SE_MOVE_CURSOR   ,
        SE_DECIDED_OK    ,
        SE_DECIDED_CANCEL,
        SE_WRONG         ,
    };

    coord slide_from_offset_x_;
    coord slide_from_offset_y_;
    coord target_x_;
    coord target_y_;

public:
    MenuBoard(const char* prm_name, const char* prm_model);

    /**
     * メニュー表示時のスライドトランジションの設定 .
     * @param prm_menu_fade_frames メニューのフェードイン（とフェードアウト）のフレーム数
     * @param prm_slide_from_offset_x メニューのスライド開始の相対X座標
     * @param prm_slide_from_offset_y メニューのスライド開始の相対X座標
     */
    void setTransition(frame prm_menu_fade_frames,
                       coord prm_slide_from_offset_x, coord prm_slide_from_offset_y);

    virtual bool condDecision() override;
    virtual bool condCancel() override;
    virtual bool condSelectNext() override;
    virtual bool condSelectPrev() override;
    virtual bool condSelectExNext() override;
    virtual bool condSelectExPrev() override;
    virtual bool condSelectCancel() override;
    virtual void moveCursor(bool prm_smooth = true) override;
    virtual void onMoveCursor(int prm_from_index, int prm_selected_index) override;
    virtual void onSelect(int prm_from_index, int prm_selected_index) override;

    virtual void initialize() override;

    /**
     * 表示完了位置を現在の_x, _yで設定しメニュー(自身)を起動 .
     * 通常は他のオブジェクトから呼び出されるメソッドです。
     */
    virtual void riseMe() override;

    /**
     * 表示完了位置を指定してメニュー(自身)を起動 .
     * 引数座標はスライドが完了して落ち着く座標を指定。
     * 通常は他のオブジェクトから呼び出されるメソッドです。
     * @param prm_target_x 表示完了X座標
     * @param prm_target_y 表示完了Y座標
     */
    virtual void rise(coord prm_target_x, coord prm_target_y);

//    /**
//     * 表示完了位置を指定してサブメニューを起動 .
//     * 引数座標はサブメニューがスライドが完了して落ち着く座標を指定。
//     * (※ void MenuActor<T>::riseSubMenu(int prm_index) を隠蔽)
//     * @param prm_index サブメニューインデックス(追加した順番。0～)
//     * @param prm_target_x サブメニュー表示完了X座標
//     * @param prm_target_y サブメニュー表示完了Y座標
//     */
//    virtual void riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y);
//    virtual void riseSubMenu(coord prm_target_x, coord prm_target_y);
    virtual void onRise() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onSink() override;

    virtual void addItem(GgafDx::FigureActor* prm_pItem,
                         coord prm_x_local, coord prm_y_local, coord prm_z_local) override;

    virtual void addItem(GgafDx::FigureActor* prm_pItem,
                         coord prm_x_local, coord prm_y_local) {
        addItem(prm_pItem, prm_x_local, prm_y_local, 0);
    }
    virtual void addItem(GgafDx::FigureActor* prm_pItem) {
        addItem(prm_pItem, 0, 0, 0);
    }

    virtual ~MenuBoard();
};

}
#endif /*MENUBOARD_H_*/

