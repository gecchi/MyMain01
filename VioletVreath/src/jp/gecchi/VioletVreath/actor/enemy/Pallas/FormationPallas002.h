#ifndef FORMATIONPALLAS002_H_
#define FORMATIONPALLAS002_H_
namespace VioletVreath {

/**
 * 敵機イリス用フォーメーションその１ .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas002 : public GgafLib::TreeFormation {
    /** イリスの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoCon_;
    /** スプライン定義資源への接続 */
    GgafLib::SplineManufactureConnection* pSplManufCon_;

public:
    /** 編隊数(RANK変動) */
    int num_Pallas_;
    /** イリスの配列(RANK変動) */
    EnemyPallas** papPallas_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    /** 移動速度(RANK変動) */
    velo velo_mv_;

public:
    FormationPallas002(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override {
    }
    virtual void onActive() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationPallas002();
};

}
#endif /*FORMATIONPALLAS002_H_*/
