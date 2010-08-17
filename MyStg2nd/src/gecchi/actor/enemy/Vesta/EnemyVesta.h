#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace MyStg2nd {

/**
 * ヴェスタ .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyVesta : public GgafDx9LibStg::DefaultMorphMeshActor {
private:
    /** [r]次回ハッチが開くフレーム */
    frame _frame_of_moment_nextopen;
    /** [r]次回ハッチが閉じるフレーム */
    frame _frame_of_moment_nextclose;
public:
    /** [r]行動パターン番号 */
    int _iMovePatternNo;
    /** [r]状況 */
    bool _is_open_hatch;
    /** [r/w]ハッチが開いているフレーム間隔 */
    frame _frame_of_open_interval;
    /** [r/w]ハッチが閉じていているフレーム間隔 */
    frame _frame_of_close_interval;
    /** [r/w]ハッチ開＞閉 或いは、閉＞開 のモーフアニメーションフレーム数 */
    frame _frame_of_morph_interval;
    /** [r/w]ハッチの土台となってるアクター */

    /** [r/w]ハッチから発射されるアクターをメンバーに持つディスパッチャー */
    GgafCore::GgafActorDispatcher* _pDispatcher_Fired;
    DispatcherConnection* _pDpcon;

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

