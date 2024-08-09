#include "jp/ggaf/core/Caretaker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/Cradle.h"
#include "jp/ggaf/core/GarbageBox.h"
#include "jp/ggaf/core/Config.h"
#include "jp/ggaf/core/scene/Spacetime.h"
#include "jp/ggaf/core/scene/DisusedScene.h"
#include "jp/ggaf/core/actor/DisusedActor.h"

#include <process.h>

using namespace GgafCore;

CRITICAL_SECTION Caretaker::CS1;
CRITICAL_SECTION Caretaker::CS2;
//CRITICAL_SECTION Caretaker::CS3;

#ifdef MY_DEBUG
unsigned int Caretaker::_num_draw = 0;
unsigned int Caretaker::_num_draw_actors = 0;
#endif
unsigned int Caretaker::_num_active_actors = 0;

Caretaker* Caretaker::_pCaretaker = nullptr;

Caretaker::Caretaker() : Object(),
  _pSpacetime(nullptr),
  _fps(0.0) {
    Caretaker::_pCaretaker = this;
    timeBeginPeriod(1);
    _frame_of_Caretaker = 0;
    _handle_god_love01 = (HANDLE)_beginthreadex(nullptr, 0, Caretaker::love, nullptr, CREATE_SUSPENDED, &_th_id01);

    if (_handle_god_love01 == 0) {
        throwCriticalException("Error! Caretaker::love() �X���b�h�쐬���s�I");
    }

//    _handle_god_send03 = (HANDLE)_beginthreadex(nullptr, 0, Caretaker::send, nullptr, CREATE_SUSPENDED, &_th_id03);
//    if (_handle_god_send03 == 0) {
//        throwCriticalException("Error!  Caretaker::send() �X���b�h�쐬���s�I");
//    }

    ::InitializeCriticalSection(&(Caretaker::CS1));
    ::InitializeCriticalSection(&(Caretaker::CS2));
//    ::InitializeCriticalSection(&(Caretaker::CS3));
    ::ResumeThread(_handle_god_love01);
    ::SetThreadPriority(_handle_god_love01, BELOW_NORMAL_PRIORITY_CLASS );
//    ::ResumeThread(_handle_god_send03);
//    ::SetThreadPriority(_handle_god_send03, NORMAL_PRIORITY_CLASS );


    DWORD time_now = timeGetTime();
    _time_of_next_view = time_now;
    _time_calc_fps_next = time_now + 1;
    _visualize_frames = 0;
    _prev_visualize_frames = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GarbageBox::_pGarbageBox = NEW GarbageBox();
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
    _was_finished_loving_flg = false;
    _is_sending_flg   = false;
    _was_finished_sending_flg = false;
    //_base_fps = CONFIG::FPS;
    _aTime_offset_of_next_view[0] = 1.0 / CONFIG::FPS;
    _aTime_offset_of_next_view[1] = CONFIG::RATE_OF_SLOWDOWN1 / CONFIG::FPS;
    _aTime_offset_of_next_view[2] = CONFIG::RATE_OF_SLOWDOWN2 / CONFIG::FPS;

    _apaTime_offset_of_next_view[0] = getArrTimeOffset((DWORD)(1.0 * 1000), CONFIG::FPS); // 1�t���[�����A(1000 / CONFIG::FPS) �~���b�Ƃ���
    _apaTime_offset_of_next_view[1] = getArrTimeOffset((DWORD)(CONFIG::RATE_OF_SLOWDOWN1 * 1000), CONFIG::FPS); // 1�t���[�����A(1500 / CONFIG::FPS) �~���b�Ƃ���
    _apaTime_offset_of_next_view[2] = getArrTimeOffset((DWORD)(CONFIG::RATE_OF_SLOWDOWN2 * 1000), CONFIG::FPS); // 1�t���[�����A(2000 / CONFIG::FPS) �~���b�Ƃ���

}


//void Caretaker::setSpacetimeFps(int prm_fps) {
//    GGAF_DELETEARR_NULLABLE(_apaTime_offset_of_next_view[0]);
//    GGAF_DELETEARR_NULLABLE(_apaTime_offset_of_next_view[1]);
//    GGAF_DELETEARR_NULLABLE(_apaTime_offset_of_next_view[2]);
//    _base_fps = prm_fps;
//    _apaTime_offset_of_next_view[0] = getArrTimeOffset(1000, _base_fps);
//    _apaTime_offset_of_next_view[1] = getArrTimeOffset(1500, _base_fps);
//    _apaTime_offset_of_next_view[2] = getArrTimeOffset(2000, _base_fps);
//    _aTime_offset_of_next_view[0] = 1.0 / _base_fps;
//    _aTime_offset_of_next_view[1] = 1.5 / _base_fps;
//    _aTime_offset_of_next_view[2] = 2.0 / _base_fps;
//}

DWORD* Caretaker::getArrTimeOffset(DWORD sec, DWORD fps) {
    DWORD base = sec / fps;
    DWORD r = sec % fps;
    double rr = 1.0*r / fps;
    DWORD* paTimeOffset = new DWORD[fps];
    double x = 1.0;

    for (int i = 0; i < (int)fps; i++) {
        x += rr;
        if (x > 1.0) {
            paTimeOffset[i] = base + 1;
            x -= 1.0;
        } else {
            paTimeOffset[i] = base;
        }
    }
    return paTimeOffset;

}


