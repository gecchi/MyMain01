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
     * World�V�[�����쐬�B������
     * ��OverRide �ł���
     */
    GgafCore::GgafUniverse* createUniverse();

    virtual ~God();
};

}
#endif /*GOD_H_*/
