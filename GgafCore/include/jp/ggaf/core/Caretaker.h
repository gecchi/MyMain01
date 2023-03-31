#ifndef GGAF_CORE_CARETAKER_H_
#define GGAF_CORE_CARETAKER_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#ifndef _MSC_VER
    #include <atomic>
#endif

#define ORDER_ID_MAX     (0xffffffffffffffffULL)

#undef pCARETAKER
#define pCARETAKER (GgafCore::Caretaker::ask())

namespace GgafCore {

#define  BEGIN_SYNCHRONIZED1   ::EnterCriticalSection(&(GgafCore::Caretaker::CS1))
#define  END_SYNCHRONIZED1     ::LeaveCriticalSection(&(GgafCore::Caretaker::CS1))
#define  BEGIN_SYNCHRONIZED2   ::EnterCriticalSection(&(GgafCore::Caretaker::CS2))
#define  END_SYNCHRONIZED2     ::LeaveCriticalSection(&(GgafCore::Caretaker::CS2))
//#define  BEGIN_SYNCHRONIZED3   ::EnterCriticalSection(&(GgafCore::Caretaker::CS3))
//#define  END_SYNCHRONIZED3     ::LeaveCriticalSection(&(GgafCore::Caretaker::CS3))
#define  SLOWDOWN_MODE_DEFAULT 0
#define  SLOWDOWN_MODE1 1
#define  SLOWDOWN_MODE2 2
/**
 * �Ǘ��� .
 * ��ɂ��̐�(Spacetime)���Ǘ������삷�邱�Ƃ�ړI�Ƃ���N���X�ł��B���Ԃ��Ԃ��炢�B<BR>
 * �{�N���X�� present() ���\�b�h���Ăё����邱�ƂŁA���̐����������ƂɂȂ�A�Ƃ����݌v�B<BR>
 * �C���X�^���X�͂P�ł��B<BR>
 * TODO:�O���[�o���ȎQ�Ƃ�ێ�������֗����N���X�ɂȂ����G�B<BR>
 * TODO:�ŏI�I�ɂ� �Ǘ��҂��Q�� new ���āA���݂� present() �����s����΁A�Q�[�����Q���s���삷��悤�ɂ��悤���ȁB
 * (����:GdxfwWorld�N���X)
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class Caretaker : public Object {

private:
    /** behave���s�������t���O */
    bool _is_behaved_flg;
    /** materialize���s�������t���O */
    bool _is_materialized_flg;

public:
    /** [r] �N���e�B�J���Z�N�V�������̂P */
    static CRITICAL_SECTION CS1;
    /** [r] �N���e�B�J���Z�N�V�������̂Q */
    static CRITICAL_SECTION CS2;
//    /** [r] �N���e�B�J���Z�N�V�������̂R */
//    static CRITICAL_SECTION CS3;
    /** [r] ���g */
    static Caretaker* _pCaretaker;
    /** [r] ���ɂ��̐������������鎞�Ԃ̃I�t�Z�b�g */
    //static DWORD _aaTime_offset_of_next_view[3][60];
    //static double _aTime_offset_of_next_view[3];

    //WORD _base_fps;
    DWORD* _apaTime_offset_of_next_view[3];
    double _aTime_offset_of_next_view[3];

    /** [r] �����Ǘ���(�ʃX���b�h)�̃G���[��ԁBnullptr������ғ����^not nullptr���ُ픭�� */
    CriticalException* _pException_god;


    /** [r] GgafCore::Caretaker::love �X���b�h�n���h��  */
    HANDLE _handle_god_love01;
    /** [r] GgafCore::Caretaker::love �X���b�hID  */
    unsigned int _th_id01;

    /** [r] GgafCore::Caretaker::send �X���b�h�n���h��  */
    HANDLE _handle_god_send03;
    /** [r] GgafCore::Caretaker::send �X���b�hID  */
    unsigned int _th_id03;

//    /** [r] �Ǘ��҂̃t���[���J�n�V�X�e������ */
//    DWORD _time_at_beginning_frame;
    /** [r] ���ɂ��̐�������������V�X�e������ */
    DWORD _time_of_next_view;

    DWORD _time_calc_fps_next;

