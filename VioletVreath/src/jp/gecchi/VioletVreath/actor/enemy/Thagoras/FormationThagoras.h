#ifndef FORMATIONTHAGORAS_H_
#define FORMATIONTHAGORAS_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * G@^SXptH[[V»ÌP .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras : public GgafLib::TreeFormation {

public:
    /** Òà(RANKÏ®) */
    int num_Thagoras_;
    /** ÒàÔut[(RANKÏ®) */
    frame interval_frames_;

    int cnt_call_up_;

public:
    FormationThagoras(const char* prm_name);

    /**
     * Òàðì¬ .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpThagoras(EnemyThagoras* prm_pThagoras, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationThagoras();
};

}
#endif /*FORMATIONTHAGORAS_H_*/
