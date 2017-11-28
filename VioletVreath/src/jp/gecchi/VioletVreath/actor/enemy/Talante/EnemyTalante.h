#ifndef ENEMYTALANTE_H_
#define ENEMYTALANTE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * 敵機タランテ .
 * ハッチ雑魚その１
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyTalante : public GgafLib::DefaultMassMeshActor {

public:
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_shot_;

    /** Y軸揃ったよフラグ */
    bool Y_ok_;
    /** Z軸揃ったよフラグ */
    bool Z_ok_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyTalante(const char* prm_name);

    void onCreateModel() override;

    /**
     * タランテの初期処理（インスタンス生成後保証）
     */
    void initialize() override;


    /**
     * タランテがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * タランテの振る舞い .
     */
    void processBehavior() override;

    /**
     * タランテの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * タランテの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pDepo_shot
     */
    virtual void config(
            GgafCore::GgafActorDepository* prm_pDepo_shot
            );


    virtual ~EnemyTalante();
};

}
#endif /*ENEMYTALANTE_H_*/

