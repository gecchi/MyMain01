#ifndef GGAF_LIB_COLLIAABOARDRECTACTOR_H_
#define GGAF_LIB_COLLIAABOARDRECTACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/AABoardRectActor.h"

namespace GgafLib {

/**
 * Board�l�p�����蔻��\���p�N���X
 * GgafDx::AABoardRectActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2022/10/11
 * @author Masatoshi Tsuge
 */
class ColliAABoardRectActor : public GgafDx::AABoardRectActor {
    static ColliAABoardRectActor* _pObj;

public:
    static ColliAABoardRectActor* get();
    static void release();

public:
    ColliAABoardRectActor(const char* prm_name);

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

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    void drawHitarea(GgafDx::CollisionChecker* prm_pChecker);

    virtual ~ColliAABoardRectActor();

};

}
#endif /*GGAF_LIB_COLLIAABOARDRECTACTOR_H_*/
