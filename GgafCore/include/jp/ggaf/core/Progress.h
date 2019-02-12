#ifndef GGAF_CORE_PROGRESS_H_
#define GGAF_CORE_PROGRESS_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#define PROGRESS_NOTHING (-1)
#define PROGRESS_NULL (-2)

typedef int_fast32_t progress;

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
class Progress : public Object {

public:
    /** [r]���ݐi���ԍ�(-1, 0�`) */
    progress _progress;
    /** [r]�P�P�ʎ��ԑO�̐i���ԍ�(-1, 0�`) */
    progress _progress_prev;
    /** [r]���̒P�ʎ��ԉ��Z���ɔ��f�\��̐i���ԍ�(-1, 0�`) */
    progress _progress_next;
    /** [r]�e�i���ԍ��̐i���ύX���̎��Ԃ̕ۑ� */
    frame* _pa_frame_of_progress_changed;
    /** [r]���ԃJ�E���^�[(���Ԍo�߂ɔ����������鉽�炩�̕ϐ�)�̎Q�� */
    frame* _p_frame_counter;
    /** �Ǘ������i���ԍ��̌� */
    int _num_progress;

public:
    /**
     * �R���X�g���N�^ .
     * ���������̐i���ԍ��� PROGRESS_NOTHING(-1) �ɐݒ肳��Ă���B<BR>
     * ����́A�ǂ̐i����Ԃł����������Ӗ��Őݒ肵�Ă���B<BR>
     * �ʏ�̐i����Ԃ� 0�` �Ƃ���B<BR>
     * @param prm_p_frame_counter ���ԃJ�E���^�[�̎Q��(���炩�o�߂ɔ����C���N�������g(+1)����Ă����ϐ��̎Q��)
     * @param prm_num_progress �ő�i���ԍ���(10��ݒ肷��� 0�ԁ`10�Ԃ�11�̐i����Ԃ��g�p�\�ƂȂ�)
     */
    Progress(frame* prm_p_frame_counter, int prm_num_progress);


    void reset();

    /**
     * ���݂̐i���ԍ��擾 .
     * @return �i���ԍ�(PROGRESS_NOTHING or 0�`)
     */
    inline progress get() const {
        return _progress;
    }

    inline int getProgressNum() const {
        return _num_progress;
    }

    /**
     * ���݂̐i���𑦍��ɐݒ肷�� .
     * �����ɔ��f�����B-1 �͐ݒ�s�B<BR>
     * �������Ȃǂł͂��� reset(int) ���g�p���A<BR>
     * ��ԕω����� change(int) ���g�p����B<BR>
     * �Ƃ����݌v�B<BR>
     * �y���Ӂz<BR>
     * hasJustChanged() �͐������܂���B<BR>
     * @param prm_progress �i���ԍ�(0�`)
     */
    void reset(progress prm_progress);

    /**
     * ���݂̐i���𖳂� PROGRESS_NOTHING(-1) �ɐݒ肷�� .
     * �����ɔ��f�����B
     */
    void setNothing();

    /**
     * �����̐i���ԍ��֕ύX���ꂽ���̎��Ԃ𒲂ׂ� .
     * @param prm_progress �i���ԍ�(0�`)
     * @return �����̐i���ԍ��֕ύX���ꂽ��(����)�̎���
     */
    frame getFrameWhenChanged(progress prm_progress) const;

    /**
     * ���݂̐i���ԍ����ŉ��t���[���Ȃ̂����擾(0�`) .
     * hasJustChanged() �������� 1 ���Ԃ�B�i���Z�b�g�����j
     * ���̌�A���Z����Ă����B
     * @return �i�����o�ߎ���
     */
    inline frame getFrame() const {
        return ((*_p_frame_counter) - _pa_frame_of_progress_changed[_progress+1]);
    }

    /**
     * ���݂̐i���ԍ����ł̃t���[�����ƈ����̃t���[�����������𒲂ׂ� .
     * @param prm_frame
     * @return
     */
    inline bool hasArrivedAt(frame prm_frame) const {
        return prm_frame == ((*_p_frame_counter) - _pa_frame_of_progress_changed[_progress+1]) ? true : false;
    }

