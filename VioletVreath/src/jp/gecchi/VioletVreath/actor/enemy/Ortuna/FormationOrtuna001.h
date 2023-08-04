#ifndef FORMATIONORTUNA001_H_
#define FORMATIONORTUNA001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * オルトゥナ用フォーメーションその１ .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationOrtuna001 : public VvFormationActor<GgafLib::TreeFormation> {

public:
    /** 編隊数(RANK変動) */
    int num_Ortuna_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;

    int index_called_up_;

public:
    FormationOrtuna001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    /**
     * オルトゥナCalledUp時にコールバックされるメソッド。
     * @param prm_pOrtuna CalledUpされたオルトゥナ
     * @param prm_index インデックス (0～・・・)
     */
    virtual void onCalledUpOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual ~FormationOrtuna001();
};

}
#endif /*FORMATIONORTUNA001_H_*/
