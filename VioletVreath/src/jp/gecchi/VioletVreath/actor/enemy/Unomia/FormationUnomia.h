#ifndef FORMATIONUNOMIA_H_
#define FORMATIONUNOMIA_H_
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * 敵機ウーノミア用フォーメーション基底 .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia : public GgafLib::DepositoryFormation {

public:
    /** ウーノミア借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoConn_Unomia_;
    GgafCore::GgafActorDepository* pDepo_shot_;

    /** スプライン定義資源への接続 */
    GgafLib::SplineManufactureConnection** papSplManufConnection_;
    /** 編隊列数(RANK変動) */
    int RF_num_formation_col_;
    /** １列の編隊数(RANK変動) */
    int RF_num_formation_row_;
    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame RF_interval_frames_;
    /** 編隊メンバーの移動速度(RANK変動) */
    velo RF_mv_velo_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_spl_id スプライン定義ID(XXX.spl の XXX)
     */
    FormationUnomia(const char* prm_name, const char* prm_spl_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpUnomia(EnemyUnomia* pEnemyUnomia, int col) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationUnomia();
};

}
#endif /*FORMATIONUNOMIA_H_*/
