#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace VioletVreath {

/**
 * ヴェスタ .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyVesta : public GgafLib::DefaultMorphMeshActor {
private:
    /** [r]次回ハッチが開くフレーム */
    frame frame_of_moment_nextopen_;
    /** [r]次回ハッチが閉じるフレーム */
    frame frame_of_moment_nextclose_;
public:
    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    /** [r]行動パターン番号 */
    int iMovePatternNo_;
    /** [r]状況 */
    bool is_open_hatch_;
    /** [r/w]ハッチが開いているフレーム間隔 */
    frame frame_of_open_interval_;
    /** [r/w]ハッチが閉じていているフレーム間隔 */
    frame frame_of_close_interval_;
    /** [r/w]ハッチ開＞閉 或いは、閉＞開 のモーフアニメーションフレーム数 */
    frame frame_of_morph_interval_;
    /** [r/w]ハッチの土台となってるアクター */

    /** [r/w]ハッチから発射されるアクターをメンバーに持つデポジトリ */
    GgafCore::GgafActorDepository* pDepo_Fired_;
    DepositoryConnection* pDpcon_;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyVesta(const char* prm_name);

    /**
     * ヴェスタモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * ヴェスタの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ヴェスタのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ヴェスタの振る舞い .
     */
    void processBehavior() override;
    /**
     * ヴェスタの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ヴェスタの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyVesta();
};

}
#endif /*ENEMYVESTA_H_*/

