#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

#define  ___BeginSynchronized ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  ___EndSynchronized ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))
/**
 * �_�N���X.
 * ��ɂ��̐�(GgafUniverse)���Ǘ������삷�邱�Ƃ�ړI�Ƃ���N���X�ł��B��Ԃ��炢�B<BR>
 * �{�N���X�� be() ���\�b�h���Ăё����邱�ƂŁA���̐����������ƂɂȂ�A�Ƃ����݌v�B<BR>
 * �C���X�^���X�͂P�ł��B<BR>
 * TODO:�O���[�o���ȎQ�Ƃ�ێ�������֗����N���X�ɂȂ����G�B<BR>
 * TODO:�ŏI�I�ɂ� �_���Q�� new ���āA���݂� be() �����s����΁A�Q�[�����Q���s���삷��悤�ɂ��悤���ȁB
 * (����:GdxfwWorld�N���X)
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class GgafGod : public GgafObject {

private:

    /** behave���s�������t���O */
    bool _is_behaved_flg;
    /** materialize���s�������t���O */
    bool _is_materialized_flg;
public:
    /** be() �ł��邩�ǂ��� */
    bool _can_be;
    /** be() �����ǂ��� */
    bool _is_being;
    /** [r]���g */
    static GgafGod* _pGod;
    /** [r]�����H��(�ʃX���b�h)�̃G���[��ԁBNULL������ғ����^not NULL���ُ픭�� */
    static GgafCriticalException* _pException_Factory;
    /** [r]���ɂ��̐������������鎞�Ԃ̃I�t�Z�b�g */
    static DWORD _aTime_OffsetOfNextFrame[];
    /** [r]GgafFactory::work �X���b�h�n���h��  */
    HANDLE _handleFactory01;
    /** [r]GgafFactory::work �X���b�hID  */
    unsigned int _thID01;
    /** [r]�N���e�B�J���Z�N�V�����i�Z�}�t�H�j */
    static CRITICAL_SECTION CS1;
    /** [r]�N���e�B�J���Z�N�V�����i�Z�}�t�H�j */
    static CRITICAL_SECTION CS2;
    /** [r]�_�̃t���[���J�n�V�X�e������ */
    DWORD _time_at_beginning_frame;
    /** [r]���ɂ��̐�������������V�X�e������ */
    DWORD _expected_time_of_next_frame;
    /** [r]�_�a������̃t���[���� */
    DWORD _godframe;
    /** [r]���̐������o���ł��Ȃ������i�X�L�b�v�����j�� */
    DWORD _skip_count_of_frame;
    /** [r]���̐� */
    GgafUniverse* _pUniverse;
    /** [r]fps�l�i��1000ms���Ɍv�Z�����j */
    float _fps;
    /** [r]�O��fps�v�Z���̃V�X�e������ */
    DWORD _time_prev;
    /** [r]�`��t���[���J�E���^ */
    DWORD _frame_of_visualize;
    /** [r]�O��fps�v�Z���̕`��t���[���J�E���g�l */
    DWORD _frame_of_prev_visualize;
    /** [r]���t���[���̕`��� */
    static int _num_actor_drawing;


    bool _was_cleaned;
    /**
     * �R���X�g���N�^ .
     * �ʃX���b�h�ōH����ғ������܂��B
     */
    GgafGod();

    /**
     * �݂�܂��B�Ƃ������\�b�h .
     * �_���݂邷�Ȃ킿�A���̐��������A�A�v�����i�s���܂��B<BR>
     * OS���ŁA���̃��\�b�h���Ђ�����Ăё����Ă��������B<BR>
     */
    void be();

    /**
     * ���̐��̏u�Ԃ�n�� .
     */
    virtual void presentUniversalMoment();

    /**
     * ���̐���R������ .
     */
    virtual void executeUniversalJudge();

    /**
     * ���̐��̋�I�Ȃ��̂��쐬 .
     */
    virtual void makeUniversalMaterialize();

    /**
     * ���̐��̏�Ԃ����o�� .
     */
    virtual void presentUniversalVisualize();

    /**
     * ���̐��̌�n�� .
     */
    virtual void finalizeUniversal();

    /**
     * ���̐����擾 .
     * ���ʂŃI�[�o�[���C�h�\�B<BR>
     * @return ���̐�
     */
    virtual GgafUniverse* getUniverse() {
        return _pUniverse;
    }

    /**
     * ���̐���n�� .
     * ���ʂł��̐��̐������@���������Ă��������B<BR>
     * @return ���̐�
     */
    virtual GgafUniverse* createUniverse() = 0;

    virtual void clean();

    virtual ~GgafGod();
};

}
#endif /*GGAFGOD_H_*/
