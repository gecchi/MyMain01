#ifndef FORMATIONJUNO001_H_
#define FORMATIONJUNO001_H_
namespace MyStg2nd {

#define NUM_JUNO_FORMATION001 20
/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * ���g�͏o���|�C���g�̒��S
 */
class FormationJuno001 : public GgafDx9LibStg::FormationActor {

    EnemyJuno* _pEnemyJuno[NUM_JUNO_FORMATION001];
public:
    /** �o���͈͕�BOX */
    int _X1_app, _Y1_app, _Z1_app, _X2_app, _Y2_app, _Z2_app;
    /** �S�́i�o���͈͂�Juno�̈ړ��������� */
    angle _incX, _incY, _incZ;
    /** �S�̂�X */
    static int _X_FormationWhole;
    /** �S�̂�X���� */
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
