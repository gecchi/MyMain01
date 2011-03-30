#ifndef GOD_H_
#define GOD_H_

namespace MyStg2nd {

/** ゲーム時のVirtualButton */
#define VB_PLAY God::_pVbtn_PLAY
/** UI操作時のVirtualButton */
#define VB_UI God::_pVbtn_UI
/** VB_PLAY or VB_UI のどちらかで、アクティブな方のVirtualButton */
#define VB God::_pVbtn_Active

/**
 * 神
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class God : public GgafDx9LibStg::DefaultGod {

public:
    DispatcherManager* _pDispatcherManager;
    Spline3DManager* _pSpline3DManager;
    SplineManager* _pSplineManager;

    static GgafDx9LibStg::VirtualButton* _pVbtn_PLAY;
    static GgafDx9LibStg::VirtualButton* _pVbtn_UI;
    static GgafDx9LibStg::VirtualButton* _pVbtn_Active;
    static GgafDx9LibStg::VirtualButton* _pVbtn_Active_next_frame;

    God(HINSTANCE prm_hInstance, HWND prm_hWnd);

    /**
     * VBを更新を予約する。 .
     * @param prm_pVB
     */
    void setVB(GgafDx9LibStg::VirtualButton* prm_pVB) {
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
        GgafDx9LibStg::DefaultGod::presentUniversalMoment();
    }

    /**
     * Worldシーンを作成。を実装
     * ＜OverRide です＞
     */
    GgafCore::GgafUniverse* createUniverse() override;
    virtual void clean() override;
    virtual ~God();
};

}

#endif /*GOD_H_*/
