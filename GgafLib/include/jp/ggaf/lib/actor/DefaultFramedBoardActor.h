#ifndef GGAF_LIB_DEFAULTFRAMEDBOARDACTOR_H_
#define GGAF_LIB_DEFAULTFRAMEDBOARDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/FramedBoardActor.h"

namespace GgafLib {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx::FramedBoardActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ĐF�X��ʕ\�����쐬���܂��傤�B<BR>
 * @version 1.00
 * @since 2017/08/22
 * @author Masatoshi Tsuge
 */
class DefaultFramedBoardActor : public GgafDx::FramedBoardActor {

public:
    DefaultFramedBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual ~DefaultFramedBoardActor();

};

}
#endif /*GGAF_LIB_DEFAULTFRAMEDBOARDACTOR_H_*/
