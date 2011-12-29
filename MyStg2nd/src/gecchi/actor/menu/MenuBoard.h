#ifndef MENUBOARD_H_
#define MENUBOARD_H_

namespace MyStg2nd {

/**
 * 本アプリの標準メニューボード .
 * @version 1.00
 * @since 2011/12/26
 * @author Masatoshi Tsuge
 */
class MenuBoard : public GgafLib::DefaultBoardMenu {

public:
    enum {
        SE_MENU_OPEN = 0,
        SE_MOVE_CURSOR,
        SE_DECIDED_NOMAL,
        SE_DECIDED_CANCEL,
        SE_MENU_CLOSE,
    };
    coord _menu_fade_frames;
    coord _slide_from_offset_X;
    coord _slide_from_offset_Y;
    coord _target_X;
    coord _target_Y;

    MenuBoard(const char* prm_name, const char* prm_model);

    /**
     * メニュー表示時のスライドトランジションの設定 .
     * @param prm_menu_fade_frames メニューのフェードイン（とフェードアウト）のフレーム数
     * @param prm_slide_from_offset_X メニューのスライド開始の相対X座標
     * @param prm_slide_from_offset_Y メニューのスライド開始の相対X座標
     */
    void setTransition(frame prm_menu_fade_frames,
                       coord prm_slide_from_offset_X, coord prm_slide_from_offset_Y);


    virtual bool condMoveCursorNext() override;
    virtual bool condMoveCursorPrev() override;
    virtual bool condMoveCursorExNext() override;
    virtual bool condMoveCursorExPrev() override;
    virtual bool condMoveCursorCancel() override;
    virtual bool condDecision() override;
    virtual void moveCursor() override;

    virtual void initialize() override;

    /**
     * 表示完了位置を現在の_X, _Yで設定しメニューを起動 .
     */
    virtual void rise() override;

    /**
     * 表示完了位置を指定してメニューを起動 .
     * 引数座標はスライドが完了して落ち着く座標を指定。
     * @param prm_target_X 表示完了X座標
     * @param prm_target_Y 表示完了Y座標
     */
    virtual void rise(coord prm_target_X, coord prm_target_Y);

    /**
     * 表示完了位置を指定してサブメニューを起動 .
     * 引数座標はサブメニューがスライドが完了して落ち着く座標を指定。
     * @param prm_pSubMenu サブメニュー
     * @param prm_target_X 表示完了X座標
     * @param prm_target_Y 表示完了Y座標
     */
    virtual void riseSub(MenuBoard* prm_pSubMenu,
                         coord prm_target_X, coord prm_target_Y);

    virtual void onRisen() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onSunk() override;

    virtual ~MenuBoard();
};

}
#endif /*MENUBOARD_H_*/

