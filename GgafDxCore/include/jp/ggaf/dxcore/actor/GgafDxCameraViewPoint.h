#ifndef GGAFDXCORE_GGAFDXCAMERAVIEWPOINT_H_
#define GGAFDXCORE_GGAFDXCAMERAVIEWPOINT_H_
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * カメラの視点の目標点クラス.
 * @version 1.00
 * @since 2009/10/14
 * @author Masatoshi Tsuge
 */
class GgafDxCameraViewPoint : public GgafDxGeometricActor {

public:
    coord _x_prev, _y_prev, _z_prev;
    frame _offset_frames;

public:
    GgafDxCameraViewPoint();

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

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    bool isMoving();

    virtual ~GgafDxCameraViewPoint();
};

}
#endif /*GGAFDXCORE_GGAFDXCAMERAVIEWPOINT_H_*/
