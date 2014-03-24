#ifndef FORMATIONGERIA_H_
#define FORMATIONGERIA_H_
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * ���g�͏o���|�C���g�̒��S
 */
class FormationGeria : public GgafLib::DefaultGeometricActor {
    /** �Q���A�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_EnemyGeria_;

public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** �o���͈͕�BOX */
    int X1_app_, Y1_app_, Z1_app_, X2_app_, Y2_app_, Z2_app_;
    int frame_app_interval_;

public:
    /**
     * �R���X�g���N�^ .
     * Geria�t�H�[���[�V�������`���܂��B
     * @param prm_name           �t�H�[���[�V�������i�f�o�b�O�p�j
     * @param prm_X1_app         Geria�o���͈�AAB(�����s�����́FAxis-Aligned Box)�̍����OX���W�i���S����̃I�t�Z�b�g�����[�J�����W�j
     * @param prm_Y1_app         Geria�o���͈�AAB�̍����OY���W�i���[�J�����W�j
     * @param prm_Z1_app         Geria�o���͈�AAB�̍����OZ���W�i���[�J�����W�j
     * @param prm_X2_app         Geria�o���͈�AAB�̉E����X���W�i���[�J�����W�j
     * @param prm_Y2_app         Geria�o���͈�AAB�̉E����Y���W�i���[�J�����W�j
     * @param prm_Z2_app         Geria�o���͈�AAB�̉E����Z���W�i���[�J�����W�j
     * @param prm_x              Geria�o���͈�AAB�̒��SX���W�i��΍��W�j
     * @param prm_y              Geria�o���͈�AAB�̒��SY���W�i��΍��W�j
     * @param prm_z              Geria�o���͈�AAB�̒��SZ���W�i��΍��W�j
     * @param prm_veloMv_App     Geria�o���͈�AAB�S�̂̈ړ����x
     * @param prm_angRzMv_AppBox Geria�o���͈�AAB�S�̂̈ړ����p��Z����]�p
     * @param prm_angRyMv_AppBox Geria�o���͈�AAB�S�̂̈ړ����p��Y����]�p
     * @param prm_veloMv_Geria    �eGeria�̈ړ����x�����l
     * @param prm_angRzMv_GeriaMv �eGeria�̈ړ����p��Z����]�p�����l
     * @param prm_angRyMv_GeriaMv �eGeria�̈ړ����p��Y����]�p�����l
     * @param prm_nGeriaStock     Geria�̃X�g�b�N��(�o�b�t�@��)
     * @param prm_frame_app_interval Geria�̏o���Ԋu
     * @return
     */
    FormationGeria(const char* prm_name,
            int prm_X1_app, int prm_Y1_app, int prm_Z1_app,
            int prm_X2_app, int prm_Y2_app, int prm_Z2_app,
            int prm_x, int prm_y, int prm_z,
            velo prm_veloMv_App,
            angle prm_angRzMv_AppBox, angle prm_angRyMv_AppBox,
            velo prm_veloMv_Geria,
            angle prm_angRzMv_GeriaMv, angle prm_angRyMv_GeriaMv,
            int prm_nGeriaStock,
            int prm_frame_app_interval);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~FormationGeria();
};

}
#endif /*FORMATIONGERIA_H_*/