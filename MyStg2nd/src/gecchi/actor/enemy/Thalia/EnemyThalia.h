#ifndef ENEMYTHALIA_H_
#define ENEMYTHALIA_H_

#define THALIA_SCENE_PROG_MOVE  1
#define THALIA_SCENE_PROG_TURN_OPEN  2
#define THALIA_SCENE_PROG_FIRE_BEGIN  3
#define THALIA_SCENE_PROG_IN_FIRE 4
#define THALIA_SCENE_PROG_CLOSE 5

namespace MyStg2nd {



/**
 * 敵機タリア .
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
//class EnemyThalia : public GgafDx9LibStg::DefaultMorphMeshActor {
class EnemyThalia : public GgafDx9LibStg::CubeMapMorphMeshActor {
    /** 移動スプラインプログラム */
    GgafDx9Core::GgafDx9SplineProgram* _pSplineProgram;
    /** 弾ストック */
    GgafCore::GgafActorDispatcher* _pDispatcher_Shot;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDispatcher* _pDispatcher_ShotEffect;
public:
    /** 行動パターン番号 */
    int _iMovePatternNo;

    velo _veloTopMv;

    GgafDx9LibStg::LaserChipDispatcher* _pLaserChipDispatcher;
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyThalia(const char* prm_name);

    void onCreateModel() override;

    /**
     * タリアの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * タリアがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * タリアの振る舞い .
     */
    void processBehavior() override;

    /**
     * タリアの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * タリアの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 発射弾Dispatcher設定 .
     * initialize() までに設定して下さい。
     * @param prm_pDispatcher
     */
    void setDispatcher_Shot(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_Shot = prm_pDispatcher;
    }

    /**
     * スプライン移動設定 .
     * initialize() までに設定して下さい。
     * @param prm_pSplineProgram
     */
    void setSplineProgram(GgafDx9Core::GgafDx9SplineProgram* prm_pSplineProgram) {
        _pSplineProgram = prm_pSplineProgram;
    }

    /**
     * ショット発射効果エフェクト設定 .
     * @param prm_pDispatcher
     */
    void setDispatcher_ShotEffect(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_ShotEffect = prm_pDispatcher;
    }

    virtual ~EnemyThalia();
};

}
#endif /*ENEMYTHALIA_H_*/

