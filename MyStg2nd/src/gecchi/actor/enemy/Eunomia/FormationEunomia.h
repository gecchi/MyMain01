#ifndef FORMATIONEUNOMIA_H_
#define FORMATIONEUNOMIA_H_
namespace MyStg2nd {

/**
 * 敵機エウノミア用フォーメーション基底 .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia : public GgafLib::DepositoryFormation {

public:
    /** エウノミア借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon_Eunomia;
    /** エウノミアの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon_shot;
    /** スプライン定義資源への接続 */
    GgafLib::SplineManufactureConnection** _papSplManufCon;
    /** 編隊列数(RANK変動) */
    int _R_num_formation_col;
    /** １列の編隊数(RANK変動) */
    int _R_num_formation_row;
    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame _R_interval_frames;
    /** 編隊メンバーの移動速度(RANK変動) */
    velo _R_mv_velo;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_spl_id スプライン定義ID(XXX.spl の XXX)
     */
    FormationEunomia(const char* prm_name, const char* prm_spl_id) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_LastDestroyed  最後に破壊されたアクター
     */
    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationEunomia();
};

}
#endif /*FORMATIONEUNOMIA_H_*/
