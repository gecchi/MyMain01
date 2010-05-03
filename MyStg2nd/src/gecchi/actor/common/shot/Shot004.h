#ifndef SHOT004_H_
#define SHOT004_H_
namespace MyStg2nd {

/**
 * �ėp�e003(��) .
 * �j��s�\�œ��������ړ�<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot004 : public SingleLaser {
public:

    Shot004(const char* prm_name);

    void onCreateModel() override {
    }
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

    virtual ~Shot004();
};

}
#endif /*SHOT004_H_*/