void Caretaker::present() {
    // �y�����z
    // �P�T�C�N���i�P�t���[���j�̏����͈ȉ��̗l�ɑ傫���T�ɕ����A���Ɏ��s������̂Ƃ����B
    //
    // �@Mo = presentMoment();      ��� ���C�������E�K�{����
    // �ABe = presentBehave();      ��� �ړ������E�K�{����
    // �BJu = presentJudge();       ��� ���菈���E�K�{����
    // �CMa = presentMaterialize(); ��� �`�揈��(�d��)�E�X�L�b�v��
    // �DVi = presentVisualize();   ��� �`��t���b�v�����E�X�L�b�v��(�A���C�ƇD�̓Z�b�g����)
    // �ECl = presentClosing();     ��� �ŏI�����E�K�{����
    //
    // �����ōs�Ȃ��������Ƃ́w�ł������A�DVi �� 1/60 �b���Ɉ��肵�Ď��s���邱�Ɓx�Ƃ����B
    // �����ŁA���̗l�Ȑ݌v���s�����B
    // �E�悸 �DVi �����s�������^�C�~���O��\�ߌ��肷��B����́A�@���ɏ������d���Ȃ낤�Ƃ��ς��Ȃ��B
    //    _time_of_next_view = _time_of_next_view + (1/60�b)
    //   �Ƃ���B
    // �E�BJu �����s�������_�ŁA�CMa�A�DVi �����s���邩�ǂ������c���_time_of_next_view �܂ł̎��ԂŔ��f����B
    //   ���Ԃɗ]�T���L��ꍇ�A�BJu ���s�㑦���� �CMa ���s�A���̌� _time_of_next_view �܂ő҂� �CVi ���s����B
    //   ���� �BJu ���s��A���t���[���ɂ߂荞��ł����ꍇ �CMa�A�DVi �̓X�L�b�v�B
    // �E��L����{���[���Ƃ��A_max_skip_frames �t���[���ɂP��͕K�� �CMa�A�DVi �����s����B
    //   ����͂ǂ�Ȃɏ������d�����Ȃ낤�Ƃ��A�v���O�����������Ă��邱�Ƃ����o�����邽�߁B
    //
    //
    //�y���莞�̗��z�}�z
    //        _time_of_next_view                                        _time_of_next_view
    //                 |        3frame begin(_frame_of_Caretaker++)               |        4frame begin(_frame_of_Caretaker++)
    //                 |             |                                            |             |
    //                 v             v                                            v             v
    // ====================================================================================================================================> ����
    //  <--- wait ---> |(�DVi)| �ECl | �@Mo | �ABe | �BJu |(�CMa)|<---- wait ---->|(�DVi)| �ECl | �@Mo | �ABe | �BJu |(�CMa)|<--- wait -
    //                 |             |                                            |             |
    // -- 2frame ------------------->|<-------------------------- 3frame ---------------------->|<-------------  4frame -------------------
    //                 |                                                          |
    //                 |<----------------- 1/60 sec ----------------------------->|
    //                 |                                         |
    //                 |<----- ���������ł���ΑO�l�ߏ���    --->|
    //                         ���̕�wait���������肷��B
    //
    // �����Ӂ�
    // �E�����܂� �DVi �� 1/60 �b���̃^�C�~���O�ŏ������鎖��D��Ŗڎw���d�g�݂ł����āA
    //   �����t���[���J�E���^�� 1/60 �b���ɃJ�E���g�A�b�v�����Ƃ����d�g�݂ł͖����i�l�����Ă��Ȃ��j�B
    //   _time_of_next_view �` ���� _time_of_next_view �͏�ɌŒ莞��(1/60 sec)�ł��邪�A
    //   �Ⴆ�Ώ�}�ł� 3frame begin  �` 4frame begin �Ԃ̎��Ԃ͑O�����ɂ��ϓ�����B
    //

    if (_pSpacetime == nullptr) {
        //���̐����܂������ꍇ�́A�悸���̐����쐬�B
        _pSpacetime = createSpacetime();
#ifdef MY_DEBUG
        if (_pSpacetime == nullptr) {
            throwCriticalException("Error! ���̐����������ĉ������I");
        }
#endif
        _pSpacetime->_pCaretaker = this;
        DWORD time_now = timeGetTime();
        _time_of_next_view = time_now + 100; //0.1�b��J�n
        _time_calc_fps_next = time_now + 1;
    }
#ifdef MY_DEBUG
    //�Ǘ��ҁi�ʃX���b�h�j��O���`�F�b�N
    if (_pException_god) {
        throw *_pException_god;
    }
#endif
    //�t���[���Ǝ��Ԃ̓������s��
    if (_sync_frame_time) {
        DWORD time_now = timeGetTime();
        _time_of_next_view = time_now + 100; //0.1�b��J�n
        _time_calc_fps_next = time_now + 1;
        _TRACE_("Caretaker::present() �t���[���Ǝ��Ԃ̓��������{�B");
        _sync_frame_time = false;
    }

    if (_is_behaved_flg == false) {
        //BEGIN_SYNCHRONIZED1; // ----->�r���J�n
        _frame_of_Caretaker++;
        presentMoment(); //�@
        presentBehave(); //�A
        presentJudge();  //�B
        _time_of_next_view += _apaTime_offset_of_next_view[_slowdown_mode][_cnt_frame];
        _cnt_frame++;
        if (_cnt_frame >= CONFIG::FPS) { _cnt_frame = 0; }
        //�C�����s���邩�Y��
        if (timeGetTime() >= _time_of_next_view) {
            //�`��^�C�~���O�t���[���ɂȂ����A�����͉߂��Ă���ꍇ
            //�`�斳���i�X�L�b�v���j�C�̓p�X����B
            _is_materialized_flg = false;
        } else {
            //�`��^�C�~���O�t���[���ɂȂ��Ă��Ȃ��B�]�T������B
            //�`��L��i�X�L�b�v�Ȃ��j
             _is_materialized_flg = true;
            presentMaterialize(); //�C
            //�A�� �C �ɂ��I�[�o�[������������Ȃ��B
        }
        _is_behaved_flg = true;
        //END_SYNCHRONIZED1;  // <-----�r���I��
    }

    DWORD time_now = timeGetTime();
    if (time_now >= _time_of_next_view) {
        //�`��^�C�~���O�t���[���ɂȂ����A�����͉߂��Ă���ꍇ
//TODO:�v�m�F
//        BEGIN_SYNCHRONIZED1;  // ----->�r���J�n
        if (_is_materialized_flg) {
            //�`��L��i�X�L�b�v�Ȃ��j�i�@�A�B�C ���s�ς݂̏ꍇ�j
            presentVisualize();  _visualize_frames++; //�D
        } else {
            //�`�斳���i�X�L�b�v���j�i�@�A�B���s�ς݁A�C���s���Ă��Ȃ��̂ŇD���X�L�b�v���悤���ȁj
            _skip_count_of_frame++;

            if (_skip_count_of_frame >= _max_skip_frames) {
                //�A���A�X�L�b�v����Ƃ����Ă� MAX_SKIP_FRAME �t���[���ɂP���
                //�������`�悵�āA�A�v�������삵�Ă��邱�Ƃ��A�s�[���B�i�������C�D�����s�j
                presentMaterialize(); //�C
                presentVisualize();  _visualize_frames++; //�D
                _skip_count_of_frame = 0;
            } else {
                //�C�D���X�L�b�v�ƂȂ�B
            }
        }
        presentClosing(); //�E
        _is_behaved_flg = false;
//TODO:�v�m�F
//        END_SYNCHRONIZED1;    // <-----�r���I��

        //fps�v�Z
        if (time_now >= _time_calc_fps_next) {
            const int d_visualize_frames = _visualize_frames - _prev_visualize_frames;
            if (d_visualize_frames == 0) {
                _fps = 0;
            } else {
                static const double inv_offset_default = 1.0f / _aTime_offset_of_next_view[SLOWDOWN_MODE_DEFAULT];
                _fps = inv_offset_default * d_visualize_frames * _aTime_offset_of_next_view[SLOWDOWN_MODE_DEFAULT];
            }
            _time_calc_fps_next += 1000;
            _prev_visualize_frames = _visualize_frames;
        }

     } else { //�`��^�C�~���O�t���[���ɂȂ��ĂȂ�(�]�T������)
         Sleep(1); //<--- wait ---> �� �ЂƂƂ�
     }
    return;
}

