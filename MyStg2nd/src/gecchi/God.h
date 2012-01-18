#ifndef GOD_H_
#define GOD_H_

namespace MyStg2nd {

/** ゲーム時のVirtualButton */
#define VB_PLAY MyStg2nd::God::_pVbtn_PLAY
/** UI操作時のVirtualButton */
#define VB_UI MyStg2nd::God::_pVbtn_UI
/** VB_PLAY or VB_UI のどちらかで、アクティブな方のVirtualButton */
#define VB MyStg2nd::God::_pVbtn_Active


//#define connectToDepositoryManager(X) (connectToDepositoryManager(X)))
#define connectToDepositoryManager(X,Y) ((MyStg2nd::DepositoryConnection*)(P_GOD->_pDepoManager->connect((X),(Y))))
#define connectToSplineLineManager(X)   ((MyStg2nd::SplineLineConnection*)(P_GOD->_pSpl3DManager->connect(X)))

/**
 * 神
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class God : public GgafLib::DefaultGod {

public:
    DepositoryManager* _pDepoManager;
    SplineLineManager* _pSpl3DManager;


    static GgafLib::VirtualButton* _pVbtn_PLAY;
    static GgafLib::VirtualButton* _pVbtn_UI;
    static GgafLib::VirtualButton* _pVbtn_Active;
    static GgafLib::VirtualButton* _pVbtn_Active_next_frame;

    /**
     * コンストラクタ .
     * @param prm_hInstance
     * @param prm_pHWndPrimary
     */
    God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * VBを更新を予約する。 .
     * @param prm_pVB
     */
    void setVB(GgafLib::VirtualButton* prm_pVB) {
        if (_pVbtn_Active != prm_pVB) {
            //VBのセットが切り替わる
        }
        _pVbtn_Active_next_frame = prm_pVB;
    }

    /**
     * この世の瞬間を創造する前に、VBを更新する。
     */
    virtual void presentUniversalMoment() override {
        //VBを反映
        _pVbtn_Active = _pVbtn_Active_next_frame;
        //上位呼び出し
        GgafLib::DefaultGod::presentUniversalMoment();
    }

    /**
     * Worldシーンを作成。を実装
     * ＜OverRide です＞
     */
    GgafCore::GgafUniverse* createUniverse() override;
    virtual void clean() override;

    virtual void oops() override;

    virtual ~God();
};

}

#endif /*GOD_H_*/
