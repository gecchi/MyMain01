#ifndef DEFAULTDYNAD3DXMESHACTOR_H_
#define DEFAULTDYNAD3DXMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxDynaD3DXMeshActor.h"

namespace GgafLib {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxDynaD3DXMeshActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class DefaultDynaD3DXMeshActor : public GgafDxCore::GgafDxDynaD3DXMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* const _pScaler;
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker3D* _pColliChecker;

public:
    DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultDynaD3DXMeshActor();
};

}
#endif /*DEFAULTDYNAD3DXMESHACTOR_H_*/
