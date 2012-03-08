#ifndef GOD_H_
#define GOD_H_

namespace VioletVreath {

/** �Q�[������VirtualButton */
#define VB_PLAY VioletVreath::God::pVbtn_PLAY_
/** UI���쎞��VirtualButton */
#define VB_UI VioletVreath::God::pVbtn_UI_
/** VB_PLAY or VB_UI �̂ǂ��炩�ŁA�A�N�e�B�u�ȕ���VirtualButton */
#define VB VioletVreath::God::pVbtn_Active_


//#define connectToDepositoryManager(X) (connectToDepositoryManager(X)))
#define connectToDepositoryManager(X,Y) ((VioletVreath::DepositoryConnection*)(P_GOD->pDepoManager_->connect((X),(Y))))
#define connectToSplineLineManager(X)   ((VioletVreath::SplineLineConnection*)(P_GOD->pSpl3DManager_->connect(X)))

/**
 * �_
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
     * �R���X�g���N�^ .
     * @param prm_hInstance
     * @param prm_pHWndPrimary �P��ʖ�HWND
     * @param prm_pHWndSecondary �Q��ʖ�HWND
     */
    God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * VB���X�V��\�񂷂�B .
     * @param prm_pVB
     */
    void setVB(GgafLib::VirtualButton* prm_pVB) {
        if (pVbtn_Active_ != prm_pVB) {
            //VB�̃Z�b�g���؂�ւ��
        }
        pVbtn_Active_next_frame_ = prm_pVB;
    }

    /**
     * ���̐��̏u�Ԃ�n������O�ɁAVB���X�V����B
     */
    virtual void presentUniversalMoment() override {
        //VB�𔽉f
        pVbtn_Active_ = pVbtn_Active_next_frame_;
        //��ʌĂяo��
        GgafLib::DefaultGod::presentUniversalMoment();
    }

    /**
     * World�V�[�����쐬�B������
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual void clean() override;

    virtual void oops() override;

    virtual ~God();
};

}

#endif /*GOD_H_*/
