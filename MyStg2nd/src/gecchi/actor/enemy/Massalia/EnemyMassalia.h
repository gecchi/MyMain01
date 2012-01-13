#ifndef ENEMYMASSALIA_H_
#define ENEMYMASSALIA_H_
namespace MyStg2nd {

/**
 * �}�b�T���A  .
 * 覐ΌQ��覐�
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyMassalia : public GgafLib::DefaultMeshSetActor {

public:
    EnemyMassalia(const char* prm_name);

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

    virtual ~EnemyMassalia();
};

}
#endif /*ENEMYMASSALIA_H_*/

