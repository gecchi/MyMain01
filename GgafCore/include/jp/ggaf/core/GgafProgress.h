#ifndef GGAFPROGRESS_H_
#define GGAFPROGRESS_H_


namespace GgafCore {

/**
 * �i���Ǘ��N���X .
 * ���Ԍo�߂ɔ����A�i���ԍ���ύX���s�����\�b�h��񋟁A
 * �܂��A�i���ԍ���ύX�ɔ����l�X�ȏ��������̃��\�b�h��񋟂���B<br>
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class GgafProgress : public GgafObject {

public:
    /** [r]���ݐi���ԍ�(1�`99) */
    int _progress;
    /** [r]�P�P�ʎ��ԑO�̐i���ԍ�(1�`99) */
    int _progress_prev;
    /** [r]���̒P�ʎ��ԉ��Z���ɔ��f�\��̐i���ԍ�(1�`99) */
    int _progress_next;
    /** [r]�e�i���ԍ��̐i���ύX���̎��Ԃ̕ۑ� */
    frame* _paFrame_ProgressChanged;
    /** [r]���ԃJ�E���^�[(���Ԍo�߂ɔ����������鉽�炩�̕ϐ�)�̎Q�� */
    frame* _pFrame_count;
    /** �Ǘ������i���ԍ��̌� */
    int _num_progress;

    /**
     * �R���X�g���N�^ .
     * ���������̐i���ԍ��� -1 �ɐݒ肳��Ă���B<BR>
     * ����́A��������i���ԍ��͂ǂ̔ԍ��ł������Ƃ����Ӗ��Őݒ肵�Ă���B<BR>
     * �{���͐i���ԍ��̏����l�� 0 �Ƃ������Ƃ��낾�������A0 �Ƃ����l�͂��łɐi����\���Ă���悤�ȋC�����邽�ߔ������B<BR>
     * ��������Aset(0) �ɂ�菉���i���ԍ�������������ꍇ�́A���ɍl���͕s�v�B<BR>
     * �������Aset(0) ���s�킸�A�����Ȃ� change(0) ���s�����ہA�i���ԍ��� 0 �Ԃł� isJustChanged() ������������ʂ�����B<BR>
     * ����i���ԍ��ݒ莞�Ƀu���C�N������s�����ǂ����ŁA�l�����ꂽ���B<BR>
     * @param prm_pFrame_count ���ԃJ�E���^�[�̎Q��(���炩�o�߂ɔ����C���N�������g(+1)����Ă����ϐ��̎Q��)
     * @param prm_num_progress �ő�i���ԍ���
     */
    GgafProgress(frame* prm_pFrame_count, int prm_num_progress);

    /**
     * ���݂̐i���ԍ��擾 .
     * @return �i���ԍ�(1�`99)
     */
    virtual int get();

    /**
     * ���݂̐i����ݒ肷�� .
     * �����ɔ��f�����B<BR>
     * �������Ȃǂł͂��� set(int) ���g�p���A<BR>
     * ��ԕω����� change(int) ���g�p����B<BR>
     * �Ƃ����݌v�B<BR>
     * @param prm_progress �i���ԍ�(1�`99)
     */
    virtual void set(int prm_progress);

    /**
     * �����̐i���ԍ��֕ύX���ꂽ���̎��Ԃ𒲂ׂ� .
     * @param prm_progress �i���ԍ�(1�`99)
     * @return �����̐i���ԍ��֕ύX���ꂽ��(����)�̎���
     */
    virtual frame getFrameWhenChanged(int prm_progress);

    /**
     * ���݂̐i���ԍ����ł̌o�ߎ��Ԃ��擾 .
     * @return �i�����o�ߎ���
     */
    virtual frame getFrameInProgress();

    /**
     * �i���ԍ���ύX .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * set(int) �Ǝg�������邱�ƁB
     * @param prm_progress �i���ԍ�(1�`99)
     */
    virtual void change(int prm_progress);

    /**
     * �i���ԍ���+1���� .
     * 1�`99 �͈̔͂ƂȂ�悤�ɒ��ӂ��邱�ƁB
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * change(_progress+1) �Ɠ����Ӗ��ł���B
     */
    virtual void changeNext();

    /**
     * �i���ԍ����؂�ւ��������Ȃ̂��ǂ����𔻒�B .
     * change(int) �ɂ��i���ԍ��؂�ւ������� update() ������ true �ɂȂ�܂��B<BR>
     * set(int) �ɂ��i���ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * @return true:�i���ɐ؂�ւ��������ł���^false:����ȊO
     */
    virtual bool isJustChanged();

    /**
     * �����̐i���ԍ��ɐ؂�ւ��������Ȃ̂��ǂ������ׂ�B.
     * isJustChanged() �Ɍ��݂̐i���ԍ��̏�����t�����܂��B
     * @param prm_progress ���݂̐i���ԍ�����
     * @return true:�����̐i���ԍ��ɐ؂�ւ�����^false:�����ł͂Ȃ�
     */
    virtual bool isJustChangedTo(int prm_progress);

    /**
     * �����̐i���ԍ�����؂�ւ��������Ȃ̂��ǂ����𒲂ׂ�B.
     * isJustChanged() �ɑO��̐i���ԍ��̏�����t�����܂��B
     * @param prm_progress �O��i�؂�ւ��O�j�̐i���ԍ�
     * @return true:�؂�ւ�����ہA�O��̐i���ԍ��͈����̐i���ԍ��������^false:�����ł͂Ȃ�
     */
    virtual bool isJustChangedFrom(int prm_progress);

    /**
     * �i���ԍ����ω��������i�O��Ɠ������ǂ����j���ׂ� .
     * �ω������ꍇ�A���̐V�����i���ԍ���Ԃ��B
     * @return 0 ���� �i���ԍ�
     *         0    �F�ω����Ă��Ȃ�
     *         0�ȊO�F�ω����L��ŁA���̐V�����i���ԍ�
     */
    virtual int getChangedTo();

    /**
     * �i���ԍ���������ω����������ׂ� .
     * �ω������ꍇ�A���̌��̐i���ԍ���Ԃ��B
     * @return 0 ���� �i���ԍ�
     *         0    �F�ω����Ă��Ȃ�
     *         0�ȊO�F�ω����L��ŁA�ω��O�̌��̐i���ԍ�
     */
    virtual int getChangeFrom();

    /**
     * ���Ԃɔ����Đi�����X�V .
     * ���ԃJ�E���^�[�̑��������ŁA���̏������R�[�����Ă��������B
     */
    virtual void update();

    virtual ~GgafProgress();
};

}
#endif /*GGAFCURTAIN_H_*/
