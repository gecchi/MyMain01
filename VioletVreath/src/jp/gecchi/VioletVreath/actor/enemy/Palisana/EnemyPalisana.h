#ifndef ENEMYPALISANA_H_
#define ENEMYPALISANA_H_
namespace VioletVreath {

/**
 * 敵機パリサナ .
 * Adelheidのハッチ。
 * @version 1.00
 * @since 2014/04/16
 * @author Masatoshi Tsuge
 */
class EnemyPalisana : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT ,
        PROG_ENTRY,
        PROG_HATCH_OPEN,
        PROG_HATCH_OPEN_DONE,
        PROG_HATCH_CLOSE,
        PROG_LEAVE,
    };
    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    enum {
        MPH_HATCH_CLOSE,
        MPH_HATCH_OPEN,
    };

    /** [r/w]ハッチ開＞閉 及び、閉＞開 のモーフアニメーションフレーム数 */
    frame frame_of_morph_interval_;

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

    void acitve_open(frame prm_delay = 1);

    bool isOpenDone();

    void close_sayonara();

    virtual ~EnemyPalisana();
};

}
#endif /*ENEMYPALISANA_H_*/

