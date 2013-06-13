#ifndef MENUSELECTSUB_H_
#define MENUSELECTSUB_H_
#include "jp/ggaf/lib/actor/menu/MenuActor.hpp"

namespace VioletVreath {

/**
 * 本アプリのメニューボードのセレクト部品 .
 * @version 1.00
 * @since 2013/06/06
 * @author Masatoshi Tsuge
 */
class MenuSelectSub : public GgafLib::StringBoardMenu {

public:
    enum {
        SE_MOVE_CURSOR   ,
    };
    coord target_X_;
    coord target_Y_;

public:
    MenuSelectSub(const char* prm_name, const char* prm_model);


    virtual bool condDecision() override;
    virtual bool condCancel() override;
    virtual bool condSelectNext() override;
    virtual bool condSelectPrev() override;
    virtual bool condSelectExNext() override;
    virtual bool condSelectrExPrev() override;
    virtual bool condSelectCancel() override;
    virtual void moveCursor(bool prm_smooth = true) override;
    virtual void onMoveCursor(int prm_from, int prm_to) override;
    virtual void onSelect(int prm_from, int prm_to) override;

    virtual void initialize() override;

    /**
     * 表示完了位置を現在の_X, _Yで設定しメニュー(自身)を起動 .
     * 通常は他のオブジェクトから呼び出されるメソッドです。
     */
    virtual void riseMe() override;

    /**
     * 表示完了位置を指定してメニュー(自身)を起動 .
     * 引数座標はスライドが完了して落ち着く座標を指定。
     * 通常は他のオブジェクトから呼び出されるメソッドです。
     * @param prm_target_X 表示完了X座標
     * @param prm_target_Y 表示完了Y座標
     */
    virtual void rise(coord prm_target_X, coord prm_target_Y);

    /**
     * 表示完了位置を指定してサブメニューを起動 .
     * 引数座標はサブメニューがスライドが完了して落ち着く座標を指定。
     * (※ void MenuActor<T>::riseSubMenu(int prm_index) を隠蔽)
     * @param prm_index サブメニューインデックス(追加した順番。0～)
     * @param prm_target_X サブメニュー表示完了X座標
     * @param prm_target_Y サブメニュー表示完了Y座標
     */
    virtual void riseSubMenu(int prm_index, coord prm_target_X, coord prm_target_Y);

    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override {
    }
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override {
    }

    virtual void onRise() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onSink() override;

    virtual ~MenuSelectSub();
};

}
#endif /*MENUBOARD_H_*/

