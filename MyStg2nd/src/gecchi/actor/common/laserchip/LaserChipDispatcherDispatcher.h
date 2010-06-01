#ifndef LASERCHIPDISPATCHERDISPATCHER_H_
#define LASERCHIPDISPATCHERDISPATCHER_H_
namespace MyStg2nd {

/**
 * �i���ݖ��g�p�B���ʂ�Dispatcher �łł������j
 * ���[�U�[�`�b�v�f�B�p�b�`���[�g���܂킵�Ǘ��N���X .
 * new ������ addSubLast ���\�b�h�� LaserChip�C���X�^���X���D���Ȍ��o�^���Ă��������B<BR>
 * new ���� initialize()�܂ŁA���͐����ύX���L���ȃp�����[�^<BR>
 */
class LaserChipDispatcherDispatcher : public GgafCore::GgafActorDispatcher {
    friend class LaserChip;
public:
    LaserChipDispatcherDispatcher(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * ���[�U�[�`�b�v�f�B�p�b�`���[�̎؂��������݂� .
     * �X�g�b�N�؂�̏ꍇ�� NULL ���Ԃ�B�K���`�F�b�N���邱�ƁB
     * �g���I���� sayonara() ���Ainactivate() �����s���Ă��������B�����I�ɃX�g�b�N�ɖ߂�܂��B
     * @return �؂���ꂵ�����[�U�[�`�b�v�f�B�p�b�`���[�B�؂����ł��Ȃ��ꍇ��NULL
     */
    virtual LaserChipDispatcher* employ() override;

    /**
     * ���[�U�[�`�b�v�f�B�p�b�`���[�X�g�b�N�̒ǉ� .
     * �D���Ȃ����ǉ����ĉ������B
     * �ǉ�����΂���قǋʐ؂ꂪ�����ɂ���
     * @param prm_pDispatcher_LaserChip ���[�U�[�`�b�v�f�B�p�b�`���[
     */
    void addSubLast(LaserChipDispatcher* prm_pDispatcher_LaserChip);

     virtual ~LaserChipDispatcherDispatcher();

};

}
#endif /*LASERCHIPDISPATCHERDISPATCHER_H_*/
