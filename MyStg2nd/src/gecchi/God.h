#ifndef GOD_H_
#define GOD_H_

namespace MyStg2nd {

/** �Q�[������VirtualButton */
#define VB_PLAY MyStg2nd::God::_pVbtn_PLAY
/** UI���쎞��VirtualButton */
#define VB_UI MyStg2nd::God::_pVbtn_UI
/** VB_PLAY or VB_UI �̂ǂ��炩�ŁA�A�N�e�B�u�ȕ���VirtualButton */
#define VB MyStg2nd::God::_pVbtn_Active


//#define connectToDepositoryManager(X) (connectToDepositoryManager(X)))
#define connectToDepositoryManager(X,Y) ((MyStg2nd::DepositoryConnection*)(P_GOD->_pDepoManager->connect((X),(Y))))
#define connectToSplineLineManager(X)   ((MyStg2nd::SplineLineConnection*)(P_GOD->_pSpl3DManager->connect(X)))

/**
 * �_
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
     * �R���X�g���N�^ .
     * @param prm_hInstance
     * @param prm_pHWndPrimary
     */
    God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * VB���X�V��\�񂷂�B .
     * @param prm_pVB
     */
    void setVB(GgafLib::VirtualButton* prm_pVB) {
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
        GgafLib::DefaultGod::presentUniversalMoment();
    }

    /**
     * World�V�[�����쐬�B������
     * ��OverRide �ł���
     */
    GgafCore::GgafUniverse* createUniverse() override;
    virtual void clean() override;

    virtual void oops() override;

    virtual ~God();
};

}

#endif /*GOD_H_*/
