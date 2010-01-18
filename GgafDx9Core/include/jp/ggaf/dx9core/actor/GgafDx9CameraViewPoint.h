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

    DWORD _frame_offset;

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

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~GgafDx9CameraViewPoint();
};

}
#endif /*GGAFDX9CAMERAVIEWPOINT_H_*/