    /**
     * �i���ԍ���ύX .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * PROGRESS_NOTHING(-1) �͐ݒ�s�B
     * reset(progress) �Ǝg�������邱�ƁB
     * @param prm_progress �i���ԍ�(0�`)
     */
    virtual void change(progress prm_progress);

    /**
     * �i���ԍ����m���ʂŕύX .
     * �y�L����z<br>
     * <code>
     * _pProg->changeProbab(
     *              60, PROG_MOVE01,
     *               0, PROG_MOVE02,
     *              20, PROG_MOVE03,
     *               0, PROG_MOVE04,
     *              15, PROG_MOVE05,
     *              10, PROG_MOVE06,
     *               5, PROG_MOVE07
     *         );
     * </code>
     * �y��L�̈Ӗ��z<br>
     * 60% �̊m���Ői���ԍ��� PROG_MOVE01 �ɕύX�A<br>
     *  0% �̊m���Ői���ԍ��� PROG_MOVE02 �ɕύX�A<br>
     * 20% �̊m���Ői���ԍ��� PROG_MOVE03 �ɕύX�A<br>
     *  0% �̊m���Ői���ԍ��� PROG_MOVE04 �ɕύX�A<br>
     * 15% �̊m���Ői���ԍ��� PROG_MOVE05 �ɕύX�A<br>
     * 10% �̊m���Ői���ԍ��� PROG_MOVE06 �ɕύX�A<br>
     *  5% �̊m���Ői���ԍ��� PROG_MOVE07 �ɕύX�A<br>
     * <br>
     * �m���i�S�����j�����̍��v���K�� 100 �ɂȂ�K�v������܂��B<br>
     * �i�������I�ɁA�����̊m���̘a��100�ɂȂ�܂ŁA�i���Ɉ�����ǂݍ��ݑ����܂��B���ӂ��Ďg�p���āI�j<br>
     * @param prm_p1 �m�����̂P
     * @param prm_v1 ���̊m���ŕύX����i���ԍ����̂P(0�`)
     */
    void changeProbab(uint32_t prm_p1, progress prm_v1, ...);

    /**
     * �i���ԍ��𖳂� PROGRESS_NOTHING(-1) �ɕύX .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     */
    virtual void changeNothing();

    /**
     * �i���ԍ���+1���� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * change(_progress+1) �Ɠ����Ӗ��ł���B
     */
    virtual void changeNext();

    /**
     * ���݂̐i���ԍ����ł̃t���[�����ƈ����̃t���[���������Ȃ�΁A�i���ԍ���+1���� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * @param prm_frame
     */
    inline void changeNextWhenArrivedAt(frame prm_frame) {
        if (hasArrivedAt(prm_frame)) {
            changeNext();
        }
    }

    /**
     * �i���ԍ����؂�ւ��������Ȃ̂��ǂ����𔻒�B .
     * change(progress) �ɂ��i���ԍ��؂�ւ������� update() ������ true �ɂȂ�܂��B<BR>
     * reset(progress) �ɂ��i���ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @return true:�i���ɐ؂�ւ��������ł���^false:����ȊO
     */
    inline bool hasJustChanged() const {
        if (_progress != _progress_prev && _progress_prev >= PROGRESS_NOTHING) {
            return true;
        } else {
            return false;
        }
    }
    /**
     * ���݂̐i���ԍ���PROGRESS_NOTHING���ۂ����ׂ�B .
     * @return
     */
    inline bool isNothing() const {
        return _progress == PROGRESS_NOTHING ? true : false;
    }

    /**
     * �����̐i���ԍ��ɐ؂�ւ��������Ȃ̂��ǂ������ׂ�B.
     * hasJustChanged() �Ɍ��݂̐i���ԍ��̏�����t�����܂��B
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @param prm_progress ���݂̐i���ԍ�����
     * @return true:�����̐i���ԍ��ɐ؂�ւ�����^false:�����ł͂Ȃ�
     */
    bool hasJustChangedTo(progress prm_progress) const;

