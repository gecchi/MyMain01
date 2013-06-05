#ifndef GOD_H_
#define GOD_H_
#include "jp/ggaf/lib/DefaultGod.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryConnection.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineManager.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineConnection.h"

#undef P_GOD
#define P_GOD ((VioletVreath::God*)VioletVreath::God::_pGod)

namespace VioletVreath {

/** ゲーム時のVirtualButton */
#define VB_PLAY VioletVreath::God::pVbtn_PLAY_
/** UI操作時のVirtualButton */
#define VB_UI VioletVreath::God::pVbtn_UI_
/** VB_PLAY or VB_UI のどちらかで、アクティブな方のVirtualButton */
#define VB VioletVreath::God::pVbtn_active_

/** ゲームプレイのリプレイ再生用読み込みファイル */
#define FILE_INPUT_PLAY_REPLAY    "VB_PLAY.rep"
/** UI操作のリプレイ再生用読み込みファイル */
#define FILE_INPUT_UI_REPLAY      "VB_UI.rep"
/** ゲームプレイのリプレイ書き出しファイル */
#define FILE_OUTPUT_PLAY_REPLAY   "VB_PLAY_LAST.rep"
/** UI操作のリプレイ書き出しファイル */
#define FILE_OUTPUT_UI_REPLAY     "VB_UI_LAST.rep"
/** ゲームプレイのリプレイ書き出しファイル（デバッグ用逐次書き出し） */
#define FILE_REALTIME_OUTPUT_PLAY_REPLAY   "VB_PLAY_LAST_REALTIME.rep"
/** UI操作のリプレイ書き出しファイル（デバッグ用逐次書き出し） */
#define FILE_REALTIME_OUTPUT_UI_REPLAY     "VB_UI_LAST_REALTIME.rep"

/**
 * 神が保持する DepositoryManager に接続し、コネクションを取得。
 * X：識別文字列（DepositoryManager::processCreateResource(char* prm_idstr, void* prm_pConnector) の prm_idstr に渡る)
 */
#define connectToDepositoryManager(X) ((VioletVreath::DepositoryConnection*)(P_GOD->pDepoManager_->connect((X), this)))

/**
 * 神が保持する SplineLineManager に接続し、コネクションを取得。
 * X：識別文字列（SplineLineManager::processCreateResource(char* prm_idstr, void* prm_pConnector) の prm_idstr に渡る)
 */
#define connectToSplineLineManager(X)   ((VioletVreath::SplineLineConnection*)(P_GOD->pSpl3DManager_->connect((X), this)))

/**
 * 神
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class God : public GgafLib::DefaultGod {

public:
    DepositoryManager* pDepoManager_;
    SplineLineManager* pSpl3DManager_;

    static GgafLib::VirtualButton* pVbtn_PLAY_;
    static GgafLib::VirtualButton* pVbtn_UI_;
    static GgafLib::VirtualButton* pVbtn_active_;
    static GgafLib::VirtualButton* pVbtn_active_next_frame_;

public:
    /**
     * コンストラクタ .
     * @param prm_hInstance
     * @param prm_pHWndPrimary １画面目HWND
     * @param prm_pHWndSecondary ２画面目HWND
     */
    God();


    void initVB();

    /**
     * VBを更新を予約する。 .
     * @param prm_pVB
     */
    void setVB(GgafLib::VirtualButton* prm_pVB) {
        if (pVbtn_active_ != prm_pVB) {
            //VBのセットが切り替わる
        }
        pVbtn_active_next_frame_ = prm_pVB;
    }

    /**
     * この世の瞬間を創造する前に、VBを更新する。
     */
    virtual void presentUniversalMoment() override {
        //VBを反映
        pVbtn_active_ = pVbtn_active_next_frame_;
        //上位呼び出し
        GgafLib::DefaultGod::presentUniversalMoment();
    }

    /**
     * Worldシーンを作成。を実装
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual void clean() override;

    virtual void oops() override;

    virtual ~God();
};

}

#endif /*GOD_H_*/
