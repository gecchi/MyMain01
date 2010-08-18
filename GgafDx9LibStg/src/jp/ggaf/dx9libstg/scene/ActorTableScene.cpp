#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorTableScene::ActorTableScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "ActorTableScene";
}


GgafGroupActor* ActorTableScene::addToTable(GgafMainActor* prm_pMainActor, frame prm_max_delay_offset) {
    prm_pMainActor->inactivateImmediately();
    _table.addLast(NEW TblElem(prm_pMainActor, prm_max_delay_offset));
    return getLordActor()->addSubGroup(prm_pMainActor);
}

void ActorTableScene::initialize() {
    if (_table.length() > 0) {
        //OK
        TblElem* e = _table.get();
        e->_pActor->activateAfter(e->_max_delay_offset); //�ŏ��̃A�N�^�[���A�N�e�B�u
        _prev_active_frame = getActivePartFrame()+e->_max_delay_offset;
    } else {
        throwGgafCriticalException("ActorTableScene::initialize() ["<<getName()<<"] �e�[�u���ɃA�N�^�[������܂���");
    }
}


void ActorTableScene::processBehavior() {
    if (wasDeclaredEnd()) {
        //�I����҂̂�
    } else {
        TblElem* e = _table.get();
        GgafMainActor* pActiveActor = e->_pActor;
        if (pActiveActor->_will_inactivate_after_flg ||
            pActiveActor->_is_active_flg_in_next_frame == false ||
            pActiveActor->_will_end_after_flg) {
            //�S�� or �S�̈�O�͎���
            if (_table.isLast()) {
                //TABLE�I��
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() �I���I�I");
                end(60*60);
            } else {
                TblElem* n = _table.next(); //�A�N�e�B�u�����̂�
                n->_pActor->activate();
                _prev_active_frame = getActivePartFrame();
            }
        } else {
            //�S�� or �S�̈�O�ł͖����ꍇ�ł�
            //max_delay_offset�߂���Ύ���

            if (getActivePartFrame() >= e->_max_delay_offset+_prev_active_frame) {

                TblElem* n = _table.next(); //�A�N�e�B�u�����̂�
                n->_pActor->activate();
                _prev_active_frame = getActivePartFrame();
            }

        }
    }
}

ActorTableScene::~ActorTableScene() {
    _TRACE_("ActorTableScene::~ActorTableScene() ["<<getName()<<"] ����I�I�I�I");
}
