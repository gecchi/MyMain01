#ifndef GGAFLIB_DEFAULTFRAMEDBOARDACTOR_H_
#define GGAFLIB_DEFAULTFRAMEDBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFramedBoardActor.h"

namespace GgafLib {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxFramedBoardActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ĐF�X��ʕ\�����쐬���܂��傤�B<BR>
 * @version 1.00
 * @since 2017/08/22
 * @author Masatoshi Tsuge
 */
class DefaultFramedBoardActor : public GgafDxCore::GgafDxFramedBoardActor {

public:
    DefaultFramedBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultFramedBoardActor();

};

}
#endif /*GGAFLIB_DEFAULTFRAMEDBOARDACTOR_H_*/
