#ifndef COLLIAAPRISMACTOR_H_
#define COLLIAAPRISMACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxAAPrismActor.h"

namespace GgafLib {

/**
 * �����蔻��\���pAA�v���Y��(�����O�p��)�N���X
 * GgafDxAAPrismActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class ColliAAPrismActor : public GgafDxCore::GgafDxAAPrismActor {
    static ColliAAPrismActor* _pObj;

public:
    static ColliAAPrismActor* get();
    static void release();

public:
    ColliAAPrismActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitarea(CollisionChecker3D* prm_pChecker);

    virtual ~ColliAAPrismActor();

};

}
#endif /*COLLIAAPRISMACTOR_H_*/
