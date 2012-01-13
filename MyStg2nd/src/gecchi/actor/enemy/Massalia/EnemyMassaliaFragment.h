#ifndef ENEMYMASSALIAFRAGMENT_H_
#define ENEMYMASSALIAFRAGMENT_H_
namespace MyStg2nd {

/**
 * マッサリア断片  .
 * 隕石の断片
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyMassaliaFragment : public GgafLib::DefaultMeshSetActor {

public:

    EnemyMassaliaFragment(const char* prm_name);

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

    virtual ~EnemyMassaliaFragment();
};

}
#endif /*ENEMYMASSALIAFRAGMENT_H_*/

