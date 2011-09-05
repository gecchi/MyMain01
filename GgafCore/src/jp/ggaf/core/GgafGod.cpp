#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException* GgafGod::_pException_Factory = NULL;
CRITICAL_SECTION GgafGod::CS1;
int GgafGod::ppp = 0;

int GgafGod::_num_actor_drawing = 0;
GgafGod* GgafGod::_pGod = NULL;
DWORD GgafGod::_aaTime_OffsetOfNextFrame[3][60] = {
        {17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16},
        {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25},
        {33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34}
};
volatile bool GgafGod::_can_be = false;

GgafGod::GgafGod() : GgafObject(),
  _pUniverse(NULL),
  _fps(0) {
    TRACE("GgafGod::GgafGod");
    _frame_of_God = 0;

    _handleFactory01 = (HANDLE)::_beginthreadex(NULL, 0, GgafFactory::work, NULL, CREATE_SUSPENDED, &_thID01);

    if (_handleFactory01 == 0) {
        throwGgafCriticalException("GgafGod::GgafGod() Error! �X���b�h�쐬���s�I");
    }
    ::InitializeCriticalSection(&(GgafGod::CS1));
    ::ResumeThread(_handleFactory01);
    ::SetThreadPriority(_handleFactory01, THREAD_PRIORITY_IDLE);
    GgafGod::_pGod = this;
    _time_at_beginning_frame = timeGetTime();
    _expected_time_of_next_frame = (frame)(_time_at_beginning_frame + 3000); //3�b��
    _time_prev = _time_at_beginning_frame;
    _frame_of_visualize = 0;
    _frame_of_prev_visualize = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GgafFactory::_pGarbageBox = NEW GgafGarbageBox();
    _is_being = false;
//    _can_be = true;
    _was_cleaned = false;
    _skip_count_of_frame = 0;
    _max_skip_frames = (int)CFG_PROPERTY(MAX_SKIP_FRAME);
    _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    _sync_frame_time = false;

    _can_be = true;
}

void GgafGod::be() {
    if (_can_be) {
        _is_being = true;
        if (_pUniverse == NULL) {
            _pUniverse = createUniverse();
#ifdef MY_DEBUG
            if (_pUniverse == NULL) {
                throwGgafCriticalException("GgafGod::be() Error! ���̐����������ĉ������I");
            }
#endif
            _pUniverse->_pGod = this;
        }
#ifdef MY_DEBUG
        //�H��i�ʃX���b�h�j��O���`�F�b�N
        if (_pException_Factory) {
            throw *_pException_Factory;
        }
#endif

        if (_is_behaved_flg == false) {
            _is_behaved_flg = true;
        ___BeginSynchronized; // ----->�r���J�n
            _frame_of_God++;
            presentUniversalMoment();
            executeUniversalJudge();
        ___EndSynchronized; // <----- �r���I��
            //�`��^�C�~���O�t���[�����Z
            if (_num_actor_drawing > CFG_PROPERTY(DRAWNUM_TO_SLOWDOWN2)) {
                _slowdown_mode = SLOWDOWN_MODE_30FPS;
            } else if (_num_actor_drawing > CFG_PROPERTY(DRAWNUM_TO_SLOWDOWN1)) {
                _slowdown_mode = SLOWDOWN_MODE_40FPS;
            } else {
                _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
            }
            _expected_time_of_next_frame += _aaTime_OffsetOfNextFrame[_slowdown_mode][_frame_of_God % 60];

            //            //_expected_time_of_next_frame += _aTime_OffsetOfNextFrame[_frame_of_God % 60]; //�\��͕ς��Ȃ�
            //            if (_num_actor_drawing > 500) {
            //                _expected_time_of_next_frame += (DWORD)(_aaTime_OffsetOfNextFrame[0][_frame_of_God % 60] * 2);
            //            } else if (_num_actor_drawing > 400) {
            //                _expected_time_of_next_frame += (DWORD)(_aaTime_OffsetOfNextFrame[0][_frame_of_God % 60] * 1.5);
            //            } else {
            //                _expected_time_of_next_frame += _aaTime_OffsetOfNextFrame[0][_frame_of_God % 60];


            if (_expected_time_of_next_frame <= timeGetTime()) { //�`��^�C�~���O�t���[���ɂȂ����A�����͉߂��Ă���ꍇ
                //makeUniversalMaterialize �̓p�X
            } else {
                //�]�T�L��
                _is_materialized_flg = true;
                makeUniversalMaterialize();
            }
        }

        _time_at_beginning_frame = timeGetTime(); //

        //fps�v�Z
        if (_time_at_beginning_frame - _time_prev >= 1000) {
            _fps = (float)(_frame_of_visualize - _frame_of_prev_visualize) / (float)((_time_at_beginning_frame - _time_prev) / 1000.0f);
            _time_prev = _time_at_beginning_frame;
            _frame_of_prev_visualize = _frame_of_visualize;
        }

        if (_expected_time_of_next_frame <= _time_at_beginning_frame) { //�`��^�C�~���O�t���[���ɂȂ����A�����͉߂��Ă���ꍇ

            if (_time_at_beginning_frame > _expected_time_of_next_frame + _aaTime_OffsetOfNextFrame[_slowdown_mode][_frame_of_God % 60]) {
                //�啝�ɉ߂��Ă�����(���̃t���[���܂ŐH������ł�����)�X�L�b�v
                _skip_count_of_frame++;
                if (_skip_count_of_frame >= _max_skip_frames && _sync_frame_time == false) {
                    //�X�L�b�v����Ƃ����Ă�MAX_SKIP_FRAME�t���[���ɂP��͕`��͂���B
                    _skip_count_of_frame = 0;
                    _frame_of_visualize++;
                 ___BeginSynchronized; // ----->�r���J�n
                    if (_is_materialized_flg) {
                        presentUniversalVisualize();
                        finalizeUniversal();
                    } else {
                        makeUniversalMaterialize();
                        presentUniversalVisualize();
                        finalizeUniversal();
                    }
                 ___EndSynchronized; // <----- �r���I��
                } else {
                    //�X�L�b�v����finalizeUniversal()����
                 ___BeginSynchronized; // ----->�r���J�n
                    finalizeUniversal();
                 ___EndSynchronized; // <----- �r���I��
                }
            } else {
                //�ʏ펞�`��i�X�L�b�v�Ȃ��j
                _sync_frame_time = false;
                _frame_of_visualize++;
             ___BeginSynchronized; // ----->�r���J�n
                if (_is_materialized_flg) {
                    presentUniversalVisualize();
                    finalizeUniversal();
                } else {
                    makeUniversalMaterialize();
                    presentUniversalVisualize();
                    finalizeUniversal();

                }
             ___EndSynchronized; // <----- �r���I��
            }
            _is_behaved_flg = false;
            _is_materialized_flg = false;
        } else {//�`��^�C�~���O�t���[���ɂȂ��ĂȂ�(�]�T������)
            Sleep(2); //�H��i�ʃX���b�h�j�ɉ�
        }
        _is_being = false;
    }
    return;
}

