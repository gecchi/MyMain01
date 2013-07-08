#ifndef FORMATIONDELHEID_H_
#define FORMATIONDELHEID_H_
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * 敵機デルハイド用フォーメーション基底 .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid : public GgafLib::DepositoryFormation {

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


    /** デルハイド借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_DelheidDepo_;
    /** デルハイドの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_ShotDepo_;
    /** 始点・終点の座標計算のためのダミー */
    EnemyDelheid* pDummy_;

    /** 始点のアリサナ */
    EnemyAlisana* pAlisana_start;
    /** 終点のアリサナ */
    EnemyAlisana* pAlisana_goal;

    /** 編隊数(RANK変動) */
    int RV_NumFormation_;
    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame RV_IntervalFrames_;
    /** 編隊メンバーの初期移動速度(RANK変動) */
    velo RV_MvVelo_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     */
    FormationDelheid(const char* prm_name) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpDelheid(EnemyDelheid* pEnemyDelheid) = 0;

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


    static void order1(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);

    static void order2(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);

    static void order3(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);


    virtual ~FormationDelheid();
};

}
#endif /*FORMATIONDELHEID_H_*/
