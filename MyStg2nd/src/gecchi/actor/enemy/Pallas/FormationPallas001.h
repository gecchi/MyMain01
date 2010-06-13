#ifndef FORMATIONPALLAS001_H_
#define FORMATIONPALLAS001_H_
namespace MyStg2nd {

/**
 * 敵機イリス用フォーメーションその１ .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationPallas001 : public GgafDx9LibStg::FormationActor {
    /** イリスの発射弾の借り入れ元Dispatcher資源への接続 */
    DispatcherConnection* _pDispatcherCon;
    /** スプライン定義資源への接続 */
    Spline3DConnection* _pSplineCon;
public:
    /** 編隊数(RANK変動) */
    int _num_Pallas;
    /** イリスの配列(RANK変動) */
    EnemyPallas** _papPallas;
    /** 編隊間隔フレーム(RANK変動) */
    DWORD _frame_interval;
    /** 移動速度(RANK変動) */
    velo _mv_velo;

    FormationPallas001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual ~FormationPallas001();
};

}
#endif /*FORMATIONPALLAS001_H_*/
