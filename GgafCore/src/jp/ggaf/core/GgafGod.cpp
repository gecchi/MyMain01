#include "jp/ggaf/core/GgafGod.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/GgafCradle.h"
#include "jp/ggaf/core/GgafGarbageBox.h"
#include "jp/ggaf/core/GgafConfig.h"
#include "jp/ggaf/core/scene/GgafSpacetime.h"
#include "jp/ggaf/core/scene/GgafDisusedScene.h"
#include "jp/ggaf/core/actor/GgafDisusedActor.h"

#include <process.h>

using namespace GgafCore;

GgafCriticalException* GgafGod::_pException_factory = nullptr;

CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;
#ifdef MY_DEBUG
unsigned int GgafGod::_num_drawing = 0;
#endif
unsigned int GgafGod::_num_active_actor = 0;

GgafGod* GgafGod::_pGod = nullptr;
DWORD GgafGod::_aaTime_offset_of_next_view[3][60] = {
        {17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16},
        {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25},
        {33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34}
};

GgafGod::GgafGod() : GgafObject(),
  _pSpacetime(nullptr),
  _fps(0) {
    timeBeginPeriod(1);
    _frame_of_God = 0;
    _handle_god_love01 = (HANDLE)_beginthreadex(nullptr, 0, GgafCore::GgafGod::love, nullptr, CREATE_SUSPENDED, &_th_id01);

    if (_handle_god_love01 == 0) {
        throwGgafCriticalException("Error! �X���b�h�쐬���s�I");
    }
    ::InitializeCriticalSection(&(GgafGod::CS1));
    ::InitializeCriticalSection(&(GgafGod::CS2));
    ::ResumeThread(_handle_god_love01);
    ::SetThreadPriority(_handle_god_love01, THREAD_PRIORITY_IDLE);
    GgafGod::_pGod = this;
    _time_at_beginning_frame = timeGetTime();
    _time_of_next_view = _time_at_beginning_frame;
    _time_calc_fps_next = _time_at_beginning_frame + 1;
    _visualize_frames = 0;
    _prev_visualize_frames = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GgafGarbageBox::_pGarbageBox = NEW GgafGarbageBox();
    _was_cleaned = false;
    _skip_count_of_frame = 0;
    _max_skip_frames = (int)CONFIG::MAX_SKIP_FRAME;
    _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    _sync_frame_time = false;
    _cnt_frame = 0;
}

