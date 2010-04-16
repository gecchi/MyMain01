#ifndef MYWAVE001_H_
#define MYWAVE001_H_
namespace MyStg2nd {

class MyWave001 : public GgafDx9LibStg::DefaultMeshActor {

public:
    MyWave001(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    /**
     * ＜OverRide です＞
     */
    void processBehavior() override;

    /**
     * ＜OverRide です＞
     */
    void processJudgement() override;

    /**
     * ＜OverRide です＞
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    /**
     * ＜OverRide です＞
     */
    void onInactive() override;

    virtual ~MyWave001();
};

}
#endif /*MYWAVE001_H_*/

