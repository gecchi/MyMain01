#ifndef GGAFCORE_GGAFGOD_H_
#define GGAFCORE_GGAFGOD_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#ifndef _MSC_VER
    #include <atomic>
#endif

#define ORDER_ID_MAX     (0xffffffffffffffffULL)

#undef pGOD
#define pGOD (GgafCore::GgafGod::ask())

namespace GgafCore {

#define  BEGIN_SYNCHRONIZED1   ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  END_SYNCHRONIZED1     ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))
#define  BEGIN_SYNCHRONIZED2   ::EnterCriticalSection(&(GgafCore::GgafGod::CS2))
#define  END_SYNCHRONIZED2     ::LeaveCriticalSection(&(GgafCore::GgafGod::CS2))
#define  SLOWDOWN_MODE_DEFAULT 0
#define  SLOWDOWN_MODE_40FPS 1
#define  SLOWDOWN_MODE_30FPS 2
/**
 * �_�N���X.
 * ��ɂ��̐�(GgafSpacetime)���Ǘ������삷�邱�Ƃ�ړI�Ƃ���N���X�ł��B���Ԃ��Ԃ��炢�B<BR>
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
    /** [r] �N���e�B�J���Z�N�V�������̂P */
    static CRITICAL_SECTION CS1;
    /** [r] �N���e�B�J���Z�N�V�������̂Q */
    static CRITICAL_SECTION CS2;
    /** [r] ���g */
    static GgafGod* _pGod;
    /** [r] ���ɂ��̐������������鎞�Ԃ̃I�t�Z�b�g */
    static DWORD _aaTime_offset_of_next_view[3][60];

    /** [r] �����_(�ʃX���b�h)�̃G���[��ԁBnullptr������ғ����^not nullptr���ُ픭�� */
    GgafCriticalException* _pException_god;


    /** [r] GgafGod::love �X���b�h�n���h��  */
    HANDLE _handle_god_love01;
    /** [r] GgafGod::love �X���b�hID  */
    unsigned int _th_id01;
    /** [r] �_�̃t���[���J�n�V�X�e������ */
    DWORD _time_at_beginning_frame;
    /** [r] ���ɂ��̐�������������V�X�e������ */
    DWORD _time_of_next_view;
    /** [r] �_�a������̃t���[���� */
    frame _frame_of_God;
    int _cnt_frame;

    /** [r] ���̐������o���ł��Ȃ������i�X�L�b�v�����j�� */
    int _skip_count_of_frame;
    /** [r] ���̐� */
    GgafSpacetime* _pSpacetime;
    /** [r] fps�l�i��1000ms���Ɍv�Z�����j */
    float _fps;

    DWORD _time_calc_fps_next;
    /** [r] �`��t���[���J�E���^ */
    frame _visualize_frames;
    /** [r] �O��fps�v�Z���̕`��t���[���J�E���g�l */
    frame _prev_visualize_frames;
#ifdef MY_DEBUG
    /** [r] 1�t���[���̕`��� */
    static unsigned int _num_drawing;
#endif
    /** [r] 1�t���[���̊������A�N�^�[ */
    static unsigned int _num_active_actor;

    /** [r] �`�揈���A�ō��X�L�b�v�t���[���� */
    int _max_skip_frames;
    /** [r] ���݂̏����������[�h 0:60fps 1:40fps 2:30fps�B_aaTime_offset_of_next_view�̈�ڂ̗v�f */
    int _slowdown_mode;
    /** [r] ���Ԃƃt���[���̓����������[�h����true */
    bool _sync_frame_time;
    bool _was_cleaned;

public:
    /**
     * �R���X�g���N�^ .
     * �ʃX���b�h�Ő_���ғ������܂��B
     */
    GgafGod();

    /**
     * �u���݂���v�Ƃ������\�b�h .
     * �_�����݂���A���Ȃ킿�A���̐�(GgafSpacetime)�������A�A�v�����i�s���܂��B<BR>
     * ����Ăяo�����A���̐�(GgafSpacetime)���쐬����܂��B<BR>
     * �A�v���P�[�V�����́A�ŏ����ԒP�ʂł��̃��\�b�h���Ђ�����Ăё����Ă��������B<BR>
     */
    void be();

    /**
     * ���̐��́A�Ƃ���ŏ����ԒP�ʂ̏u�Ԃ�n�� .
     */
    virtual void presentSpacetimeMoment();

