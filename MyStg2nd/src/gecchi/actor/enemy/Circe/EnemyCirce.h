#ifndef ENEMYCIRCE_H_
#define ENEMYCIRCE_H_
namespace MyStg2nd {

/**
 * キルケ .
 * @version 1.00
 * @since 2010/03/25
 * @author Masatoshi Tsuge
 */
class EnemyCirce : public GgafDx9LibStg::DefaultMeshActor {

public:
    /** 行動パターン番号 */
    int _iMovePatternNo;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyCirce(const char* prm_name);

    /**
     * キルケモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * キルケの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * キルケのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * キルケの振る舞い .
     */
    void processBehavior() override;


    /**
     * キルケの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * キルケの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyCirce();
};

}
#endif /*ENEMYCIRCE_H_*/

