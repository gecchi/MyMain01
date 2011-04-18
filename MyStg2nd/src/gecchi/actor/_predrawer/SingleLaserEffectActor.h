#ifndef SINGLELASEREFFECTACTOR_H_
#define SINGLELASEREFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class SingleLaserEffectActor : public GgafDx9LibStg::SingleLaser {
public:

    SingleLaserEffectActor(const char* prm_name);


    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void drawHitArea() override;

    virtual ~SingleLaserEffectActor();
};

}
#endif /*SINGLELASEREFFECTACTOR_H_*/

