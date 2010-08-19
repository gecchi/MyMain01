#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorTableScene::ActorTableScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "ActorTableScene";
    _max_perform_frame = 0xffffffff;
}


GgafGroupActor* ActorTableScene::addToTable(GgafMainActor* prm_pMainActor, frame prm_max_delay_offset) {
    prm_pMainActor->inactivateImmediately();
    _table.addLast(NEW TblElem(prm_pMainActor, prm_max_delay_offset));
    return getLordActor()->addSubGroup(prm_pMainActor);
}

void ActorTableScene::initialize() {
}

void ActorTableScene::onActive() {
    if (_table.length() > 0) {
        //OK
        _frame_of_current_part_began = getActivePartFrame(); todo:��΂ɂO�ɂȂ邵�B���΃t���[���ł��������E�E�E
        _TRACE_("ActorTableScene::onActive() ["<<getName()<<"] ���܂����B_frame_of_current_part_began="<<_frame_of_current_part_began);
    } else {
        throwGgafCriticalException("ActorTableScene::onActive() ["<<getName()<<"] �e�[�u���ɃA�N�^�[����������܂���");
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
                //�ŏI�p�[�g��������TABLE�I��
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() �S�p�[�g�I���I�I");
                end(60*60);
            } else {
                TblElem* n = _table.next(); //�A�N�e�B�u�����̃p�[�g��
                if (_max_perform_frame <  getActivePartFrame() + n->_max_delay_offset) {
                    //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė������ꋤ���I��
                    _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() ���܂�Ȃ������I���P�I�I");
                    end(60*60);
                } else {
                    //�]�T�����邽�ߎ��̃p�[�g���A�N�e�B�u�ɂ���B
                    n->_pActor->activate();
                    _frame_of_current_part_began = getActivePartFrame();
                }
            }
        } else {
            //�S�� or �S�̈�O�ł͖����ꍇ�ł�
            //max_delay_offset�߂���Ύ���
            if (_table.isLast()) {
                //�ŏI�p�[�g�͎����Ȃ��̂łȂɂ����Ȃ�
                //�S�� or �S�̈�O�܂ő҂�
            } else {
                if (getActivePartFrame() >= e->_max_delay_offset+_frame_of_current_part_began) {
                    TblElem* n = _table.next(); //�A�N�e�B�u�����̃p�[�g��
                    if (_max_perform_frame <  getActivePartFrame() + n->_max_delay_offset) {
                        //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė������ꋤ���I��
                        _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() ���܂�Ȃ������I���Q�I�I");
                        end(60*60);
                    } else {
                        n->_pActor->activate();
                        _frame_of_current_part_began = getActivePartFrame();
                    }

                }
            }

        }
    }
}

ActorTableScene::~ActorTableScene() {
    _TRACE_("ActorTableScene::~ActorTableScene() ["<<getName()<<"] ����I�I�I�I");
}
