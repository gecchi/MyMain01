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
    GgafGod::_pGod = this;
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

    _pException_god = nullptr;
    _pCradleRoot = nullptr;
    _pCradleBlessing = nullptr;
    _is_loving_flg   = true;
    _have_to_rest_flg = false;
    _is_resting_flg   = false;
    _was_finished_flg = false;
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
    if (_pException_god) {
        throw *_pException_god;
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
            _is_loving_flg = false;
            _TRACE_("GgafGod::~GgafGod() �_�����������܂ő҂E�E�E");
            for (int i = 0; _was_finished_flg == false; i++) {
                Sleep(10); //�_�����������܂ő҂�
                if (i > 5*100*60) {
                    _TRACE_("GgafGod::~GgafGod() 5���ҋ@���܂������A�_���甽��������܂���B�����m��܂���I�A���� break ���܂��B�v����");
                    break;
                }
            }
            _TRACE_("GgafGod::~GgafGod() �_�����������܂���");
            //�r���̉����A�X���b�h���I������܂ő҂�
            _TRACE_("GgafGod::~GgafGod()  WaitForSingleObject(_handle_god_love01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handle_god_love01, 120*1000);  //DeleteCriticalSection���s�����߂ɕK�v
            if (r == WAIT_TIMEOUT) {
                throwGgafCriticalException("�I������͂��Ȃ̂ɁA���Ԃ�_���܂��I����Ă��܂���E�E�E�E�i�܁j�B�f�o�b�O���u���܂������H");
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

            //�^��
            _TRACE_(FUNC_NAME<<"");
            flood();
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

        //�_��O _pException_god ���N�����Ă��邩������Ȃ��B
        _TRACE_("GGAF_DELETE_NULLABLE(_pException_god);");
        GGAF_DELETE_NULLABLE(_pException_god);
        _TRACE_(FUNC_NAME<<" end");
    }
}

GgafGod::~GgafGod() {
    timeEndPeriod(1);
    clean();
    _was_cleaned = true;
}

GgafMainActor* GgafGod::receive_Actor(uint64_t prm_cradle_no, GgafObject* prm_pReceiver) {
    return (GgafMainActor*)GgafGod::receive(prm_cradle_no, prm_pReceiver);
}

GgafMainScene* GgafGod::receive_Scene(uint64_t prm_cradle_no, GgafObject* prm_pReceiver) {
    return (GgafMainScene*)receive(prm_cradle_no, prm_pReceiver);
}

void GgafGod::createCradle(uint64_t prm_cradle_no,
                           GgafObject* (*prm_pFunc)(void*, void*, void*),
                           GgafObject* prm_pWisher,
                           GgafObject* prm_pReceiver,
                           void* prm_pArg1,
                           void* prm_pArg2,
                           void* prm_pArg3) {
    _TRACE2_("���˗��l:("<<prm_pWisher<<")�� �ʃX���b�h�̐_����A [" << prm_cradle_no << "-"<<prm_pReceiver<<"]������Ƃ��Ă�`�B");
    //���ɏj�����Ă��Ȃ����`�F�b�N
    GgafCradle* pCradle = _pCradleRoot;
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
    pCradle_new->_time_of_wants = timeGetTime();
    pCradle_new->_pArg1 = prm_pArg1;
    pCradle_new->_pArg2 = prm_pArg2;
    pCradle_new->_pArg3 = prm_pArg3;
    pCradle_new->_progress = 0;
    if (_pCradleRoot == nullptr) {
        _TRACE2_("���˗��l:("<<prm_pWisher<<")�� �����A�_�l�͂��ɂł��ˁB���肢������A�������܂���ˁH�B");
        pCradle_new->_is_first_cradle_flg = true;
        pCradle_new->_is_last_cradle_flg = true;
        pCradle_new->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_new;
        _pCradleRoot = pCradle_new;
        _pCradleBlessing = pCradle_new;
    } else {
        _TRACE2_("���˗��l:("<<prm_pWisher<<")�� ��肩�����܂��Ă܂��ˁA���X��肩���������܂��B");
        pCradle_new->_is_first_cradle_flg = false;
        pCradle_new->_is_last_cradle_flg = true;
        GgafCradle* pCradle_last = _pCradleRoot->_pCradle_prev;
        pCradle_last->_is_last_cradle_flg = false;
        pCradle_last->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_last;
        pCradle_new->_pCradle_next = _pCradleRoot;
        _pCradleRoot->_pCradle_prev = pCradle_new;
    }
}

int GgafGod::chkCradle(uint64_t prm_cradle_no) {
    GgafCradle* pCradle;
    pCradle = _pCradleRoot;
    if (pCradle == nullptr) {
        return -1;
    }
    while (_is_loving_flg) {
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
    GgafCradle* pCradle= _pCradleRoot;
    GgafCradle* pCradle_my_next;
    GgafCradle* pCradle_my_prev;
    DWORD waittime = 0;
    void* objectCreation;

    if (pCradle == nullptr) {
        //��肩�����疳����G���[�����I�A�G���[���b�Z�[�W�����B
        _TRACE_(FUNC_NAME<<" ��肩���疳����G���[�����I");
        GgafGod::debuginfo();
        throwGgafCriticalException("Error! prm_cradle_no="<<prm_cradle_no<<" ��肩�����X�g��nullptr�őS�ďj���ς݂��Ă��܂��B\n"
                                   "createCradle��receive�̑Ή������Ă��܂���B\n"
                                   "���l(receive�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }

    //receive���C�����[�v
    while (_is_loving_flg) {
        if (pCradle->_cradle_no == prm_cradle_no && (pCradle->_pReceiver == nullptr || pCradle->_pReceiver == prm_pReceiver) ) {
            while (_is_loving_flg) {
                if (pCradle->_progress < 2) {
                    _TRACE2_("�����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� �˂��_�l�A["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]�̏j���܂��`�H�A5�~���b�����҂������悤�BpCradle->_progress="<<(pCradle->_progress));
#ifdef _DEBUG
                    //�f�o�b�O���̓^�C���A�E�g����
#else

                    if (waittime > 1000*600) { //��10��
                        _TRACE_(FUNC_NAME<<" �^�C���A�E�g�G���[�����I");
                        GgafGod::debuginfo();
                        //�^�C���A�E�g�G���[�����I�A�G���[���b�Z�[�W�����B
                        throwGgafCriticalException("Error! ��肩��["<<pCradle->getDebuginfo()<<"]�̏j���҂����ԃ^�C���A�E�g�A�擾�ł��܂���B\n"
                                                   "���炩�̗��R�Ń��C���X���b�h����~���Ă���\�����傫���ł��B"
                                                   "���l(receive�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
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
                        pCradle = _pCradleRoot; //������x�ŏ�����T������B
                        _TRACE_N_("�c");
                        break;
                    } else if (pCradle->_progress == 2) {
                        //����
                        pCradle = _pCradleRoot;
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
                        //�Ō�̈�� receive
                        objectCreation = pCradle->_pObject_creation;
                        pCradle->_pObject_creation = nullptr;
                        GGAF_DELETE(pCradle);
                        pCradle = nullptr;
                        _pCradleRoot = nullptr;
                        _pCradleBlessing = nullptr;
                        _TRACE2_("�����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� ���A�Ƃ���ł����_�͋�ł��ˁB�ɂɂȂ�����H�A�˂��H");
                        return (void*)objectCreation;
                    } else {
                        //���Ԃ�receive�A�����q�������B
                        pCradle_my_next = pCradle->_pCradle_next;
                        pCradle_my_prev = pCradle->_pCradle_prev;
                        pCradle_my_prev->_pCradle_next = pCradle_my_next;
                        pCradle_my_next->_pCradle_prev = pCradle_my_prev;
                        if (pCradle->_is_last_cradle_flg) {
                            pCradle_my_prev->_is_last_cradle_flg = true;
                        }
                        if (pCradle->_is_first_cradle_flg) {
                            _pCradleRoot = pCradle_my_next;
                            pCradle_my_next->_is_first_cradle_flg = true;
                        }
                        if (_pCradleBlessing == pCradle) {
                            _pCradleBlessing = pCradle_my_next;
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
                                           "createCradle() �� GgafGod::receive() �̑Ή������Ă��܂���BcreateCradle()�R��A�����͓��� GgafGod::receive() ���Q��ȏサ�Ă܂��񂩁H�B\n"
                                           "���F���l(receive�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<") �ł����B\n"
                                           "�i�����Ȃ݂ɁA���ݐ_�̍ŏI�I�[�_�[�́A��肩���ԍ�("<<pCradle->_cradle_no<<"-"<<pCradle->_pReceiver<<")�ŁA�]�񂾐l(createCradle(�Ăь�)=("<<pCradle->_pWisher<<") �ł����j");
            } else {
                pCradle = pCradle->_pCradle_next;
            }
        }
    }
    if (_pException_god) {
        throw *(_pException_god);
    }
    return nullptr;
}

void GgafGod::beginRest() {
    _TRACE_(FUNC_NAME<<" ���_���x�e��");
    _have_to_rest_flg = true;
}

bool GgafGod::isResting() {
    if (_is_resting_flg) {
        _TRACE_(FUNC_NAME<<" �_�x�~���");
    } else {
        _TRACE_(FUNC_NAME<<" �_�ғ����");
    }
    return _is_resting_flg;
}

void GgafGod::finishRest() {
    _TRACE_(FUNC_NAME<<" ���_���_�A�x�e�͂����܂��B���������I");
    _have_to_rest_flg = false;
}


void GgafGod::flood() {
    //�_�ɂ��ߍ���ł���S�Ă̂�肩����j��
    //�_(GgafGod)���A�v���I�������Ɏ��s����\��B
    _TRACE2_("���_�� �^���J�n");
    GgafCradle* pCradle = _pCradleRoot;
    if (pCradle == nullptr) {
        _TRACE2_("���_�� ���������������I�I");
        return;
    }
    uint64_t cnt = 0;
    while (_is_loving_flg || _was_finished_flg == false) {
        Sleep(10);
        _TRACE_(FUNC_NAME<<" ���_�� ���͂܂������Ă܂��E�E�E");
        cnt++;
        if (cnt > 100*60*5) {
            _TRACE_(FUNC_NAME<<" ���_�� �܂������Ă܂��E�E�E���A�����������B������");
            break;
        }
    }

    GgafGod::debuginfo();

    while (true) {
        if (pCradle->_is_last_cradle_flg) {
            _TRACE2_("���_�� ��肩���폜["<<pCradle->getDebuginfo()<<"]�A�Ō�̃X�g�b�N");
            GGAF_DELETE(pCradle);
            pCradle = nullptr;
            _pCradleRoot = nullptr;
            _pCradleBlessing = nullptr;
            break;
        } else {
            _TRACE2_("���_�� ��肩���폜["<<pCradle->getDebuginfo()<<"]");
            GgafCradle* pCradle_my_next = pCradle->_pCradle_next;
            GGAF_DELETE(pCradle);
            pCradle = pCradle_my_next;
        }
    }
    _TRACE2_("���_�� �^������");
    return;
}

void GgafGod::pardon(GgafObject* prm_pReceiver) {
    //�V��������]�񂾐l�������Ȃ����ׁA���l�̂��Ȃ���肪�����폜����i�j���ς݂̖����폜�j�B
    GgafCradle* pCradle = _pCradleRoot;
    while (pCradle) {
        if (pCradle->_pReceiver == prm_pReceiver) {
            if (pCradle->_is_last_cradle_flg && pCradle->_is_first_cradle_flg) {
                //�Ō�̈��
                GGAF_DELETE(pCradle);
                _pCradleRoot = nullptr;
                _pCradleBlessing = nullptr;
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
                    _pCradleRoot = pCradle_t_next;
                    pCradle_t_next->_is_first_cradle_flg = true;
                }
                if (_pCradleBlessing == pCradle) {
                    _pCradleBlessing = pCradle_t_next;
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
    _TRACE_(FUNC_NAME<<" ���_�� ���݂̂�肩�����");
    try {
        GgafCradle* p = _pCradleRoot;
        if (p) {
            while(p) {
                _TRACE_("�E" << p->getDebuginfo() );
                p = p->_pCradle_next;
                if (p == _pCradleRoot) {
                    break;
                }
            }
        } else {
            _TRACE_("�E��肩���͂���܂���I");
        }
    } catch (...) {
        _TRACE_(FUNC_NAME<<" �Ȃ�Ƃ������Ƃł��傤�B���݂̐_�̏�Ԃ̕\�����s�\�ł��B����Ȕn���ȁG");
    }
    _TRACE_(FUNC_NAME<<" �ȏ�");
}

unsigned __stdcall GgafGod::love(void* prm_arg) {
    return pGOD->loveEternal(prm_arg);
}
unsigned GgafGod::loveEternal(void* prm_arg) {
    try {
        GgafObject* (*funcBlessing)(void*, void*, void*) = nullptr;
        GgafObject* pObject = nullptr;
        Sleep(1000); //god �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�

        //�j�����܂��邭��_�̈����[�v�I
        while (_is_loving_flg) {
            if (_have_to_rest_flg) {
                _is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                _is_resting_flg = false;
            }

BEGIN_SYNCHRONIZED1; // ----->�r���J�n
            GgafCradle* pCradleBlessing = _pCradleBlessing;
            if (pCradleBlessing) {
                if (pCradleBlessing->_progress == 0) { //������Ȃ�܂����
                    _TRACE2_("���_�� �悵�A��肩��["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]�͖�����(_progress == "<<pCradleBlessing->_progress<<")���ȁB�䂦�ɍ�������܂��I");
                    pCradleBlessing->_progress = 1; //�X�e�[�^�X���j������
                    pCradleBlessing->_time_of_create_begin = timeGetTime();
                    funcBlessing = pCradleBlessing->_pFunc;
                    void* arg1 = pCradleBlessing->_pArg1;
                    void* arg2 = pCradleBlessing->_pArg2;
                    void* arg3 = pCradleBlessing->_pArg3;
                    _TRACE2_("���_�� �j���J�n�I["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]");
                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- �r���I��

                    pObject = (*funcBlessing)(arg1, arg2, arg3); //�j���A�����a���B

                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
                    Sleep(2);
                    _TRACE2_("���_�� �j�������I���܂ꂽ�̂�["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"] (^_^)v");
                    if (_pCradleBlessing == nullptr) {
                        //_pCradleBlessing ���j���� nullptr �ɂȂ��Ă��܂��Ă���ꍇ�L�����Z���B
                        _TRACE2_("���_�� �K�[���I�B���������j�������̂ɃL�����Z���������E�E�E�B�j�����܂��BpObject��delete!");
                        GGAF_DELETE(pObject);
END_SYNCHRONIZED1; // <----- �r���I��
                        continue;
                    } else if (_pCradleBlessing == pCradleBlessing) {
                        //����ȃP�[�X
                        pCradleBlessing->_pObject_creation = pObject; //��肩���ɏ悹��
                        pCradleBlessing->_progress = 2; //�X�e�[�^�X���j���ς݂�
                        pCradleBlessing->_time_of_create_finish = timeGetTime();
                        _TRACE2_("���_�� �j��������肩���̖�["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]���A�I�ɒu���Ƃ��܂��B");
                    }  else if (_pCradleBlessing != pCradleBlessing) {
                        _TRACE2_("���_�� �x���A��肩���̖�["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]������Ă���ԂɁA"
                                 "_pCradleBlessing ���A�ʂ̂�肩��["<<_pCradleBlessing->_cradle_no<<"-"<<_pCradleBlessing->_pReceiver<<"]���w���Ă��܂����I���Ă邩������܂���I�����I�Ɍ��ɖ߂��܂��I�v�����I");
                        _pCradleBlessing = pCradleBlessing; //�|�C���^�����߂�
                        pCradleBlessing->_pObject_creation = pObject; //��肩���ɏ悹��
                        pCradleBlessing->_progress = 2; //�X�e�[�^�X���j���ς݂�
                        pCradleBlessing->_time_of_create_finish = timeGetTime();
                        _TRACE2_("���_�� �j��������肩���̖�["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]���A�I�ɒu���Ƃ��܂��E�E�E�B");
                    }
                } else {
                    _TRACE2_("���_�� ��肩��["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]�̖��́A�����j���ς݂ŃX�g�b�N���Ă邵�E�E�E(_progress == "<<pCradleBlessing->_progress<<")�B");
                }
            }
            if (_pCradleRoot == nullptr) {
                //�������ҋ@
                _TRACE2_("���_�� ���`�������܂���B��肩�����������I�I�E�E�E�Ȃ��̂�H�B�i�ҋ@�j");
END_SYNCHRONIZED1; // <----- �r���I��
                if (_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("���_�� ���قǖZ�����Ȃ��̂ŁA�S�~���̃S�~���o���Ƃ����B");
                    GgafGarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                    GgafGarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (_pCradleRoot != nullptr && _pCradleRoot->_pCradle_prev->_progress == 0) {
                    _TRACE2_("���_�� �E�E�E���j���̂�肩��������C�z�B�ŏI�ڕW�̂�肩����["<<_pCradleRoot->_pCradle_prev->_cradle_no<<"/���l="<<_pCradleRoot->_pCradle_prev->_pReceiver<<"]�Ȃ̂��H�B");
                    _pCradleBlessing = _pCradleBlessing->_pCradle_next;
END_SYNCHRONIZED1; // <----- �r���I��
                } else {
                    _TRACE2_("���_�� ���āA���j����肩���͖����B�I�ɏj���ς̂񂪂��܂��Ă�̂𑁂���ɗ��������I�B�i�ҋ@�j");
END_SYNCHRONIZED1; // <----- �r���I��
                    if (_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("���_�� ���قǖZ�����Ȃ��������Ȃ̂ŁA�S�~���̃S�~���o���Ƃ������B");
                        GgafGarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                        GgafGarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        } // <-- while (_is_loving_flg)
        _TRACE2_("���_�� ���悤�Ȃ�A�܂���܂��傤�B");
        _was_finished_flg = true;
    } catch (GgafCriticalException& e) {
        debuginfo();
        _TRACE_("���_��O�� ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
        _is_loving_flg = false;
        _was_finished_flg = true;
        _pException_god = NEW GgafCriticalException(e.getMsg());
        return 1;
    }
    return 0;
}


