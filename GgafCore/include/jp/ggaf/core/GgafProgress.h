#ifndef GGAFPROGRESS_H_
#define GGAFPROGRESS_H_

#define PROGRESS_NOTHING (0)

typedef int progress;

namespace GgafCore {

/**
 * ��ԑJ�ڐi���Ǘ��N���X .
 * ��ԑJ�ڂ��Ǘ�����@�\���������̃N���X�ł��B
 * ���Ԍo�߂ɔ����A�i���ԍ���ύX���s�����\�b�h��񋟁A
 * �܂��A�i���ԍ���ύX�ɔ����l�X�ȏ��������̃��\�b�h��񋟂���B<br>
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class GgafProgress : public GgafObject {

public:
    /** [r]���ݐi���ԍ�(0, 1�`) */
    progress _progress;
    /** [r]�P�P�ʎ��ԑO�̐i���ԍ�(0, 1�`) */
    progress _progress_prev;
    /** [r]���̒P�ʎ��ԉ��Z���ɔ��f�\��̐i���ԍ�(0, 1�`) */
    progress _progress_next;
    /** [r]�e�i���ԍ��̐i���ύX���̎��Ԃ̕ۑ� */
    frame* _paFrame_progress_changed;
    /** [r]���ԃJ�E���^�[(���Ԍo�߂ɔ����������鉽�炩�̕ϐ�)�̎Q�� */
    frame* _pFrame_counter;
    /** �Ǘ������i���ԍ��̌� */
    int _num_progress;

public:
    /**
     * �R���X�g���N�^ .
     * ���������̐i���ԍ��� 0 �ɐݒ肳��Ă���B<BR>
     * ����́A�ǂ̐i����Ԃł����������Ӗ��Őݒ肵�Ă���B<BR>
     * �ʏ�̐i����Ԃ� 1�` �Ƃ���B<BR>
     * @param prm_pFrame_counter ���ԃJ�E���^�[�̎Q��(���炩�o�߂ɔ����C���N�������g(+1)����Ă����ϐ��̎Q��)
     * @param prm_num_progress �ő�i���ԍ���(10��ݒ肷��� 0�ԁ`10�Ԃ�11�̐i����Ԃ��g�p�\�ƂȂ�)
     */
    GgafProgress(frame* prm_pFrame_counter, int prm_num_progress);


    void reset();

    /**
     * ���݂̐i���ԍ��擾 .
     * @return �i���ԍ�(0, 1�`)
     */
    inline progress get() {
        return _progress;
    }

    /**
     * ���݂̐i���𑦍��ɐݒ肷�� .
     * �����ɔ��f�����B0 �͐ݒ�s�B<BR>
     * �������Ȃǂł͂��� reset(int) ���g�p���A<BR>
     * ��ԕω����� change(int) ���g�p����B<BR>
     * �Ƃ����݌v�B<BR>
     * �y���Ӂz<BR>
     * isJustChanged() �͐������܂���B<BR>
     * @param prm_progress �i���ԍ�(1�`)
     */
    void reset(progress prm_progress);

    /**
     * ���݂̐i����0(����)�ɐݒ肷�� .
     * �����ɔ��f�����B
     */
    void setNothing();

    /**
     * �����̐i���ԍ��֕ύX���ꂽ���̎��Ԃ𒲂ׂ� .
     * @param prm_progress �i���ԍ�(1�`)
     * @return �����̐i���ԍ��֕ύX���ꂽ��(����)�̎���
     */
    frame getFrameWhenChanged(progress prm_progress);

    /**
     * ���݂̐i���ԍ����ŉ��t���[���Ȃ̂����擾(1�`) .
     * isJustChanged() �������� 1 ���Ԃ�B�i���Z�b�g�����j
     * ���̌�A���Z����Ă����B
     * @return �i�����o�ߎ���
     */
    inline frame getFrameInProgress() {
        return ((*_pFrame_counter) - _paFrame_progress_changed[_progress]);
    }

    /**
     * �i���ԍ���ύX .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * 0 �͐ݒ�s�B
     * set(progress) �Ǝg�������邱�ƁB
     * @param prm_progress �i���ԍ�(1�`)
     */
    void change(progress prm_progress);


