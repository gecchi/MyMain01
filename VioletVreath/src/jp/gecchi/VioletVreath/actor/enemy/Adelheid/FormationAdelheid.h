#ifndef FORMATIONADELHEID_H_
#define FORMATIONADELHEID_H_
namespace VioletVreath {

/**
 * 敵機アーデルハイド用フォーメーション基底 .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationAdelheid : public GgafLib::DepositoryFormation {

public:
    enum {
        PROG_INIT  ,
        PROG_ENTRY ,
        PROG_FROMATION_MOVE1,
        PROG_FROMATION_MOVE2,
        PROG_FROMATION_MOVE3,
        PROG_FROMATION_MOVE4,
        PROG_FROMATION_MOVE5,
        PROG_LEAVE ,
    };


    /** アーデルハイド借り入れ元Depository資源への接続 */
    DepositoryConnection* pConnection_AdelheidDepo_;
    /** アーデルハイドの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pConnection_ShotDepo_;
    /** 始点・終点の座標計算のためのダミー */
    EnemyAdelheid* pDummy_;

    /** 始点のパリサナ */
    EnemyPalisana* pPalisana_start;
    /** 終点のパリサナ */
    EnemyPalisana* pPalisana_goal;

    /** 編隊数(RANK変動) */
    int rr_num_formation_;
    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame rr_interval_frames_;
    /** 編隊メンバーの初期移動速度(RANK変動) */
    velo rr_mv_velo_;
    /** 編隊メンバー全体の現在の移動速度 */
    velo mv_velo_member_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     */
    FormationAdelheid(const char* prm_name) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpAdelheid(EnemyAdelheid* pEnemyAdelheid) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;
    /**
     * スプライン情報を取得。
     * 下位で実装して下さい。
     * @return
     */
    virtual GgafLib::SplineManufacture* getSplManuf() = 0;

    virtual void onSayonaraAll() override;

    virtual ~FormationAdelheid();
};

}
#endif /*FORMATIONADELHEID_H_*/
