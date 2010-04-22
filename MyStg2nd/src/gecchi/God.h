#ifndef GOD_H_
#define GOD_H_

namespace MyStg2nd {

#define pGOD ((God*)GgafGod::_pGod)
#define pUNIVERSE ((Universe*)(GgafGod::_pGod->_pUniverse))
#define VB_PLAY God::_pVbtn_PLAY
#define VB_UI God::_pVbtn_UI

class God : public GgafDx9LibStg::DefaultGod {

public:
    static DispatcherManager _dispatcherManager;

    static GgafDx9LibStg::VirtualButton* _pVbtn_PLAY;
    static GgafDx9LibStg::VirtualButton* _pVbtn_UI;

    God(HINSTANCE prm_hInstance, HWND prm_hWnd);

    /**
     * Worldシーンを作成。を実装
     * ＜OverRide です＞
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~God();
};

}

#endif /*GOD_H_*/
