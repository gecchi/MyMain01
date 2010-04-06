#ifndef FORMATIONJUNO_H_
#define FORMATIONJUNO_H_
namespace MyStg2nd {

/**
 * フォーメーションアクタークラス .
 * 自身は出現ポイントの中心
 */
class FormationJuno : public GgafDx9LibStg::FormationActor {
    /** ジュノーストック */
    GgafCore::GgafActorDispatcher* _pDispatcher_EnemyJuno;
    CmRandomNumberGenerator* _pRndGen;
    DispatcherConnection* _pDispatcherCon;

public:
    /** 出現範囲幅BOX */
    int _X1_app, _Y1_app, _Z1_app, _X2_app, _Y2_app, _Z2_app;
    int _frame_app_interval;

    /**
     *
     * @param prm_name
     * @param prm_X1_app
     * @param prm_Y1_app
     * @param prm_Z1_app
     * @param prm_X2_app
     * @param prm_Y2_app
     * @param prm_Z2_app
     * @param prm_X
     * @param prm_Y
     * @param prm_Z
     * @param prm_veloMv_App
     * @param prm_angRzMv_AppBox
     * @param prm_angRyMv_AppBox
     * @param prm_veloMv_Juno
     * @param prm_angRzMv_JunoMv
     * @param prm_angRyMv_Juno
     * @param prm_nJunoStock
     * @param prm_frame_app_interval
     * @return
     */
    FormationJuno(const char* prm_name,
            int prm_X1_app, int prm_Y1_app, int prm_Z1_app,
            int prm_X2_app, int prm_Y2_app, int prm_Z2_app,
            int prm_X, int prm_Y, int prm_Z,
            velo prm_veloMv_App,
            angle prm_angRzMv_AppBox, angle prm_angRyMv_AppBox,
            velo prm_veloMv_Juno,
            angle prm_angRzMv_JunoMv, angle prm_angRyMv_JunoMv,
            int prm_nJunoStock,
            int prm_frame_app_interval);

    virtual void initialize() override;

    void processBehavior() override;

    virtual ~FormationJuno();
};

}
#endif /*FORMATIONJUNO_H_*/