void GgafGod::be() {

    // �y�����z
    // �P�T�C�N���i�P�t���[���j�̏����͈ȉ��̗l�ɑ傫���T�ɕ����A���Ɏ��s������̂Ƃ����B
    //
    // �@Mo = presentSpacetimeMoment();     ��� ���C�������E�K�{����
    // �AJu = executeSpacetimeJudge();      ��� ���菈���E�K�{����
    // �BMa = makeSpacetimeMaterialize();   ��� �`�揈��(�d��)�E�X�L�b�v��
    // �CVi = presentSpacetimeVisualize();  ��� �`��t���b�v�����E�X�L�b�v��(�A���B�ƇC�̓Z�b�g����)
    // �DFi = finalizeSpacetime();          ��� �ŏI�����E�K�{����
    //
    // �����ōs�Ȃ��������Ƃ́w�ł������A�CVi �� 1/60 �b���Ɉ��肵�Ď��s���邱�Ɓx�Ƃ����B
    // �����ŁA���̗l�Ȑ݌v���s�����B
    // �E�悸 �CVi �����s�������^�C�~���O��\�ߌ��肷��B����́A�@���ɏ������d���Ȃ낤�Ƃ��ς��Ȃ��B
    //    _time_of_next_view = _time_of_next_view + (1/60�b)
    //   �Ƃ���B
    // �E�AJu �����s�������_�ŁA�BMa�A�CVi �����s���邩�ǂ������c���_time_of_next_view �܂ł̎��ԂŔ��f����B
    //   ���Ԃɗ]�T���L��ꍇ�A�AJu ���s�㑦���� �BMa ���s�A���̌� _time_of_next_view �܂ő҂� �CVi ���s����B
    //   ���� �AJu ���s��A���t���[���ɂ߂荞��ł����ꍇ �BMa�A�CVi �̓X�L�b�v�B
    // �E��L����{���[���Ƃ��A_max_skip_frames �t���[���ɂP��͕K�� �BMa�A�CVi �����s����B
    //   ����͂ǂ�Ȃɏ������d�����Ȃ낤�Ƃ��A�v���O�����������Ă��邱�Ƃ����o�����邽�߁B
    //
    //
    //�y���莞�̗��z�}�z
    //        _time_of_next_view                                              _time_of_next_view
    //                 |              3frame begin                                      |              4frame begin
    //                 |                   |                                            |                   |
    //                 v                   v                                            v                   v
    // ==================================================================================================================================================> ����
    //  <--- wait ---> |(2f-�CVi)| 2f-�DFi | 3f-�@Mo | 3f-�AJu |(3f-�BMa)|<--- wait --->|(3f-�CVi)| 3f-�DFi | 4f-�@Mo | 4f-�AJu |(4f-�BMa)|<--- wait -
    //                 |                   |                                            |                   |
    // -- 2frame ------------------------->|<-------------------------- 3frame ---------------------------->|<----------------  4frame ---------
    //                 |                                                                |
    //                 |<----------------------- 1/60 sec ----------------------------->|
    //                 |                                                 |
    //                 |<--- ���������I���΁A�����O�l�߂ɂł��� ------>|
    //                       ���̕�wait���������肷��B
    //
    // �����Ӂ�
    // �E�����܂� �CVi �� 1/60 �b��������D��Ŗڎw���d�g�݂ł����āA
    //   �����t���[���J�E���^�� 1/60 �b���ɃJ�E���g�A�b�v�����Ƃ����d�g�݂ł͖����i�l�����Ă��Ȃ��j�B
    //   _time_of_next_view �` ���� _time_of_next_view �͏�ɌŒ莞��(1/60 sec)�ł��邪�A
    //   �Ⴆ�Ώ�}�ł� 3frame begin  �` 4frame begin �Ԃ̎��Ԃ͑O�����ɂ��ϓ�����B
    //

    if (_pSpacetime == nullptr) {
        //���̐����܂������ꍇ�́A�悸���̐����쐬�B
        _pSpacetime = createSpacetime();
#ifdef MY_DEBUG
        if (_pSpacetime == nullptr) {
            throwGgafCriticalException("Error! ���̐����������ĉ������I");
        }
#endif
        _pSpacetime->_pGod = this;
        _time_at_beginning_frame = timeGetTime();
        _time_of_next_view = _time_at_beginning_frame+100; //0.1�b��J�n
        _time_calc_fps_next = _time_at_beginning_frame + 1;
    }
#ifdef MY_DEBUG
    //�_�i�ʃX���b�h�j��O���`�F�b�N
    if (_pException_factory) {
        throw *_pException_factory;
    }
#endif

    if (_is_behaved_flg == false) {
        _is_behaved_flg = true;
        BEGIN_SYNCHRONIZED1; // ----->�r���J�n
        _frame_of_God++;
        presentSpacetimeMoment(); //�@
        executeSpacetimeJudge();  //�A
        _time_of_next_view += _aaTime_offset_of_next_view[_slowdown_mode][_cnt_frame];
        _cnt_frame++;
        if (_cnt_frame == 60) { _cnt_frame = 0; }
        if (timeGetTime() >= _time_of_next_view) { //�`��^�C�~���O�t���[���ɂȂ����A�����͉߂��Ă���ꍇ
            //makeSpacetimeMaterialize �̓p�X
            _is_materialized_flg = false;
        } else {
            //�`��^�C�~���O�t���[���ɂȂ��Ă��Ȃ��B�]�T������B
             _is_materialized_flg = true;
            makeSpacetimeMaterialize(); //�B
            //�A�� makeSpacetimeMaterialize() �ɂ��I�[�o�[���邩������Ȃ��B
        }
        END_SYNCHRONIZED1;  // <-----�r���I��
    }

    _time_at_beginning_frame = timeGetTime();

    if (_time_at_beginning_frame >= _time_of_next_view) {
        //�`��^�C�~���O�t���[���ɂȂ����A�����͉߂��Ă���ꍇ
        BEGIN_SYNCHRONIZED1;  // ----->�r���J�n
        if (_is_materialized_flg) { // �B makeSpacetimeMaterialize() ���s�ς݂̏ꍇ
            //�`��L��i�X�L�b�v�Ȃ��j
            presentSpacetimeVisualize();  _visualize_frames++; //�C
            finalizeSpacetime(); //�D
        } else {                   // �B makeSpacetimeMaterialize() ���s���Ă��Ȃ��ꍇ
            //�`�斳���i�X�L�b�v���j
            if (_sync_frame_time) { //�����������[�h����
                //�������ŕ`��Ȃ��B
                finalizeSpacetime(); //�D
            } else {   //�����������[�h�ł͂Ȃ��ꍇ�͒ʏ�X�L�b�v
                _skip_count_of_frame++;
                //�A���A�X�L�b�v����Ƃ����Ă� MAX_SKIP_FRAME �t���[���ɂP��͕`��͂���B
                if (_skip_count_of_frame >= _max_skip_frames) {
                    makeSpacetimeMaterialize(); //�B
                    presentSpacetimeVisualize();  _visualize_frames++; //�C
                    finalizeSpacetime();        //�D
                    _skip_count_of_frame = 0;
                } else {
                    finalizeSpacetime(); //�D
                }
            }
        }
        _is_behaved_flg = false;
        END_SYNCHRONIZED1;    // <-----�r���I��

        //fps�v�Z
        if (_time_at_beginning_frame >= _time_calc_fps_next) {
            const int d_visualize_frames = _visualize_frames - _prev_visualize_frames;
            if (d_visualize_frames == 0) {
                _fps = 0;
            } else {
                _fps = (float)(d_visualize_frames) *
                              ((1.0f * _aaTime_offset_of_next_view[_slowdown_mode][0]) / (1.0f*_aaTime_offset_of_next_view[SLOWDOWN_MODE_DEFAULT][0]));
            }
            _time_calc_fps_next += 1000;
            _prev_visualize_frames = _visualize_frames;
        }

     } else { //�`��^�C�~���O�t���[���ɂȂ��ĂȂ�(�]�T������)
         _sync_frame_time = false;
         Sleep(1); //<--- wait ---> �� �ЂƂƂ�
     }
    return;
}

