#ifndef GGAF_LIB_DEFAULTDYNAD3DXMESHACTOR_H_
#define GGAF_LIB_DEFAULTDYNAD3DXMESHACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/DynaD3DXMeshActor.h"

namespace GgafLib {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx::DynaD3DXMeshActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class DefaultDynaD3DXMeshActor : public GgafDx::DynaD3DXMeshActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker* _pColliChecker;

public:
    DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model);

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

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultDynaD3DXMeshActor();
};

}
#endif /*GGAF_LIB_DEFAULTDYNAD3DXMESHACTOR_H_*/
