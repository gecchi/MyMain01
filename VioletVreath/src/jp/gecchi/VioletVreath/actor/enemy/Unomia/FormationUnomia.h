#ifndef FORMATIONUNOMIA_H_
#define FORMATIONUNOMIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機ウーノミア用フォーメーション基底 .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia : public GgafLib::TreeFormation {

public:
    /** ウーノミアの玉、借り入れ元Depository資源への接続 */
    GgafCore::ActorDepository* pDepo_shot_;

    /** 曲線移動の情報資源への接続 */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    /** 編隊列数(RANK変動) */
    int num_formation_col_;
    /** １列の編隊数(RANK変動) */
    int num_formation_row_;
    /** 編隊数 */
    int num_formation_member_;
    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame launch_interval_;
    /** 編隊メンバーの移動速度(RANK変動) */
    velo mv_velo_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_ldr_id 曲線移動の情報ID(XXX.ldr の XXX)
     */
    FormationUnomia(const char* prm_name, const char* prm_ldr_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCalledUpUnomia(EnemyUnomia* pEnemyUnomia, int col) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationUnomia();
};

}
#endif /*FORMATIONUNOMIA_H_*/