void GgafGod::presentSpacetimeMoment() {
    GgafSpacetime* pSpacetime = _pSpacetime;
    pSpacetime->nextFrame();
    pSpacetime->behave();
    pSpacetime->settleBehavior();
}

void GgafGod::executeSpacetimeJudge() {
    _pSpacetime->preJudge();
    _pSpacetime->judge();
}

void GgafGod::makeSpacetimeMaterialize() {
    if (GgafGod::_num_active_actor > CONFIG::OBJNUM_TO_SLOWDOWN2) {
        _slowdown_mode = SLOWDOWN_MODE_30FPS;
    } else if (GgafGod::_num_active_actor > CONFIG::OBJNUM_TO_SLOWDOWN1) {
        _slowdown_mode = SLOWDOWN_MODE_40FPS;
    } else {
        _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    }
#ifdef MY_DEBUG
    GgafGod::_num_drawing = 0;
#endif
    GgafGod::_num_active_actor = 0;
    GgafSpacetime* pSpacetime = _pSpacetime;
    pSpacetime->preDraw();
    pSpacetime->draw();
    pSpacetime->afterDraw();
}

void GgafGod::presentSpacetimeVisualize() {
    _pSpacetime->dump();
}

void GgafGod::finalizeSpacetime() {
    _pSpacetime->doFinally();
}

