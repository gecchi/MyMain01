#ifndef GOD_H_
#define GOD_H_

namespace VioletVreath {

/** ゲーム時のVirtualButton */
#define VB_PLAY VioletVreath::God::pVbtn_PLAY_
/** UI操作時のVirtualButton */
#define VB_UI VioletVreath::God::pVbtn_UI_
/** VB_PLAY or VB_UI のどちらかで、アクティブな方のVirtualButton */
#define VB VioletVreath::God::pVbtn_Active_


//#define connectToDepositoryManager(X) (connectToDepositoryManager(X)))
#define connectToDepositoryManager(X,Y) ((VioletVreath::DepositoryConnection*)(P_GOD->pDepoManager_->connect((X),(Y))))
#define connectToSplineLineManager(X)   ((VioletVreath::SplineLineConnection*)(P_GOD->pSpl3DManager_->connect(X)))

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
    static GgafLib::VirtualButton* pVbtn_Active_;
    static GgafLib::VirtualButton* pVbtn_Active_next_frame_;

    /**
     * コンストラクタ .
     * @param prm_hInstance
     * @param prm_pHWndPrimary １画面目HWND
     * @param prm_pHWndSecondary ２画面目HWND
     */
    God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * VBを更新を予約する。 .
     * @param prm_pVB
     */
    void setVB(GgafLib::VirtualButton* prm_pVB) {
        if (pVbtn_Active_ != prm_pVB) {
            //VBのセットが切り替わる
        }
        pVbtn_Active_next_frame_ = prm_pVB;
    }

    /**
     * この世の瞬間を創造する前に、VBを更新する。
     */
    virtual void presentUniversalMoment() override {
        //VBを反映
        pVbtn_Active_ = pVbtn_Active_next_frame_;
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
