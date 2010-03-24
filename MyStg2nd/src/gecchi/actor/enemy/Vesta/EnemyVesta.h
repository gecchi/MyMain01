#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace MyStg2nd {

/**
 * テスト用 .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyVesta : public GgafDx9LibStg::DefaultMorphMeshActor {

public:
    /** 行動パターン番号 */
    int _iMovePatternNo;
    /** 状況 */
    bool _is_open_hatch;
    /** ハッチが開いているフレーム間隔 */
    DWORD _frame_of_open_interval;
    /** ハッチが閉じていているフレーム間隔 */
    DWORD _frame_of_close_interval;
    /** 次回ハッチが開くフレーム */
    DWORD _frame_of_moment_nextopen;
    /** 次回ハッチが閉じるフレーム */
    DWORD _frame_of_moment_nextclose;
    /** ハッチ開閉モーションに費やすフレーム数 */
    DWORD _frame_of_morph_interval;
    /** 土台となってるアクター */
    GgafDx9Core::GgafDx9GeometricActor* _pActor_Foundation;
    /** 発射されるアクターをメンバーに持つディスパッチャー */
    GgafCore::GgafActorDispatcher* _pDispatcher_Fired;
    DispatcherConnection* _pDpcon;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyVesta(const char* prm_name);

    /**
     * たまごモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * たまごの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * たまごのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * たまごの振る舞い .
     */
    void processBehavior() override;

    /**
     * たまごの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * たまごの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyVesta();
};

}
#endif /*ENEMYVESTA_H_*/