    /**
     * ���̐��́A�n�����ꂽ�ŏ����ԒP�ʂ̏u�Ԃɂ��ĐR���i�`�F�b�N�j���� .
     */
    virtual void executeSpacetimeJudge();

    /**
     * ���̐��́A�n�����ꂽ�ŏ����ԒP�ʂ̏u�Ԃ�������� .
     */
    virtual void makeSpacetimeMaterialize();

    /**
     * ���̐��ɕ`���������A�يE�̐l�ԋ��ɂ��F���i�ڎ��j�ł���悤�ɕ\�ʉ����� .
     */
    virtual void presentSpacetimeVisualize();

    /**
     * ���̐��̎��̍ŏ����ԒP�ʂ̏u�Ԃ�n�����邽�߂̏����A��n�� .
     */
    virtual void finalizeSpacetime();

    /**
     * ���̐����擾 .
     * ���ʂŃI�[�o�[���C�h�\�B<BR>
     * @return ���̐�
     */
    virtual GgafSpacetime* getSpacetime() {
        return _pSpacetime;
    }

    /**
     * ���̐���n�� .
     * ���ʂł��̐��̑n�����@���������Ă��������B<BR>
     * @return ���̐�
     */
    virtual GgafSpacetime* createSpacetime() = 0;

    /**
     * �`����ꎞ��~���A�t���[���Ǝ��Ԃ̓������s��
     */
    void syncTimeFrame() {
        _sync_frame_time = true;
    }

    virtual void clean();

    /**
     * �_�u���܂����`�I�v .
     * ��O�������ɃR�[���o�b�N����܂��B
     */
    virtual void oops() {
        _TRACE_("(-_-;) {Oops!");
    }

    /**
     * �y�� .
     * @return ����
     */
    static GgafGod* ask() {
        return GgafGod::_pGod;
    }

    virtual ~GgafGod();


private:
    /**
     * �_�ɂ�肩�����s���i���C���X���b�h���g�p�j .
     * @param prm_cradle_no	��肩���ԍ�
     * @param prm_pFunc	���ۂɏj���������s���֐��̃|�C���^
     * @param prm_pWisher �]�񂾐l
     * @param prm_pReceiver �󂯎��\���
     * @param prm_pArg1	�j���������s���֐��ւ̈���1
     * @param prm_pArg2	�j���������s���֐��ւ̈���2
     * @param prm_pArg3	�j���������s���֐��ւ̈���3
     */
    void createCradle(uint64_t prm_cradle_no,
                      GgafObject* (*prm_pFunc)(void*, void*, void*),
                      GgafObject* prm_pWisher,
                      GgafObject* prm_pReceiver,
                      void* prm_pArg1,
                      void* prm_pArg2,
                      void* prm_pArg3);

    /**
     * �]�񂾖����󂯎��i���C���X���b�h���g�p�j .
     * ���j���������ꍇ�A�j������������܂ő҂B<BR>
     * @param   prm_cradle_no	��肩���ԍ�
     * @param   prm_pReceiver	���l
     * @return	���̃|�C���^
     */
    void* receive(uint64_t prm_cradle_no, GgafObject* prm_pReceiver);

public:
    /** �擪�̂�肩�� */
    GgafCradle* _pCradleRoot;
    /** ���ݏj�����̂�肩�� */
    GgafCradle* _pCradleBlessing;
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
    volatile bool _was_finished_flg;
#else
    /** [r]�����Ă�t���O */
    volatile std::atomic<bool> _is_loving_flg;
    /** [r]�x�ރt���O */
    volatile std::atomic<bool> _have_to_rest_flg;
    /** [r]�x�ł���t���O */
    volatile std::atomic<bool> _is_resting_flg;
    /** [r]���̂���� */
    volatile std::atomic<bool> _was_finished_flg;
#endif
public:
    /**
     * �_�ɃA�N�^�[���j�����Ă��炤���߂́A��肩��������i���C���X���b�h���g�p�j .
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
    void createActorCradle(uint64_t prm_cradle_no,
                           X* (*prm_pFunc)(void*, void*, void*),
                           GgafObject* prm_pWisher,
                           GgafObject* prm_pReceiver,
                           void* prm_pArg1,
                           void* prm_pArg2,
                           void* prm_pArg3) {
        createCradle(prm_cradle_no, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * �_�ɃV�[���쐬�i�j���j���Ă��炤���߂́A��肩��������i���C���X���b�h���g�p�j .
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
    void createSceneCradle(uint64_t prm_cradle_no,
                           X* (*prm_pFunc)(void*, void*, void*),
                           GgafObject* prm_pWisher,
                           GgafObject* prm_pReceiver,
                           void* prm_pArg1,
                           void* prm_pArg2,
                           void* prm_pArg3) {
        createCradle(prm_cradle_no, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
    }

    /**
     * �]�񂾃A�N�^�[���󂯎��B�i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * ���j���������ꍇ�A�j������������܂ő҂B<BR>
     * @param   prm_cradle_no ��肩���ԍ�
     * @param   prm_pReceiver ���l
     * @return	�������ꂽ�A�N�^�[�̃|�C���^
     */
    GgafMainActor* receive_Actor(uint64_t prm_cradle_no, GgafObject* prm_pReceiver);

