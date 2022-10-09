#ifndef GGAF_LIB_COLLIAAPRISMACTOR_H_
#define GGAF_LIB_COLLIAAPRISMACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/debug/AAPrismActor.h"

namespace GgafLib {

/**
 * �����蔻��\���pAA�v���Y��(�����O�p��)�N���X
 * GgafDx::AAPrismActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class ColliAAPrismActor : public GgafDx::AAPrismActor {
    static ColliAAPrismActor* _pObj;

public:
    static ColliAAPrismActor* get();
    static void release();

public:
    ColliAAPrismActor(const char* prm_name);

    //void processDraw() {} //�I�[�o�[���C�h�������ɂ���B
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

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    void drawHitarea(CollisionChecker* prm_pColliChecker);

    virtual ~ColliAAPrismActor();

};

}
#endif /*GGAF_LIB_COLLIAAPRISMACTOR_H_*/
