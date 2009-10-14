#ifndef GGAFDX9CAMERAVIEWPOINT_H_
#define GGAFDX9CAMERAVIEWPOINT_H_
namespace GgafDx9Core {

/**
 * メッシュアクターの具象クラス.
 */
class GgafDx9CameraViewPoint : public GgafDx9GeometricActor {

public:

    DWORD _frame_offset;

    GgafDx9CameraViewPoint();

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement() {
    }

    virtual void processPreDraw() {
    }

    virtual void processDraw() {
    }

    virtual void processAfterDraw() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }


    virtual ~GgafDx9CameraViewPoint();
};

}
#endif /*GGAFDX9CAMERAVIEWPOINT_H_*/
