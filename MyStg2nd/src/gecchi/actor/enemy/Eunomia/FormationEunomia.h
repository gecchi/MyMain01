#ifndef FORMATIONEUNOMIA_H_
#define FORMATIONEUNOMIA_H_
namespace MyStg2nd {

/**
 * 敵機エウノミア用フォーメーション基底 .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia : public GgafDx9LibStg::FormationActor {

public:
    /** エウノミア借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon_Eunomia;

    /** エウノミアの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon_shot;
    /** スプライン定義資源への接続 */
//    GgafDx9LibStg::SplineSourceConnection* _pSplSrcCon;
    GgafDx9LibStg::SplineManufactureConnection** _papSplManufCon;
    /** 編隊列数(RANK変動) */
    int _num_formation_col;
    /** １列の編隊数(RANK変動) */
    int _num_formation_row;
//    /** エウノミアの2次元配列(RANK変動) */
//    EnemyEunomia*** _papapEunomia;
    /** 編隊間隔フレーム(RANK変動) */
    frame _interval_frames;
    /** 移動速度(RANK変動) */
    velo _mv_velo;

    int _n;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_col            編隊列数 ( >= 1)
     * @param prm_row            １列の編隊数 ( >= 1)
     * @param prm_interval_frames エウノミアの間隔(frame) ( >= 1)
     * @param prm_mv_velo        速度
     * @param prm_spl_id         スプライン定義ファイルプレフィクス
     *                           "FormationEunomia001_0.spl" の "FormationEunomia001" を設定
     * @return
     */
    FormationEunomia(const char* prm_name, int   prm_col,
                                           int   prm_row,
                                           frame prm_interval_frames,
                                           velo  prm_mv_velo,
                                           const char* prm_spl_id) ;

    virtual void initialize() override;

    virtual void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) = 0;

    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) override {
    }

    virtual void processBehavior() override;

    virtual ~FormationEunomia();
};

}
#endif /*FORMATIONEUNOMIA_H_*/
