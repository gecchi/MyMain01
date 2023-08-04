#ifndef FORMATIONAPPHO001_H_
#define FORMATIONAPPHO001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機アッポー用フォーメーションその１ .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationAppho001 : public VvFormationActor<GgafLib::TreeFormation> {

public:
    /** 編隊数(RANK変動) */
    int num_Appho_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;

    int cnt_called_up_;

public:
    FormationAppho001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCalledUpAppho(EnemyAppho* prm_pAppho, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual ~FormationAppho001();
};

}
#endif /*FORMATIONAPPHO001_H_*/
