#ifndef ENEMYERMIONEARM_H_
#define ENEMYERMIONEARM_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機エミオネの触手基底 .
 * @version 1.00
 * @since 2012/11/06
 * @author Masatoshi Tsuge
 */
class EnemyErmioneArm : public GgafLib::DefaultMeshSetActor {
public:
    enum {
        PROG_INIT   ,
        PROG_WAITING,
        PROG_NOTHING,
        PROG_AIMING ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    angvelo aiming_ang_velo_;
    angle aiming_movable_limit_ang_;
    frame behave_frames_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyErmioneArm(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

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

    virtual ~EnemyErmioneArm();
};

}
#endif /*ENEMYERMIONEARM_H_*/

