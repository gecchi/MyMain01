#ifndef FORMATIONJUNO001_H_
#define FORMATIONJUNO001_H_
namespace MyStg2nd {

#define NUM_JUNO_FORMATION001 20
/**
 * フォーメーションアクタークラス .
 * 自身は出現ポイントの中心
 */
class FormationJuno001 : public GgafDx9LibStg::FormationActor {

    EnemyJuno* _pEnemyJuno[NUM_JUNO_FORMATION001];
public:
    /** 出現範囲幅BOX */
    int _X1_app, _Y1_app, _Z1_app, _X2_app, _Y2_app, _Z2_app;
    /** 全体（出現範囲とJunoの移動方向差分 */
    angle _incX, _incY, _incZ;
    /** 全体のX */
    static int _X_FormationWhole;
    /** 全体のX増分 */
    static int _incX;


    FormationJuno001(const char* prm_name);

    void setInitializeProperty(
            prm_X1_app, prm_Y1_app, prm_Z1_app, prm_X2_app, prm_Y2_app, prm_Z2_app,
            prm_X, prm_Y, prm_Z,
            prm_veloMv_App,
            prm_angRzMv_AppBox, prm_angRyMv_AppBox,
            prm_veloMv_Juno,
            prm_angRzMv_JunoMv, prm_angRyMv_Juno,
            prm_frame_app_interval

    virtual void initialize() override;

    void processBehavior() override;

    virtual ~FormationJuno001();
};

}
#endif /*FORMATIONJUNO001_H_*/
