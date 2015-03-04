#ifndef GGAFLIB_DEFAULTCAMERAVIEWPOINT_H_
#define GGAFLIB_DEFAULTCAMERAVIEWPOINT_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"

namespace GgafLib {

/**
 * �W���̎��_�I�u�W�F�N�g .
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class DefaultCameraViewPoint : public GgafDxCore::GgafDxCameraViewPoint {

public:
    DefaultCameraViewPoint(const char* prm_name);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultCameraViewPoint(); //�f�X�g���N�^
};

}
#endif /*GGAFLIB_DEFAULTCAMERAVIEWPOINT_H_*/