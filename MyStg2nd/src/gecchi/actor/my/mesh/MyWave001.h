#ifndef MYWAVE001_H_
#define MYWAVE001_H_
namespace MyStg2nd {

class MyWave001 : public GgafDx9LibStg::DefaultMeshActor {

public:
    MyWave001(const char* prm_name, const char* prm_model);

    /**
     * ＜OverRide です＞
     */
    void initialize();

    /**
     * ＜OverRide です＞
     */
    void processBehavior();

    /**
     * ＜OverRide です＞
     */
    void processJudgement();

    /**
     * ＜OverRide です＞
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    /**
     * ＜OverRide です＞
     */
    void onRefrain();

    virtual ~MyWave001();
};

}
#endif /*MYWAVE001_H_*/

