#ifndef FORMATIONTHAGORAS_H_
#define FORMATIONTHAGORAS_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機タゴラス用フォーメーションその１ .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras : public GgafLib::TreeFormation {

public:
    /** 編隊数(RANK変動) */
    int num_Thagoras_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;

    int cnt_call_up_;

public:
    FormationThagoras(const char* prm_name);

    /**
     * 編隊を作成 .
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
