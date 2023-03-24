#ifndef ENEMYEMUS_H_
#define ENEMYEMUS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機エムス .
 * レーザーハッチ。
 * @version 1.00
 * @since 2012/10/22
 * @author Masatoshi Tsuge
 */
class EnemyEmus : public VvEnemyActor<GgafLib::DefaultMassMorphMeshActor> {

public:
    /** [r]状況 */
    bool is_open_hatch_;
    /** [r/w]ハッチが開いているフレーム間隔 */
    frame frame_of_open_interval_;
    /** [r/w]ハッチが閉じていているフレーム間隔 */
    frame frame_of_close_interval_;
    /** [r/w]ハッチ開＞閉 及び、閉＞開 のモーフアニメーションフレーム数 */
    frame frame_of_morph_interval_;

//    /** [r]レーザーセットのストアー(レーザーチップのデポジトリのデポジトリ) */
//    GgafCore::ActorDepositoryStore* pDepoStore_laser_set;
//    /** [r]デポジトリマネージャーへの接続 */
//    DepositoryConnection* pConn_pDepoStore_laser_set;
    /** [r]レーザーセット(レーザーチップのデポジトリ) */
    GgafCore::ActorDepository* pDepo_;

    frame ini_wait_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyEmus(const char* prm_name);

    /**
     * エムスモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * エムスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エムスがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エムスの振る舞い .
     */
    void processBehavior() override;
    void processChangeGeoFinal() override;
    /**
     * エムスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エムスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyEmus();
};

}
#endif /*ENEMYEMUS_H_*/

