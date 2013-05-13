#ifndef FORMATIONHEBE_H_
#define FORMATIONHEBE_H_
namespace VioletVreath {

/**
 * 敵機ヘーベ用フォーメーション基底 .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationHebe : public GgafLib::DepositoryFormation {

public:
    /** ヘーベ借り入れ元Depository資源への接続 */
    DepositoryConnection* pConnection_HebeDepo_;
    /** ヘーベの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pConnection_ShotDepo_;

    /** 編隊数(RANK変動) */
    int rr_num_formation_;
    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame rr_interval_frames_;
    /** 編隊メンバーの移動速度(RANK変動) */
    velo rr_mv_velo_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_spl_id スプライン定義ID(XXX.spl の XXX)
     */
    FormationHebe(const char* prm_name, const char* prm_spl_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpHebe(EnemyHebe* pEnemyHebe) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual GgafLib::SplineManufacture* getSplManuf() = 0;

    virtual ~FormationHebe();
};

}
#endif /*FORMATIONHEBE_H_*/
