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
    DepositoryConnection* _pDepoCon_Massalia;
    /** マッサリア断片借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon_Fragment;
    /** マッサリア断片の断片借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon_Fragment2;
    /** マッサリア断片の断片借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon_Fragment3;

    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame _R_interval_frames;
    /** 編隊メンバーの初期移動速度(RANK変動) */
    velo _R_mv_velo;

    /**
     * コンストラクタ .
     * @param prm_name
     */
    FormationMassalia(const char* prm_name);

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

//    virtual void processOnActiveMassalia(EnemyMassalia* pEnemyMassalia, int col) = 0;

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationMassalia();
};

}
#endif /*FORMATIONEUNOMIA_H_*/
