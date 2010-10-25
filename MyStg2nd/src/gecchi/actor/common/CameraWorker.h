#ifndef CAMERAWORKER_H_
#define CAMERAWORKER_H_



namespace MyStg2nd {

/**
 * カメラ.
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class CameraWorker : public GgafCore::GgafMainActor {

public:
    /** カメラ位置番号 */
    int _pos_camera;


    CameraWorker(const char* prm_name);

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
    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }
    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }
    virtual ~CameraWorker(); //デストラクタ
};

}
#endif /*CAMERA_H_*/
