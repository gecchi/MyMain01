#ifndef FORMATIONPALLAS002_H_
#define FORMATIONPALLAS002_H_
namespace MyStg2nd {

/**
 * 敵機イリス用フォーメーションその１ .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas002 : public GgafDx9Core::GgafDx9FormationActor {
    /** イリスの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon;
    /** スプライン定義資源への接続 */
    GgafDx9LibStg::SplineManufactureConnection* _pSplManufCon;
public:
    /** 編隊数(RANK変動) */
    int _num_Pallas;
    /** イリスの配列(RANK変動) */
    EnemyPallas** _papPallas;
    /** 編隊間隔フレーム(RANK変動) */
    frame _interval_frames;
    /** 移動速度(RANK変動) */
    velo _mv_velo;

    FormationPallas002(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override {
    }
    virtual void onActive() override;
    virtual ~FormationPallas002();
};

}
#endif /*FORMATIONPALLAS002_H_*/
