#ifndef GGAF_CORE_PHASE_H_
#define GGAF_CORE_PHASE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#ifdef _MSC_VER
    #if _MSC_VER < 1600
        #include <map>
        #define unordered_map map
    #else
        #include <unordered_map>
    #endif
#else
        #include <unordered_map>
#endif

#define GGAF_PHASE_NOTHING (-1)
#define GGAF_PHASE_NULL (-2)

namespace GgafCore {

/**
 * �t�F�[�Y�Ǘ��N���X .
 * ���Ԍo�߂ɔ����A�t�F�[�Y�ԍ���ύX���s�����\�b�h��񋟁A
 * �܂��A�t�F�[�Y�ԍ���ύX�ɔ����l�X�ȏ��������̃��\�b�h��񋟂���B<br>
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class Phase : public Object {

public:
    /** [r]���݃t�F�[�Y�ԍ�(-1, 0�`) */
    int _phase_no;
    /** [r]�P�t���[���O�̃t�F�[�Y�ԍ�(-1, 0�`) */
    int _phase_no_prev;
    /** [r]���̃t���[�����Z���ɔ��f�\��̃t�F�[�Y�ԍ�(-1, 0�`) */
    int _phase_no_next;
    /** [r]�e�t�F�[�Y�ԍ��̃t�F�[�Y�ύX���̎��Ԃ̕ۑ� */
    std::unordered_map<int, frame> _map_phase_no_changed_frame;
    /** [r]���ԃJ�E���^�[(���Ԍo�߂ɔ����������鉽�炩�̕ϐ�)�̎Q�� */
    frame* _p_frame_counter;

public:
    /**
     * �R���X�g���N�^ .
     * ���������̃t�F�[�Y�ԍ��� GGAF_PHASE_NOTHING(-1) �ɐݒ肳��Ă���B<BR>
     * ����́A�ǂ̃t�F�[�Y�ł����������Ӗ��Őݒ肵�Ă���B<BR>
     * �ʏ�̃t�F�[�Y�� 0�` �Ƃ���B<BR>
     * @param prm_p_frame_counter �Ǘ�����t���[���ϐ��̎Q��
     */
    Phase(frame* prm_p_frame_counter);

    /**
     * ���݂̃t�F�[�Y�ԍ��擾 .
     * @return �t�F�[�Y�ԍ�(GGAF_PHASE_NOTHING or 0�`)
     */
    inline int getCurrent() const {
        return _phase_no;
    }

    /**
     * ���݂̃t�F�[�Y�𑦍��ɐݒ肷�� .
     * �����ɔ��f�����B-1 �͐ݒ�s�B<BR>
     * �������Ȃǂł͂��� reset(int) ���g�p���A<BR>
     * ��ԕω����� change(int) ���g�p����B<BR>
     * �Ƃ����݌v�B<BR>
     * �y���Ӂz<BR>
     * hasJustChanged() �͐������܂���B<BR>
     * @param prm_phase_no �t�F�[�Y�ԍ�(0�`)
     */
    void reset(int prm_phase_no);

    /**
     * ���݂̃t�F�[�Y�𑦍��ɖ���(GGAF_PHASE_NOTHING(-1)) �ɐݒ肷�� .
     */
    void reset();

    /**
     * ���݂̃t�F�[�Y�𖳂�(GGAF_PHASE_NOTHING(-1)) �ɐݒ肷�� .
     * �����ɔ��f�����B
     */
    void setNothing();

    /**
     * �����̃t�F�[�Y�ԍ��֕ύX���ꂽ���̎��Ԃ𒲂ׂ� .
     * @param prm_phase_no �t�F�[�Y�ԍ�(0�`)
     * @return �����̃t�F�[�Y�ԍ��֕ύX���ꂽ��(����)�̎���
     */
    frame getFrameWhenChanged(int prm_phase_no);

    /**
     * ���݂̃t�F�[�Y�ԍ����ŉ��t���[���Ȃ̂����擾(0�`) .
     * hasJustChanged() �������� 1 ���Ԃ�B�i���Z�b�g�����j
     * ���̌�A���Z����Ă����B
     * @return �t�F�[�Y���o�ߎ���
     */
    inline frame getFrame() const {
        std::unordered_map<int, frame>::const_iterator i = _map_phase_no_changed_frame.find(_phase_no);
        return ((*_p_frame_counter) - (i->second));
    }

    /**
     * ���݂̃t�F�[�Y�ԍ����ł̃t���[�����ƈ����̃t���[�����������𒲂ׂ� .
     * @param prm_frame
     * @return
     */
    inline bool hasArrivedFrameAt(frame prm_frame) const {
        std::unordered_map<int, frame>::const_iterator i = _map_phase_no_changed_frame.find(_phase_no);
        return prm_frame == ((*_p_frame_counter) - (i->second)) ? true : false;
    }