void Caretaker::presentMoment() {
    _pSpacetime->nextFrame();
}
void Caretaker::presentBehave() {
    _pSpacetime->behave();
    _pSpacetime->settleBehavior();
}
void Caretaker::presentJudge() {
    _pSpacetime->judge();
#ifdef MY_DEBUG
    _pSpacetime->_is_running_processHitCheck = true;
#endif
    _pSpacetime->processHitCheck(); //Spacetime�̂�
#ifdef MY_DEBUG
    _pSpacetime->_is_running_processHitCheck = false;
#endif
}

void Caretaker::presentMaterialize() {
    if (Caretaker::_num_active_actors > CONFIG::OBJNUM_TO_SLOWDOWN2) {
        _slowdown_mode = SLOWDOWN_MODE2;
    } else if (Caretaker::_num_active_actors > CONFIG::OBJNUM_TO_SLOWDOWN1) {
        _slowdown_mode = SLOWDOWN_MODE1;
    } else {
        _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    }
#ifdef MY_DEBUG
    Caretaker::_num_draw = 0;
    Caretaker::_num_draw_actors = 0;
#endif
    Caretaker::_num_active_actors = 0;
    Spacetime* pSpacetime = _pSpacetime;
    pSpacetime->preDraw();
    pSpacetime->draw();
    pSpacetime->afterDraw();
}

void Caretaker::presentVisualize() {
    _pSpacetime->dump();
}

