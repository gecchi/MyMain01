#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException* GgafGod::_pException_Factory = NULL;
CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;
int GgafGod::_num_actor_playing = 0;
GgafGod* GgafGod::_pGod = NULL;
DWORD GgafGod::_aTime_OffsetOfNextFrame[] = {17, 17, 16, 17, 17, 16, 17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17,
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
    _expected_time_of_next_frame = (DWORD)(_time_at_beginning_frame + 1000);
    _time_prev = _time_at_beginning_frame;
    _frame_of_visualize = 0;
    _frame_of_prev_visualize = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GgafFactory::_pGarbageBox = NEW GgafGarbageBox();

}

void GgafGod::be() {
    if (_pUniverse == NULL) {
        _pUniverse = createUniverse();
        if (_pUniverse == NULL) {
            throwGgafCriticalException("GgafGod::be() Error! ���̐����������ĉ������I");
        }
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
        makeUniversalMoment();
        makeUniversalJudge();
     ___EndSynchronized; // <----- �r���I��
        //�`��^�C�~���O�t���[�����Z
        //_expected_time_of_next_frame += _aTime_OffsetOfNextFrame[_godframe % 60]; //�\��͕ς��Ȃ�
        if (_num_actor_playing > 800) {
            _expected_time_of_next_frame += (_aTime_OffsetOfNextFrame[_godframe % 60] * 3);
        } else if (_num_actor_playing > 700) {
            _expected_time_of_next_frame += (_aTime_OffsetOfNextFrame[_godframe % 60] * 2);
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
        _fps = (float)(_frame_of_visualize - _frame_of_prev_visualize) / (float)((_time_at_beginning_frame - _time_prev) / 1000.0);
        _TRACE_(_godframe<<"Frame "<<_num_actor_playing<<"Actor "<<_fps<<"Fps");
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
                    makeUniversalVisualize();
                    makeUniversalFinalize();
                } else {
                    makeUniversalMaterialize();
                    makeUniversalVisualize();
                    makeUniversalFinalize();
                }
                //getUniverse()->cleane(10);
             ___EndSynchronized; // <----- �r���I��
            } else {
                //�X�L�b�v����makeUniversalFinalize()����
             ___BeginSynchronized; // ----->�r���J�n
                makeUniversalFinalize();
             ___EndSynchronized; // <----- �r���I��
            }
        } else {
            //�ʏ펞�`��i�X�L�b�v�Ȃ��j
            _frame_of_visualize++;
         ___BeginSynchronized; // ----->�r���J�n
            if (_is_materialized_flg) {
                makeUniversalVisualize();
                makeUniversalFinalize();
            } else {
                makeUniversalMaterialize();
                makeUniversalVisualize();
                makeUniversalFinalize();

            }
         ___EndSynchronized; // <----- �r���I��
        }
        _is_behaved_flg = false;
        _is_materialized_flg = false;
    } else {//�`��^�C�~���O�t���[���ɂȂ��ĂȂ�(�]�T������)
        Sleep(1); //�H��i�ʃX���b�h�j�ɉ�
    }

    return;
}

void GgafGod::makeUniversalMoment() {
    _pUniverse->nextFrame();
    _pUniverse->behave();
}

void GgafGod::makeUniversalJudge() {
    _pUniverse->judge();
}

void GgafGod::makeUniversalMaterialize() {
    _num_actor_playing = 0;
    _pUniverse->preDraw();
    _pUniverse->draw();
    _pUniverse->afterDraw();
}

void GgafGod::makeUniversalVisualize() {
    _pUniverse->dump();
}

void GgafGod::makeUniversalFinalize() {
    _pUniverse->finally();
}

GgafGod::~GgafGod() {
    TRACE("GgafGod::~GgafGod start");
    if (_pUniverse != NULL) {
        //�H����~�߂�
        Sleep(20);
        GgafFactory::_is_working_flg = false;
        while (GgafFactory::_was_finished_flg == false) {
            Sleep(10); //�H�ꂪ���������܂ő҂�
        }

        //�H��|��
     ___BeginSynchronized; // ----->�r���J�n
        GgafFactory::clean();
        //�S�~��
        GgafFactory::_pGarbageBox->_pGarbageRootScene->dump();
        GgafFactory::_pGarbageBox->_pGarbageRootActor->dump();
        DELETE_IMPOSSIBLE_NULL(GgafFactory::_pGarbageBox);
     ___EndSynchronized; // <----- �r���I��

        //���̐��Ő����Ă��镨���|��
        Sleep(20);
     ___BeginSynchronized; // ----->�r���J�n
        DELETE_IMPOSSIBLE_NULL(_pUniverse);
     ___EndSynchronized; // <----- �r���I��
    }

    //�r���̉���
    CloseHandle(_handleFactory01);
    DeleteCriticalSection(&(GgafGod::CS2));
    DeleteCriticalSection(&(GgafGod::CS1));

    DELETE_POSSIBLE_NULL(_pException_Factory);TRACE("GgafGod::~GgafGod end");
}
