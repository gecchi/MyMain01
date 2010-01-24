#ifndef FORMATIONIRIS002_H_
#define FORMATIONIRIS002_H_
namespace MyStg2nd {

/**
 * 敵機イリス用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris002 : public GgafDx9LibStg::FormationActor {

    /** 移動用スプライン */
    static GgafDx9Core::GgafDx9Spline3D _sp;

    /** */
    DispatcherConnection* _pDispatcherCon;

public:
    /** 編隊数(RANK変動) */
    int _num_Iris;
    /** イリスの配列(RANK変動) */
    EnemyIris** _papIris;
    /** 編隊間隔フレーム(RANK変動) */
    DWORD _frame_interval;
    /** 移動速度(RANK変動) */
    velo _move_velocity;

    FormationIris002(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationIris002();
};

}
#endif /*FORMATIONIRIS002_H_*/
