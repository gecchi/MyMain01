#ifndef FORMATIONEBE_H_
#define FORMATIONEBE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * 敵機エーベ用フォーメーション基底 .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationEbe : public GgafLib::DepositoryFormation {

public:
    /** エーベ借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_pEbeDepo_;
    /** エーベの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_pShotDepo_;

    /** 編隊数(RANK変動) */
    int RV_Num_;
    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame RV_LaunchInterval;
    /** 編隊メンバーの移動速度(RANK変動) */
    velo RV_MvVelo_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_ldr_id 曲線移動の情報ID(XXX.ldr の XXX)
     */
    FormationEbe(const char* prm_name, const char* prm_ldr_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCalledUpEbe(EnemyEbe* pEnemyEbe) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual GgafDx::CurveManufacture* getSplManuf() = 0;

    virtual ~FormationEbe();
};

}
#endif /*FORMATIONEBE_H_*/
