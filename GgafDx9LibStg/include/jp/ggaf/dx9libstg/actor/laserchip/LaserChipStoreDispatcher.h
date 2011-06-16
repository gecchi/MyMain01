#ifndef LASERCHIPSTOREDISPATCHER_H_
#define LASERCHIPSTOREDISPATCHER_H_
namespace GgafDx9LibStg {

/**
 * �i���ݖ��g�p�B���ʂ�Store �łł������B�g�p����ꍇ�� onReset() ������������K�v����j
 * ���[�U�[�`�b�v�f�B�X�p�b�`���[�̃f�B�X�p�b�`���[�B
 * �܂背�[�U�[�`�b�v�f�B�X�p�b�`���g���܂킵�Ǘ��N���X �B
 * new ������ addSubLast ���\�b�h�� LaserChip�C���X�^���X���D���Ȍ��o�^���Ă��������B<BR>
 * new ���� initialize()�܂ŁA���͐����ύX���L���ȃp�����[�^<BR>
 */
class LaserChipStoreDispatcher : public GgafCore::GgafActorStore {
    friend class LaserChip;
public:
    LaserChipStoreDispatcher(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * ���[�U�[�`�b�v�f�B�p�b�`���[�̎؂��������݂� .
     * �X�g�b�N�؂�̏ꍇ�� NULL ���Ԃ�B�K���`�F�b�N���邱�ƁB
     * �g���I���� sayonara() ���Ainactivate() �����s���Ă��������B�����I�ɃX�g�b�N�ɖ߂�܂��B
     * @return �؂���ꂵ�����[�U�[�`�b�v�f�B�p�b�`���[�B�؂����ł��Ȃ��ꍇ��NULL
     */
    virtual LaserChipStore* dispatch() override;

    /**
     * ���[�U�[�`�b�v�f�B�p�b�`���[�X�g�b�N�̒ǉ� .
     * �D���Ȃ����ǉ����ĉ������B
     * �ǉ�����΂���قǋʐ؂ꂪ�����ɂ���
     * @param prm_pStore_LaserChip ���[�U�[�`�b�v�f�B�p�b�`���[
     */
    void addSubLast(LaserChipStore* prm_pStore_LaserChip);

     virtual ~LaserChipStoreDispatcher();

};

}
#endif /*LASERCHIPSTOREDISPATCHER_H_*/
