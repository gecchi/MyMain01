#ifndef FORMATIONPALLAS001_H_
#define FORMATIONPALLAS001_H_
namespace VioletVreath {

/**
 * 敵機パラス用フォーメーションその１ .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas001 : public GgafLib::TreeFormation {

public:
    /** パラスの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon;
    /** スプライン定義資源への接続 */
    GgafLib::SplineManufactureConnection* _pSplManufCon;
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

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override;

    virtual ~FormationPallas001();
};

}
#endif /*FORMATIONPALLAS001_H_*/
