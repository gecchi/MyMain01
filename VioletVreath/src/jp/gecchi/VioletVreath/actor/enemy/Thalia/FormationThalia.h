#ifndef FORMATIONTHALIA_H_
#define FORMATIONTHALIA_H_
namespace VioletVreath {

/**
 * 敵機タリア用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationThalia : public GgafLib::TreeFormation {
public:
    /** 編隊数(RANK変動) */
    int num_Thalia_;
    /** タリアの配列(RANK変動) */
    EnemyThalia** papThalia_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    /** 移動速度(RANK変動) */
    velo velo_mv_;

    DepositoryConnection* pDpcon_;

    FormationThalia(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override {
    }

    virtual ~FormationThalia();
};

}
#endif /*FORMATIONTHALIA_H_*/
