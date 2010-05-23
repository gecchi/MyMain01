#ifndef VARIETYTORUS001_H_
#define VARIETYTORUS001_H_
namespace MyStg2nd {

/**
 * 地形トーラス .
 * 最初に作った地形
 * @version 1.00
 * @since 2010/05/08
 * @author Masatoshi Tsuge
 */
class VarietyTorus001 : public Torus {

public:

    VarietyTorus001(const char* prm_name);
    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~VarietyTorus001();
};

}
#endif /*VARIETYTORUS001_H_*/

