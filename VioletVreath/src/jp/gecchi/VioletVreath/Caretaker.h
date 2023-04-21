#ifndef CARETAKER_H_
#define CARETAKER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/manager/EffectManager.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryConnection.h"
#include "jp/gecchi/VioletVreath/manager/CurveSourceManagerEx.h"
#include "jp/gecchi/VioletVreath/manager/CurveManufactureManagerEx.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#undef pCARETAKER
#define pCARETAKER ((VioletVreath::Caretaker*)GgafCore::Caretaker::ask())

namespace VioletVreath {

/** �Q�[������VirtualButton */
#define VV_VB_PLAY VioletVreath::Caretaker::pVbtn_PLAY_
/** UI���쎞��VirtualButton */
#define VV_VB_UI VioletVreath::Caretaker::pVbtn_UI_
/** VV_VB_PLAY or VV_VB_UI �̂ǂ��炩�ŁA�A�N�e�B�u�ȕ���VirtualButton */
#define VVB VioletVreath::Caretaker::pVbtn_active_

/** �Q�[���v���C�̃��v���C�Đ��p�ǂݍ��݃t�@�C�� */
#define FILE_INPUT_PLAY_REPLAY    "VV_VB_PLAY.rep"
/** UI����̃��v���C�Đ��p�ǂݍ��݃t�@�C�� */
#define FILE_INPUT_UI_REPLAY      "VV_VB_UI.rep"
/** �Q�[���v���C�̃��v���C�����o���t�@�C�� */
#define FILE_OUTPUT_PLAY_REPLAY   "VV_VB_PLAY_LAST.rep"
/** UI����̃��v���C�����o���t�@�C�� */
#define FILE_OUTPUT_UI_REPLAY     "VV_VB_UI_LAST.rep"
/** �Q�[���v���C�̃��v���C�����o���t�@�C���i�f�o�b�O�p���������o���j */
#define FILE_REALTIME_OUTPUT_PLAY_REPLAY   "VV_VB_PLAY_LAST_REALTIME.rep"
/** UI����̃��v���C�����o���t�@�C���i�f�o�b�O�p���������o���j */
#define FILE_REALTIME_OUTPUT_UI_REPLAY     "VV_VB_UI_LAST_REALTIME.rep"

/**
 * �Ǘ��҂��ێ����� DepositoryManager �ɐڑ����A�R�l�N�V�������擾�B
 * X�F���ʕ�����iDepositoryManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) �� prm_idstr �ɓn��)
 */
#define connectToDepositoryManager(X) ((VioletVreath::DepositoryConnection*)(pCARETAKER->pDepoManager_->connect((X), this)))

#define connectToXpmManager(X) ((VioletVreath::XpmConnection*)(pCARETAKER->pXpmManager_->connect((X), this)))

#define P1 0
#define P2 1


/**
 * �Ǘ���
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class Caretaker : public GgafLib::DefaultCaretaker {

public:
    DepositoryManager* pDepoManager_;
    XpmManager* pXpmManager_;

    static GgafLib::VirtualButton* pVbtn_PLAY_;
    static GgafLib::VirtualButton* pVbtn_UI_;
    static GgafLib::VirtualButton* pVbtn_active_;
    static GgafLib::VirtualButton* pVbtn_active_next_frame_;
    static bool g_should_reboot_;
public:
    /**
     * �R���X�g���N�^ .
     */
    Caretaker();

    void initVB();

    HRESULT initDevice() override;

    /**
     * VB���X�V��\�񂷂�B .
     * @param prm_pVVB
     */
    void setVB(GgafLib::VirtualButton* prm_pVVB) {
        if (pVbtn_active_ != prm_pVVB) {
            //VB�̃Z�b�g���؂�ւ��
        }
        pVbtn_active_next_frame_ = prm_pVVB;
    }

    /**
     * VB���X�V����B
     */
    virtual void presentBehave() override {
        //VB�𔽉f
        pVbtn_active_ = pVbtn_active_next_frame_;
        //��ʌĂяo��
        GgafLib::DefaultCaretaker::presentBehave();
    }

    /**
     * World�V�[�����쐬�B������
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual Spacetime* getSpacetime() override {  //���ς̖߂�l
        return (Spacetime*)_pSpacetime;
    }

    /**
     * �A�v���P�[�V�����ċN�� .
     */
    static void reboot();

    virtual void clean() override;

    virtual void oops() override;

    virtual EffectManager* createEffectManager() override;  //���ς̖߂�l

    virtual CurveSourceManagerEx* createCurveSourceManager() override;  //���ς̖߂�l
    virtual CurveManufactureManagerEx* createCurveManufactureManager() override;  //���ς̖߂�l

    virtual ~Caretaker();
};

}

#endif /*CARETAKER_H_*/
