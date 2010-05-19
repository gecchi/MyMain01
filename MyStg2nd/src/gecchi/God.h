#ifndef GOD_H_
#define GOD_H_

namespace MyStg2nd {

#define pGOD ((God*)GgafGod::_pGod)
#define pUNIVERSE ((Universe*)(GgafGod::_pGod->_pUniverse))
#define VB_PLAY God::_pVbtn_PLAY
#define VB_UI God::_pVbtn_UI
#define VB God::_pVbtn_Active

class God : public GgafDx9LibStg::DefaultGod {

public:
    static DispatcherManager _dispatcherManager;

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

    virtual ~God();
};

}

#endif /*GOD_H_*/