void GgafGod::clean() {
    if (!_was_cleaned) {
        _TRACE_(FUNC_NAME<<" start");
        if (_pSpacetime) {
            _TRACE_("_pSpacetime != nullptr");
            //�_���~�߂�
            Sleep(10);
            GgafGod::_is_working_flg = false;
            _TRACE_("GgafGod::~GgafGod() �_�����������܂ő҂E�E�E");
            for (int i = 0; GgafGod::_was_finished_flg == false; i++) {
                Sleep(10); //�_�����������܂ő҂�
                if (i > 10*100*60) {
                    _TRACE_("GgafGod::~GgafGod() 10���ҋ@���܂������A�_���甽��������܂���B����break���܂��B�v����");
                    break;
                }
            }
            _TRACE_("GgafGod::~GgafGod() �_�����������܂���");
            //�r���̉����A�X���b�h���I������܂ő҂�
            _TRACE_("GgafGod::~GgafGod()  WaitForSingleObject(_handle_god_love01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handle_god_love01, 120*1000);  //DeleteCriticalSection���s�����߂ɕK�v
            if (r == WAIT_TIMEOUT) {
                throwGgafCriticalException("�_�������������ɂ�������炸�A�Q�������Ă��X���b�h���c���Ă��܂��B");
            }
            _TRACE_("GgafGod::~GgafGod()  CloseHandle(_handle_god_love01) .....");
            CloseHandle(_handle_god_love01);
            _TRACE_("GgafGod::~GgafGod()  DeleteCriticalSection(&(GgafGod::CS1)); .....");
            DeleteCriticalSection(&(GgafGod::CS1));
            _handle_god_love01 = nullptr;
            _TRACE_("GgafGod::~GgafGod() �����ɐ_�X���b�h���I���B�N���e�B�J���Z�N�V��������");

#ifdef MY_DEBUG
            //�c���[�\���\��
            _TRACE_("Dumping _pSpacetime ...");
            _pSpacetime->dump();
#endif

            //�_�|��
            _TRACE_(FUNC_NAME<<"");
            GgafGod::cleanCradle();
            //�S�~��
#ifdef MY_DEBUG
            _TRACE_("Dumping GgafGarbageBox::_pGarbageBox->_pDisusedScene ...");
            GgafGarbageBox::_pGarbageBox->_pDisusedScene->dump();
            _TRACE_("GgafGarbageBox::_pGarbageBox->_pDisusedActor ...");
            GgafGarbageBox::_pGarbageBox->_pDisusedActor->dump();
#endif
            _TRACE_("GGAF_DELETE(GgafGarbageBox::_pGarbageBox);");
            GGAF_DELETE(GgafGarbageBox::_pGarbageBox);
            //���̐��Ő����Ă��镨���|��
            Sleep(20);
            _TRACE_("GGAF_DELETE(_pSpacetime);");
            GGAF_DELETE(_pSpacetime);
            _TRACE_("GgafGod::~GgafGod()  DeleteCriticalSection(&(GgafGod::CS2)); .....");
            DeleteCriticalSection(&(GgafGod::CS2));
        }

        //�_��O _pException_factory ���N�����Ă��邩������Ȃ��B
        _TRACE_("GGAF_DELETE_NULLABLE(_pException_factory);");
        GGAF_DELETE_NULLABLE(_pException_factory);
        _TRACE_(FUNC_NAME<<" end");
    }
}


GgafGod::~GgafGod() {
    timeEndPeriod(1);
    clean();
    _was_cleaned = true;
}


//������
GgafCradle* GgafGod::ROOT_CRADLE = nullptr;
GgafCradle* GgafGod::CREATING_CRADLE = nullptr;
#ifdef _MSC_VER
volatile bool GgafGod::_is_working_flg   = true;
volatile bool GgafGod::_have_to_rest_flg = false;
volatile bool GgafGod::_is_resting_flg   = false;
volatile bool GgafGod::_was_finished_flg = false;
#else
volatile std::atomic<bool> GgafGod::_is_working_flg(true);
volatile std::atomic<bool> GgafGod::_have_to_rest_flg(false);
volatile std::atomic<bool> GgafGod::_is_resting_flg(false);
volatile std::atomic<bool> GgafGod::_was_finished_flg(false);
#endif

GgafMainActor* GgafGod::receiveActor2(uint64_t prm_cradle_no, GgafObject* prm_pReceiver) {
    return (GgafMainActor*)GgafGod::receive(prm_cradle_no, prm_pReceiver);
}

GgafMainScene* GgafGod::receiveScene2(uint64_t prm_cradle_no, GgafObject* prm_pReceiver) {
    return (GgafMainScene*)GgafGod::receive(prm_cradle_no, prm_pReceiver);
}


//���̃��\�b�h�̓��C���X���b�h�����s����B
void GgafGod::createCradle(uint64_t prm_cradle_no,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        GgafObject* prm_pWisher,
                        GgafObject* prm_pReceiver,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {

    _TRACE2_("���q:("<<prm_pWisher<<")�� �ʃX���b�h�̐_����A [" << prm_cradle_no << "-"<<prm_pReceiver<<"]������Ƃ��Ă�`�B");
    //���ɏj�����Ă��Ȃ����`�F�b�N
    GgafCradle* pCradle = GgafGod::ROOT_CRADLE;
    while (pCradle) {
        if (pCradle->_cradle_no == prm_cradle_no &&  pCradle->_pReceiver == prm_pReceiver) {
            _TRACE_("���x���� GgafGod::createCradle( ������ƁA[" << prm_cradle_no << "-"<<prm_pReceiver<<"]�́A�Q�d�j�����Ă��܂���I�A�������܂��B�Ӑ}���Ă��܂����H");
            return;
        }
        if (pCradle->_is_last_cradle_flg) {
            break;
        }
        pCradle = pCradle->_pCradle_next;
    }
    //���͖����ł���悤�Ȃ̂Ő擪�ɃX�g�b�N
    GgafCradle* pCradle_new;
    pCradle_new = NEW GgafCradle(prm_cradle_no);
    pCradle_new->_pObject_creation=nullptr;
    pCradle_new->_pFunc = prm_pFunc;
    pCradle_new->_pWisher = prm_pWisher;
    pCradle_new->_pReceiver = prm_pReceiver;
    pCradle_new->_time_of_wish = timeGetTime();
    pCradle_new->_pArg1 = prm_pArg1;
    pCradle_new->_pArg2 = prm_pArg2;
    pCradle_new->_pArg3 = prm_pArg3;
    pCradle_new->_progress = 0;
    if (GgafGod::ROOT_CRADLE == nullptr) {
        _TRACE2_("���q:("<<prm_pWisher<<")�� �����A�_�͋�������ł��ˁB�j��������A�����ł����ˁH�B");
        pCradle_new->_is_first_cradle_flg = true;
        pCradle_new->_is_last_cradle_flg = true;
        pCradle_new->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_new;
        GgafGod::ROOT_CRADLE = pCradle_new;
        GgafGod::CREATING_CRADLE = pCradle_new;
    } else {
        _TRACE2_("���q:("<<prm_pWisher<<")�� ��肩�����܂��Ă܂��ˁA���X��肩���������܂��B");
        pCradle_new->_is_first_cradle_flg = false;
        pCradle_new->_is_last_cradle_flg = true;
        GgafCradle* pCradle_last = GgafGod::ROOT_CRADLE->_pCradle_prev;
        pCradle_last->_is_last_cradle_flg = false;
        pCradle_last->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_last;
        pCradle_new->_pCradle_next = GgafGod::ROOT_CRADLE;
        GgafGod::ROOT_CRADLE->_pCradle_prev = pCradle_new;
    }
}

int GgafGod::chkProgress(uint64_t prm_cradle_no) {
    GgafCradle* pCradle;
    pCradle = GgafGod::ROOT_CRADLE;
    if (pCradle == nullptr) {
        return -1;
    }
    while (GgafGod::_is_working_flg) {
        if (pCradle->_cradle_no == prm_cradle_no) {
            return pCradle->_progress;
        } else {
            if (pCradle->_is_last_cradle_flg) {
                return -1;
            } else {
                pCradle = pCradle->_pCradle_next;
            }
        }
    }
    return -2;
}

void* GgafGod::receive(uint64_t prm_cradle_no, GgafObject* prm_pReceiver) {
    _TRACE2_("�����l:"<< (prm_pReceiver ? prm_pReceiver->toString() : "nullptr") <<"("<<prm_pReceiver<<")�� �܂��ǁA["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]�����ɗ��܂�������ƁB");
    GgafCradle* pCradle= GgafGod::ROOT_CRADLE;
    GgafCradle* pCradle_my_next;
    GgafCradle* pCradle_my_prev;
    DWORD waittime = 0;
    void* objectCreation;

    if (pCradle == nullptr) {
        //��肩����������G���[�����I�A�G���[���b�Z�[�W�����B
        _TRACE_(FUNC_NAME<<" ��肩����������G���[�����I");
        GgafGod::debuginfo();
        throwGgafCriticalException("Error! prm_cradle_no="<<prm_cradle_no<<" ��肩�����X�g��nullptr�őS�ďj���ς݂��Ă��܂��B\n"
                                   "oreder��obtain�̑Ή������Ă��܂���B\n"
                                   "���l(obtain�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }

    //obtain���C�����[�v
    while (GgafGod::_is_working_flg) {
        if (pCradle->_cradle_no == prm_cradle_no && (pCradle->_pReceiver == nullptr || pCradle->_pReceiver == prm_pReceiver) ) {
            while (GgafGod::_is_working_flg) {
                if (pCradle->_progress < 2) {
                    _TRACE2_("�����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� �˂��_������A["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]�̏j���܂��`�H�A5�~���b�����҂������悤�BpCradle->_progress="<<(pCradle->_progress));
#ifdef _DEBUG
                    //�f�o�b�O���̓^�C���A�E�g����
#else

                    if (waittime > 1000*600) { //��10��
                        _TRACE_(FUNC_NAME<<" �^�C���A�E�g�G���[�����I");
                        GgafGod::debuginfo();
                        //�^�C���A�E�g�G���[�����I�A�G���[���b�Z�[�W�����B
                        throwGgafCriticalException("Error! ��肩��["<<pCradle->getDebuginfo()<<"]�̏j���҂����ԃ^�C���A�E�g�A�擾�ł��܂���B\n"
                                                   "���炩�̗��R�Ń��C���X���b�h����~���Ă���\�����傫���ł��B"
                                                   "���l(obtain�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
                    } else {
                    }
#endif
                    END_SYNCHRONIZED1; // <----- �r���I��
                    Sleep(5);
                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
                    waittime += 5;
                    if (pCradle->_progress == 1) {
                        //����ς�
                        _TRACE_N_("�I");
                        continue; //�҂�
                    } else if (pCradle->_progress == 0) {
                        //������H
                        pCradle = GgafGod::ROOT_CRADLE; //������x�ŏ�����T������B
                        _TRACE_N_("�c");
                        break;
                    } else if (pCradle->_progress == 2) {
                        //����
                        pCradle = GgafGod::ROOT_CRADLE; //������x�ŏ�����T������B
                        _TRACE_N_("(^_^)v");
                        break;
                    }
                } else {

#ifdef MY_DEBUG
                    if (waittime > 0) {
                        _TRACE_N_("���҂����I");
                    }
#endif
                    _TRACE2_("�����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� ��`���A["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]�͏j�������ł��ˁB�������ɁI");
                    if (pCradle->_is_first_cradle_flg && pCradle->_is_last_cradle_flg) {
                        //�Ō�̈�� obtain
                        objectCreation = pCradle->_pObject_creation;
                        pCradle->_pObject_creation = nullptr;
                        GGAF_DELETE(pCradle);
                        pCradle = nullptr;
                        GgafGod::ROOT_CRADLE = nullptr;
                        GgafGod::CREATING_CRADLE = nullptr;
                        _TRACE2_("�����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� ���A�Ƃ���ł����_�͋�ł��ˁB�ɂɂȂ�����H�A�˂��H");
                        return (void*)objectCreation;
                    } else {
                        //���Ԃ�obtain�A�����q�������B
                        pCradle_my_next = pCradle->_pCradle_next;
                        pCradle_my_prev = pCradle->_pCradle_prev;
                        pCradle_my_prev->_pCradle_next = pCradle_my_next;
                        pCradle_my_next->_pCradle_prev = pCradle_my_prev;
                        if (pCradle->_is_last_cradle_flg) {
                            pCradle_my_prev->_is_last_cradle_flg = true;
                        }
                        if (pCradle->_is_first_cradle_flg) {
                            GgafGod::ROOT_CRADLE = pCradle_my_next;
                            pCradle_my_next->_is_first_cradle_flg = true;
                        }
                        if (GgafGod::CREATING_CRADLE == pCradle) {
                            GgafGod::CREATING_CRADLE = pCradle_my_next;
                        }
                        objectCreation = pCradle->_pObject_creation;
                        pCradle->_pObject_creation = nullptr;
                        GGAF_DELETE(pCradle);
                        pCradle = nullptr;

                        return (void*)objectCreation;
                    }
                }
            }
        } else {
            if (pCradle->_is_last_cradle_flg) {
                _TRACE_(FUNC_NAME<<" ��肩���̌`�Ղ������A�擾�o���Ȃ��G���[�����I");
                GgafGod::debuginfo();
                //��肩���̌`�Ղ������A�擾�o���Ȃ��G���[�����I�A�G���[���b�Z�[�W�����B
                throwGgafCriticalException("���_���S���T���܂������ǁA����Ȃ�肩��("<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"����ւ� ��肩���ԍ�:"<<prm_cradle_no<<"-"<<prm_pReceiver<<")�́A����܂���B\n"
                                           "oreder() �� GgafGod::receive() �̑Ή������Ă��܂���Boreder()�R��A�����͓��� GgafGod::receive() ���Q��ȏサ�Ă܂��񂩁H�B\n"
                                           "���F���l(obtain�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<") �ł����B\n"
                                           "�i�����Ȃ݂ɁA���ݐ_�̍ŏI�I�[�_�[�́A��肩���ԍ�("<<pCradle->_cradle_no<<"-"<<pCradle->_pReceiver<<")�ŁA�]�񂾐l(createCradle(�Ăь�)=("<<pCradle->_pWisher<<") �ł����j");
            } else {
                pCradle = pCradle->_pCradle_next;
            }
        }
    }
    if (GgafGod::_pException_factory) {
        throw *(GgafGod::_pException_factory);
    }
    return nullptr;
}

void GgafGod::beginRest() {
    _TRACE_(FUNC_NAME<<" ���_���_�A�x�e���Ȃ���");
    GgafGod::_have_to_rest_flg = true;
}

bool GgafGod::isResting() {
    if (GgafGod::_is_resting_flg) {
        _TRACE_(FUNC_NAME<<" �_�x�~���");
    } else {
        _TRACE_(FUNC_NAME<<" �_�ғ����");
    }
    return GgafGod::_is_resting_flg;
}

void GgafGod::finishRest() {
    _TRACE_(FUNC_NAME<<" ���_���_�A�x�e�͂����܂��B���������I");
    GgafGod::_have_to_rest_flg = false;
}

//�_�ɂ��ߍ���ł���S�Ă̂�肩����j��
//�_(GgafGod)���A�v���I�������Ɏ��s����\��B
void GgafGod::cleanCradle() {
    _TRACE2_("���_�� ��肩���|���J�n");
    GgafCradle* pCradle = GgafGod::ROOT_CRADLE;
    if (pCradle == nullptr) {
        _TRACE2_("���_�� ���������������I�I");
        return;
    }
    uint64_t cnt = 0;
    while (GgafGod::_is_working_flg || GgafGod::_was_finished_flg == false) {
        Sleep(10);
        _TRACE_(FUNC_NAME<<" ���_�� �܂������Ă܂��E�E�E");
        cnt++;
        if (cnt > 100*60*5) {
            _TRACE_(FUNC_NAME<<" ���_�� �܂������Ă܂��E�E�E�����҂��Ă��܂���B������");
            break;
        }
    }

    GgafGod::debuginfo();

    while (true) {
        if (pCradle->_is_last_cradle_flg) {
            _TRACE2_("���_�� ��肩���폜["<<pCradle->getDebuginfo()<<"]�A�Ō�̃X�g�b�N");
            GGAF_DELETE(pCradle);
            pCradle = nullptr;
            GgafGod::ROOT_CRADLE = nullptr;
            GgafGod::CREATING_CRADLE = nullptr;
            break;
        } else {
            _TRACE2_("���_�� ��肩���폜["<<pCradle->getDebuginfo()<<"]");
            GgafCradle* pCradle_my_next = pCradle->_pCradle_next;
            GGAF_DELETE(pCradle);
            pCradle = pCradle_my_next;
        }
    }
    _TRACE2_("���_�� ��肩����|������");
    return;
}

void GgafGod::fate(GgafObject* prm_pReceiver) {
    GgafCradle* pCradle = GgafGod::ROOT_CRADLE;
    while (pCradle) {
        if (pCradle->_pReceiver == prm_pReceiver) {
            if (pCradle->_is_last_cradle_flg && pCradle->_is_first_cradle_flg) {
                //�Ō�̈��
                GGAF_DELETE(pCradle);
                GgafGod::ROOT_CRADLE = nullptr;
                GgafGod::CREATING_CRADLE = nullptr;
                break; //�I��
            } else {
                //�Ԃ̏ꍇ�A�|�C���^���q�������B
                GgafCradle* pCradle_t_next = pCradle->_pCradle_next;
                GgafCradle* pCradle_t_prev = pCradle->_pCradle_prev;
                pCradle_t_prev->_pCradle_next = pCradle_t_next;
                pCradle_t_next->_pCradle_prev = pCradle_t_prev;

                if (pCradle->_is_last_cradle_flg) {
                    pCradle_t_prev->_is_last_cradle_flg = true;
                }
                if (pCradle->_is_first_cradle_flg) {
                    GgafGod::ROOT_CRADLE = pCradle_t_next;
                    pCradle_t_next->_is_first_cradle_flg = true;
                }
                if (GgafGod::CREATING_CRADLE == pCradle) {
                    GgafGod::CREATING_CRADLE = pCradle_t_next;
                }
                _TRACE_(FUNC_NAME<<" ���l("<<prm_pReceiver<<")���S�ׁ̈A��肩�����폜���܂��B" << pCradle->getDebuginfo() << "");
                GGAF_DELETE(pCradle);
                pCradle = pCradle_t_next;
                continue;
            }
        } else {
            if (pCradle->_is_last_cradle_flg) {
                break; //�I��
            } else {
                pCradle = pCradle->_pCradle_next;
                continue;
            }
        }
    }
}

void GgafGod::debuginfo() {
    _TRACE_(FUNC_NAME<<" ���f�o�b�O��� ���݂̐_�̏��");
    try {
        GgafCradle* p = GgafGod::ROOT_CRADLE;
        if (p) {
            while(p) {
                _TRACE_("�E" << p->getDebuginfo() );
                p = p->_pCradle_next;
                if (p == GgafGod::ROOT_CRADLE) {
                    break;
                }
            }
        } else {
            _TRACE_("�E�I�[�_�[����܂���I");
        }
    } catch (...) {
        _TRACE_(FUNC_NAME<<" �Ȃ�Ƃ������Ƃł��傤�B���݂̐_�̏�Ԃ̕\�����s�\�ł��B");
    }
    _TRACE_(FUNC_NAME<<" �ȏ�");
}

unsigned __stdcall GgafGod::love(void* prm_arg) {
    //_CrtSetBreakAlloc(65854);
    try {
        GgafObject* (*func)(void*, void*, void*) = nullptr;
        GgafObject* pObject = nullptr;
        Sleep(1000); //god �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�

        //���i�����܂���_���[�v�I
        while (GgafGod::_is_working_flg) {
            if (GgafGod::_have_to_rest_flg) {
                GgafGod::_is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                GgafGod::_is_resting_flg = false;
            }

BEGIN_SYNCHRONIZED1; // ----->�r���J�n
            GgafCradle* pCradle_creating = GgafGod::CREATING_CRADLE;
            if (pCradle_creating) {
                if (pCradle_creating->_progress == 0) { //������Ȃ�܂����
                    _TRACE2_("���_�� �悵�A��肩��["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]�͖�����(_progress == "<<pCradle_creating->_progress<<")���ȁB�䂦�ɍ�������܂��I");
                    pCradle_creating->_progress = 1; //�X�e�[�^�X���j������
                    pCradle_creating->_time_of_create_begin = timeGetTime();
                    func = pCradle_creating->_pFunc;
                    void* arg1 = pCradle_creating->_pArg1;
                    void* arg2 = pCradle_creating->_pArg2;
                    void* arg3 = pCradle_creating->_pArg3;
                    _TRACE2_("���_�� �j���J�n�I["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]");
                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- �r���I��

                    pObject = (*func)(arg1, arg2, arg3); //���i�̏j���I

                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
                    Sleep(2);
                    _TRACE2_("���_�� �j�������I�i��["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"] (^_^)v");
                    if (GgafGod::CREATING_CRADLE == nullptr) {
                        //GgafGod::CREATING_CRADLE ���j���� nullptr �ɂȂ��Ă��܂��Ă���ꍇ�L�����Z���B
                        _TRACE2_("���_�� �K�[���I�B��������������̂ɃL�����Z���������E�E�E�B�j�����܂��BpObject��delete!");
                        GGAF_DELETE(pObject);
END_SYNCHRONIZED1; // <----- �r���I��
                        continue;
                    } else if (GgafGod::CREATING_CRADLE == pCradle_creating) {
                        //����ȃP�[�X
                        pCradle_creating->_pObject_creation = pObject; //���i�o�^
                        pCradle_creating->_progress = 2; //�X�e�[�^�X���j���ς݂�
                        pCradle_creating->_time_of_create_finish = timeGetTime();
                        _TRACE2_("���_�� �j��������肩���̕i["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]���A�I�ɒu���Ƃ��܂��B");
                    }  else if (GgafGod::CREATING_CRADLE != pCradle_creating) {
                        _TRACE2_("���_�� �x���A��肩���̕i["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]������Ă���ԂɁA"
                                 "CREATING_CRADLE ���A�ʂ̂�肩��["<<GgafGod::CREATING_CRADLE->_cradle_no<<"-"<<GgafGod::CREATING_CRADLE->_pReceiver<<"]���w���Ă��܂����I���Ă邩������܂���I�����I�Ɍ��ɖ߂��܂��I�v�����I");
                        GgafGod::CREATING_CRADLE = pCradle_creating; //�|�C���^�����߂�
                        pCradle_creating->_pObject_creation = pObject; //���i�o�^
                        pCradle_creating->_progress = 2; //�X�e�[�^�X���j���ς݂�
                        pCradle_creating->_time_of_create_finish = timeGetTime();
                        _TRACE2_("���_�� �j��������肩���̕i["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]���A�I�ɒu���Ƃ��܂��E�E�E�B");
                    }
                } else {
                    _TRACE2_("���_�� ��肩��["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]�́A��������ĒI�ɒu���Ă��邵�E�E�E(_progress == "<<pCradle_creating->_progress<<")�B");
                }
            }
            if (GgafGod::ROOT_CRADLE == nullptr) {
                //�������ҋ@
                _TRACE2_("���_�� �_�ɂ͉��`�������܂���B�����Ȃ�ł���肩�����������I�I�E�E�E�Ȃ��̂�H�B�i�ҋ@�j");
END_SYNCHRONIZED1; // <----- �r���I��
                if (GgafGod::_pGod->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("���_�� ���قǖZ�����Ȃ��̂ŁA�S�~���̃S�~���o���Ƃ����B");
                    GgafGarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                    GgafGarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (GgafGod::ROOT_CRADLE != nullptr && GgafGod::ROOT_CRADLE->_pCradle_prev->_progress == 0) {
                    _TRACE2_("���_�� �E�E�E���j���̂�肩��������C�z�B�ŏI�ڕW�̂�肩����["<<GgafGod::ROOT_CRADLE->_pCradle_prev->_cradle_no<<"/���l="<<GgafGod::ROOT_CRADLE->_pCradle_prev->_pReceiver<<"]�Ȃ̂��H�B");
                    GgafGod::CREATING_CRADLE = GgafGod::CREATING_CRADLE->_pCradle_next;
END_SYNCHRONIZED1; // <----- �r���I��
                } else {
                    _TRACE2_("���_�� ���āA���j����肩���͖����B�I�ɏj���ς̂񂪂��܂��Ă�̂𑁂���ɗ��������I�B�i�ҋ@�j");
END_SYNCHRONIZED1; // <----- �r���I��
                    if (GgafGod::_pGod->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("���_�� ���قǖZ�����Ȃ��������Ȃ̂ŁA�S�~���̃S�~���o���Ƃ������B");
                        GgafGarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                        GgafGarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        } // <-- while (GgafGod::_is_working_flg)
        _TRACE2_("���_�� �_�͂���ɂēX���܂��ł��B���悤�Ȃ�A�܂���܂��傤�B");
        GgafGod::_was_finished_flg = true;
    } catch (GgafCriticalException& e) {
        GgafGod::debuginfo();
        _TRACE_("���_��O�� ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
        GgafGod::_is_working_flg = false;
        GgafGod::_was_finished_flg = true;
        GgafGod::_pException_factory = NEW GgafCriticalException(e.getMsg());
        return 1;
    }
    return 0;
}


