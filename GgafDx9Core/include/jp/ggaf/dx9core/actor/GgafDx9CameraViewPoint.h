#ifndef GGAFDX9CAMERAVIEWPOINT_H_
#define GGAFDX9CAMERAVIEWPOINT_H_
namespace GgafDx9Core {

/**
 * カメラの視点の目標点クラス.
 * @version 1.00
 * @since 2009/10/14
 * @author Masatoshi Tsuge
 */
class GgafDx9CameraViewPoint : public GgafDx9GeometricActor {

public:

    frame _frame_offset;

    GgafDx9CameraViewPoint();

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

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~GgafDx9CameraViewPoint();
};

}
#endif /*GGAFDX9CAMERAVIEWPOINT_H_*/
