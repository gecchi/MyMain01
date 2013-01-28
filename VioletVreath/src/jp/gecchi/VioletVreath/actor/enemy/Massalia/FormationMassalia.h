#ifndef FORMATIONMASSALIA_H_
#define FORMATIONMASSALIA_H_
namespace VioletVreath {

/**
 * マッサリア群 .
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class FormationMassalia : public GgafLib::DepositoryFormation {

public:
    /** マッサリア借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoCon_Massalia_;
    /** マッサリア断片借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoCon_Fragment_;
    /** マッサリア断片の断片借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoCon_Fragment_2_;
    /** マッサリア断片の断片借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoCon_Fragment_3_;

    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame R_interval_frames_;
    /** 編隊メンバーの初期移動速度(RANK変動) */
    velo R_mv_velo_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     */
    FormationMassalia(const char* prm_name);

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

//    virtual void processOnActiveMassalia(EnemyMassalia* pEnemyMassalia, int col) = 0;

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationMassalia();
};

}
#endif /*FORMATIONEUNOMIA_H_*/
