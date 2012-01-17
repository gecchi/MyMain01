#ifndef ENEMYMASSALIAFRAGMENT2_H_
#define ENEMYMASSALIAFRAGMENT2_H_
namespace MyStg2nd {

/**
 * É}ÉbÉTÉäÉAífï–ÇÃífï–  .
 * Ë¶êŒÇÃífï–ÇÃífï–
 * @version 1.00
 * @since 2012/01/16
 * @author Masatoshi Tsuge
 */
class EnemyMassaliaFragment2 : public GgafLib::DefaultMeshSetActor {

public:

    EnemyMassaliaFragment2(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void processFinal() override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyMassaliaFragment2();
};

}
#endif /*ENEMYMASSALIAFRAGMENT2_H_*/