    /**
     * �t�F�[�Y�ԍ���ύX .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * GGAF_PHASE_NOTHING(-1) �͐ݒ�s�B
     * reset(int) �Ǝg�������邱�ƁB
     * @param prm_phase_no �t�F�[�Y�ԍ�(0�`)
     */
    virtual void change(int prm_phase_no);

    /**
     * �t�F�[�Y�ԍ����m���ʂŕύX .
     * �y�L����z<br>
     * <code>
     * _pPhase->changeProbab(
     *              60, PHASE_MOVE01,
     *               0, PHASE_MOVE02,
     *              20, PHASE_MOVE03,
     *               0, PHASE_MOVE04,
     *              15, PHASE_MOVE05,
     *              10, PHASE_MOVE06,
     *               5, PHASE_MOVE07
     *         );
     * </code>
     * �y��L�̈Ӗ��z<br>
     * 60% �̊m���Ńt�F�[�Y�ԍ��� PHASE_MOVE01 �ɕύX�A<br>
     *  0% �̊m���Ńt�F�[�Y�ԍ��� PHASE_MOVE02 �ɕύX�A<br>
     * 20% �̊m���Ńt�F�[�Y�ԍ��� PHASE_MOVE03 �ɕύX�A<br>
     *  0% �̊m���Ńt�F�[�Y�ԍ��� PHASE_MOVE04 �ɕύX�A<br>
     * 15% �̊m���Ńt�F�[�Y�ԍ��� PHASE_MOVE05 �ɕύX�A<br>
     * 10% �̊m���Ńt�F�[�Y�ԍ��� PHASE_MOVE06 �ɕύX�A<br>
     *  5% �̊m���Ńt�F�[�Y�ԍ��� PHASE_MOVE07 �ɕύX�A<br>
     * <br>
     * �m���i�S�����j�����̍��v���K�� 100 �ɂȂ�K�v������܂��B<br>
     * �i�������I�ɁA�����̊m���̘a��100�ɂȂ�܂ŁA�i���Ɉ�����ǂݍ��ݑ����܂��B���ӂ��Ďg�p���āI�j<br>
     * @param prm_p1 �m�����̂P
     * @param prm_v1 ���̊m���ŕύX����t�F�[�Y�ԍ����̂P(0�`)
     */
    void changeProbab(uint32_t prm_p1, int prm_v1, ...);

    /**
     * �t�F�[�Y�ԍ��𖳂� GGAF_PHASE_NOTHING(-1) �ɕύX .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     */
    virtual void changeNothing();

    /**
     * �t�F�[�Y�ԍ���+1���� .
     * �A���A����ɂ͔��f���ꂸ update() ���ɔ��f�����B
     * change(_phase_no+1) �Ɠ����Ӗ��ł���B
     */
    virtual void changeNext();

