#ifndef LASERCHIPDEPOSITORYSTORE_H_
#define LASERCHIPDEPOSITORYSTORE_H_
namespace GgafDx9LibStg {

/**
 * �i���ݖ��g�p�B���ʂ�Depository �łł������B�g�p����ꍇ�� onReset() ������������K�v����j
 * ���[�U�[�`�b�v�f�|�W�g���̃f�|�W�g���B
 * �܂背�[�U�[�`�b�v�f�B�X�p�b�`���g���܂킵�Ǘ��N���X �B
 * new ������ addSubLast ���\�b�h�� LaserChip�C���X�^���X���D���Ȍ��o�^���Ă��������B<BR>
 * new ���� initialize()�܂ŁA���͐����ύX���L���ȃp�����[�^<BR>
 */
class LaserChipDepositoryStore : public GgafCore::GgafActorDepository {
    friend class LaserChip;
public:
    LaserChipDepositoryStore(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * ���[�U�[�`�b�v�f�B�p�b�`���[�̎؂��������݂� .
     * �X�g�b�N�؂�̏ꍇ�� NULL ���Ԃ�B�K���`�F�b�N���邱�ƁB
     * �g���I���� sayonara() ���Ainactivate() �����s���Ă��������B�����I�ɃX�g�b�N�ɖ߂�܂��B
     * @return �؂���ꂵ�����[�U�[�`�b�v�f�B�p�b�`���[�B�؂����ł��Ȃ��ꍇ��NULL
     */
    virtual LaserChipDepository* dispatch() override;

    /**
     * ���[�U�[�`�b�v�f�B�p�b�`���[�X�g�b�N�̒ǉ� .
     * �D���Ȃ����ǉ����ĉ������B
     * �ǉ�����΂���قǋʐ؂ꂪ�����ɂ���
     * @param prm_pDepo_LaserChip ���[�U�[�`�b�v�f�B�p�b�`���[
     */
    void addSubLast(LaserChipDepository* prm_pDepo_LaserChip);

     virtual ~LaserChipDepositoryStore();

};

}
#endif /*LASERCHIPDEPOSITORYSTORE_H_*/
