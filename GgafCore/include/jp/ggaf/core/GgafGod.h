#ifndef GGAFGOD_H_
#define GGAFGOD_H_
namespace GgafCore {

#define  ___BeginSynchronized ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  ___EndSynchronized ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))

/**
 * �_�N���X.
 * ��ɐ��E(GgafWorld)���Ǘ����܂��B<BR>
 * ���̐����Q�[���A�v���Ƃ���Ȃ�΁A���̃N���X�����ɂ��炢�B<BR>
 * ��{�I�ɃC���X�^���X�͂P�ł��B<BR>
 * ���̑��A�v�����ŃO���[�o���ȎQ�Ƃ��W����������A�Ȃɂ��ƔώG�ŕ֗����N���X�ł�����B<BR>
 * TODO:�Q�� new ���āA���݂� be() �����s����΁A���s���삷�邩����
 */
class GgafGod : public GgafObject {

public:
    /** ���g */
    static GgafGod* _pGod;

    /** �����H��(�ʃX���b�h)�̃G���[��ԁBNULL������ғ����^not NULL���ُ픭�� */
    static GgafCriticalException* _pException_Factory;
    /** ���ɐ��E�����������鎞�Ԃ̃I�t�Z�b�g */
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
    /** ���ɐ��E������������V�X�e������ */
    DWORD _expected_time_of_next_frame;
    /** �_�a������̃t���[���� */
    DWORD _godframe;
    /** ���E�����o���ł��Ȃ������i�X�L�b�v�����j�� */
    DWORD _skip_count_of_frame;
    /** ���E */
    GgafWorld* _pWorld;

    /** fps�l�i��1000ms���Ɍv�Z�����j */
    float _fps;
    /** �O��fps�v�Z���̃V�X�e������ */
    DWORD _time_prev;
    /** �`��t���[���J�E���^ */
    DWORD _frame_of_visualize;
    /** �O��fps�v�Z���̕`��t���[���J�E���g�l */
    DWORD _frame_of_prev_visualize;

    /**  */
    static int _num_actor_playing;

    bool _is_behaved_flg;
    bool _is_materialized_flg;

    /**
     * �R���X�g���N�^.
     * �ʃX���b�h�ōH����ғ������܂��B
     */
    GgafGod();

    /**
     * �����ɋ��Ă܂�.<BR>
     */
    void be();

    /**
     * ���E�𑶍݂�����<BR>
     */
    virtual void makeWorldBe();

    /**
     * ���E��R������<BR>
     */
    virtual void makeWorldJudge();

    /**
     * ���E���������<BR>
     */
    virtual void makeWorldMaterialize();

    /**
     * ���E�����o������<BR>
     */
    virtual void makeWorldVisualize();

    /**
     * ���E�̌�n��<BR>
     */
    virtual void makeWorldFinalize();

    /**
     * ���E���擾<BR>
     * @return ���E
     */
    virtual GgafWorld* getWorld() {
        return _pWorld;
    }

    /**
     * ���E��n��<BR>
     * @return ���E
     */
    virtual GgafWorld* createWorld() = 0;

    virtual ~GgafGod();
};

}
#endif /*GGAFGOD_H_*/
