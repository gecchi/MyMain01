#ifndef ENEMYOMULUS_H_
#define ENEMYOMULUS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機オムルス .
 * スクランブルハッチ。
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyOmulus : public VvEnemyActor<GgafLib::DefaultMassMorphMeshActor> {
private:
//    /** [r]次回ハッチが開くフレーム(内部計算用) */
//    frame frame_of_moment_nextopen_;
//    /** [r]次回ハッチが閉じるフレーム(内部計算用) */
//    frame frame_of_moment_nextclose_;
public:
    /** [r]状況 */
    bool is_open_hatch_;
    /** [r/w]ハッチが開いているフレーム間隔 */
    frame frame_of_open_interval_;
    /** [r/w]ハッチが閉じていているフレーム間隔 */
    frame frame_of_close_interval_;
    /** [r/w]ハッチ開＞閉 及び、閉＞開 のモーフアニメーションフレーム数 */
    frame frame_of_morph_interval_;

    /** [r/w]ハッチから発射されるアクターをメンバーに持つデポジトリ */
    GgafCore::ActorDepository* pDepo_Fired_;
    DepositoryConnection* pConn_depo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOmulus(const char* prm_name);

    /**
     * オムルスモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * オムルスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * オムルスがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * オムルスの振る舞い .
     */
    void processBehavior() override;
    void processChangeGeoFinal() override;
    /**
     * オムルスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * オムルスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyOmulus();
};

}
#endif /*ENEMYOMULUS_H_*/

