#ifndef GOD_H_
#define GOD_H_

namespace MyStg2nd {

#define pGOD ((God*)GgafGod::_pGod)
#define pUNIVERSE ((Universe*)(GgafGod::_pGod->_pUniverse))

class God : public GgafDx9LibStg::DefaultGod {

public:
    static DispatcherManager _dispatcherManager;

    God(HINSTANCE prm_hInstance, HWND prm_hWnd);

    /**
     * Worldシーンを作成。を実装
     * ＜OverRide です＞
     */
    GgafCore::GgafUniverse* createUniverse();

    virtual ~God();
};

}

#endif /*GOD_H_*/
