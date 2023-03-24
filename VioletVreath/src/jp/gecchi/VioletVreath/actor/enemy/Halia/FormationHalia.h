#ifndef FORMATIONHALIA_H_
#define FORMATIONHALIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機ハリア用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationHalia : public GgafLib::TreeFormation {
public:
    /** 編隊数(RANK変動) */
    int num_Halia_;
    /** ハリアの配列(RANK変動) */
    EnemyHalia** papHalia_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    /** 移動速度(RANK変動) */
    velo velo_mv_;


public:
    FormationHalia(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual ~FormationHalia();
};

}
#endif /*FORMATIONHALIA_H_*/
