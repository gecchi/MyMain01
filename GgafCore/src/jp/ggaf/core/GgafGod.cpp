#include "jp/ggaf/core/GgafGod.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/GgafGarbageBox.h"
#include "jp/ggaf/core/GgafProperties.h"
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
    _handleFactory01 = (HANDLE)_beginthreadex(nullptr, 0, GgafCore::GgafFactory::work, nullptr, CREATE_SUSPENDED, &_thID01);

    if (_handleFactory01 == 0) {
        throwGgafCriticalException("Error! �X���b�h�쐬���s�I");
    }
    ::InitializeCriticalSection(&(GgafGod::CS1));
    ::InitializeCriticalSection(&(GgafGod::CS2));
    ::ResumeThread(_handleFactory01);
    ::SetThreadPriority(_handleFactory01, THREAD_PRIORITY_IDLE);
    GgafGod::_pGod = this;
    _time_at_beginning_frame = timeGetTime();
    _time_of_next_view = (frame)(_time_at_beginning_frame);
    _time_calc_fps_next = _time_at_beginning_frame + 1;
    _visualize_frames = 0;
    _prev_visualize_frames = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GgafGarbageBox::_pGarbageBox = NEW GgafGarbageBox();
    _was_cleaned = false;
    _skip_count_of_frame = 0;
    _max_skip_frames = (int)PROPERTY::MAX_SKIP_FRAME;
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
        _time_of_next_view = (frame)(_time_at_beginning_frame+100); //0.1�b��J�n
        _time_calc_fps_next = _time_at_beginning_frame + 1;
    }
#ifdef MY_DEBUG
    //�H��i�ʃX���b�h�j��O���`�F�b�N
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
    _pSpacetime->judge();
}

void GgafGod::makeSpacetimeMaterialize() {
    if (GgafGod::_num_active_actor > PROPERTY::OBJNUM_TO_SLOWDOWN2) {
        _slowdown_mode = SLOWDOWN_MODE_30FPS;
    } else if (GgafGod::_num_active_actor > PROPERTY::OBJNUM_TO_SLOWDOWN1) {
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
            //�H����~�߂�
            Sleep(10);
            GgafFactory::_is_working_flg = false;
            _TRACE_("GgafGod::~GgafGod() �H�ꂪ���������܂ő҂E�E�E");
            for (int i = 0; GgafFactory::_was_finished_flg == false; i++) {
                Sleep(10); //�H�ꂪ���������܂ő҂�
                if (i > 10*100*60) {
                    _TRACE_("GgafGod::~GgafGod() 10���ҋ@���܂������A�H�ꂩ�甽��������܂���B����break���܂��B�v����");
                    break;
                }
            }
            _TRACE_("GgafGod::~GgafGod() �H�ꂪ���������܂���");
            //�r���̉����A�X���b�h���I������܂ő҂�
            _TRACE_("GgafGod::~GgafGod()  WaitForSingleObject(_handleFactory01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handleFactory01, 120*1000);  //DeleteCriticalSection���s�����߂ɕK�v
            if (r == WAIT_TIMEOUT) {
                throwGgafCriticalException("�H�ꂪ�����������ɂ�������炸�A�Q�������Ă��X���b�h���c���Ă��܂��B");
            }
            _TRACE_("GgafGod::~GgafGod()  CloseHandle(_handleFactory01) .....");
            CloseHandle(_handleFactory01);
            _TRACE_("GgafGod::~GgafGod()  DeleteCriticalSection(&(GgafGod::CS1)); .....");
            DeleteCriticalSection(&(GgafGod::CS1));
            _handleFactory01 = nullptr;
            _TRACE_("GgafGod::~GgafGod() �����ɍH��X���b�h���I���B�N���e�B�J���Z�N�V��������");

#ifdef MY_DEBUG
            //�c���[�\���\��
            _TRACE_("Dumping _pSpacetime ...");
            _pSpacetime->dump();
#endif

            //�H��|��
            _TRACE_(FUNC_NAME<<"");
            GgafFactory::clean();
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

        //�H���O _pException_factory ���N�����Ă��邩������Ȃ��B
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
