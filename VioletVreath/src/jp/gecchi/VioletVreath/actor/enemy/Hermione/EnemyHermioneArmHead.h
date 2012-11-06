#ifndef ENEMYHERMIONEARMHEAD_H_
#define ENEMYHERMIONEARMHEAD_H_
namespace VioletVreath {

/**
 * 敵機ヘルミオネの触手の胴体 .
 * グラの触手に挑戦ッッ！！！
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyHermioneArmHead : public GgafLib::DefaultMeshSetActor {
public:
    enum {
        PROG_INIT         = 1,
        PROG_NOTHING,
        PROG_AIMING,

    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    angvelo aim_ang_velo_;
    angle aim_movable_limit_ang_;

    /** [r/w]ハッチから発射されるアクターをメンバーに持つデポジトリ */
    DepositoryConnection* pDpcon_;
    GgafCore::GgafActorDepository* pDepo_Fired_;


    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyHermioneArmHead(const char* prm_name);

    /**
     * ロムルスモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * ロムルスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ロムルスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ロムルスの振る舞い .
     */
    void processBehavior() override;
    /**
     * ロムルスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ロムルスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    void config(angle prm_aim_movable_limit_ang,
                frame prm_aim_ang_velo) {
        aim_movable_limit_ang_ = prm_aim_movable_limit_ang;
        aim_ang_velo_ = prm_aim_ang_velo;
    }


    void execAim();
    virtual ~EnemyHermioneArmHead();
};

}
#endif /*ENEMYHERMIONEARMHEAD_H_*/

