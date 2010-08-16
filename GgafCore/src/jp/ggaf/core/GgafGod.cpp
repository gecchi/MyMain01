#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException* GgafGod::_pException_Factory = NULL;
CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;
int GgafGod::_num_actor_drawing = 0;
GgafGod* GgafGod::_pGod = NULL;
UINT32 GgafGod::_aTime_OffsetOfNextFrame[] = {17, 17, 16, 17, 17, 16, 17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17,
                                             17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 16,
                                             17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17,
                                             17, 17, 16, 17, 17, 17};
GgafGod::GgafGod() : GgafObject(),
  _pUniverse(NULL),
  _fps(0) {
    TRACE("GgafGod::GgafGod");
    _godframe = 0;

    _handleFactory01 = (HANDLE)::_beginthreadex(NULL, 0, GgafFactory::work, NULL, CREATE_SUSPENDED, &_thID01);

    if (_handleFactory01 == 0) {
        throwGgafCriticalException("GgafGod::GgafGod() Error! �X���b�h�쐬���s�I");
    }
    ::InitializeCriticalSection(&(GgafGod::CS1));
    ::InitializeCriticalSection(&(GgafGod::CS2));
    ::ResumeThread(_handleFactory01);
    ::SetThreadPriority(_handleFactory01, THREAD_PRIORITY_IDLE);
    GgafGod::_pGod = this;
    _time_at_beginning_frame = timeGetTime();
    _expected_time_of_next_frame = (UINT32)(_time_at_beginning_frame + 3000); //3�b��
    _time_prev = _time_at_beginning_frame;
    _frame_of_visualize = 0;
    _frame_of_prev_visualize = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GgafFactory::_pGarbageBox = NEW GgafGarbageBox();
    _is_being = false;
    _can_be = true;
    _was_cleaned = false;
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

        //�H��i�ʃX���b�h�j��O���`�F�b�N
        if (_pException_Factory != NULL) {
            throw *_pException_Factory;
        }

        if (_is_behaved_flg == false) {
            _is_behaved_flg = true;
         ___BeginSynchronized; // ----->�r���J�n
            _godframe++;
            presentUniversalMoment();
            executeUniversalJudge();
         ___EndSynchronized; // <----- �r���I��
            //�`��^�C�~���O�t���[�����Z
            //_expected_time_of_next_frame += _aTime_OffsetOfNextFrame[_godframe % 60]; //�\��͕ς��Ȃ�
            if (_num_actor_drawing > 500) {
                _expected_time_of_next_frame += (UINT32)(_aTime_OffsetOfNextFrame[_godframe % 60] * 2);
            } else if (_num_actor_drawing > 400) {
                _expected_time_of_next_frame += (UINT32)(_aTime_OffsetOfNextFrame[_godframe % 60] * 1.5);
            } else {
                _expected_time_of_next_frame += _aTime_OffsetOfNextFrame[_godframe % 60];
            }


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
            _TRACE_(_godframe<<"Frame "<<_num_actor_drawing<<"Actor "<<_fps<<"Fps");
            _time_prev = _time_at_beginning_frame;
            _frame_of_prev_visualize = _frame_of_visualize;
        }

        if (_expected_time_of_next_frame <= _time_at_beginning_frame) { //�`��^�C�~���O�t���[���ɂȂ����A�����͉߂��Ă���ꍇ

            if (_time_at_beginning_frame > _expected_time_of_next_frame + _aTime_OffsetOfNextFrame[_godframe % 60]) {
                //�啝�ɉ߂��Ă�����(���̃t���[���܂ŐH������ł�����)�X�L�b�v
                _skip_count_of_frame++;
                if (_skip_count_of_frame >= GGAF_PROPERTY(MAX_SKIP_FRAME)) {
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
    _pUniverse->afterDraw();
}

void GgafGod::presentUniversalVisualize() {
    _pUniverse->dump();
}

void GgafGod::finalizeUniversal() {
    _pUniverse->finally();
}

void GgafGod::clean() {
    if (!_was_cleaned) {
        _TRACE_("GgafGod::clean() start");
        if (_pUniverse != NULL) {
            _TRACE_("_pUniverse != NULL");
            //�H����~�߂�
            Sleep(10);
            GgafFactory::_is_working_flg = false;
            for (int i = 0; GgafFactory::_was_finished_flg == false; i++) {
                Sleep(60); //�H�ꂪ���������܂ő҂�
                if (i > 2000) {
                    _TRACE_("GgafGod::~GgafGod() �Q���ҋ@���܂������A�H�ꂩ�甽��������܂���Bbreak���܂��B�v����");
                }
            }
            //�r���̉���
            CloseHandle(_handleFactory01);
            DeleteCriticalSection(&(GgafGod::CS2));
            DeleteCriticalSection(&(GgafGod::CS1));

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
