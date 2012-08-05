#ifndef MYSHOT001_H_
#define MYSHOT001_H_
namespace VioletVreath {

/**
 * 自機ショット001 .
 * @version 1.00
 * @since 2010/07/04
 * @author Masatoshi Tsuge
 */
class MyShot001 : public GgafLib::SingleLaser {
public:

    MyShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

//    void drawHitArea() override;

    virtual ~MyShot001();
};

}
#endif /*MYSHOT001_H_*/

