#ifndef ENEMYASSALIABASE_H_
#define ENEMYASSALIABASE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * ÉGÉ~ÉäÉA .
 * Ë¶êŒåQÇÃË¶êŒ
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyEmiliaBase : public GgafLib::DefaultMeshSetActor {

protected:
    void appearFragment(const char* prm_dp_name);
    virtual void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) = 0;

public:
    enum {
        SE_DAMAGED   ,
        SE_EXPLOSION ,
    };

public:
    EnemyEmiliaBase(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual void onInactive() override;



    virtual ~EnemyEmiliaBase();
};

}
#endif /*ENEMYASSALIABASE_H_*/