    /** [r] �Ǘ��Ғa������̃t���[���� */
    frame _frame_of_Caretaker;
    frame _cnt_frame;

    /** [r] ���̐������o���ł��Ȃ������i�X�L�b�v�����j�� */
    int _skip_count_of_frame;
    /** [r] ���̐� */
    Spacetime* _pSpacetime;
    /** [r] fps�l�i��1000ms���Ɍv�Z�����j */
    double _fps;


    /** [r] �`��t���[���J�E���^ */
    frame _visualize_frames;
    /** [r] �O��fps�v�Z���̕`��t���[���J�E���g�l */
    frame _prev_visualize_frames;
#ifdef MY_DEBUG
    /** [r] 1�t���[���̕`��� */
    static unsigned int _num_draw;
    static unsigned int _num_draw_actors;
#endif
    /** [r] 1�t���[���̊������A�N�^�[ */
    static unsigned int _num_active_actors;

    /** [r] �`�揈���A�ō��X�L�b�v�t���[���� */
    int _max_skip_frames;
    /** [r] ���݂̏����������[�h 0:60fps 1:40fps 2:30fps�B_aaTime_offset_of_next_view�̈�ڂ̗v�f */
    int _slowdown_mode;

    bool _was_cleaned;
public:
    /**
     * �R���X�g���N�^ .
     * �ʃX���b�h�ŊǗ��҂��ғ������܂��B
     */
    Caretaker();

    /**
     * �񋟂��� .
     * �Ǘ��҂��񋟂���A���Ȃ킿�A���̐�(Spacetime)�������A�A�v�����i�s���܂��B<BR>
     * ����Ăяo�����A���̐�(Spacetime)���쐬����܂��B<BR>
     * �A�v���P�[�V�����́A�ŏ����ԒP�ʂł��̃��\�b�h���Ђ�����Ăё����Ă��������B<BR>
     */
    void present();

    /**
     * ���̐���FPS��ݒ肷�� .
     * ���ݒ�̏ꍇ�̓f�t�H���g�� 60 FPS
     * @param prm_fps FPS�l
     */
    void setSpacetimeFps(int prm_fps);

    /**
     * ���̐��́A�ŏ����ԒP�ʂ̎��Ԃ𗬂� .
     */
    virtual void presentMoment();

    /**
     * ���̐��́A�ŏ����ԒP�ʂ̐U�镑�����s�� .
     */
    virtual void presentBehave();

    /**
     * ���̐��́A�ŏ����ԒP�ʂ̏u�Ԃɂ��ĐR���i�`�F�b�N�j���� .
     */
    virtual void presentJudge();

    /**
     * ���̐��́A�ŏ����ԒP�ʂ̏u�Ԃ���̉����� .
     */
    virtual void presentMaterialize();

    /**
     * ��̉����ꂽ�����A�يE�̐l�ԋ��i����j�ɂ��F���ł���悤�Ɏ��o������ .
     */
    virtual void presentVisualize();

    /**
     * ���̐��̎��̍ŏ����ԒP�ʂ̏u�Ԃ�n�����邽�߂̏����A��n�� .
     */
    virtual void presentClosing();

    /**
     * ���̐����擾 .
     * ���ʂŃI�[�o�[���C�h�\�B<BR>
     * @return ���̐�
     */
    virtual Spacetime* getSpacetime() {
        return _pSpacetime;
    }

    /**
     * ���̐���n�� .
     * ���ʂł��̐��̑n�����@���������Ă��������B<BR>
     * @return ���̐�
     */
    virtual Spacetime* createSpacetime() = 0;

    /**
     * �t���[���Ǝ��Ԃ̓������s��
     */
    void syncTimeFrame() {
        _sync_frame_time = true;
    }

    void calmDown();

    virtual void clean();

    /**
     * �Ǘ��ҁu���܂����`�I�v .
     * ��O�������ɃR�[���o�b�N����܂��B
     */
    virtual void oops() {
        _TRACE_("(-_-;) {Oops!");
    }

    /**
     * �y�� .
     * @return ����
     */
    static Caretaker* ask() {
        return GgafCore::Caretaker::_pCaretaker;
    }

    virtual ~Caretaker();


private:

