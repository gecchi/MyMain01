#ifndef ENEMYEMUS_H_
#define ENEMYEMUS_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機エムス .
 * レーザーハッチ。
 * @version 1.00
 * @since 2012/10/22
 * @author Masatoshi Tsuge
 */
class EnemyEmus : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT       ,
        PROG_HATCH_CLOSE,
        PROG_HATCH_OPEN ,
        PROG_FIRE       ,
        PROG_NOTHING    ,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** [r]状況 */
    bool is_open_hatch_;
    /** [r/w]ハッチが開いているフレーム間隔 */
    frame frame_of_open_interval_;
    /** [r/w]ハッチが閉じていているフレーム間隔 */
    frame frame_of_close_interval_;
    /** [r/w]ハッチ開＞閉 及び、閉＞開 のモーフアニメーションフレーム数 */
    frame frame_of_morph_interval_;

    /** [r]レーザーセットのストアー(レーザーチップのデポジトリのデポジトリ) */
    GgafCore::GgafActorDepositoryStore* pLaserChipDepoStore_;
    /** [r]デポジトリマネージャーへの接続 */
    DepositoryConnection* pConn_LaserChipDepoStore_;
    /** [r]レーザーセット(レーザーチップのデポジトリ) */
    GgafLib::LaserChipDepository* pLaserChipDepo_;

    bool is_firing_;

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
     * エムスのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エムスの振る舞い .
     */
    void processBehavior() override;
    /**
     * エムスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エムスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyEmus();
};

}
#endif /*ENEMYEMUS_H_*/

