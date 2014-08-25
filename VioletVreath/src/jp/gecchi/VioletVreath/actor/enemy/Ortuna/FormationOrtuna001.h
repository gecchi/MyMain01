#ifndef FORMATIONORTUNA001_H_
#define FORMATIONORTUNA001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * オルトゥナ用フォーメーションその１ .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationOrtuna001 : public GgafLib::TreeFormation {

public:
    /** 編隊数(RANK変動) */
    int num_Ortuna_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;

    int index_call_up_;

public:
    FormationOrtuna001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    /**
     * オルトゥナCallUp時にコールバックされるメソッド。
     * @param prm_pOrtuna CallUpされたオルトゥナ
     * @param prm_index インデックス (0〜・・・)
     */
    virtual void onCallUpOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationOrtuna001();
};

}
#endif /*FORMATIONORTUNA001_H_*/
