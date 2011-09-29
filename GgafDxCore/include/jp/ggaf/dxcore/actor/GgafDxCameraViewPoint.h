#ifndef GGAFDXCAMERAVIEWPOINT_H_
#define GGAFDXCAMERAVIEWPOINT_H_
namespace GgafDxCore {

/**
 * カメラの視点の目標点クラス.
 * @version 1.00
 * @since 2009/10/14
 * @author Masatoshi Tsuge
 */
class GgafDxCameraViewPoint : public GgafDxGeometricActor {

public:

    frame _offset_frames;

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

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~GgafDxCameraViewPoint();
};

}
#endif /*GGAFDXCAMERAVIEWPOINT_H_*/
