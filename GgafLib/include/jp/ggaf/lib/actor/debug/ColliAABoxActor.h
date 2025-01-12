#ifndef GGAF_LIB_COLLIAABACTOR_H_
#define GGAF_LIB_COLLIAABACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/AABActor.h"

namespace GgafLib {

/**
 * �����蔻��\���p�L���[�u�N���X
 * GgafDx::AABActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class ColliAABoxActor : public GgafDx::AABActor {
    static ColliAABoxActor* _pObj;

public:
    static ColliAABoxActor* get();
    static void release();

public:
    ColliAABoxActor(const char* prm_name);

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

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    void drawHitarea(GgafDx::CollisionChecker* prm_pColliChecker);

    virtual ~ColliAABoxActor();

};

}
#endif /*GGAF_LIB_COLLIAABACTOR_H_*/