    DWORD* getArrTimeOffset(DWORD sec, DWORD fps);

    /**
     * �Ǘ��҂ւ̂�肩���̑҂��s��ɐV���Ȃ�肩���ǉ�����i���C���X���b�h���g�p�j .
     * @param prm_cradle_no	��肩���ԍ�
     * @param prm_pFunc	���ۂɏj���������s���֐��̃|�C���^
     * @param prm_pWisher �]�񂾐l
     * @param prm_pReceiver �󂯎��\���
     * @param prm_pArg1	�j���������s���֐��ւ̈���1
     * @param prm_pArg2	�j���������s���֐��ւ̈���2
     * @param prm_pArg3	�j���������s���֐��ւ̈���3
     */
    void addCradle(uint64_t prm_cradle_no,
                   Object* (*prm_pFunc)(void*, void*, void*),
                   Object* prm_pWisher,
                   Object* prm_pReceiver,
                   void* prm_pArg1,
                   void* prm_pArg2,
                   void* prm_pArg3);

    /**
     * �Ǘ��҂ւ̂�肩���s����������A�����󂯎��i���C���X���b�h���g�p�j .
     * ���j���������ꍇ�A�j������������܂ő҂B<BR>
     * @param prm_cradle_no	��肩���ԍ�
     * @param prm_pReceiver	���l
     * @param prm_was_just_wondering ������ƋC�ɂȂ��������t���O
     *                  true:�����󂯂Ƃ�܂ő҂��A��肩�����X�g������o���Ȃ�
     *                  false:�����󂯂Ƃ�A��肩�����X�g����폜
     * @return	���̃|�C���^
     */
    void* takeOutObject(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering);


public:
    /** �擪�̂�肩�� */
    Cradle* _pCradleRoot;
    /** ���ݏj�����̂�肩�� */
    Cradle* _pCradleBlessing;
    //_pCradleBlessing �́A�S�ďj���ς݂̏ꍇ�A�ŏI��肩�����w���Â���
    //�S�ďj���ς݂��A��肩�����S�Ĉ������ꂽ�ꍇ�� nullptr �ɂȂ�B
    //_is_last_cradle_flg == false ����ɔ��肵�A�ŏI��肩���łȂ��Ȃ�����i�V�K��肩��������΁j�A
    //�j�����s���Ď��ɐi�߂�B _is_last_cradle_flg == false �ɂȂ�܂ŏj�����Â���
    // �܂��A�擪�Ɩ����̂�肩�����|�C���^�łȂ����Ă���(��)

