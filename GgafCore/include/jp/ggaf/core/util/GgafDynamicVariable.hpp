#ifndef GGAFDYNAMICVARIABLE_H_
#define GGAFDYNAMICVARIABLE_H_
namespace GgafCore {

/**
 */
template<class T>  //T:�Ǘ�����v�f�̃|�C���^�̌^
class GgafDynamicVariable : public GgafObject {

public:

    T* _pVariable;

    /**
     * �R���X�g���N�^ .
     */
    GgafDynamicVariable(T* prm_variable, T prm_max_velo, T prm_max_acce);


    /** [r/w]X�������ړ����x */
    T _velo;
    /** [r/w]X�������ړ����x��� */
    T _veloTop;
    /** [r/w]X�������ړ����x���� */
    T _veloBottom;
    /** [r/w]X�������ړ������x */
    T _acce;
    /** [r/w]X�������ړ������x���*/
    T _acceTop;
    /** [r/w]X�������ړ������x����*/
    T _acceBottom;

    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�����s����true */
    bool _smooth_velo_seq_flg;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�����s�������̉����x�ݒ�itrue�F�����x0�ɐݒ�^false:�����x�����̂܂܂ɂ��Ă����j */
    bool _smooth_velo_seq_endacc_flg;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�g�b�v�X�s�[�h�i�����ړ������x�j */
    T _smooth_velo_seq_top_velo;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�I�����̑��x */
    T _smooth_velo_seq_end_velo;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW�ړ����� */
    T _smooth_velo_seq_target_distance;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�ɊJ�n���猻�݂܂ł̈ړ����� */
    T _smooth_velo_seq_distance;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW���� */
    int  _smooth_velo_seq_target_frames;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�ɊJ�n���猻�݂܂ł̌o�ߎ��� */
    int  _smooth_velo_seq_frame_of_spent;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ��ʒu */
    int  _smooth_velo_seq_p1;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ��ʒu */
    int  _smooth_velo_seq_p2;
    /** [r]�Ȃ߂炩�Ȉړ��V�[�N�G���X�̐i���� */
    int  _smooth_velo_seq_progress;

    /**
     * X�������ړ����x�ݒ� .
     * @param prm_velo X�������ړ����x
     */
    void setVelo(T prm_velo);

    /**
     * X�������ړ����x���Z .
     * @param prm_velo X�������ړ����x����
     */
    void addVelo(T prm_velo);

    /**
     * X�������ړ����x�̏������������ .
     * @param prm_velo01 ���x�P
     * @param prm_velo02 ���x�Q
     */
    void forceVeloRange(T prm_velo01, T prm_velo02);

    /**
     * X�������ړ������x�ݒ� .
     * @param prm_acce X�������ړ������x
     */
    void setAcce(T prm_acce);

    /**
     * X�������ړ������x���Z .
     * @param prm_acce X�������ړ������x����
     */
    void addAcce(T prm_acce);

    /**
     * X�������ړ������x�̏������������ .
     * @param prm_acce01 �����x�P
     * @param prm_acce02 �����x�Q
     */
    void forceAcceRange(T prm_acce01, T prm_acce02);



    /**
     * ���qB���U�镑�� .
     * ���qB�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɍ��qB��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();








    /**
     * �Ȃ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE�����w��A���x�ϓ�) .
     * �ړ��ɔ�₳��鎞��(Te)��3�̃Z�N�V�����ɕ����A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� p1*Te �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���(or����)�ړ�<BR>
     * �E���� p1*Te �` ���� p2*Te �܂� �E�E�E �g�b�v�X�s�[�h�œ����ړ�<BR>
     * �E���� p2*Te �` ���� Te    �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���(or����)�ړ�<BR>
     * �����}�Q��<BR>
     * <pre>
     *
     *    ���x(v)
     *     ^
     *     |
     *     |                         Vo:�����_�̑��x
     *     |                         Ve:�ŏI���x
     *     |                          D:�ڕW�ړ�����
     *   Vt|....___________          Te:�ڕW���ԁi�t���[�����j
     *     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *     | /  :         :    |     Vt:�����E���Ԃ��瓱���������g�b�v�X�s�[�h
     *     |/   :         :    |
     *   Vo|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * �ŏI�X�s�[�h(Ve)�A�ڕW�ړ�����(D)�A���B�ڕW����(Te)�A�y�� p1, p2 ���w�肷��B<BR>
     * �g�b�v�X�s�[�h(Vt)�͓����Ŏ����v�Z�����肳���B<BR>
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void execSmoothSequence(T prm_end_velo, T prm_target_distance,
                              int prm_target_frames, float prm_p1, float prm_p2,
                              bool prm_endacc_flg = true);


    /**
     * �Ȃ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���x�E�����w��A���ԕϓ�) .
     * �ړ�������3�̃Z�N�V����(d1,d2,d3)�ɕ����A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� d1       �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���(or����)�ړ�<BR>
     * �E���� d1    �` ���� d1+d2    �܂� �E�E�E �g�b�v�X�s�[�h�œ����ړ�<BR>
     * �E���� d1+d2 �` ���� d1+d2+d3 �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���(or����)�ړ�<BR>
     * �����}�Q��<BR>
     * <pre>
     *    ���x(v)
     *     ^
     *     |                         Vo:�����_�̑��x
     *     |                         Vt:�g�b�v�X�s�[�h
     *     |                         Ve:�ŏI���x
     *     |         D=d1+d2+d3       D:�ڕW�ړ�����(D=d1+d2+d3)
     *   Vt|....___________          p1:�g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     *     |   /|         |�_            �܂�    d1 = D*p1 �ƂȂ�悤�� p1 (0.0�`1.0)
     *   Ve|../.|.........|..�_      p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     *     | /  |         |    |         �܂� d1+d2 = D*p2 �ƂȂ�悤�� p2 (0.0�`1.0)
     *     |/   |         |    |     Te:��₳���K�v���ԁi�t���[�����j
     *   Vo| d1 |    d2   | d3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |                  Te
     *
     * </pre>
     * �g�b�v�X�s�[�h(Vt)�A�ŏI�X�s�[�h(Ve)�A�ڕW�ړ�����(D)�A�y�� p1, p2 ���w�肷��B<BR>
     * ��₳��鎞��(Te)�͓����Ŏ����v�����肳���B<BR>
     * <BR>
     * @param prm_top_velo �g�b�v�X�s�[�h(Vt)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     * @param prm_endacc_flg
     */
    void execSmoothSequenceD(T prm_top_velo, T prm_end_velo,
                               T prm_target_distance, float prm_p1, float prm_p2,
                               bool prm_endacc_flg = true);


    /**
     * �Ȃ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���x�E���Ԏw��A�����ϓ�)  .
     * �ړ��ɔ�₳��鎞��(Te)��3�̃Z�N�V�����ɕ����A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� p1*Te �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���(or����)�ړ�<BR>
     * �E���� p1*Te �` ���� p2*Te �܂� �E�E�E �g�b�v�X�s�[�h�œ����ړ�<BR>
     * �E���� p2*Te �` ���� Te    �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���(or����)�ړ�<BR>
     * �����}�Q��<BR>
     * <pre>
     *
     *    ���x(v)
     *     ^
     *     |
     *     |                         Vo:�����_�̑��x
     *     |                         Vt:�g�b�v�X�s�[�h
     *     |                         Ve:�ŏI���x
     *   Vt|....___________          Te:���B�ڕW���ԁi�t���[�����j
     *     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *     | /  :         :    |      D:�K�v�Ȉړ�����
     *     |/   :         :    |
     *   Vo|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * �g�b�v�X�s�[�h(Vt)�A�ŏI�X�s�[�h(Ve)�A���B�ڕW����(Te)�A�y�� p1, p2 ���w�肷��B<BR>
     * �K�v�Ȉړ�����(D)�͓����Ŏ����v�Z�����肳���B<BR>
     * <BR>
     * @param prm_top_velo �g�b�v�X�s�[�h(Vt)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_target_frames ���B�ڕW����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     * @param prm_endacc_flg true:�ڕW���ԂɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void execSmoothSequenceT(T prm_top_velo, T prm_end_velo,
                               int prm_target_frames, float prm_p1, float prm_p2,
                               bool prm_endacc_flg = true);






    /**
     * �ړ������x���A�u��~���ړ������v�ɂ��ݒ肷�� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^       a:�������x
     *     |       D:�ړ������i��~�ɔ�₷�����j
     *     |      Vo:�����_�̑��x
     *   Vo|      Te:��~����t���[��
     *     |�_
     *     |  �_
     *     |    �_ �Εӂ̌X��a
     *     |   D  �_
     *     |        �_
     *   --+----------�_-----> ����(t)
     *   0 |          Te
     *
     *    D = (1/2) Vo Te  �E�E�E�@
     *    a = -Vo / Te     �E�E�E�A
     *    �@���
     *    Te = 2D / Vo
     *    ������A�֑��
     *    a = -Vo / (2D / Vo)
     *    �� a = -(Vo^2) / 2D
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�����̋���(D)����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * ��~�܂ł̃t���[��(Te) �� ����(D) �ɂ��ω����邽�ߎw��s�B<BR>
     * @param prm_target_distance ��~���ړ�����(D)
     */
    void setAcceToStop(T prm_target_distance);

    /**
     * �ړ������x���A�u�ڕW���B���x�v�u�ړ�����(�B����܂łɔ�₷����)�v�ɂ��ݒ� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^        a:�����x
     *     |        D:�ړ������i�ڕW���B���x�ɒB����܂łɔ�₷�����j
     *     |       Vo:�����_�̑��x
     *     |       Vt:�ڕW���B���x
     *     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
     *   Vt|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �Εӂ̌X��a
     *     |�^      |
     *   Vo|    D   |
     *     |        |
     *   --+--------+---> ����(t)
     *   0 |        Te
     *
     *    D = (1/2) (Vo + Vt) Te   �E�E�E�@
     *    a = (Vt - Vo) / Te         �E�E�E�A
     *    �@��� Te = (Vt - Vo) / a
     *    ������A�֑��
     *    D = (Vt^2 - Vo^2) / 2a
     *    �� a = (Vt^2 - Vo^2) / 2D
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�ڕW���B���x(Vt)�ƁA�ړ�����(D)����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * �ڕW���B�܂ŕK�v�ȃt���[��(Te) �̓p�����[�^�ɂ��ω����邽�ߎw��s�B<BR>
     * �ߑ��FsetAcceBy_Dv(0, D) �� setAcceToStop(D) �Ɠ����ł���
     * @param prm_target_distance  �ڕW���B���x�ɒB����܂łɔ�₷����(D)
     * @param prm_target_velo �ڕW���B���x(Vt)
     */
    void setAcceBy_Dv(T prm_target_distance, T prm_target_velo);


    /**
     * �ړ������x���A�u�ڕW���B���x�v�u��₷���ԁv�ɂ��ݒ� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^        a:�����x
     *     |        D:�ړ�����
     *     |       Vo:�����_�̑��x
     *     |       Vt:�ڕW���B���x
     *     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
     *   Vt|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �Εӂ̌X��a
     *     |�^      |
     *   Vo|    D   |
     *     |        |
     *   --+--------+---> ����(t�t���[��)
     *   0 |        Te
     *
     *    a = (Vt-Vo) / Te
     *    D�͖���
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�ڕW���B���x(Vt)�ƁA���̓��B����(Te) ����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * �ړ�����(D)�́A�p�����[�^�ɂ��ω����邽�ߎw��s�B<BR>
     * @param prm_target_frames ��₷����(Te)
     * @param prm_target_velo  �ڕW���B���x(Vt)
     */
    void setAcceBy_tv(int prm_target_frames, T prm_target_velo);

    /**
     * �f�X�g���N�^.
     * �����ێ�����v�f�̒l�́Anullptr�Ŗ����ꍇ�A���ꂼ�� delete �ɂ��������܂��B<BR>
     * TODO:delete[] �₻�̑��̉�����@�ɑΉ�
     */
    virtual ~GgafDynamicVariable();


};

//////////////////////////////////////////////////////////////////

/**
 * ��������͎�����
 */

template<class T>
GgafDynamicVariable<T>::GgafDynamicVariable(T* prm_pVariable, T prm_max_velo, T prm_max_acce) :
    GgafObject() {
    _pVariable = prm_pVariable;
    _velo = (T)0;
    _acce = (T)0;
    _veloTop =  (T)prm_max_velo;
    _veloBottom =  (T)(-prm_max_velo);
    _acceTop =  (T)prm_max_acce;
    _acceBottom =  (T)(-prm_max_acce);


    _smooth_velo_seq_flg = false;
    _smooth_velo_seq_endacc_flg = true;
    _smooth_velo_seq_top_velo = (T)0;
    _smooth_velo_seq_end_velo = (T)0;
    _smooth_velo_seq_target_distance = (T)0;
    _smooth_velo_seq_distance = (T)0;
    _smooth_velo_seq_target_frames = 0;
    _smooth_velo_seq_frame_of_spent = 0;
    _smooth_velo_seq_p1 = 0;
    _smooth_velo_seq_p2 = 0;
    _smooth_velo_seq_progress = -1;
}

template<class T>
void GgafDynamicVariable<T>::behave() {
    //X�������ړ������x�̏���
    _velo += _acce;
    setVelo(_velo);

    //�Ȃ߂炩�ړ��V�[�N�G���X�N����
    if (_smooth_velo_seq_flg) {
        if (_smooth_velo_seq_target_frames < 0) {
            //�ڕW�����w��̏ꍇ
            if (_smooth_velo_seq_progress == 0) {
                //�����ݒ�
                setAcceBy_Dv(_smooth_velo_seq_p1, _smooth_velo_seq_top_velo);
                _smooth_velo_seq_progress++;
            } else if (_smooth_velo_seq_progress == 1) {
                //������
                if (_smooth_velo_seq_distance >= _smooth_velo_seq_p1) {
                    //p1 �ɓ��B����� ������
                    setAcce(0);
                    setVelo(_smooth_velo_seq_top_velo);
                    _smooth_velo_seq_progress++;
                }
            } else if (_smooth_velo_seq_progress == 2) {
                //������
                if (_smooth_velo_seq_distance >= _smooth_velo_seq_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setAcceBy_Dv(_smooth_velo_seq_target_distance - _smooth_velo_seq_distance, _smooth_velo_seq_end_velo);
                    _smooth_velo_seq_progress++;
                }
            } else if (_smooth_velo_seq_progress == 3) {
                //������
                if (_smooth_velo_seq_distance >= _smooth_velo_seq_target_distance) {
                    //�ڕW�����֓��B
                    setVelo(_smooth_velo_seq_end_velo);
                    if (_smooth_velo_seq_endacc_flg) {
                        setAcce(0);
                    }
                    _smooth_velo_seq_progress++;
                    _smooth_velo_seq_flg = false; //�����܂�
                }
            }
        } else {
            //�ڕW���Ԏw��̏ꍇ
            if (_smooth_velo_seq_progress == 0) {
                //�����ݒ�
                setAcceBy_tv(_smooth_velo_seq_p1, _smooth_velo_seq_top_velo);
                _smooth_velo_seq_progress++;
            } else if (_smooth_velo_seq_progress == 1) {
                //������
                if (_smooth_velo_seq_frame_of_spent >= _smooth_velo_seq_p1) {
                    //p1 �ɓ��B����� ������
                    setAcce(0);
                    setVelo(_smooth_velo_seq_top_velo);
                    _smooth_velo_seq_progress++;
                }
            } else if (_smooth_velo_seq_progress == 2) {
                //������
                if (_smooth_velo_seq_frame_of_spent >= _smooth_velo_seq_p2) {
                    //p2 �ɓ��B����� ����t���[�����猸����
                    setAcceBy_tv(_smooth_velo_seq_target_frames - _smooth_velo_seq_frame_of_spent, _smooth_velo_seq_end_velo);
                    _smooth_velo_seq_progress++;
                }
            } else if (_smooth_velo_seq_progress == 3) {
                //������
                if (_smooth_velo_seq_frame_of_spent >= _smooth_velo_seq_target_frames) {
                    //�ڕW�����֓��B
                    setVelo(_smooth_velo_seq_end_velo);
                    if (_smooth_velo_seq_endacc_flg) {
                        setAcce(0);
                    }
                    _smooth_velo_seq_progress++;
                    _smooth_velo_seq_flg = false; //�����܂�
                }
            }
        }
    } else {
        _smooth_velo_seq_progress = -1;
    }

    if (_smooth_velo_seq_flg) {
        if (_smooth_velo_seq_target_frames < 0) {
            _smooth_velo_seq_distance+=ABS(_velo);
        } else {
            _smooth_velo_seq_frame_of_spent++;
        }
    } else {

    }


    //Actor�ɔ��f
    (*_pVariable)+= _velo;
}


template<class T>
void GgafDynamicVariable<T>::forceVeloRange(T prm_velo01, T prm_velo02) {
    if (prm_velo01 < prm_velo02) {
        _veloTop = prm_velo02;
        _veloBottom = prm_velo01;
    } else {
        _veloTop = prm_velo01;
        _veloBottom = prm_velo02;
    }
    setVelo(_velo); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

template<class T>
void GgafDynamicVariable<T>::setVelo(T prm_velo) {
    if (prm_velo > _veloTop) {
        _velo = _veloTop;
    } else if (prm_velo < _veloBottom) {
        _velo = _veloBottom;
    } else {
        _velo = prm_velo;
    }
}

template<class T>
void GgafDynamicVariable<T>::addVelo(T prm_velo) {
    _velo += prm_velo;
    if (_velo > _veloTop) {
        _velo = _veloTop;
    } else if (_velo < _veloBottom) {
        _velo = _veloBottom;
    }
}

template<class T>
void GgafDynamicVariable<T>::setAcce(T prm_acce) {
    if (prm_acce > _acceTop) {
        _acce = _acceTop;
    } else if (prm_acce < _acceBottom) {
        _acce = _acceBottom;
    } else {
        _acce = prm_acce;
    }
}

template<class T>
void GgafDynamicVariable<T>::addAcce(T prm_acce) {
    setAcce(_acce + prm_acce);
}

template<class T>
void GgafDynamicVariable<T>::forceAcceRange(T prm_acce01, T prm_acce02) {
    if (prm_acce01 < prm_acce02) {
        _acceTop = prm_acce02;
        _acceBottom = prm_acce01;
    } else {
        _acceTop = prm_acce01;
        _acceBottom = prm_acce02;
    }
    setAcce(_acce); //�Đݒ肵�Ĕ͈͓��ɕ␳
}
template<class T>
void GgafDynamicVariable<T>::setAcceToStop(T prm_target_distance) {
    // a = -(Vo^2) / 2D
    _acce  =  -(1.0*_velo*_velo) / (2.0*prm_target_distance);
    if (_acce < 0) {
        _acce += 1;
    } else {
        _acce -= 1;
    }
    //(frame)((2.0*prm_target_distance) / _velo); //�g�p�t���[����
}

template<class T>
void GgafDynamicVariable<T>::setAcceBy_tv(int prm_target_frames, T prm_target_velo) {
    //a = (Vt-Vo) / Te
    _acce = (prm_target_velo - _velo) / (1.0f*prm_target_frames);
}

template<class T>
void GgafDynamicVariable<T>::setAcceBy_Dv(T prm_target_distance, T prm_target_velo) {
    // a = (Vt^2 - Vo^2) / 2D
    _acce =  ((1.0f*prm_target_velo*prm_target_velo) - (1.0f*_velo*_velo)) / (2.0f*prm_target_distance);
    if (_acce < 0) {
        _acce += 1;
    } else {
        _acce -= 1;
    }
    //(frame)((1.0*prm_target_velo - _velo) / _acce); //�g�p�t���[����

    // �y�⑫�z
    // Vo <= 0  ����  Vt <= 0 �ꍇ�A���邢��  Vo >= 0  ����  Vt >= 0  �ꍇ�́AD(�ڕW����)����L���Ŗ��Ȃ��B
    // �ł�
    // Vo < 0   ����  Vt > 0  �ꍇ�A���邢��  Vo > 0   ����  Vt < 0   �ꍇ�́A�ǂ��Ȃ邩�H
    //
    //    ���x(v)
    //     ^        a:�����x
    //     |        D:�ړ������i�ڕW���B���x�ɒB����܂łɔ�₷�����j
    //     |       Vo:�����_�̑��x
    //     |       Vt:�ڕW���B���x
    //     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
    //  Vo |
    //     |�_
    //     |  �_  �X����a
    //     | D1 �_
    //     |      �_ Tc     Te
    //   --+--------�_------+---> ����(t)
    //   0 |          �_ D2 |
    //     |            �_  |
    //   Vt|..............�_|
    //     |
    //
    //    D ��S�̂̈ړ������Ƃ���
    //    D = D1 - D2 , v = 0 �� t �� Tc �Ƃ���
    //
    //    D1 = (1/2) Vo Tc
    //    D2 = (1/2) -Vt (Te - Tc)
    //    D = D1 - D2 ���
    //    D = (1/2) Vo Tc -  { (1/2) -Vt (Te - Tc) }
    //      = (Vo Tc + Vt Te - Vt Tc) / 2    �E�E�E�@
    //
    //    ���� v = a t + Vo �ɂ����� v = 0 �� t = Tc �ł���̂�
    //    0 = a Tc + Vo
    //    Tc = -Vo / a
    //    ����� �@ �֑��
    //    D = (Vo (-Vo / a) + Vt Te - Vt (-Vo / a)) / 2 �E�E�E�A
    //    �܂� a = (Vt - Vo) / Te �ł���̂�
    //    Te = (Vt - Vo) / a ����� �A �֑��
    //    �����
    //    D = (Vo (-Vo / a) + Vt ((Vt - Vo) / a) - Vt (-Vo / a)) / 2
    //
    //    a �ɂ��ĉ���
    //
    //    D = ( -(Vo^2) / a  + (Vt (Vt - Vo)) / a + (Vt Vo) / a) / 2
    //    a D = { -(Vo^2) + (Vt (Vt - Vo)) + (Vt Vo) } / 2
    //    a = { -(Vo^2) + (Vt (Vt - Vo)) + (Vt Vo) } / 2D
    //    a = (-(Vo^2) + Vt^2 - Vt Vo + Vt Vo) / 2D
    //    a = (Vt^2 - Vo^2) / 2D
    //
    //    ���� a = (Vt^2 - Vo^2) / 2D �ƂȂ�̂�
    //    Vo <= 0  ����  Vt <= 0 �ꍇ�A���邢��  Vo >= 0  ����  Vt >= 0  �ꍇ�Ɠ����ł���
}

template<class T>
void GgafDynamicVariable<T>::execSmoothSequence(T prm_end_velo, T prm_target_distance,
                                         int prm_target_frames, float prm_p1, float prm_p2,
                                         bool prm_endacc_flg) {
    _smooth_velo_seq_flg = true;
    _smooth_velo_seq_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_velo_seq_p2 = (int)(prm_target_frames*prm_p2);
    _smooth_velo_seq_end_velo = prm_end_velo;
    _smooth_velo_seq_target_distance = prm_target_distance;
    _smooth_velo_seq_distance = 0;
    _smooth_velo_seq_target_frames = prm_target_frames;
    _smooth_velo_seq_frame_of_spent = 0;
    _smooth_velo_seq_progress = 0;

    //���g�b�v�X�s�[�h(Vt) ���v�Z��
    //
    //    ���x(v)
    //     ^
    //     |                          D:�ڕW�ړ�����
    //     |                         Vo:�����_�̑��x
    //     |                         Vt:�g�b�v�X�s�[�h
    //     |                         Ve:�ŏI���x
    //   Vt|....�Q�Q�Q�Q�Q           Te:�ڕW���ԁi�t���[�����j
    //     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��
    //   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��
    //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
    //     |/   :         :    |
    //   Vo|    :    D    :    |
    //     |    :         :    |
    //   --+----+---------+----+-----> ����(t:�t���[��)
    //   0 |  p1*Te     p2*Te  Te
    //
    // �ړ�����D�́A���̑�`�{�����̒����`�{�E�̑�` �̖ʐςł���A
    // D = (1/2) (Vo + Vt) p1 Te + Vt (p2-p1)Te  +  (1/2) (Ve + Vt) (1-p2)Te
    // �����Vt�ɂ��ĉ���
    // Vt = ( 2D - p1 Te Vo + (p2 - 1) Te Ve ) / ( (p2 - p1 + 1) Te )
    _smooth_velo_seq_top_velo =
         ((2.0*prm_target_distance) - (prm_p1*prm_target_frames*_velo) + ((prm_p2-1.0)*prm_target_frames*prm_end_velo))
         / ((prm_p2-prm_p1+1.0)*prm_target_frames);

}

template<class T>
void GgafDynamicVariable<T>::execSmoothSequenceD(T prm_top_velo, T prm_end_velo,
                                          T prm_target_distance, float prm_p1, float prm_p2,
                                          bool prm_endacc_flg) {
    _smooth_velo_seq_flg = true;
    _smooth_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_velo_seq_top_velo = prm_top_velo;
    _smooth_velo_seq_end_velo = prm_end_velo;
    _smooth_velo_seq_target_distance = prm_target_distance;
    _smooth_velo_seq_distance = 0;
    _smooth_velo_seq_target_frames = -1; //�ڕW���Ԃ͎g��Ȃ��ꍇ�͕���ݒ肵�Ă���(��������Ŏg�p)
    _smooth_velo_seq_frame_of_spent = 0;
    _smooth_velo_seq_p1 = (int)(prm_target_distance*prm_p1);
    _smooth_velo_seq_p2 = (int)(prm_target_distance*prm_p2);
    _smooth_velo_seq_progress = 0;
}

template<class T>
void GgafDynamicVariable<T>::execSmoothSequenceT(T prm_top_velo, T prm_end_velo,
                                          int prm_target_frames, float prm_p1, float prm_p2,
                                          bool prm_endacc_flg) {
    _smooth_velo_seq_flg = true;
    _smooth_velo_seq_endacc_flg = prm_endacc_flg;
    _smooth_velo_seq_top_velo = prm_top_velo;
    _smooth_velo_seq_end_velo = prm_end_velo;
    _smooth_velo_seq_target_distance = 0;
    _smooth_velo_seq_distance = 0;
    _smooth_velo_seq_target_frames = prm_target_frames;
    _smooth_velo_seq_frame_of_spent = 0;
    _smooth_velo_seq_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_velo_seq_p2 = (int)(prm_target_frames*prm_p1);
    _smooth_velo_seq_progress = 0;
}


template<class T>
GgafDynamicVariable<T>::~GgafDynamicVariable() {
}

}
#endif /*GGAFDYNAMICVARIABLE_H_*/
