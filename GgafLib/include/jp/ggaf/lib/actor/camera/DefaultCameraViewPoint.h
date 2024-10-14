#ifndef GGAF_LIB_DEFAULTCAMERAVIEWPOINT_H_
#define GGAF_LIB_DEFAULTCAMERAVIEWPOINT_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"

namespace GgafLib {

/**
 * �W���̎��_�I�u�W�F�N�g .
 * @version 1.00
 * @since 2010/10/22
 * @author Masatoshi Tsuge
 */
class DefaultCameraViewPoint : public GgafDx::CameraViewPoint {

public:
    DefaultCameraViewPoint(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    void slideMvTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2);

    void slideMvTo(GgafDx::GeometricActor* pTarget, frame t, double prm_p1, double prm_p2);

    virtual ~DefaultCameraViewPoint();
};

}
#endif /*GGAF_LIB_DEFAULTCAMERAVIEWPOINT_H_*/