void GgafGod::presentUniversalMoment() {
    _pUniverse->nextFrame();
    _pUniverse->behave();
}

void GgafGod::executeUniversalJudge() {
    _pUniverse->settleBehavior();
    _pUniverse->judge();
}

void GgafGod::makeUniversalMaterialize() {
    _num_actor_drawing = 0;
    _pUniverse->preDraw();
    _pUniverse->draw();
#ifdef MY_DEBUG
    //afterDraw() �̓f�o�b�O���̓����蔻��̈�\���Ɏg�p����Ă���B
    _pUniverse->afterDraw();
#endif
}

void GgafGod::presentUniversalVisualize() {
    _pUniverse->dump();
}

void GgafGod::finalizeUniversal() {
    _pUniverse->doFinally();
}

void GgafGod::clean() {
    if (!_was_cleaned) {
        _TRACE_("GgafGod::clean() start");
        if (_pUniverse) {
            _TRACE_("_pUniverse != NULL");
            //�H����~�߂�
            Sleep(10);
            GgafFactory::_is_working_flg = false;
            _TRACE_("GgafGod::~GgafGod() �H�ꂪ���������܂ő҂E�E�E");
            for (int i = 0; GgafFactory::_was_finished_flg == false; i++) {
                Sleep(60); //�H�ꂪ���������܂ő҂�
                if (i > 3000) {
                    _TRACE_("GgafGod::~GgafGod() �R���ҋ@���܂������A�H�ꂩ�甽��������܂���B����break���܂��B�v����");
                    break;
                }
            }
            _TRACE_("GgafGod::~GgafGod() �H�ꂪ���������܂���");
            //�r���̉����A�X���b�h���I������܂ő҂�
            _TRACE_("GgafGod::~GgafGod()  WaitForSingleObject(_handleFactory01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handleFactory01, 120*1000);  //DeleteCriticalSection���s�����߂ɕK�v
            if (r == WAIT_TIMEOUT) {
                throwGgafCriticalException("GgafGod::~GgafGod() �H�ꂪ�����������ɂ�������炸�A�Q�������Ă��X���b�h���c���Ă��܂��B");
            }
            _TRACE_("GgafGod::~GgafGod()  CloseHandle(_handleFactory01) .....");
            CloseHandle(_handleFactory01);
            _TRACE_("GgafGod::~GgafGod()  DeleteCriticalSection(&(GgafGod::CS1)); .....");
            DeleteCriticalSection(&(GgafGod::CS1));
            _handleFactory01 = NULL;
            _TRACE_("GgafGod::~GgafGod() �����ɍH��X���b�h���I���B�N���e�B�J���Z�N�V��������");

    #ifdef MY_DEBUG
            //�c���[�\���\��
            _TRACE_("Dumping _pUniverse ...");
            _pUniverse->dump();
    #endif

            //�H��|��
            _TRACE_("GgafFactory::clean()");
            GgafFactory::clean();
            //�S�~��
    #ifdef MY_DEBUG
            _TRACE_("Dumping GgafFactory::_pGarbageBox->_pDisusedScene ...");
            GgafFactory::_pGarbageBox->_pDisusedScene->dump();
            _TRACE_("GgafFactory::_pGarbageBox->_pDisusedActor ...");
            GgafFactory::_pGarbageBox->_pDisusedActor->dump();
    #endif
            _TRACE_("DELETE_IMPOSSIBLE_NULL(GgafFactory::_pGarbageBox);");
            DELETE_IMPOSSIBLE_NULL(GgafFactory::_pGarbageBox);
            //���̐��Ő����Ă��镨���|��
            Sleep(20);
            _TRACE_("DELETE_IMPOSSIBLE_NULL(_pUniverse);");
            DELETE_IMPOSSIBLE_NULL(_pUniverse);
        }

        //�H���O _pException_Factory ���N�����Ă��邩������Ȃ��B
        _TRACE_("DELETE_POSSIBLE_NULL(_pException_Factory);");
        DELETE_POSSIBLE_NULL(_pException_Factory);
        _TRACE_("GgafGod::clean() end");
    }
}


GgafGod::~GgafGod() {
    clean();
    _was_cleaned = true;
}
