#ifndef MYWAVE001_H_
#define MYWAVE001_H_
namespace MyStg2nd {

class MyWave001 : public GgafDx9LibStg::DefaultMeshActor {

public:
    MyWave001(const char* prm_name, const char* prm_model);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processJudgement();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void onInact();

    virtual ~MyWave001();
};

}
#endif /*MYWAVE001_H_*/

