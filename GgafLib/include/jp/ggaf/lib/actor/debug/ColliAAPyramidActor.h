#ifndef GGAF_LIB_COLLIAAPYRAMIDACTOR_H_
#define GGAF_LIB_COLLIAAPYRAMIDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/AAPyramidActor.h"

namespace GgafLib {

/**
 * �����蔻��\���pAA�s���~�b�h(�����O�p��)�N���X
 * GgafDx::AAPyramidActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2016/01/18
 * @author Masatoshi Tsuge
 */
class ColliAAPyramidActor : public GgafDx::AAPyramidActor {
    static ColliAAPyramidActor* _pObj;

public:
    static ColliAAPyramidActor* get();
    static void release();

public:
    ColliAAPyramidActor(const char* prm_name);

    //void processDraw() {} //�I�[�o�[���C�h�������ɂ���B
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

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    void drawHitarea(GgafDx::CollisionChecker* prm_pColliChecker);

    virtual ~ColliAAPyramidActor();

};

}
#endif /*GGAF_LIB_COLLIAAPYRAMIDACTOR_H_*/
