#ifndef GOD_H_
#define GOD_H_
#include "jp/ggaf/lib/DefaultGod.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryConnection.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineManager.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineConnection.h"

#undef P_GOD
#define P_GOD ((VioletVreath::God*)VioletVreath::God::_pGod)

namespace VioletVreath {

/** �Q�[������VirtualButton */
#define VB_PLAY VioletVreath::God::pVbtn_PLAY_
/** UI���쎞��VirtualButton */
#define VB_UI VioletVreath::God::pVbtn_UI_
/** VB_PLAY or VB_UI �̂ǂ��炩�ŁA�A�N�e�B�u�ȕ���VirtualButton */
#define VB VioletVreath::God::pVbtn_active_

/** �Q�[���v���C�̃��v���C�Đ��p�ǂݍ��݃t�@�C�� */
#define FILE_INPUT_PLAY_REPLAY    "VB_PLAY.rep"
/** UI����̃��v���C�Đ��p�ǂݍ��݃t�@�C�� */
#define FILE_INPUT_UI_REPLAY      "VB_UI.rep"
/** �Q�[���v���C�̃��v���C�����o���t�@�C�� */
#define FILE_OUTPUT_PLAY_REPLAY   "VB_PLAY_LAST.rep"
/** UI����̃��v���C�����o���t�@�C�� */
#define FILE_OUTPUT_UI_REPLAY     "VB_UI_LAST.rep"
/** �Q�[���v���C�̃��v���C�����o���t�@�C���i�f�o�b�O�p���������o���j */
#define FILE_REALTIME_OUTPUT_PLAY_REPLAY   "VB_PLAY_LAST_REALTIME.rep"
/** UI����̃��v���C�����o���t�@�C���i�f�o�b�O�p���������o���j */
#define FILE_REALTIME_OUTPUT_UI_REPLAY     "VB_UI_LAST_REALTIME.rep"

/**
 * �_���ێ����� DepositoryManager �ɐڑ����A�R�l�N�V�������擾�B
 * X�F���ʕ�����iDepositoryManager::processCreateResource(char* prm_idstr, void* prm_pConnector) �� prm_idstr �ɓn��)
 */
#define connectToDepositoryManager(X) ((VioletVreath::DepositoryConnection*)(P_GOD->pDepoManager_->connect((X), this)))

/**
 * �_���ێ����� SplineLineManager �ɐڑ����A�R�l�N�V�������擾�B
 * X�F���ʕ�����iSplineLineManager::processCreateResource(char* prm_idstr, void* prm_pConnector) �� prm_idstr �ɓn��)
 */
#define connectToSplineLineManager(X)   ((VioletVreath::SplineLineConnection*)(P_GOD->pSpl3DManager_->connect((X), this)))

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
    static GgafLib::VirtualButton* pVbtn_active_;
    static GgafLib::VirtualButton* pVbtn_active_next_frame_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_hInstance
     * @param prm_pHWndPrimary �P��ʖ�HWND
     * @param prm_pHWndSecondary �Q��ʖ�HWND
     */
    God();


    void initVB();

    /**
     * VB���X�V��\�񂷂�B .
     * @param prm_pVB
     */
    void setVB(GgafLib::VirtualButton* prm_pVB) {
        if (pVbtn_active_ != prm_pVB) {
            //VB�̃Z�b�g���؂�ւ��
        }
        pVbtn_active_next_frame_ = prm_pVB;
    }

    /**
     * ���̐��̏u�Ԃ�n������O�ɁAVB���X�V����B
     */
    virtual void presentUniversalMoment() override {
        //VB�𔽉f
        pVbtn_active_ = pVbtn_active_next_frame_;
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