    /**
     * �]�񂾃V�[�����󂯎��B�i���C���X���b�h���g�p�j .
     * ���C���������Ăяo���܂��B<BR>
     * ���j���������ꍇ�A�j������������܂ő҂B<BR>
     * @param   prm_cradle_no ��肩���ԍ�
     * @param   prm_pReceiver ���l
     * @return	�������ꂽ�V�[���̃|�C���^
     */
    GgafMainScene* receive_Scene(uint64_t prm_cradle_no, GgafObject* prm_pReceiver);

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
                         GgafObject* prm_pWisher,
                         GgafObject* prm_pReceiver,
                         void* prm_pArg1,
                         void* prm_pArg2,
                         void* prm_pArg3,
                         GgafObject* prm_org) {
        createCradle(ORDER_ID_MAX, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(receive(ORDER_ID_MAX, prm_org));
    }

    template<class X>
    X* makeActor(X* (*prm_pFunc)(void*, void*, void*),
                         GgafObject* prm_pWisher,
                         GgafObject* prm_pReceiver,
                         void* prm_pArg1,
                         void* prm_pArg2,
                         void* prm_pArg3,
                         GgafObject* prm_org) {
        createActorCradle(ORDER_ID_MAX, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(receive_Actor(ORDER_ID_MAX, prm_org));
    }

    template<class X>
    X* makeScene(X* (*prm_pFunc)(void*, void*, void*),
                         GgafObject* prm_pWisher,
                         GgafObject* prm_pReceiver,
                         void* prm_pArg1,
                         void* prm_pArg2,
                         void* prm_pArg3,
                         GgafObject* prm_org) {
        createSceneCradle(ORDER_ID_MAX, (GgafObject* (*)(void*, void*, void*))prm_pFunc, prm_pWisher, prm_pReceiver, prm_pArg1, prm_pArg2, prm_pArg3);
        return (X*)(receive_Scene(ORDER_ID_MAX, prm_org));
    }

    /**
     * �]�񂾖����o���オ���Ă��邩���ׂ�B�i���C���X���b�h���g�p�j .
     * @param prm_cradle_no   ��肩���ԍ�
     * @return ��肩���ԍ��̖��̐i���(-2:�_�������Ă��Ȃ�/-1:��肩�����̂�����/0:��肩���͍݂邪���j��/1:�j����/2:�j���ς݁j
     */
    int chkCradle(uint64_t prm_cradle_no);

    /**
     * �^�� .
     * ��肩����|������i���C���X���b�h���g�p�j .
     * ���C�������̐_���Ăяo���܂��B<BR>
     * _pCradleRoot ���w���Ă����肩���̘A�����X�g��S�ĉ������<BR>
     * ���ӁF�K���ȉ��̂悤�ɃN���e�B�J���Z�N�V�����ň͂�ŌĂяo���Ă��������I�B<BR>
     * ���R�[�h�၄ <BR>
     *     BEGIN_SYNCHRONIZED1; // ----->�r���J�n<BR>
     * GgafGod::clean();<BR>
     *     END_SYNCHRONIZED1; // <----- �r���I��<BR>
     */
    void flood();

    /**
     * �e�͂��� .
     * @param prm_pReceiver �󂯎��͂��������l
     */
    void pardon(GgafObject* prm_pReceiver);

    /**
     * �� .
     * �_�iGgafGod�j�������ݒ莞�ɕʃX���b�h�ň�x���s����܂��B<BR>
     * �_�����ʂ܂Łi�A�v���I���܂Łj�i���Ɉ��������܂��B<BR>
     */
    static unsigned __stdcall love(void* prm_arg);

    /**
     * �i���̈� .
     * ��肩������t�ďj��������a�������܂��B
     * @param prm_arg
     */
    unsigned loveEternal(void* prm_arg);

    /**
     * �_�ꎞ�x�~���w�� �i���C���X���b�h���g�p�j .
     * �������Ăяo���Ă������ɋx�~��ԂɂȂ�Ƃ͌���܂���B<BR>
     * isResting() �Ŋ��S�x�~����܂Œ��ׂ鑱����K�v������܂��B<BR>
     */
    void beginRest();
    /**
     * �_�̏�Ԃ��擾�i���C���X���b�h���g�p�j .
     * @return true=�x�~���/false=�ғ����
     */
    bool isResting();

    /**
     * �_�x�~�̉������w�� �i���C���X���b�h���g�p�j .
     */
    void finishRest();

    /**
     * �j������(�����͂P��) .
     * @tparam X ���̌^
     * @param p1 �������ׂ̈̈���1 (�g�p�����)
     * @param p2 �������ׂ̈̈���2 (���������)
     * @param p3 �������ׂ̈̈���3 (���������)
     * @return �������ꂽ��
     */
    template<class X>
    static X* bless(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((const char*)p1);
        return p;
    }

    /**
     * �j������(�����͂Q��) .
     * @tparam X ���̌^
     * @param p1 �������ׂ̈̈���1 (�g�p�����)
     * @param p2 �������ׂ̈̈���2 (�g�p�����)
     * @param p3 �������ׂ̈̈���3 (���������)
     * @return �������ꂽ��
     */
    template<class X>
    static X* bless2(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((const char*)p1, (const char*)p2);
        return p;
    }
    template<class X>
    static X* bless3(void* p1, void* p2, void* p3) {
        //p1 : ����
        X* p = NEW X((const char*)p1, (const char*)p2, (const char*)p3);
        return p;
    }

    void debuginfo();

};


#define requestActor1(ID, CLASS)                   (GgafCore::GgafGod::_pGod->createActorCradle<CLASS>((ID),GgafCore::GgafGod::bless, this, this, (void*)(#CLASS "_" #ID),(void*)(nullptr),(void*)(nullptr)))
#define requestActor2(ID, CLASS, NAME)             (GgafCore::GgafGod::_pGod->createActorCradle<CLASS>((ID),GgafCore::GgafGod::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
#define requestActor3(ID, CLASS, NAME, ARG1)       (GgafCore::GgafGod::_pGod->createActorCradle<CLASS>((ID),GgafCore::GgafGod::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr)))
#define requestActor4(ID, CLASS, NAME, ARG1, ARG2) (GgafCore::GgafGod::_pGod->createActorCradle<CLASS>((ID),GgafCore::GgafGod::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2)))
#define selectRequestActorMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define requestScene1(ID, CLASS)                   (GgafCore::GgafGod::_pGod->createSceneCradle<CLASS>((ID),GgafCore::GgafGod::bless, this, this, (void*)(#CLASS "_" #ID),(void*)(nullptr),(void*)(nullptr)))
#define requestScene2(ID, CLASS, NAME)             (GgafCore::GgafGod::_pGod->createSceneCradle<CLASS>((ID),GgafCore::GgafGod::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr)))
#define requestScene3(ID, CLASS, NAME, ARG1)       (GgafCore::GgafGod::_pGod->createSceneCradle<CLASS>((ID),GgafCore::GgafGod::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr)))
#define requestScene4(ID, CLASS, NAME, ARG1, ARG2) (GgafCore::GgafGod::_pGod->createSceneCradle<CLASS>((ID),GgafCore::GgafGod::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2)))
#define selectRequestSceneMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define desireActor1(CLASS)                   (GgafCore::GgafGod::_pGod->makeActor<CLASS>(GgafCore::GgafGod::bless, this, this, (void*)(#CLASS),(void*)(nullptr),(void*)(nullptr),this))
#define desireActor2(CLASS, NAME)             (GgafCore::GgafGod::_pGod->makeActor<CLASS>(GgafCore::GgafGod::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr),this))
#define desireActor3(CLASS, NAME, ARG1)       (GgafCore::GgafGod::_pGod->makeActor<CLASS>(GgafCore::GgafGod::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr),this))
#define desireActor4(CLASS, NAME, ARG1, ARG2) (GgafCore::GgafGod::_pGod->makeActor<CLASS>(GgafCore::GgafGod::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2),this))
#define selectDesireActorMacro(_1,_2,_3,_4,MACRO,...) MACRO

#define desireScene1(CLASS)                   (GgafCore::GgafGod::_pGod->makeScene<CLASS>(GgafCore::GgafGod::bless, this, this, (void*)(#CLASS),(void*)(nullptr),(void*)(nullptr),this))
#define desireScene2(CLASS, NAME)             (GgafCore::GgafGod::_pGod->makeScene<CLASS>(GgafCore::GgafGod::bless, this, this, (void*)(NAME),(void*)(nullptr),(void*)(nullptr),this))
#define desireScene3(CLASS, NAME, ARG1)       (GgafCore::GgafGod::_pGod->makeScene<CLASS>(GgafCore::GgafGod::bless2, this, this, (void*)(NAME),(void*)(ARG1),(void*)(nullptr),this))
#define desireScene4(CLASS, NAME, ARG1, ARG2) (GgafCore::GgafGod::_pGod->makeScene<CLASS>(GgafCore::GgafGod::bless3, this, this, (void*)(NAME),(void*)(ARG1),(void*)(ARG2),this))
#define selectDesireSceneMacro(_1,_2,_3,_4,MACRO,...) MACRO

#ifdef _MSC_VER
    //MSVC�̏ꍇ
    #define ___EXPAND( X ) X
    /** �A�N�^�[��_�ɖ]�� */
    #define requestActor(ID,...) ___EXPAND( selectRequestActorMacro(__VA_ARGS__,requestActor4,requestActor3,requestActor2,requestActor1)(ID,__VA_ARGS__) )
    /** �V�[����_�ɖ]�� */
    #define requestScene(ID,...) ___EXPAND( selectRequestSceneMacro(__VA_ARGS__,requestScene4,requestScene3,requestScene2,requestScene1)(ID,__VA_ARGS__) )
    /** �V�[����_�ɖ]�݁A�j������A�󂯎���܂ŋ��~�ɑ҂� */
    #define desireActor(...) ___EXPAND( selectDesireActorMacro(__VA_ARGS__,desireActor4,desireActor3,desireActor2,desireActor1)(__VA_ARGS__) )
    /** �V�[����_�ɖ]�݁A�j������A�󂯎���܂ŋ��~�ɑ҂� */
    #define desireScene(...) ___EXPAND( selectDesireSceneMacro(__VA_ARGS__,desireScene4,desireScene3,desireScene2,desireScene1)(__VA_ARGS__) )
#else
    //GCC�̏ꍇ
    /** �A�N�^�[��_�ɖ]�� */
    #define requestActor(ID,...) selectRequestActorMacro(__VA_ARGS__,requestActor4,requestActor3,requestActor2,requestActor1)(ID,__VA_ARGS__)
    /** �V�[����_�ɖ]�� */
    #define requestScene(ID,...) selectRequestSceneMacro(__VA_ARGS__,requestScene4,requestScene3,requestScene2,requestScene1)(ID,__VA_ARGS__)
    /** �V�[����_�ɖ]�݁A�j������A�󂯎���܂ŋ��~�ɑ҂� */
    #define desireActor(...) selectDesireActorMacro(__VA_ARGS__,desireActor4,desireActor3,desireActor2,desireActor1)(__VA_ARGS__)
    /** �V�[����_�ɖ]�݁A�j������A�󂯎���܂ŋ��~�ɑ҂� */
    #define desireScene(...) selectDesireSceneMacro(__VA_ARGS__,desireScene4,desireScene3,desireScene2,desireScene1)(__VA_ARGS__)
#endif

/** �]�܂�j�����ꂽ�A�N�^�[���󂯎�� */
#define receiveActor(ID) (GgafCore::GgafGod::_pGod->receive_Actor((ID),this))
/** �]�܂�j�����ꂽ�V�[�����󂯎�� */
#define receiveScene(ID) (GgafCore::GgafGod::_pGod->receive_Scene((ID),this))
}
#endif /*GGAFCORE_GGAFGOD_H_*/
