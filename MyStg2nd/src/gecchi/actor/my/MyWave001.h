#ifndef MYWAVE001_H_
#define MYWAVE001_H_
namespace MyStg2nd {

class MyWave001 : public GgafLib::DefaultMeshActor {

public:
    MyWave001(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize() override;

    /**
     * ��OverRide �ł���
     */
    void processBehavior() override;

    /**
     * ��OverRide �ł���
     */
    void processJudgement() override;

    /**
     * ��OverRide �ł���
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    /**
     * ��OverRide �ł���
     */
    void onInactive() override;

    virtual ~MyWave001();
};

}
#endif /*MYWAVE001_H_*/

