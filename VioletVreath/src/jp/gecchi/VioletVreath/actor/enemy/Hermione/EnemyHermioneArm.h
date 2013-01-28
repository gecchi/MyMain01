#ifndef ENEMYHERMIONEARM_H_
#define ENEMYHERMIONEARM_H_
namespace VioletVreath {

/**
 * 敵機ヘルミオネの触手基底 .
 * @version 1.00
 * @since 2012/11/06
 * @author Masatoshi Tsuge
 */
class EnemyHermioneArm : public GgafLib::DefaultMeshSetActor {
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

    angvelo aiming_ang_velo_;
    angle aiming_movable_limit_ang_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyHermioneArm(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    /**
     * 初期処理（インスタンス生成後保証）
     */
    virtual void initialize() override;

    /**
     * がアクティブになった瞬間の処理 .
     */
    virtual void onActive() override;

    /**
     * 振る舞い .
     */
    virtual void processBehavior() override;
    /**
     * 振る舞い後の判定処理 .
     */
    virtual void processJudgement() override;


    virtual void onInactive() override;

    /**
     * 腕の節の設定 .
     * @param prm_aiming_movable_limit_ang エイミング時関節可動角度制限範囲(10 を指定で -10 ～ +10 と言う設定になる)
     * @param prm_aiming_ang_velo エイミング時関節可動角速度
     */
    virtual void config(angle prm_aiming_movable_limit_ang,
                        frame prm_aiming_ang_velo) {
        aiming_movable_limit_ang_ = prm_aiming_movable_limit_ang;
        aiming_ang_velo_ = prm_aiming_ang_velo;
    }
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~EnemyHermioneArm();
};

}
#endif /*ENEMYHERMIONEARM_H_*/

