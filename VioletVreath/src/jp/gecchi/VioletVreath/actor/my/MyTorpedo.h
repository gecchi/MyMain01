#ifndef MYTORPEDO_H_
#define MYTORPEDO_H_

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
    MyTorpedoController* pOptionTorpedoCtrler_;
    /** [r]�����̈ړ��O�ՃG�t�F�N�g�̐� */
    int length_TailEffect_;
    /** [r]�����̈ړ��O�ՃG�t�F�N�g�̃f�|�W�g�� */
    GgafLib::LaserChipDepository* pTailEffectDepository_;
    /** [r]�������ˎ��̍��W */
    int begin_X_,begin_Y_,begin_Z_;
    /** [r]���B�ڕW�̃A�N�^�[�Bnullptr�̏ꍇ�͎��@�O���̃Q�[���̈拫�E�_��ڕW�Ƃ���d�g�� */
    GgafDxCore::GgafDxGeometricActor* pTarget_;

    int move_section_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pOptionTorpedoController �e�A�N�^�[�ƂȂ鋛���R�����[���[ .
     * @return
     */
    MyTorpedo(const char* prm_name, MyTorpedoController* prm_pOptionTorpedoController);

    void onCreateModel() override {
    }

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyTorpedo();
};

}
#endif /*MYTORPEDO*/

