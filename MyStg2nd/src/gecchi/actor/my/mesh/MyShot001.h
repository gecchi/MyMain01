#ifndef MYSHOT001_H_
#define MYSHOT001_H_
namespace MyStg2nd {

/**
 * 自機ショット001 .
 * @version 1.00
 * @since 2010/07/04
 * @author Masatoshi Tsuge
 */
class MyShot001 : public GgafDx9LibStg::SingleLaser {
public:

    MyShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }
    void processHappen(int prm_no) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void drawHitArea() override;

    virtual ~MyShot001();
};

}
#endif /*MYSHOT001_H_*/