    /**
     * �i���ԍ���0(����)�ɕύX .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     */
    void changeNothing();

    /**
     * �i���ԍ���+1���� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * change(_progress+1) �Ɠ����Ӗ��ł���B
     */
    void changeNext();

    /**
     * �i���ԍ����؂�ւ��������Ȃ̂��ǂ����𔻒�B .
     * change(progress) �ɂ��i���ԍ��؂�ւ������� update() ������ true �ɂȂ�܂��B<BR>
     * reset(progress) �ɂ��i���ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @return true:�i���ɐ؂�ւ��������ł���^false:����ȊO
     */
    inline bool isJustChanged() {
        if (_progress != _progress_prev && _progress_prev > -1) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * �����̐i���ԍ��ɐ؂�ւ��������Ȃ̂��ǂ������ׂ�B.
     * isJustChanged() �Ɍ��݂̐i���ԍ��̏�����t�����܂��B
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @param prm_progress ���݂̐i���ԍ�����
     * @return true:�����̐i���ԍ��ɐ؂�ւ�����^false:�����ł͂Ȃ�
     */
    bool isJustChangedTo(progress prm_progress);

    /**
     * �����̐i���ԍ�����؂�ւ��������Ȃ̂��ǂ����𒲂ׂ�B.
     * isJustChanged() �ɑO��̐i���ԍ��̏�����t�����܂��B
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @param prm_progress �O��i�؂�ւ��O�j�̐i���ԍ�
     * @return true:�؂�ւ�����ہA�O��̐i���ԍ��͈����̐i���ԍ��������^false:�����ł͂Ȃ�
     */
    bool isJustChangedFrom(progress prm_progress);

    /**
     * �i���ԍ����ω��������i�O��Ɠ������ǂ����j���ׂ� .
     * �ω������ꍇ�A���̐V�����i���ԍ���Ԃ��B
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * reset(progress) �ɂ��i���ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * @return 0(false) ���� �i���ԍ�
     *         0(false)�F�i���ԍ����ω����Ă��Ȃ�
     *         0�ȊO   �F�i���ԍ����ω���������ł���̂ŁA���̐V�����i���ԍ���Ԃ�
     */
    progress getProgOnChange();

    /**
     * �i���ԍ���������ω����������ׂ� .
     * �ω������ꍇ�A���̌��̐i���ԍ���Ԃ��B
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * reset(progress) �ɂ��i���ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * @return 0(false) ���� �i���ԍ�
     *         0(false)�F�i���ԍ����ω����Ă��Ȃ�
     *         0�ȊO   �F�i���ԍ����ω�����������ł���̂ŁA�ω��O�̌��̐i���ԍ��Ԃ�
     */
    progress getFromProgOnChange();

    /**
     * �i���ԍ������t���[���ɕύX�����\��Ȃ�΁A���݂̐i���ԍ����擾���� .
     * ����t���[������ change(progress) ���� changeNext() �����s�ς݂̏ꍇ�A�擾�����������B
     * @return 0(false) ���� �i���ԍ�
     *         0(false)�F���t���[���ɐi���ԍ����ύX�����\��ł͂Ȃ��B
     *         0�ȊO   �F���t���[���ɐi���ԍ����ύX�����\��ł���̂ŁA���݂̐i���ԍ���Ԃ��B
     */
    progress getProgWhenWillChange();

    /**
     * �i���ԍ������t���[���ɕύX�����\��Ȃ�΁A���̕ύX�����i���ԍ����擾���� .
     * ����t���[������ change(progress) ���� changeNext() �����s�ς݂̏ꍇ�A�擾�����������B
     * @return 0(false) ���� �i���ԍ�
     *         0(false)�F���t���[���ɐi���ԍ����ύX�����\��ł͂Ȃ��B
     *         0�ȊO   �F���t���[���ɐi���ԍ����ύX�����\��ł���̂ŁA���̐V�����i���ԍ���Ԃ��B
     */
    progress getToProgWhenWillChange();

    /**
     * ���Ԃɔ����Đi�����X�V .
     * ���ԃJ�E���^�[�̑��������ŁA���̏������R�[�����Ă��������B
     */
    virtual void update();

    virtual ~GgafProgress();
};

}
#endif /*GGAFPROGRESS_H_*/
