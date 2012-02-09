#ifndef ENEMYMASSALIAFRAGMENT3_H_
#define ENEMYMASSALIAFRAGMENT3_H_
namespace MyStg2nd {

/**
 * É}ÉbÉTÉäÉAífï–ÇÃífï–  .
 * Ë¶êŒÇÃífï–ÇÃífï–
 * @version 1.00
 * @since 2012/01/17
 * @author Masatoshi Tsuge
 */
class EnemyMassaliaFragment3 : public GgafLib::DefaultMeshSetActor {

public:

    EnemyMassaliaFragment3(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyMassaliaFragment3();
};

}
#endif /*ENEMYMASSALIAFRAGMENT3_H_*/

