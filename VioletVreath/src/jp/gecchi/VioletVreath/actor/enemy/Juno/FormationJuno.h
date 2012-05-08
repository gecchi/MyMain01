#ifndef FORMATIONJUNO_H_
#define FORMATIONJUNO_H_
namespace VioletVreath {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * ���g�͏o���|�C���g�̒��S
 */
class FormationJuno : public GgafLib::DefaultGeometricActor {
    /** �W���m�[�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_EnemyJuno_;
    DepositoryConnection* pDepoCon_;

public:
    /** �o���͈͕�BOX */
    int X1_app_, Y1_app_, Z1_app_, X2_app_, Y2_app_, Z2_app_;
    int frame_app_interval_;

    /**
     * �R���X�g���N�^ .
     * Juno�t�H�[���[�V�������`���܂��B
     * @param prm_name           �t�H�[���[�V�������i�f�o�b�O�p�j
     * @param prm_X1_app         Juno�o���͈�AAB(�����s�����́FAxis-Aligned Box)�̍����OX���W�i���S����̃I�t�Z�b�g�����[�J�����W�j
     * @param prm_Y1_app         Juno�o���͈�AAB�̍����OY���W�i���[�J�����W�j
     * @param prm_Z1_app         Juno�o���͈�AAB�̍����OZ���W�i���[�J�����W�j
     * @param prm_X2_app         Juno�o���͈�AAB�̉E����X���W�i���[�J�����W�j
     * @param prm_Y2_app         Juno�o���͈�AAB�̉E����Y���W�i���[�J�����W�j
     * @param prm_Z2_app         Juno�o���͈�AAB�̉E����Z���W�i���[�J�����W�j
     * @param prm_X              Juno�o���͈�AAB�̒��SX���W�i��΍��W�j
     * @param prm_Y              Juno�o���͈�AAB�̒��SY���W�i��΍��W�j
     * @param prm_Z              Juno�o���͈�AAB�̒��SZ���W�i��΍��W�j
     * @param prm_veloMv_App     Juno�o���͈�AAB�S�̂̈ړ����x
     * @param prm_angRzMv_AppBox Juno�o���͈�AAB�S�̂̈ړ����p��Z����]�p
     * @param prm_angRyMv_AppBox Juno�o���͈�AAB�S�̂̈ړ����p��Y����]�p
     * @param prm_veloMv_Juno    �eJuno�̈ړ����x�����l
     * @param prm_angRzMv_JunoMv �eJuno�̈ړ����p��Z����]�p�����l
     * @param prm_angRyMv_JunoMv �eJuno�̈ړ����p��Y����]�p�����l
     * @param prm_nJunoStock     Juno�̃X�g�b�N��(�o�b�t�@��)
     * @param prm_frame_app_interval Juno�̏o���Ԋu
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

    virtual void processBehavior() override;

    virtual ~FormationJuno();
};

}
#endif /*FORMATIONJUNO_H_*/
