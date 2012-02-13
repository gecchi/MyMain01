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
    MyOptionTorpedoController* _pMyOptionTorpedoController;
    /** [r]�����̈ړ��O�ՃG�t�F�N�g�̐� */
    int _length_TailEffect;
    /** [r]�����̈ړ��O�ՃG�t�F�N�g�̃f�|�W�g�� */
    GgafLib::LaserChipDepository* _pTailEffectDepository;
    /** [r]�������ˎ��̍��W */
    int _begin_X,_begin_Y,_begin_Z;
    /** [r]���B�ڕW�̃A�N�^�[�BNULL�̏ꍇ�͎��@�O���̃Q�[���̈拫�E�_��ڕW�Ƃ���d�g�� */
    GgafDxCore::GgafDxGeometricActor* _pTarget;

    int _move_section;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pMyOptionTorpedoController �e�A�N�^�[�ƂȂ鋛���R�����[���[ .
     * @return
     */
    MyTorpedo(const char* prm_name, MyOptionTorpedoController* prm_pMyOptionTorpedoController);

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

