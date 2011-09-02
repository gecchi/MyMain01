#ifndef FORMATIONIRIS001_H_
#define FORMATIONIRIS001_H_
namespace MyStg2nd {

/**
 * 敵機イリス用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris001 : public GgafDx9LibStg::FormationActor {
    /** イリスの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* _pDepoCon;
    /** スプライン定義資源への接続 */
    Spline3DConnection* _pSplCon;
public:
    /** 編隊数(RANK変動) */
    int _num_Iris;
    /** イリスの配列(RANK変動) */
    EnemyIris** _papIris;
    /** 編隊間隔フレーム(RANK変動) */
    frame _interval_frames;
    /** 移動速度(RANK変動) */
    velo _mv_velo;

    FormationIris001(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual ~FormationIris001();
};

}
#endif /*FORMATIONIRIS001_H_*/
