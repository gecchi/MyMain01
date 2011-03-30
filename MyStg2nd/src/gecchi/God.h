#ifndef GOD_H_
#define GOD_H_

namespace MyStg2nd {

/** �Q�[������VirtualButton */
#define VB_PLAY God::_pVbtn_PLAY
/** UI���쎞��VirtualButton */
#define VB_UI God::_pVbtn_UI
/** VB_PLAY or VB_UI �̂ǂ��炩�ŁA�A�N�e�B�u�ȕ���VirtualButton */
#define VB God::_pVbtn_Active

/**
 * �_
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
     * VB���X�V��\�񂷂�B .
     * @param prm_pVB
     */
    void setVB(GgafDx9LibStg::VirtualButton* prm_pVB) {
        if (_pVbtn_Active != prm_pVB) {
            //VB�̃Z�b�g���؂�ւ��
        }
        _pVbtn_Active_next_frame = prm_pVB;
    }

    /**
     * ���̐��̏u�Ԃ�n������O�ɁAVB���X�V����B
     */
    virtual void presentUniversalMoment() override {
        //VB�𔽉f
        _pVbtn_Active = _pVbtn_Active_next_frame;
        //��ʌĂяo��
        GgafDx9LibStg::DefaultGod::presentUniversalMoment();
    }

    /**
     * World�V�[�����쐬�B������
     * ��OverRide �ł���
     */
    GgafCore::GgafUniverse* createUniverse() override;
    virtual void clean() override;
    virtual ~God();
};

}

#endif /*GOD_H_*/
