#ifndef GGAFPROGRESS_H_
#define GGAFPROGRESS_H_
namespace GgafCore {


/**
 * �i���Ǘ��N���X .
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class GgafProgress : public GgafObject {

public:

    /** [r]���ݐi��ID(1�`99) */
    int _progress;
    /** [r]�P�t���[���O�i��ID(1�`99) */
    int _progress_prev;
    /** [r]���t���[�����Z���ɔ��f�\��̐i��ID(1�`99) */
    int _progress_nextframe;
    /** [r]�i��ID�C�x���g���t���[���X�g�b�N */
    frame* _paFrame_ProgressChanged;
    frame* _pFrame_behaving;

    /**
     * �R���X�g���N�^ .
     */
    GgafProgress(frame* prm_pFrame_behaving, int prm_num);


    /**
     * ���݂̐i��ID�擾 .
     * @return �i��ID(1�`99)
     */
    virtual int get();

    /**
     * ���݂̐i����ݒ肷�� .
     * �����ɔ��f�����B<BR>
     * �������Ȃǂł͂��� set(int) ���g�p���A<BR>
     * ��ԕω����� change(int) ���g�p����B<BR>
     * �Ƃ����݌v�B<BR>
     * @param prm_progress �i��ID(1�`99)
     */
    virtual void set(int prm_progress);

    /**
     * �i��ID���N���������̃t���[���擾 .
     * @param prm_progress �i��ID(1�`99)
     * @return �����̒��߂̐i��ID���N�������Ƃ��̃t���[��
     */
    virtual frame getFrameWhenChanged(int prm_progress);

    /**
     * �i�����o�߃t���[�����擾 .
     * @return �i�����o�߃t���[��
     */
    virtual frame getActivePartFrameInProgress();

    /**
     * �i��ID��ύX .
     * �A���A����t���[�����ł͔��f���ꂸ�AnextFrame() ���ɔ��f�����B
     * @param prm_progress �i��ID(1�`99)
     */
    virtual void change(int prm_progress);

    /**
     * �i��ID��+1���� .
     * 1�`99 �͈̔͂ƂȂ�悤�ɒ��ӂ��邱�ƁB
     * �A���A����t���[�����ł͔��f���ꂸ�AnextFrame() ���ɔ��f�����B
     */

    virtual void changeNext();

    /**
     * �����̐i��ID�ɐ؂�ւ�������ǂ������ׂ�B.
     * �؂�ւ���� nextFrame() ����1�t���[������true�ɂȂ�܂��B
     * @param prm_progress �؂�ւ�������ǂ������ׂ����i��ID
     * @return true:�����̐i��ID�ɐ؂�ւ�����^false:����ȊO
     */
    virtual bool wasChangedTo(int prm_progress);

    /**
     * ���݂̐i���ɐ؂�ւ��������Ȃ̂��𔻒�B
     * change(int) �ɂ��؂�ւ���ꂽ�ہA nextFrame() ����1�t���[������ true �ɂȂ�܂��B
     * @return true:�i���ɐ؂�ւ��������ł���^false:����ȊO
     */
    virtual bool isJustChanged();

    /**
     * �����̐i��ID����؂�ւ�����̂��ǂ����𒲂ׂ�B.
     * �؂�ւ�����ۂɁA���O�̐i��ID�������Ƃ��Ē��ׂ邱�Ƃ��o����B
     * �؂�ւ���� nextFrame() ����1�t���[������true�ɂȂ�܂��B
     * @param prm_progress �؂�ւ�����ہA�O�̐i��ID�͉��ł��������ǂ������ׂ����i��ID
     * @return true:�؂�ւ�����ہA�O�̐i��ID�͈����̐i��ID�������^false:����ȊO
     */
    virtual bool wasChangedFrom(int prm_progress);

    /**
     * �i��ID���ω��������i�O��Ɠ������ǂ����j���ׂ� .
     * �ω������ꍇ�A���̐V�����i��ID��Ԃ��B
     * @return 0 ���� �i��ID
     *         0    �F�ω����Ă��Ȃ�
     *         0�ȊO�F�ω����L��ŁA���̐V�����i��ID
     */
    virtual int getChangedTo();

    /**
     * �i��ID���ω��������i�O��Ɠ������ǂ����j���ׂ� .
     * �ω������ꍇ�A���̌��̐i��ID��Ԃ��B
     * @return 0 ���� �i��ID
     *         0    �F�ω����Ă��Ȃ�
     *         0�ȊO�F�ω����L��ŁA�ω��O�̌��̐i��ID
     */
    virtual int getChangedFrom();


    virtual void update();

    virtual ~GgafProgress();
};

}
#endif /*GGAFCURTAIN_H_*/
