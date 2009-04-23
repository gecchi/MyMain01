#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

/**
 * アストラエア .
 */
class EnemyAstraea : public DefaultMeshEnemyActor {

private:

public:
    /** 弾ストック */
    GgafDx9LibStg::RotationActor* _pRotEnemyMeshShots001;
    /** RotationActorをコンストラクタで生成したか否か */
    bool _createRotationActor;

    int _X_turn; // 折り返すX座標
    int _Y_turn; // 折り返すY座標
    int _Z_turn; // 折り返すZ座標
    int _veloBegin;
    int _incZ;

    int _iMovePatternNo;

    /**
     * コンストラクタ
     * @param prm_name オブジェクト名
     * @param prm_model モデル名
     */
    EnemyAstraea(const char* prm_name);

    /**
     * コンストラクタ
     * @param prm_name オブジェクト
     * @param prm_model モデル
     * @param prm_pRotEnemyMeshShots001 発射弾ストックのローテーションアクター
     * @return
     */
    EnemyAstraea(const char* prm_name, GgafDx9LibStg::RotationActor* prm_pRotEnemyMeshShots001);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    bool isOffScreen();

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

