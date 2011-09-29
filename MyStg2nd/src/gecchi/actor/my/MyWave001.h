#ifndef MYWAVE001_H_
#define MYWAVE001_H_
namespace MyStg2nd {

class MyWave001 : public GgafLib::DefaultMeshActor {

public:
    MyWave001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processJudgement() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void onInactive() override;

    virtual ~MyWave001();
};

}
#endif /*MYWAVE001_H_*/

