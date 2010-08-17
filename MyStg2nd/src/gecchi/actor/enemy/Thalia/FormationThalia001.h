#ifndef FORMATIONTHALIA001_H_
#define FORMATIONTHALIA001_H_
namespace MyStg2nd {

/**
 * 敵機タリア用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationThalia001 : public GgafDx9Core::GgafDx9FormationActor {
    /** タリアの発射弾の借り入れ元Dispatcher資源への接続 */
    DispatcherConnection* _pDispatcherCon;
    /** スプライン定義資源への接続 */
    Spline3DConnection* _pSplineCon;
public:
    /** 編隊数(RANK変動) */
    int _num_Thalia;
    /** タリアの配列(RANK変動) */
    EnemyThalia** _papThalia;
    /** 編隊間隔フレーム(RANK変動) */
    frame _frame_interval;
    /** 移動速度(RANK変動) */
    velo _mv_velo;

    FormationThalia001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual ~FormationThalia001();
};

}
#endif /*FORMATIONTHALIA001_H_*/
