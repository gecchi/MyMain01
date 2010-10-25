#ifndef TESTCAMWORKER_H_
#define TESTCAMWORKER_H_


namespace MyStg2nd {

/**
 * 何もしないカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class TestCamWorker : public CameraWorker {

public:

    TestCamWorker(const char* prm_name);
    virtual void initialize() override {
    }

    void onPushed() override;

    void onPoped() override {
    }

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~TestCamWorker(); //デストラクタ
};

}
#endif /*TESTCAMWORKER_H_*/
