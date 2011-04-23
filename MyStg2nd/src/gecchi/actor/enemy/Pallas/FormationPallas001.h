#ifndef FORMATIONPALLAS001_H_
#define FORMATIONPALLAS001_H_
namespace MyStg2nd {

/**
 * 敵機パラス用フォーメーションその１ .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas001 : public GgafDx9Core::GgafDx9FormationActor {

public:
    /** パラスの発射弾の借り入れ元Dispatcher資源への接続 */
    DispatcherConnection* _pDispatcherCon;
    /** スプライン定義資源への接続 */
    SplineConnection* _pSplineCon;
    /** 編隊数(RANK変動) */
    int _num_Pallas;
    /** パラスの配列(RANK変動) */
    EnemyPallas** _papPallas;
    /** 編隊間隔フレーム(RANK変動) */
    frame _interval_frames;
    /** 移動速度(RANK変動) */
    velo _mv_velo;

    FormationPallas001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合
     * @param prm_pActorLast 最後に破壊されたアクター
     */
    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) override;

    virtual ~FormationPallas001();
};

}
#endif /*FORMATIONPALLAS001_H_*/
