#ifndef FORMATIONTHALIA_H_
#define FORMATIONTHALIA_H_
namespace MyStg2nd {

/**
 * 敵機タリア用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationThalia : public GgafDx9Core::GgafDx9FormationActor {
public:
    /** 編隊数(RANK変動) */
    int _num_Thalia;
    /** タリアの配列(RANK変動) */
    EnemyThalia** _papThalia;
    /** 編隊間隔フレーム(RANK変動) */
    frame _interval_frames;
    /** 移動速度(RANK変動) */
    velo _mv_velo;

    DepositoryConnection* _pDpcon;

    FormationThalia(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;


    virtual ~FormationThalia();
};

}
#endif /*FORMATIONTHALIA_H_*/
