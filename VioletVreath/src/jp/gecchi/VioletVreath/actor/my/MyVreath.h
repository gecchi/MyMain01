#ifndef MYVREATH_H_
#define MYVREATH_H_
namespace VioletVreath {

/**
 * Vreath .
 * @version 1.00
 * @since 2012/05/11
 * @author Masatoshi Tsuge
 */
class MyVreath : public GgafLib::DefaultMeshActor {

public:
    MyVreath(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~MyVreath();
};

}
#endif /*MYVREATH_H_*/