    //      _pCradleRoot
    //        ��
    //      pCradle <-> pCradle <-> pCradle <-> pCradle <-> pCradle <-> pCradle
    //     (�j����)     (�j����)   �i�j�����j   (������)    (������)    (������)
    //                                 ��                                _is_last_cradle_flg == true
    //                           _pCradleBlessing
    //                      �j�����I����ƉE�ɓ���  ===>
    //
    //prev <------�Â���肩��----------------------------------�V������肩��-----> next
    //                                               ��肩���͖����ɂ��Ă���
#ifdef _MSC_VER
    //x86�n�Ȃ�΃A�g�~�b�N��������E�E�E�E�E�E�E�E�B
    /** [r]�����Ă�t���O */
    volatile bool _is_loving_flg;
    /** [r]�x�ރt���O */
    volatile bool _have_to_rest_flg;
    /** [r]�x�ł���t���O */
    volatile bool _is_resting_flg;
    /** [r]���̂���� */
    volatile bool _was_finished_loving_flg;
    /** [r]�يE���蒆�t�t���O */
    volatile bool _is_sending_flg;
    /** [r]�يE���̂���� */
    volatile bool _was_finished_sending_flg;
    /** [r] ���Ԃƃt���[���̓����������[�h����true */
    volatile bool _sync_frame_time;
#else
    /** [r]�����Ă�t���O */
    volatile std::atomic<bool> _is_loving_flg;
    /** [r]�x�ރt���O */
    volatile std::atomic<bool> _have_to_rest_flg;
    /** [r]�x�ł���t���O */
    volatile std::atomic<bool> _is_resting_flg;
    /** [r]���̂���� */
    volatile std::atomic<bool> _was_finished_loving_flg;
    /** [r]�يE���蒆�t���O */
    volatile std::atomic<bool> _is_sending_flg;
    /** [r]�يE���̂���� */
    volatile std::atomic<bool> _was_finished_sending_flg;
    /** [r] ���Ԃƃt���[���̓����������[�h����true */
    volatile std::atomic<bool> _sync_frame_time;
#endif
public:
    /**
     * �Ǘ��҂ɃA�N�^�[���j�����Ă��炤���߂́A��肩��������i���C���X���b�h���g�p�j .
     * @tparam X ��肩���A�N�^�[�̌^
     * @param prm_cradle_no ��肩���ԍ�
     * @param prm_pFunc ���ۂɏj���������s���֐��̃|�C���^
     * @param prm_pWisher ��肩����
     * @param prm_pReceiver ���l
     * @param prm_pArg1 �j���������s���֐��ւ̈���1
     * @param prm_pArg2 �j���������s���֐��ւ̈���2
     * @param prm_pArg3 �j���������s���֐��ւ̈���3
     */
    template<class X>
    void addActorCradle(uint64_t prm_cradle_no,
                        X* (*prm_pFunc)(void*, void*, void*),
                        Object* prm_pWisher,
                        Object* prm_pReceiver,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
        addCradle(prm_cradle_no, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * �Ǘ��҂ɃV�[���쐬�i�j���j���Ă��炤���߂́A��肩��������i���C���X���b�h���g�p�j .
     * @tparam X ��肩���V�[���̌^
     * @param prm_cradle_no ��肩���ԍ�
     * @param prm_pFunc	���ۂɏj���������s���֐��̃|�C���^
     * @param prm_pWisher ��肩����
     * @param prm_pReceiver ���l
     * @param prm_pArg1	�j���������s���֐��ւ̈���1
     * @param prm_pArg2	�j���������s���֐��ւ̈���2
     * @param prm_pArg3	�j���������s���֐��ւ̈���3
     */
    template<class X>
    void addSceneCradle(uint64_t prm_cradle_no,
                        X* (*prm_pFunc)(void*, void*, void*),
                        Object* prm_pWisher,
                        Object* prm_pReceiver,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
        addCradle(prm_cradle_no, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * �]�񂾃A�N�^�[���󂯎��B�i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * ���j���������ꍇ�A�j������������܂ő҂B<BR>
     * @param   prm_cradle_no ��肩���ԍ�
     * @param   prm_pReceiver ���l
     * @param   prm_was_just_wondering ������ƋC�ɂȂ��������t���O
     *                  true:�����󂯂Ƃ�܂ő҂��A��肩�����X�g������o���Ȃ�
     *                  false:�����󂯂Ƃ�A��肩�����X�g����폜
     * @return	�������ꂽ�A�N�^�[�̃|�C���^
     */
    MainActor* takeOutActor(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering = false);

    /**
     * �]�񂾃V�[�����󂯎��B�i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * ���j���������ꍇ�A�j������������܂ő҂B<BR>
     * @param   prm_cradle_no ��肩���ԍ�
     * @param   prm_pReceiver ���l
     * @param   prm_was_just_wondering ������ƋC�ɂȂ��������t���O
     *                  true:�����󂯂Ƃ�܂ő҂��A��肩�����X�g������o���Ȃ�
     *                  false:�����󂯂Ƃ�A��肩�����X�g����폜
     * @return	�������ꂽ�V�[���̃|�C���^
     */
    MainScene* takeOutScene(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering = false);

    /**
     * �]��ŁA�j�������܂ő҂��āA�����Ɏ󂯎��B
     * @tparam X ��肩�����̌^
     * @param prm_pFunc
     * @param prm_pWisher
     * @param prm_pReceiver
     * @param prm_pArg1
     * @param prm_pArg2
     * @param prm_pArg3
     * @param prm_org
     * @return �o���オ������
     */
    template<class X>
    X* makeObject(X* (*prm_pFunc)(void*, void*, void*),
                  Object* prm_pWisher,
                  Object* prm_pReceiver,
                  void* prm_pArg1,
                  void* prm_pArg2,
                  void* prm_pArg3,
                  Object* prm_org) {
        addCradle(ORDER_ID_MAX, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(takeOutObject(ORDER_ID_MAX, prm_org, false));
    }

    template<class X>
    X* makeActor(X* (*prm_pFunc)(void*, void*, void*),
                 Object* prm_pWisher,
                 Object* prm_pReceiver,
                 void* prm_pArg1,
                 void* prm_pArg2,
                 void* prm_pArg3,
                 Object* prm_org) {
        addActorCradle(ORDER_ID_MAX, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(takeOutActor(ORDER_ID_MAX, prm_org, false));
    }

    template<class X>
    X* makeScene(X* (*prm_pFunc)(void*, void*, void*),
                 Object* prm_pWisher,
                 Object* prm_pReceiver,
                 void* prm_pArg1,
                 void* prm_pArg2,
                 void* prm_pArg3,
                 Object* prm_org) {
        addSceneCradle(ORDER_ID_MAX, (Object* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(takeOutScene(ORDER_ID_MAX, prm_org, false));
    }

    /**
     * �]�񂾖����o���オ���Ă��邩���ׂ�B�i���C���X���b�h���g�p�j .
     * @param prm_cradle_no   ��肩���ԍ�
     * @return ��肩���ԍ��̖��̐i����(-2:�Ǘ��҂������Ă��Ȃ�/-1:��肩�����̂�����/0:��肩���͍݂邪���j��/1:�j����/2:�j���ς݁j
     */
    int chkCradle(uint64_t prm_cradle_no);

    /**
     * ���̂Ă� .
     * �h���āi�Ƃ��̖��j�����ׂď����i���C���X���b�h���g�p�j .
     * ���C�������̊Ǘ��҂��Ăяo���܂��B<BR>
     * _pCradleRoot ���w���Ă����肩���̘A�����X�g��S�ĉ������<BR>
     * ���ӁF�K���ȉ��̂悤�ɃN���e�B�J���Z�N�V�����ň͂�ŌĂяo���Ă��������I�B<BR>
     * ���R�[�h�၄ <BR>
     *     BEGIN_SYNCHRONIZED1; // ----->�r���J�n<BR>
     * GgafCore::Caretaker::clean();<BR>
     *     END_SYNCHRONIZED1; // <----- �r���I��<BR>
     */
    void desert();

    /**
     * ������� .
     * �󂯎��͂��������l�����Ȃ������̂ŁA�d���Ȃ��̂�
     * ���肢����Ă�������j������B
     * @param prm_pReceiver �󂯎��͂��������l
     */
    void repent(Object* prm_pReceiver);

    /**
     * �� .
     * �Ǘ��ҁiCaretaker�j�������ݒ莞�ɕʃX���b�h�ň�x���s����܂��B<BR>
     * �Ǘ��҂����ʂ܂Łi�A�v���I���܂Łjloving ���܂��B<BR>
     */
    static unsigned __stdcall love(void* prm_arg);

    /**
     * ���ݖ��g�p .
     * @param prm_arg
     */
    static unsigned __stdcall send(void* prm_arg);

    /**
     * �i���̈� .
     * ��肩������t�ďj��������a�������܂��B
     * @param prm_arg
     */
    unsigned loving(void* prm_arg);

    /**
     * ���ݖ��g�p .
     * @param prm_arg
     */
    unsigned sending(void* prm_arg);

    /**
     * �Ǘ��҈ꎞ�x�~���w�� �i���C���X���b�h���g�p�j .
     * �������Ăяo���Ă������ɋx�~��ԂɂȂ�Ƃ͌���܂���B<BR>
     * isResting() �Ŋ��S�x�~����܂Œ��ׂ鑱����K�v������܂��B<BR>
     */
    void beginRest();
    /**
     * �Ǘ��҂̏�Ԃ��擾�i���C���X���b�h���g�p�j .
     * @return true=�x�~���/false=�ғ����
     */
    bool isResting();

    /**
     * �Ǘ��ҋx�~�̉������w�� �i���C���X���b�h���g�p�j .
     */
    void finishRest();

    /**
     * �j������(�����͂P��) .
     * @tparam X �^
     * @param p1 ����1 (�g�p�����(���O))
     * @param p2 ����2 (���������)
     * @param p3 ����3 (���������)
     * @return �j�����ꂽ��
     */
    template<class X>
    static X* bless(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((const char*)p1);
        return p;
    }

    /**
     * �j������(�����͂Q��) .
     * @tparam X �^
     * @param p1 ����1 (�g�p�����(���O))
     * @param p2 ����2 (�g�p�����)
     * @param p3 ����3 (���������)
     * @return �j�����ꂽ��
     */
    template<class X>
    static X* bless2(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((const char*)p1, (const char*)p2);
        return p;
    }

    /**
     * �j������(�����͂R��) .
     * @tparam X �^
     * @param p1 ����1 (�g�p�����(���O))
     * @param p2 ����2 (�g�p�����)
     * @param p3 ����3 (�g�p�����)
     * @return �j�����ꂽ��
     */
    template<class X>
    static X* bless3(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((const char*)p1, (const char*)p2, (const char*)p3);
        return p;
    }

    void debuginfo();

};


#define requestActor1(ID, CLASS)                   (GgafCore::Caretaker::_pCaretaker->addActorCradle<CLASS>((ID),GgafCore::Caretaker::bless, this, this, (void*)(#CLASS "_" #ID),(void*)(nullptr),(void*)(nullptr)))
#define requestActor2(ID, CLASS, NAME)             (GgafCore::Caretaker::_pCaretaker->addActorCradle<CLASS>((ID),GgafCore::Caretaker::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
#define requestActor3(ID, CLASS, NAME, ARG1)       (GgafCore::Caretaker::_pCaretaker->addActorCradle<CLASS>((ID),GgafCore::Caretaker::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr)))
#define requestActor4(ID, CLASS, NAME, ARG1, ARG2) (GgafCore::Caretaker::_pCaretaker->addActorCradle<CLASS>((ID),GgafCore::Caretaker::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2)))
#define selectRequestActorMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define requestScene1(ID, CLASS)                   (GgafCore::Caretaker::_pCaretaker->addSceneCradle<CLASS>((ID),GgafCore::Caretaker::bless, this, this, (void*)(#CLASS "_" #ID),(void*)(nullptr),(void*)(nullptr)))
#define requestScene2(ID, CLASS, NAME)             (GgafCore::Caretaker::_pCaretaker->addSceneCradle<CLASS>((ID),GgafCore::Caretaker::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
#define requestScene3(ID, CLASS, NAME, ARG1)       (GgafCore::Caretaker::_pCaretaker->addSceneCradle<CLASS>((ID),GgafCore::Caretaker::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr)))
#define requestScene4(ID, CLASS, NAME, ARG1, ARG2) (GgafCore::Caretaker::_pCaretaker->addSceneCradle<CLASS>((ID),GgafCore::Caretaker::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2)))
#define selectRequestSceneMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define desireActor1(CLASS)                   (GgafCore::Caretaker::_pCaretaker->makeActor<CLASS>(GgafCore::Caretaker::bless, this, this, (void*)(#CLASS),(void*)(nullptr),(void*)(nullptr),this))
#define desireActor2(CLASS, NAME)             (GgafCore::Caretaker::_pCaretaker->makeActor<CLASS>(GgafCore::Caretaker::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr),this))
#define desireActor3(CLASS, NAME, ARG1)       (GgafCore::Caretaker::_pCaretaker->makeActor<CLASS>(GgafCore::Caretaker::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr),this))
#define desireActor4(CLASS, NAME, ARG1, ARG2) (GgafCore::Caretaker::_pCaretaker->makeActor<CLASS>(GgafCore::Caretaker::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2),this))
#define selectDesireActorMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define desireScene1(CLASS)                   (GgafCore::Caretaker::_pCaretaker->makeScene<CLASS>(GgafCore::Caretaker::bless, this, this, (void*)(#CLASS),(void*)(nullptr),(void*)(nullptr),this))
#define desireScene2(CLASS, NAME)             (GgafCore::Caretaker::_pCaretaker->makeScene<CLASS>(GgafCore::Caretaker::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr),this))
#define desireScene3(CLASS, NAME, ARG1)       (GgafCore::Caretaker::_pCaretaker->makeScene<CLASS>(GgafCore::Caretaker::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr),this))
#define desireScene4(CLASS, NAME, ARG1, ARG2) (GgafCore::Caretaker::_pCaretaker->makeScene<CLASS>(GgafCore::Caretaker::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2),this))
#define selectDesireSceneMacro(_1,_2,_3,_4,MACRO,...) MACRO

#ifdef _MSC_VER
    //MSVC�̏ꍇ
    #define ___EXPAND( X ) X
    /** �A�N�^�[���Ǘ��҂ɖ]�� */
    #define requestActor(ID,...) ___EXPAND( selectRequestActorMacro(__VA_ARGS__,requestActor4,requestActor3,requestActor2,requestActor1)(ID,__VA_ARGS__) )
    /** �V�[�����Ǘ��҂ɖ]�� */
    #define requestScene(ID,...) ___EXPAND( selectRequestSceneMacro(__VA_ARGS__,requestScene4,requestScene3,requestScene2,requestScene1)(ID,__VA_ARGS__) )
    /** �V�[�����Ǘ��҂ɖ]�݁A�j������A�󂯎���܂ŋ��~�ɑ҂� */
    #define desireActor(...) ___EXPAND( selectDesireActorMacro(__VA_ARGS__,desireActor4,desireActor3,desireActor2,desireActor1)(__VA_ARGS__) )
    /** �V�[�����Ǘ��҂ɖ]�݁A�j������A�󂯎���܂ŋ��~�ɑ҂� */
    #define desireScene(...) ___EXPAND( selectDesireSceneMacro(__VA_ARGS__,desireScene4,desireScene3,desireScene2,desireScene1)(__VA_ARGS__) )
#else
    //GCC�̏ꍇ
    /** �A�N�^�[���Ǘ��҂ɖ]�� */
    #define requestActor(ID,...) selectRequestActorMacro(__VA_ARGS__,requestActor4,requestActor3,requestActor2,requestActor1)(ID,__VA_ARGS__)
    /** �V�[�����Ǘ��҂ɖ]�� */
    #define requestScene(ID,...) selectRequestSceneMacro(__VA_ARGS__,requestScene4,requestScene3,requestScene2,requestScene1)(ID,__VA_ARGS__)
    /** �V�[�����Ǘ��҂ɖ]�݁A�j������A�󂯎���܂ŋ��~�ɑ҂� */
    #define desireActor(...) selectDesireActorMacro(__VA_ARGS__,desireActor4,desireActor3,desireActor2,desireActor1)(__VA_ARGS__)
    /** �V�[�����Ǘ��҂ɖ]�݁A�j������A�󂯎���܂ŋ��~�ɑ҂� */
    #define desireScene(...) selectDesireSceneMacro(__VA_ARGS__,desireScene4,desireScene3,desireScene2,desireScene1)(__VA_ARGS__)
#endif

/** �]�܂�j�����ꂽ�A�N�^�[���󂯎��BpresentMoment()�ApresentJudge() �̊Ԃ̂ݎg�p�\ */
#define receiveActor(ID) (GgafCore::Caretaker::_pCaretaker->takeOutActor((ID),this,false))
/** �]�܂�j�����ꂽ�V�[�����󂯎��B presentMoment()�ApresentJudge() �̊Ԃ̂ݎg�p�\ */
#define receiveScene(ID) (GgafCore::Caretaker::_pCaretaker->takeOutScene((ID),this,false))

/** �]�܂�j�����ꂽ�A�N�^�[���󂯎���܂ő҂BpresentMoment()�ApresentJudge() �̊Ԃ̂ݎg�p�\ */
#define waitForRequestActor(ID) (GgafCore::Caretaker::_pCaretaker->takeOutActor((ID),this,true))
/** �]�܂�j�����ꂽ�V�[�����󂯎���܂ő҂B presentMoment()�ApresentJudge() �̊Ԃ̂ݎg�p�\ */
#define waitForRequestScene(ID) (GgafCore::Caretaker::_pCaretaker->takeOutScene((ID),this,true))

}
#endif /*GGAF_CORE_CARETAKER_H_*/