void Caretaker::presentClosing() {
    _pSpacetime->doFinally();
}
void Caretaker::calmDown() {
    _TRACE_("Caretaker::calmDown() _was_finished_loving_flg="<<_was_finished_loving_flg);
    if (_was_finished_loving_flg == false) {
        _is_loving_flg = false;
        Sleep(10);
        _TRACE_("Caretaker::~Caretaker() �Ǘ��҂����������܂ő҂E�E�E");
        for (int i = 0; _was_finished_loving_flg == false; i++) {
            Sleep(10); //�Ǘ��҂����������܂ő҂�
            if (i > 5*100*60) {
                _TRACE_("Caretaker::~Caretaker() 5���ҋ@���܂������A�Ǘ��҂��甽��������܂���B�����m��܂���I�A���� break ���܂��B�v����");
                break;
            }
        }
        _TRACE_("Caretaker::~Caretaker() �Ǘ��҂����������܂���");
    }
}
void Caretaker::clean() {
    _TRACE_(FUNC_NAME<<" begin");
    if (!_was_cleaned) {
        if (_pSpacetime) {
            _TRACE_("_pSpacetime != nullptr");
            //�Ǘ��҂��~�߂�
            calmDown();
            //�r���̉����A�X���b�h���I������܂ő҂�
            _TRACE_("Caretaker::~Caretaker()  WaitForSingleObject(_handle_god_love01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handle_god_love01, 120*1000);  //DeleteCriticalSection���s�����߂ɕK�v
            if (r == WAIT_TIMEOUT) {
                throwCriticalException("�I������͂��Ȃ̂ɁA���Ԃ�Ǘ��҂̈����܂��I����Ă��܂���E�E�E�E�i�܁j�B�f�o�b�O���u���܂������H");
            }
            _TRACE_("Caretaker::~Caretaker()  CloseHandle(_handle_god_love01) .....");
            CloseHandle(_handle_god_love01);
            _TRACE_("Caretaker::~Caretaker()  DeleteCriticalSection(&(Caretaker::CS1)); .....");
            DeleteCriticalSection(&(Caretaker::CS1));
            _handle_god_love01 = nullptr;

//            _TRACE_("Caretaker::~Caretaker()  WaitForSingleObject(_handle_god_send03, 120*1000) .....");
//            r = WaitForSingleObject(_handle_god_send03, 120*1000);  //DeleteCriticalSection���s�����߂ɕK�v
//            if (r == WAIT_TIMEOUT) {
//                throwCriticalException("�I������͂��Ȃ̂ɁA���Ԃ�Ǘ��҂̈يE���肪�܂��I����Ă��܂���E�E�E�E�i�܁j�B�f�o�b�O���u���܂������H");
//            }
//            _TRACE_("Caretaker::~Caretaker()  CloseHandle(_handle_god_send03) .....");
//            CloseHandle(_handle_god_send03);
//            _TRACE_("Caretaker::~Caretaker()  DeleteCriticalSection(&(Caretaker::CS3)); .....");
//            DeleteCriticalSection(&(Caretaker::CS3));
//            _handle_god_send03 = nullptr;

            _TRACE_("Caretaker::~Caretaker() �����ɊǗ��҃X���b�h���I���B�N���e�B�J���Z�N�V��������");

#ifdef MY_DEBUG
            //�c���[�\���\��
            _TRACE_("Dumping _pSpacetime ...");
            _pSpacetime->dump();
#endif

            //�^��
            desert();
            //�S�~��
#ifdef MY_DEBUG
            _TRACE_("Dumping GarbageBox::_pGarbageBox->_pDisusedScene ...");
            GarbageBox::_pGarbageBox->_pDisusedScene->dump();
            _TRACE_("Dumping GarbageBox::_pGarbageBox->_pDisusedActor ...");
            GarbageBox::_pGarbageBox->_pDisusedActor->dump();
#endif
            _TRACE_(FUNC_NAME<<" GGAF_DELETE(GarbageBox::_pGarbageBox) begin");
            GGAF_DELETE(GarbageBox::_pGarbageBox);
            _TRACE_(FUNC_NAME<<" GGAF_DELETE(GarbageBox::_pGarbageBox) end");
            //���̐��Ő����Ă��镨���|��
            Sleep(20);
            _TRACE_(FUNC_NAME<<" GGAF_DELETE(_pSpacetime); begin");
            GGAF_DELETE(_pSpacetime);
            _TRACE_(FUNC_NAME<<" GGAF_DELETE(_pSpacetime); end");

            _TRACE_("Caretaker::~Caretaker()  DeleteCriticalSection(&(Caretaker::CS2)); .....");
            DeleteCriticalSection(&(Caretaker::CS2));
        }

        GGAF_DELETEARR(_apaTime_offset_of_next_view[0]);
        GGAF_DELETEARR(_apaTime_offset_of_next_view[1]);
        GGAF_DELETEARR(_apaTime_offset_of_next_view[2]);
        //�Ǘ��җ�O _pException_god ���N�����Ă��邩������Ȃ��B
        _TRACE_("GGAF_DELETE_NULLABLE(_pException_god);");
        GGAF_DELETE_NULLABLE(_pException_god);
    }
    _TRACE_(FUNC_NAME<<" end");
}

Caretaker::~Caretaker() {
    _sync_frame_time = false;
    calmDown();
    timeEndPeriod(1);
    clean();
    _was_cleaned = true;
}

MainActor* Caretaker::takeOutActor(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering) {
    return (MainActor*)takeOutObject(prm_cradle_no, prm_pReceiver, prm_was_just_wondering);
}

MainScene* Caretaker::takeOutScene(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering) {
    return (MainScene*)takeOutObject(prm_cradle_no, prm_pReceiver, prm_was_just_wondering);
}

void Caretaker::addCradle(uint64_t prm_cradle_no,
                          Object* (*prm_pFunc)(void*, void*, void*),
                          Object* prm_pWisher,
                          Object* prm_pReceiver,
                          void* prm_pArg1,
                          void* prm_pArg2,
                          void* prm_pArg3) {
    _TRACE2_("���˗��l:("<<prm_pWisher<<")�� �ʃX���b�h�̊Ǘ��҂���A [" << prm_cradle_no << "-"<<prm_pReceiver<<"]������Ƃ��Ă�`�B");
    //���ɏj�����Ă��Ȃ����`�F�b�N
    Cradle* pCradle = _pCradleRoot;
    while (pCradle) {
        if (pCradle->_cradle_no == prm_cradle_no &&  pCradle->_pReceiver == prm_pReceiver) {
            _TRACE_("�y�x���z Caretaker::addCradle() ��肩��[" << prm_cradle_no << "-"<<prm_pReceiver<<"]�͊��ɑ��݂��Ă܂���I�B�Ӑ}���Ă��܂����H");
            return;
        }
        if (pCradle->_is_last_cradle_flg) {
            break;
        }
        pCradle = pCradle->_pCradle_next;
    }
    //��肩���͖����ł���悤�Ȃ̂Ő擪�ɃX�g�b�N
    Cradle* pCradle_new;
    pCradle_new = NEW Cradle(prm_cradle_no);
    pCradle_new->_pObject_creation=nullptr;
    pCradle_new->_pFunc = prm_pFunc;
    pCradle_new->_pWisher = prm_pWisher;
    pCradle_new->_pReceiver = prm_pReceiver;
    pCradle_new->_time_of_wants = timeGetTime();
    pCradle_new->_pArg1 = prm_pArg1;
    pCradle_new->_pArg2 = prm_pArg2;
    pCradle_new->_pArg3 = prm_pArg3;
    pCradle_new->_progress_no = 0;
    if (_pCradleRoot == nullptr) {
        _TRACE2_("���˗��l:("<<prm_pWisher<<")�� �����A�Ǘ��җl�͂��ɂł��ˁB���肢������A�������܂���ˁH�B");
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
        Cradle* pCradle_last = _pCradleRoot->_pCradle_prev;
        pCradle_last->_is_last_cradle_flg = false;
        pCradle_last->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_last;
        pCradle_new->_pCradle_next = _pCradleRoot;
        _pCradleRoot->_pCradle_prev = pCradle_new;
    }
}

int Caretaker::chkCradle(uint64_t prm_cradle_no) {
    Cradle* pCradle;
    pCradle = _pCradleRoot;
    if (pCradle == nullptr) {
        return -1;
    }
    while (_is_loving_flg) {
        if (pCradle->_cradle_no == prm_cradle_no) {
            return pCradle->_progress_no;
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


void* Caretaker::takeOutObject(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering) {
    _TRACE2_("�����l:"<< (prm_pReceiver ? prm_pReceiver->toString() : "nullptr") <<"("<<prm_pReceiver<<")�� �܂��ǁA["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]�����ɗ��܂�������ƁB");
#ifdef _DEBUG
    if (_is_behaved_flg) {
        throwCriticalException("Error! prm_cradle_no="<<prm_cradle_no<<" presentMoment()�ApresentJudge() �Ŏ󂯎���Ăق����ł��B\n"
                               " ���Ԃ񍡂� �N���e�B�J���Z�N�V�����O�ł͂Ȃ����낤���E�E�E����͍���B\n"
                                   "���l(receive�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }
#endif
    Cradle* pCradle= _pCradleRoot;
    Cradle* pCradle_my_next;
    Cradle* pCradle_my_prev;
    DWORD waittime = 0;
    void* objectCreation;

    if (pCradle == nullptr) {
        //��肩�����疳����G���[�����I�A�G���[���b�Z�[�W�����B
        _TRACE_(FUNC_NAME<<" ��肩�����疳����G���[�����I");
        Caretaker::debuginfo();
        throwCriticalException("Error! prm_cradle_no="<<prm_cradle_no<<" ��肩�����X�g��nullptr�őS�ďj���ς݂��Ă��܂��B\n"
                                   "addCradle��receive�̑Ή������Ă��܂���B\n"
                                   "���l(receive�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }

    //receive���C�����[�v
    BEGIN_SYNCHRONIZED1;
    while (_is_loving_flg) {
        if (pCradle->_cradle_no == prm_cradle_no && (pCradle->_pReceiver == nullptr || pCradle->_pReceiver == prm_pReceiver) ) {
            while (_is_loving_flg) {
                if (pCradle->_progress_no < 2) {
                    _TRACE2_("�����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� �˂��Ǘ��җl�A["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]�̏j���܂��`�H�A5�~���b�����҂������悤�BpCradle->_phase_no="<<(pCradle->_progress_no));
#ifdef _DEBUG
                    //�f�o�b�O���̓^�C���A�E�g����
#else
                    if (waittime > 1000*600) { //��10��
                        _TRACE_(FUNC_NAME<<" �^�C���A�E�g�G���[�����I");
                        Caretaker::debuginfo();
                        //�^�C���A�E�g�G���[�����I�A�G���[���b�Z�[�W�����B
                        throwCriticalException("Error! ��肩��["<<pCradle->getDebuginfo()<<"]�̏j���҂����ԃ^�C���A�E�g�A�擾�ł��܂���B\n"
                                                   "���炩�̗��R�Ń��C���X���b�h����~���Ă���\�����傫���ł��B"
                                                   "���l(receive�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
                    } else {
                    }
#endif
                    END_SYNCHRONIZED1; // <----- �r���I��
                    Sleep(5);
                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
                    waittime += 5;
                    if (pCradle->_progress_no == 1) {
                        //����ς�
                        _TRACE_N_("�I");
                        continue; //�҂�
                    } else if (pCradle->_progress_no == 0) {
                        //������H
                        pCradle = _pCradleRoot; //������x�ŏ�����T������B
                        _TRACE_N_("�c");
                        break;
                    } else if (pCradle->_progress_no == 2) {
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
                    if (prm_was_just_wondering) {
                        _TRACE2_("�����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� �����������A�܂��󂯎��܂���I�B������ƕ����Ă݂������`");
                        objectCreation = pCradle->_pObject_creation;
                        END_SYNCHRONIZED1;
                        return (void*)objectCreation;
                    }
                    if (pCradle->_is_first_cradle_flg && pCradle->_is_last_cradle_flg) {
                        //�Ō�̈�� receive
                        objectCreation = pCradle->_pObject_creation;
                        pCradle->_pObject_creation = nullptr;
                        GGAF_DELETE(pCradle);
                        pCradle = nullptr;
                        _pCradleRoot = nullptr;
                        _pCradleBlessing = nullptr;
                        _TRACE2_("�����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� ���A�Ƃ���ł����Ǘ��҂͋�ł��ˁB�ɂɂȂ�����H�A�˂��H");
                        END_SYNCHRONIZED1;
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
                        END_SYNCHRONIZED1;
                        return (void*)objectCreation;
                    }
                }
            }
        } else {
            if (pCradle->_is_last_cradle_flg) {
                _TRACE_(FUNC_NAME<<" ��肩���̌`�Ղ������A�擾�o���Ȃ��G���[�����I");
                Caretaker::debuginfo();
                END_SYNCHRONIZED1;
                //��肩���̌`�Ղ������A�擾�o���Ȃ��G���[�����I�A�G���[���b�Z�[�W�����B
                throwCriticalException("���Ǘ��ҁ��S���T���܂������ǁA����Ȃ�肩��("<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"����ւ� ��肩���ԍ�:"<<prm_cradle_no<<"-"<<prm_pReceiver<<")�́A����܂���B\n"
                                           "addCradle() �� Caretaker::takeOutObject() �̑Ή������Ă��܂���BaddCradle()�R��A�����͓��� Caretaker::takeOutObject() ���Q��ȏサ�Ă܂��񂩁H�B\n"
                                           "���F���l(receive�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<") �ł����B\n"
                                           "�i�����Ȃ݂ɁA���݊Ǘ��҂̍ŏI�I�[�_�[�́A��肩���ԍ�("<<pCradle->_cradle_no<<"-"<<pCradle->_pReceiver<<")�ŁA�]�񂾐l(addCradle(�Ăь�)=("<<pCradle->_pWisher<<") �ł����j");
            } else {
                pCradle = pCradle->_pCradle_next;
            }
        }
    }
#ifdef MY_DEBUG
    if (_pException_god) {
        throw *(_pException_god);
    }
#endif
    END_SYNCHRONIZED1;
    return nullptr;
}

void Caretaker::beginRest() {
    _TRACE_(FUNC_NAME<<" ���Ǘ��ҁ��x�e��");
    _have_to_rest_flg = true;
}

bool Caretaker::isResting() {
    if (_is_resting_flg) {
        _TRACE_(FUNC_NAME<<" �Ǘ��ҋx�~���");
    } else {
        _TRACE_(FUNC_NAME<<" �Ǘ��҉ғ����");
    }
    return _is_resting_flg;
}

void Caretaker::finishRest() {
    _TRACE_(FUNC_NAME<<" ���Ǘ��ҁ��Ǘ��ҁA�x�e�͂����܂��B���������I");
    _have_to_rest_flg = false;
}


void Caretaker::desert() {
    //�Ǘ��҂ɂ��ߍ���ł���S�Ă̂�肩����j��
    //�Ǘ���(Caretaker)���A�v���I�������Ɏ��s����\��B
    _TRACE_("���Ǘ��ҁ� �����E�E�E���̂Ă悤�E�E�E");
    Cradle* pCradle = _pCradleRoot;
    if (pCradle == nullptr) {
        _TRACE_("���Ǘ��ҁ� ���������������I�I");
        return;
    }
    uint64_t cnt = 0;
    while (_is_loving_flg || _was_finished_loving_flg == false) {
        Sleep(10);
        _TRACE_(FUNC_NAME<<" ���Ǘ��҂̈��� ���͂܂������Ă܂��E�E�E");
        cnt++;
        if (cnt > 100*60*5) {
            _TRACE_(FUNC_NAME<<" ���Ǘ��҂̈��� �܂������Ă܂��E�E�E���A�����������B���E�ł�");
            break;
        }
    }

    Caretaker::debuginfo();
    _TRACE_("���Ǘ��ҁ� ��肩���폜�J�n");
    while (true) {
        if (pCradle->_is_last_cradle_flg) {
            _TRACE_("���Ǘ��ҁ� ��肩���폜["<<pCradle->getDebuginfo()<<"]�A�Ō�̃X�g�b�N");
            GGAF_DELETE(pCradle);
            pCradle = nullptr;
            _pCradleRoot = nullptr;
            _pCradleBlessing = nullptr;
            break;
        } else {
            _TRACE_("���Ǘ��ҁ� ��肩���폜["<<pCradle->getDebuginfo()<<"]");
            Cradle* pCradle_my_next = pCradle->_pCradle_next;
            GGAF_DELETE(pCradle);
            pCradle = pCradle_my_next;
        }
    }
    _TRACE_("���Ǘ��ҁ� ��肩���폜�I��");
    return;
}

void Caretaker::repent(Object* prm_pReceiver) {
    //�V��������]�񂾐l�������Ȃ����ׁA���l�̂��Ȃ���肪�����폜����i�j���ς݂̖����폜�j�B
    Cradle* pCradle = _pCradleRoot;
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
                Cradle* pCradle_t_next = pCradle->_pCradle_next;
                Cradle* pCradle_t_prev = pCradle->_pCradle_prev;
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

void Caretaker::debuginfo() {
    _TRACE_(FUNC_NAME<<" ���Ǘ��ҁ� ���݂̂�肩�����");
    try {
        Cradle* p = _pCradleRoot;
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
        _TRACE_(FUNC_NAME<<" �Ȃ�Ƃ������Ƃł��傤�B���݂̊Ǘ��҂̏�Ԃ̕\�����s�\�ł��B����Ȕn���ȁG");
    }
    _TRACE_(FUNC_NAME<<" �ȏ�");
}

unsigned __stdcall Caretaker::love(void* prm_arg) {
    return pCARETAKER->loving(prm_arg);
}
unsigned Caretaker::loving(void* prm_arg) {
    try {
        Object* (*funcBlessing)(void*, void*, void*) = nullptr;
        Object* pObject = nullptr;
        Sleep(1000); //crtkr �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�

        //�j�����܂��邭��Ǘ��҂̈����[�v�I
        while (_is_loving_flg) {
            if (_have_to_rest_flg) {
                _is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                _is_resting_flg = false;
            }

BEGIN_SYNCHRONIZED1; // ----->�r���J�n
            Cradle* pCradleBlessing = _pCradleBlessing;
            if (pCradleBlessing) {
                if (pCradleBlessing->_progress_no == 0) { //������Ȃ�܂����
                    _TRACE2_("���Ǘ��҂̈��� �悵�A��肩��["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]�͖�����(_phase_no == "<<pCradleBlessing->_progress_no<<")���ȁB�䂦�ɍ�������܂��I");
                    pCradleBlessing->_progress_no = 1; //�X�e�[�^�X���j������
                    pCradleBlessing->_time_of_create_begin = timeGetTime();
                    funcBlessing = pCradleBlessing->_pFunc;
                    void* arg1 = pCradleBlessing->_pArg1;
                    void* arg2 = pCradleBlessing->_pArg2;
                    void* arg3 = pCradleBlessing->_pArg3;
                    _TRACE2_("���Ǘ��҂̈��� �j���J�n�I["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]");
//                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- �r���I��

                    pObject = (*funcBlessing)(arg1, arg2, arg3); //�j���A�����a���B

                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
//                    Sleep(2);
                    _TRACE2_("���Ǘ��҂̈��� �j�������I���܂ꂽ�̂�["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"] (^_^)v");
                    if (_pCradleBlessing == nullptr) {
                        //_pCradleBlessing ���j���� nullptr �ɂȂ��Ă��܂��Ă���ꍇ�L�����Z���B
                        _TRACE2_("���Ǘ��҂̈��� �K�[���I�B���������j�������̂ɃL�����Z���������E�E�E�B�j�����܂��BpObject��delete!");
                        GGAF_DELETE(pObject);
END_SYNCHRONIZED1; // <----- �r���I��
                        continue;
                    } else if (_pCradleBlessing == pCradleBlessing) {
                        //����ȃP�[�X
                        pCradleBlessing->_pObject_creation = pObject; //��肩���ɏ悹��
                        pCradleBlessing->_progress_no = 2; //�X�e�[�^�X���j���ς݂�
                        pCradleBlessing->_time_of_create_finish = timeGetTime();
                        _TRACE2_("���Ǘ��҂̈��� �j��������肩���̖�["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]���A�I�ɒu���Ƃ��܂��B");
                    }  else if (_pCradleBlessing != pCradleBlessing) {
                        _TRACE2_("���Ǘ��҂̈��� �x���A��肩���̖�["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]������Ă���ԂɁA"
                                 "_pCradleBlessing ���A�ʂ̂�肩��["<<_pCradleBlessing->_cradle_no<<"-"<<_pCradleBlessing->_pReceiver<<"]���w���Ă��܂����I���Ă邩������܂���I�����I�Ɍ��ɖ߂��܂��I�v�����I");
                        _pCradleBlessing = pCradleBlessing; //�|�C���^�����߂�
                        pCradleBlessing->_pObject_creation = pObject; //��肩���ɏ悹��
                        pCradleBlessing->_progress_no = 2; //�X�e�[�^�X���j���ς݂�
                        pCradleBlessing->_time_of_create_finish = timeGetTime();
                        _TRACE2_("���Ǘ��҂̈��� �j��������肩���̖�["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]���A�I�ɒu���Ƃ��܂��E�E�E�B");
                    }
                } else {
                    _TRACE2_("���Ǘ��҂̈��� ��肩��["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]�̖��́A�����j���ς݂ŃX�g�b�N���Ă邵�E�E�E(_phase_no == "<<pCradleBlessing->_progress_no<<")�B");
                }
            }
            if (_pCradleRoot == nullptr) {
                //�������ҋ@
                _TRACE2_("���Ǘ��҂̈��� ���`�������܂���B��肩�����������I�I�E�E�E�Ȃ��̂�H�B�i�ҋ@�j");
END_SYNCHRONIZED1; // <----- �r���I��
                if (_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("���Ǘ��҂̈��� ���قǖZ�����Ȃ��̂ŁA�S�~���̃S�~���o���Ƃ����B");
                    GarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                    GarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (_pCradleRoot != nullptr && _pCradleRoot->_pCradle_prev->_progress_no == 0) {
                    _TRACE2_("���Ǘ��҂̈��� �E�E�E�I�A���j���̂�肩��������C�z�B�ŏI�ڕW�̂�肩����["<<_pCradleRoot->_pCradle_prev->_cradle_no<<"/���l="<<_pCradleRoot->_pCradle_prev->_pReceiver<<"]�Ȃ̂��H�B");
                    _pCradleBlessing = _pCradleBlessing->_pCradle_next;
END_SYNCHRONIZED1; // <----- �r���I��
                } else {
                    _TRACE2_("���Ǘ��҂̈��� ���āA���j����肩���͖����B�I�ɂ��܂��Ă�̂𑁂����ɗ��������I�B�i�ҋ@�j");
END_SYNCHRONIZED1; // <----- �r���I��
                    if (_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("���Ǘ��҂̈��� ���قǖZ�����Ȃ��������Ȃ̂ŁA�S�~���̃S�~���o���Ƃ������c�B");
                        GarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                        GarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        } // <-- while (_is_loving_flg)
        _TRACE2_("���Ǘ��҂̈��� ���悤�Ȃ�A�܂���܂��傤�B");
        _was_finished_loving_flg = true;
    } catch (CriticalException& e) {
        debuginfo();
        _TRACE_("���Ǘ��җ�O�̈��� ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
        _is_loving_flg = false;
        _was_finished_loving_flg = true;
        _pException_god = NEW CriticalException(e.getMsg());
        return 1;
    }
    return 0;
}

unsigned __stdcall Caretaker::send(void* prm_arg) {
    return pCARETAKER->sending(prm_arg);
}

unsigned Caretaker::sending(void* prm_arg) {
    try {
        //Object* (*funcBlessing)(void*, void*, void*) = nullptr;
        //Object* pObject = nullptr;
        Sleep(1000); //crtkr �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�

        //�S�~�|�����܂���Ǘ��҂̈يE���胋�[�v�I
        while (_is_sending_flg) {
BEGIN_SYNCHRONIZED1; // ----->�r���J�n
            GarbageBox::_pGarbageBox->clean(5); //�V����
            GarbageBox::_cnt_cleaned = 0;
END_SYNCHRONIZED1; // <----- �r���I��
            Sleep(2);
        } // <-- while (_is_loving_flg)
        _TRACE2_("���Ǘ��҂̈يE���聄 ���悤�Ȃ�A�܂���܂��傤�B");
        _was_finished_sending_flg = true;
    } catch (CriticalException& e) {
        debuginfo();
        _TRACE_("���Ǘ��җ�O�̈يE���聄 ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
        _is_sending_flg = false;
        _was_finished_sending_flg = true;
        _pException_god = NEW CriticalException(e.getMsg());
        return 1;
    }
    return 0;
}


