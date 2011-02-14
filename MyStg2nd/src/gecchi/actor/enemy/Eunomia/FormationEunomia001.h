#ifndef FORMATIONEUNOMIA001_H_
#define FORMATIONEUNOMIA001_H_
namespace MyStg2nd {

/**
 * 敵機エウノミア用フォーメーションその１ .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia001 : public GgafDx9Core::GgafDx9FormationActor {

public:
    /** エウノミアの発射弾の借り入れ元Dispatcher資源への接続 */
    DispatcherConnection* _pDispatcherCon;
    /** スプライン定義資源への接続 */
    SplineConnection** _papSplineCon;
    /** 編隊列数(RANK変動) */
    int _num_formation_col;
    /** １列の編隊数(RANK変動) */
    int _num_formation_row;
    /** エウノミアの2次元配列(RANK変動) */
    EnemyEunomia*** _papapEunomia;
    /** 編隊間隔フレーム(RANK変動) */
    frame _frame_interval;
    /** 移動速度(RANK変動) */
    velo _mv_velo;

    int _n;

    FormationEunomia001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) = 0;

    virtual void processBehavior() override;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合
     * @param prm_pActorLast 最後に破壊されたアクター
     */
    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) override;

    virtual ~FormationEunomia001();
};

}
#endif /*FORMATIONEUNOMIA001_H_*/
