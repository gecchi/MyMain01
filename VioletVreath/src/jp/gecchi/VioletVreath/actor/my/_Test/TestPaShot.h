#ifndef TESTPASHOT_H_
#define TESTPASHOT_H_
namespace VioletVreath {

/**
 * パーショット .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestPaShot : public GgafLib::SingleLaser {
public:

    TestPaShot(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~TestPaShot();
};

}
#endif /*TESTPASHOT_H_*/

