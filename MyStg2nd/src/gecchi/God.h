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

    God(HINSTANCE prm_hInstance, HWND prm_hWnd);

    /**
     * WorldƒV[ƒ“‚ğì¬B‚ğÀ‘•
     * ƒOverRide ‚Å‚·„
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~God();
};

}

#endif /*GOD_H_*/
