#ifndef GGAFLIB_COLLIAAPYRAMIDACTOR_H_
#define GGAFLIB_COLLIAAPYRAMIDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxAAPyramidActor.h"

namespace GgafLib {

/**
 * �����蔻��\���pAA�s���~�b�h(�����O�p��)�N���X
 * GgafDxAAPyramidActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2016/01/18
 * @author Masatoshi Tsuge
 */
class ColliAAPyramidActor : public GgafDxCore::GgafDxAAPyramidActor {
    static ColliAAPyramidActor* _pObj;

public:
    static ColliAAPyramidActor* get();
    static void release();

public:
    ColliAAPyramidActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitarea(CollisionChecker* prm_pColliChecker);

    virtual ~ColliAAPyramidActor();

};

}
#endif /*GGAFLIB_COLLIAAPYRAMIDACTOR_H_*/
