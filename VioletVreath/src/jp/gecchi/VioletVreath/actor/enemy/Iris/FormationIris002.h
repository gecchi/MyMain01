#ifndef FORMATIONIRIS002_H_
#define FORMATIONIRIS002_H_
namespace VioletVreath {

/**
 * 敵機イリス用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris002 : public GgafLib::TreeFormation {

    DepositoryConnection* pDepoCon_;
    SplineLineConnection* pSplLineCon_;
public:
    /** 編隊数(RANK変動) */
    int num_Iris_;
    /** イリスの配列(RANK変動) */
    EnemyIris** papIris_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    /** 移動速度(RANK変動) */
    velo velo_mv_;

    FormationIris002(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationIris002();
};

}
#endif /*FORMATIONIRIS002_H_*/
