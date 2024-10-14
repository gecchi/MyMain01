#ifndef ENEMYALISANA_H_
#define ENEMYALISANA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機アリサナ .
 * Delheidのハッチ。FormationDelheidが管理する。
 * @version 1.00
 * @since 2014/04/16
 * @author Masatoshi Tsuge
 */
class EnemyAlisana : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    /** [r/w]ハッチ開＞閉 及び、閉＞開 のモーフアニメーションフレーム数 */
    frame frame_of_morph_interval_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAlisana(const char* prm_name);

    /**
     * アリサナモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;

    /**
     * アリサナの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アリサナがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アリサナの振る舞い .
     */
    void processBehavior() override;
    /**
     * アリサナの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アリサナの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    void acitve_open(frame prm_delay = 1);

    bool isOpenDone();

    void close_sayonara();

    virtual ~EnemyAlisana();
};

}
#endif /*ENEMYALISANA_H_*/

