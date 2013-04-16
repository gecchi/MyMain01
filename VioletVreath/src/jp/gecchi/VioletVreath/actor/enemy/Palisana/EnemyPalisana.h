#ifndef ENEMYPALISANA_H_
#define ENEMYPALISANA_H_
namespace VioletVreath {

/**
 * 敵機パリサナ .
 * アーデルハイド(EnemyAdelheid)のハッチ。
 * @version 1.00
 * @since 2014/04/16
 * @author Masatoshi Tsuge
 */
class EnemyPalisana : public GgafLib::DefaultMorphMeshActor {
private:
//    /** [r]次回ハッチが開くフレーム(内部計算用) */
//    frame frame_of_moment_nextopen_;
//    /** [r]次回ハッチが閉じるフレーム(内部計算用) */
//    frame frame_of_moment_nextclose_;
public:
    enum {
        PROG_INIT         = 1,
        PROG_ENTRY,
        PROG_HATCH_OPEN,
        PROG_HATCH_CLOSE,
        PROG_LEAVE,
    };
    enum {
        SE_DAMAGED   = 0,
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

    /** [r/w]ハッチから発射されるアクターをメンバーに持つデポジトリ */
    GgafCore::GgafActorDepository* pDepo_Fired_;
    DepositoryConnection* pDepoConnection_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyPalisana(const char* prm_name);

    /**
     * パリサナモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * パリサナの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * パリサナのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * パリサナの振る舞い .
     */
    void processBehavior() override;
    /**
     * パリサナの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * パリサナの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    void acitve_open();

    void close_sayonara();

    virtual ~EnemyPalisana();
};

}
#endif /*ENEMYPALISANA_H_*/