    /**
     * �����̐i���ԍ�����؂�ւ��������Ȃ̂��ǂ����𒲂ׂ�B.
     * hasJustChanged() �ɑO��̐i���ԍ��̏�����t�����܂��B
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @param prm_progress �O��i�؂�ւ��O�j�̐i���ԍ�
     * @return true:�؂�ւ�����ہA�O��̐i���ԍ��͈����̐i���ԍ��������^false:�����ł͂Ȃ�
     */
    bool hasJustChangedFrom(progress prm_progress) const;

    /**
     * �i���ԍ����ω��������i�O��Ɠ������ǂ����j���ׂ� .
     * �ω������ꍇ�A���̐V�����i���ԍ���Ԃ��B
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * reset(progress) �ɂ��i���ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * @return PROGRESS_NULL(-2) ���� PROGRESS_NOTHING(-1) ���� �i���ԍ�
     *         PROGRESS_NULL   �F�i���ԍ����ω����Ă��Ȃ�
     *         PROGRESS_NOTHING�F�i���ԍ������� PROGRESS_NOTHING(-1) �ɕω��������ゾ�����B
     *         0�`             �F�i���ԍ����ω���������ł���̂ŁA���̐V�����i���ԍ���Ԃ�
     */
    progress getProgOnChange() const;

    /**
     * �i���ԍ���������ω����������ׂ� .
     * �ω������ꍇ�A���̌��̐i���ԍ���Ԃ��B
     * change(progress) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * reset(progress) �ɂ��i���ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * @return PROGRESS_NULL(-2) ���� PROGRESS_NOTHING(-1) ���� �i���ԍ�
     *         PROGRESS_NULL   �F�i���ԍ����ω����Ă��Ȃ�
     *         PROGRESS_NOTHING�F�i���ԍ������� PROGRESS_NOTHING(-1) ����ω��������ゾ�����B
     *         0�`             �F�i���ԍ����ω�����������ł���̂ŁA�ω��O�̌��̐i���ԍ��Ԃ�
     */
    progress getFromProgOnChange() const;

    /**
     * �i���ԍ������t���[���ɕύX�����\��Ȃ�΁A���݂̐i���ԍ����擾���� .
     * ����t���[������ change(progress) ���� changeNext() �����s�ς݂̏ꍇ�A�擾�����������B
     * @return PROGRESS_NULL(-2) ���� PROGRESS_NOTHING(-1) ���� �i���ԍ�
     *         PROGRESS_NULL   �F���t���[���ɐi���ԍ����ύX�����\��ł͂Ȃ��B
     *         PROGRESS_NOTHING�F���ݐi�������� PROGRESS_NOTHING(-1) �ŁA���t���[���ɐi���ԍ����ύX�����\��ł���B
     *         0�`             �F���t���[���ɐi���ԍ����ύX�����\��ł���̂ŁA���݂̐i���ԍ���Ԃ��B
     */
    progress getProgWhenProgWillChange() const;

    /**
     * �i���ԍ������t���[���ɕύX�����\��Ȃ�΁A���̕ύX�����i���ԍ����擾���� .
     * ����t���[������ change(progress) ���� changeNext() �����s�ς݂̏ꍇ�A�擾�����������B
     * @return PROGRESS_NULL(-2) ���� PROGRESS_NOTHING(-1) ���� �i���ԍ�
     *         PROGRESS_NULL   �F���t���[���ɐi���ԍ����ύX�����\��ł͂Ȃ��B
     *         PROGRESS_NOTHING�F���t���[���ɐi������ PROGRESS_NOTHING(-1) �ƂȂ�\��ł���B
     *         0�`             �F���t���[���ɐi���ԍ����ύX�����\��ł���̂ŁA���̐V�����i���ԍ���Ԃ��B
     */
    progress getToProgWhenProgWillChange() const;

    /**
     * ���Ԃɔ����Đi�����X�V .
     * ���ԃJ�E���^�[�̑��������ŁA���̏������R�[�����Ă��������B
     */
    virtual void update();

    virtual ~Progress();
};

}
#endif /*GGAF_CORE_PROGRESS_H_*/