    /**
     * �t�F�[�Y�ԍ����؂�ւ��������Ȃ̂��ǂ����𔻒�B .
     * change(int) �ɂ��t�F�[�Y�ԍ��؂�ւ������� update() ������ true �ɂȂ�܂��B<BR>
     * reset(int) �ɂ��t�F�[�Y�ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * change(int) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @return true:�t�F�[�Y�ɐ؂�ւ��������ł���^false:����ȊO
     */
    inline bool hasJustChanged() const {
        if (_phase_no != _phase_no_prev && _phase_no_prev >= GGAF_PHASE_NOTHING) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * ���݂̃t�F�[�Y�ԍ���GGAF_PHASE_NOTHING���ۂ����ׂ�B .
     * @return
     */
    inline bool isNothing() const {
        return _phase_no == GGAF_PHASE_NOTHING ? true : false;
    }

    /**
     * �����̃t�F�[�Y�ԍ��ɐ؂�ւ��������Ȃ̂��ǂ������ׂ�B.
     * hasJustChanged() �Ɍ��݂̃t�F�[�Y�ԍ��̏�����t�����܂��B
     * change(int) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @param prm_phase_no ���݂̃t�F�[�Y�ԍ�����
     * @return true:�����̃t�F�[�Y�ԍ��ɐ؂�ւ�����^false:�����ł͂Ȃ�
     */
    bool hasJustChangedTo(int prm_phase_no) const;

    /**
     * �����̃t�F�[�Y�ԍ�����؂�ւ��������Ȃ̂��ǂ����𒲂ׂ�B.
     * hasJustChanged() �ɑO��̃t�F�[�Y�ԍ��̏�����t�����܂��B
     * change(int) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * @param prm_phase_no �O��i�؂�ւ��O�j�̃t�F�[�Y�ԍ�
     * @return true:�؂�ւ�����ہA�O��̃t�F�[�Y�ԍ��͈����̃t�F�[�Y�ԍ��������^false:�����ł͂Ȃ�
     */
    bool hasJustChangedFrom(int prm_phase_no) const;

    /**
     * �t�F�[�Y�ԍ����ω��������i�O��Ɠ������ǂ����j���ׂ� .
     * �ω������ꍇ�A���̐V�����t�F�[�Y�ԍ���Ԃ��B
     * change(int) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * reset(int) �ɂ��t�F�[�Y�ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * @return GGAF_PHASE_NULL(-2) ���� GGAF_PHASE_NOTHING(-1) ���� �t�F�[�Y�ԍ�
     *         GGAF_PHASE_NULL   �F�t�F�[�Y�ԍ����ω����Ă��Ȃ�
     *         GGAF_PHASE_NOTHING�F�t�F�[�Y�ԍ������� GGAF_PHASE_NOTHING(-1) �ɕω��������ゾ�����B
     *         0�`               �F�t�F�[�Y�ԍ����ω���������ł���̂ŁA���̐V�����t�F�[�Y�ԍ���Ԃ�
     */
    int getWhenChanged() const;

    /**
     * �t�F�[�Y�ԍ���������ω����������ׂ� .
     * �ω������ꍇ�A���̌��̃t�F�[�Y�ԍ���Ԃ��B
     * change(int) ���� changeNext() �����s�������t���[���Ŏ擾�����������B
     * reset(int) �ɂ��t�F�[�Y�ԍ��؂�ւ����ꍇ�͐������܂���B<BR>
     * @return GGAF_PHASE_NULL(-2) ���� GGAF_PHASE_NOTHING(-1) ���� �t�F�[�Y�ԍ�
     *         GGAF_PHASE_NULL   �F�t�F�[�Y�ԍ����ω����Ă��Ȃ�
     *         GGAF_PHASE_NOTHING�F�t�F�[�Y�ԍ������� GGAF_PHASE_NOTHING(-1) ����ω��������ゾ�����B
     *         0�`               �F�t�F�[�Y�ԍ����ω�����������ł���̂ŁA�ω��O�̌��̃t�F�[�Y�ԍ��Ԃ�
     */
    int getPrevWhenChanged() const;

    /**
     * �t�F�[�Y�ԍ������t���[���ɕύX�����\��Ȃ�΁A���݂̃t�F�[�Y�ԍ����擾���� .
     * ����t���[������ change(int) ���� changeNext() �����s�ς݂̏ꍇ�A�擾�����������B
     * @return GGAF_PHASE_NULL(-2) ���� GGAF_PHASE_NOTHING(-1) ���� �t�F�[�Y�ԍ�
     *         GGAF_PHASE_NULL   �F���t���[���Ƀt�F�[�Y�ԍ����ύX�����\��ł͂Ȃ��B
     *         GGAF_PHASE_NOTHING�F���݃t�F�[�Y������ GGAF_PHASE_NOTHING(-1) �ŁA���t���[���Ƀt�F�[�Y�ԍ����ύX�����\��ł���B
     *         0�`               �F���t���[���Ƀt�F�[�Y�ԍ����ύX�����\��ł���̂ŁA���݂̃t�F�[�Y�ԍ���Ԃ��B
     */
    int getWillChangeNextFrame() const;

    /**
     * �t�F�[�Y�ԍ������t���[���ɕύX�����\��Ȃ�΁A���̕ύX�����t�F�[�Y�ԍ����擾���� .
     * ����t���[������ change(int) ���� changeNext() �����s�ς݂̏ꍇ�A�擾�����������B
     * @return GGAF_PHASE_NULL(-2) ���� GGAF_PHASE_NOTHING(-1) ���� �t�F�[�Y�ԍ�
     *         GGAF_PHASE_NULL   �F���t���[���Ƀt�F�[�Y�ԍ����ύX�����\��ł͂Ȃ��B
     *         GGAF_PHASE_NOTHING�F���t���[���Ƀt�F�[�Y���� GGAF_PHASE_NOTHING(-1) �ƂȂ�\��ł���B
     *         0�`               �F���t���[���Ƀt�F�[�Y�ԍ����ύX�����\��ł���̂ŁA���̐V�����t�F�[�Y�ԍ���Ԃ��B
     */
    int getPrevWillChangeNextFrame() const;

    /**
     * �t�F�[�Y�����̏�ԂɍX�V .
     * ���ԃJ�E���^�[�̑����������ŁA���̏������R�[�����Ă��������B
     */
    virtual void update();

    virtual ~Phase();
};

}
#endif /*GGAF_CORE_PHASE_H_*/
