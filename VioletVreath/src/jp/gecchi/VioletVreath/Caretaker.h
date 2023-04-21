#ifndef CARETAKER_H_
#define CARETAKER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/manager/EffectManager.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryConnection.h"
#include "jp/gecchi/VioletVreath/manager/CurveSourceManagerEx.h"
#include "jp/gecchi/VioletVreath/manager/CurveManufactureManagerEx.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#undef pCARETAKER
#define pCARETAKER ((VioletVreath::Caretaker*)GgafCore::Caretaker::ask())

namespace VioletVreath {

/** ゲーム時のVirtualButton */
#define VV_VB_PLAY VioletVreath::Caretaker::pVbtn_PLAY_
/** UI操作時のVirtualButton */
#define VV_VB_UI VioletVreath::Caretaker::pVbtn_UI_
/** VV_VB_PLAY or VV_VB_UI のどちらかで、アクティブな方のVirtualButton */
#define VVB VioletVreath::Caretaker::pVbtn_active_

/** ゲームプレイのリプレイ再生用読み込みファイル */
#define FILE_INPUT_PLAY_REPLAY    "VV_VB_PLAY.rep"
/** UI操作のリプレイ再生用読み込みファイル */
#define FILE_INPUT_UI_REPLAY      "VV_VB_UI.rep"
/** ゲームプレイのリプレイ書き出しファイル */
#define FILE_OUTPUT_PLAY_REPLAY   "VV_VB_PLAY_LAST.rep"
/** UI操作のリプレイ書き出しファイル */
#define FILE_OUTPUT_UI_REPLAY     "VV_VB_UI_LAST.rep"
/** ゲームプレイのリプレイ書き出しファイル（デバッグ用逐次書き出し） */
#define FILE_REALTIME_OUTPUT_PLAY_REPLAY   "VV_VB_PLAY_LAST_REALTIME.rep"
/** UI操作のリプレイ書き出しファイル（デバッグ用逐次書き出し） */
#define FILE_REALTIME_OUTPUT_UI_REPLAY     "VV_VB_UI_LAST_REALTIME.rep"

/**
 * 管理者が保持する DepositoryManager に接続し、コネクションを取得。
 * X：識別文字列（DepositoryManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) の prm_idstr に渡る)
 */
#define connectToDepositoryManager(X) ((VioletVreath::DepositoryConnection*)(pCARETAKER->pDepoManager_->connect((X), this)))

#define connectToXpmManager(X) ((VioletVreath::XpmConnection*)(pCARETAKER->pXpmManager_->connect((X), this)))

#define P1 0
#define P2 1


/**
 * 管理者
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class Caretaker : public GgafLib::DefaultCaretaker {

public:
    DepositoryManager* pDepoManager_;
    XpmManager* pXpmManager_;

    static GgafLib::VirtualButton* pVbtn_PLAY_;
    static GgafLib::VirtualButton* pVbtn_UI_;
    static GgafLib::VirtualButton* pVbtn_active_;
    static GgafLib::VirtualButton* pVbtn_active_next_frame_;
    static bool g_should_reboot_;
public:
    /**
     * コンストラクタ .
     */
    Caretaker();

    void initVB();

    HRESULT initDevice() override;

    /**
     * VBを更新を予約する。 .
     * @param prm_pVVB
     */
    void setVB(GgafLib::VirtualButton* prm_pVVB) {
        if (pVbtn_active_ != prm_pVVB) {
            //VBのセットが切り替わる
        }
        pVbtn_active_next_frame_ = prm_pVVB;
    }

    /**
     * VBを更新する。
     */
    virtual void presentBehave() override {
        //VBを反映
        pVbtn_active_ = pVbtn_active_next_frame_;
        //上位呼び出し
        GgafLib::DefaultCaretaker::presentBehave();
    }

    /**
     * Worldシーンを作成。を実装
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual Spacetime* getSpacetime() override {  //共変の戻り値
        return (Spacetime*)_pSpacetime;
    }

    /**
     * アプリケーション再起動 .
     */
    static void reboot();

    virtual void clean() override;

    virtual void oops() override;

    virtual EffectManager* createEffectManager() override;  //共変の戻り値

    virtual CurveSourceManagerEx* createCurveSourceManager() override;  //共変の戻り値
    virtual CurveManufactureManagerEx* createCurveManufactureManager() override;  //共変の戻り値

    virtual ~Caretaker();
};

}

#endif /*CARETAKER_H_*/
