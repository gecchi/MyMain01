#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

#define  ___BeginSynchronized ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  ___EndSynchronized ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))

/**
 * �_�N���X.
 * ��ɂ��̐����Ǘ������삷�邱�Ƃ�ړI�Ƃ���N���X�ł��B��Ԃ��炢�B<BR>
 * �{�N���X�� be() ���\�b�h���Ăё����邱�ƂŁA���̗]�͓����܂��B<BR>
 * ��{�I�ɃC���X�^���X�͂P�ł��B<BR>
 * ���̑��A�A�v�����ŃO���[�o���ȎQ�Ƃ��݂�����֗����N���X�ł�����B<BR>
 * TODO:�ŏI�I�ɂ� �_���Q�� new ���āA���݂� be() �����s����΁A�Q�[�����Q���s���삷��悤�ɂ��悤�B
 */
class GgafGod : public GgafObject {

public:
    /** ���g */
    static GgafGod* _pGod;

    /** �����H��(�ʃX���b�h)�̃G���[��ԁBNULL������ғ����^not NULL���ُ픭�� */
    static GgafCriticalException* _pException_Factory;
    /** ���ɂ��̐������������鎞�Ԃ̃I�t�Z�b�g */
    static DWORD _aTime_OffsetOfNextFrame[];

    /** GgafFactory::work �X���b�h�n���h��  */
    HANDLE _handleFactory01;
    /** GgafFactory::work �X���b�hID  */
    unsigned int _thID01;
    /** �N���e�B�J���Z�N�V�����i�Z�}�t�H�j */
    static CRITICAL_SECTION CS1;
    static CRITICAL_SECTION CS2;

    /** �_�̃t���[���J�n�V�X�e������ */
    DWORD _time_at_beginning_frame;
    /** ���ɂ��̐�������������V�X�e������ */
    DWORD _expected_time_of_next_frame;
    /** �_�a������̃t���[���� */
    DWORD _godframe;
    /** ���̐������o���ł��Ȃ������i�X�L�b�v�����j�� */
    DWORD _skip_count_of_frame;
    /** ���̐� */
    GgafUniverse* _pUniverse;

    /** fps�l�i��1000ms���Ɍv�Z�����j */
    float _fps;
    /** �O��fps�v�Z���̃V�X�e������ */
    DWORD _time_prev;
    /** �`��t���[���J�E���^ */
    DWORD _frame_of_visualize;
    /** �O��fps�v�Z���̕`��t���[���J�E���g�l */
    DWORD _frame_of_prev_visualize;

    /**  */
    static int _num_actor_drawing;

    bool _is_behaved_flg;
    bool _is_materialized_flg;

    /**
     * �R���X�g���N�^.
     * �ʃX���b�h�ōH����ғ������܂��B
     */
    GgafGod();

    /**
     * �݂�܂��B�Ƃ������\�b�h�B.<BR>
     * �_���݂邷�Ȃ킿�A���̐��������A�A�v�����i�s���܂��B<BR>
     * OS���ŁA���̃��\�b�h���Ђ�����Ăё����Ă��������B<BR>
     */
    void be();

    /**
     * ���̐��̏u�Ԃ�n��<BR>
     */
    virtual void presentUniversalMoment();

    /**
     * ���̐��̏u�Ԃ�R������<BR>
     */
    virtual void enforcementUniversalJudge();

    /**
     * ���̐��̏u�Ԃ̋�I�Ȃ��̂��쐬<BR>
     */
    virtual void makeUniversalMaterialize();

    /**
     * ���̐��̏u�Ԃ̏�Ԃ��f����<BR>
     */
    virtual void presentUniversalVisualize();

    /**
     * ���̐��̌�n��<BR>
     */
    virtual void finalizeUniversal();

    /**
     * ���̐����擾<BR>
     * ���ʂŃI�[�o�[���C�h���Ă��������B<BR>
     * @return ���̐�
     */
    virtual GgafUniverse* getUniverse() {
        return _pUniverse;
    }

    /**
     * ���̐���n��<BR>
     * @return ���̐�
     */
    virtual GgafUniverse* createUniverse() = 0;

    virtual ~GgafGod();
};

}
#endif /*GGAFGOD_H_*/
