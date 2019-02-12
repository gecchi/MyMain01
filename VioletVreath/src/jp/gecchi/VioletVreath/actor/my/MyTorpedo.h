#ifndef MYTORPEDO_H_
#define MYTORPEDO_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"


#define MyTorpedo_IN_FIRE 1
#define MyTorpedo_RELEASE 2
namespace VioletVreath {

/**
 * ���� .
 * �I�v�V�������ێ����Ă��郍�b�N�I���̓G�߂����Ĕ��ł䂫�܂��B
 * @version 1.00
 * @since 2010/09/21
 * @author Masatoshi Tsuge
 */
class MyTorpedo : public GgafLib::DefaultMeshSetActor {

public:
    /** [r]�e�A�N�^�[�ƂȂ鋛���R�����[���[ */
    MyTorpedoController* pTorpedoCtrler_;
    /** [r]�����̈ړ��O�ՃG�t�F�N�g�̐� */
    int length_TailEffect_;
    /** [r]�����̈ړ��O�ՃG�t�F�N�g�̃f�|�W�g�� */
    GgafLib::LaserChipDepository* pTailEffectDepository_;
    /** [r]�������ˎ��̍��W */
    int begin_x_,begin_y_,begin_z_;
    /** [r]���B�ڕW�̃A�N�^�[�Bnullptr�̏ꍇ�͎��@�O���̃Q�[���̈拫�E�_��ڕW�Ƃ���d�g�� */
    GgafDx::GeometricActor* pTarget_;

    int move_section_;

    angle trz_,try_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pTorpedoController �e�A�N�^�[�ƂȂ鋛���R�����[���[ .
     * @return
     */
    MyTorpedo(const char* prm_name, MyTorpedoController* prm_pTorpedoController);

    void onCreateModel() override {
    }

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~MyTorpedo();
};

}
#endif /*MYTORPEDO*/

