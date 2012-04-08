#ifndef SINGLELASEREFFECTACTOR_H_
#define SINGLELASEREFFECTACTOR_H_
namespace VioletVreath {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class SingleLaserTestActor : public GgafLib::SingleLaser {
public:

    SingleLaserTestActor(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~SingleLaserTestActor();
};

}
#endif /*SINGLELASEREFFECTACTOR_H_*/

