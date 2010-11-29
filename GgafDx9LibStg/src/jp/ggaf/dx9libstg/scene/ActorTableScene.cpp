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
    if (prm_pMainActor->_obj_class | Obj_GgafDx9FormationActor) {
        //OK
    } else if (prm_pMainActor->_obj_class | Obj_GgafDx9DrawableActor) {
        //OK
    } else {
        _TRACE_("ActorTableScene::processBehavior() GgafDx9FormationActor,Obj_GgafDx9DrawableActor �ȊO���o�^����Ă��܂��B")
    }
    prm_pMainActor->inactivateImmediately();
    _table.addLast(NEW TblElem(prm_pMainActor, prm_max_delay_offset), true);
    return getLordActor()->addSubGroup(prm_pMainActor);
}

void ActorTableScene::onActive() {
    if (_table.length() > 0) {
        _frame_of_current_part_began = getActivePartFrame();
        _table.first();
        _table.getCurrent()->_pActor->activate();
        //OK
        //_frame_of_current_part_began = getActivePartFrame(); todo:��΂ɂO�ɂȂ邵�B���΃t���[���ł��������E�E�E
        _TRACE_("ActorTableScene::onActive() ["<<getName()<<"] ���܂����B");
    } else {
        throwGgafCriticalException("ActorTableScene::onActive() ["<<getName()<<"] �e�[�u���ɃA�N�^�[����������܂���");
    }
}


void ActorTableScene::processBehavior() {

    if (wasDeclaredEnd()) {
        //�I����҂̂�
    } else {

        if (!getLordActor()->getSubFirst()) {
            end(30*60);
            return;
        }

        TblElem* e = _table.getCurrent();
        GgafMainActor* pActiveActor = e->_pActor;
        //�S�Ŕ���
        bool was_destroyed = false;
        if (pActiveActor->_obj_class | Obj_GgafDx9FormationActor) {
            GgafDx9FormationActor* pF = (GgafDx9FormationActor*)pActiveActor;
            if (pF->_num_sub == 0) {
                was_destroyed = true;
            } else {
                was_destroyed = false;
            }
        } else if (pActiveActor->_obj_class | Obj_GgafDx9DrawableActor) {
            if (pActiveActor->isDisappear()) {
                was_destroyed = true;
            } else {
                was_destroyed = false;
            }
        } else {
            was_destroyed = false;
        }

        if (was_destroyed) {
            //�S�� or �S�̈�O�͎���
            if (_table.isLast()) {
                //�ŏI�p�[�g��������TABLE�I��
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() �S�p�[�g�I���I�I");
                end(30*60);
            } else {
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] pActiveActor="<<pActiveActor->getName()<<" ���łɂ�葁�񂵂����[�I�I");
                //�ŏI�p�[�g�ł͂Ȃ��ꍇ�A�e�[�u���S�̂̋��e�t���[�������f
                if (_max_perform_frame <  getActivePartFrame()) {
                    //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė�������ăV�[���I��
                    _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() ���܂�Ȃ������I���P�I�I");
                    end(30*60); //0.5����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
                } else {
                    //�]�T�����邽�ߎ��̃p�[�g���A�N�e�B�u�ɂ���B
                    TblElem* n = _table.next(); //�A�N�e�B�u�����̃p�[�g��
                    n->_pActor->activate();     //�G�A�N�e�B�u
                    _frame_of_current_part_began = getActivePartFrame();
                }
            }
        } else {
            //�S�� or �S�̈�O�ł͖����ꍇ
            if (_table.isLast()) {
                //�ŏI�p�[�g�͎����Ȃ��̂łȂɂ����Ȃ�
                //��̑S�� or �S�̈�O����Ɉ���������܂ő҂�
            } else {
                //max_delay_offset�߂���Ύ���
                if (getActivePartFrame() >= e->_max_delay_offset+_frame_of_current_part_began) {
                    if (_max_perform_frame <  getActivePartFrame()) {
                        //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė������ꋤ���I��
                        _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() ���܂�Ȃ������I���Q�I�I");
                        end(30*60); //0.5����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
                    } else {
                        TblElem* n = _table.next(); //�A�N�e�B�u�����̃p�[�g��
                        n->_pActor->activate();
                        _frame_of_current_part_began = getActivePartFrame();
                    }

                }
            }
        }
    }
}

ActorTableScene::~ActorTableScene() {
}
