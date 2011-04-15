#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorTableScene::ActorTableScene(const char* prm_name) : GgafDx9Scene(prm_name) {
    _class_name = "ActorTableScene";
    _max_perform_frame = 0xffffffff;
}


GgafGroupActor* ActorTableScene::addToTable(GgafDx9FormationActor* prm_pFormationActor, frame prm_max_delay_offset) {
    if (prm_pFormationActor->_obj_class | Obj_GgafDx9FormationActor) {
        //OK
    } else {
        throwGgafCriticalException("ActorTableScene::processBehavior() GgafDx9FormationActor �ȊO���o�^����Ă��܂��B")
    }
    prm_pFormationActor->_frame_offset_end = FORMATION_END_DELAY;
    prm_pFormationActor->inactivateImmediately();
    _table.addLast(NEW TblElem(prm_pFormationActor, prm_max_delay_offset), true);

    return getLordActor()->addSubGroup(prm_pFormationActor);
}

void ActorTableScene::onActive() {
    if (_table.length() > 0) {
        _frame_of_current_part_began = getActivePartFrame();
        _table.first();
        _table.getCurrent()->_pFormationActor->activate();
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
            end(FORMATION_END_DELAY);
            return;
        }

        TblElem* e = _table.getCurrent();
        GgafDx9FormationActor* pF = e->_pFormationActor;
        //�S�Ŕ���
        bool was_destroyed = false;

        if (pF->_num_sub == 0) { //�ґ��j��ɂ��S��(��ʊO�ɓ������ꍇ��0�ɂ͂Ȃ�Ȃ�)
            was_destroyed = true;
        } else {
            was_destroyed = false;
        }

        if (was_destroyed) {
            //�S�ł̏ꍇ
            if (_table.isLast()) {
                //�ŏI�p�[�g��������TABLE�I��
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() �S�p�[�g�I���I�I");
                end(FORMATION_END_DELAY);
            } else {
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] pActiveActor="<<pActiveActor->getName()<<" ���łɂ�葁�񂵂����[�I�I");
                //�ŏI�p�[�g�ł͂Ȃ��ꍇ�A�e�[�u���S�̂̋��e�t���[�������f
                if (_max_perform_frame <  getActivePartFrame()) {
                    //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė�������ăV�[���I��
                    _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() ���܂�Ȃ������I���P�I�I");
                    end(FORMATION_END_DELAY); //0.5����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
                    //����end() �ɂ��A�{�����擪�� wasDeclaredEnd() ���^�ƂȂ�
                } else {
                    //�]�T�����邽�ߎ��̃p�[�g���A�N�e�B�u�ɂ���B
                    TblElem* n = _table.next(); //�A�N�e�B�u�����̃p�[�g��
                    n->_pFormationActor->activate();     //�G�A�N�e�B�u
                    _frame_of_current_part_began = getActivePartFrame();
                }
            }
        } else {
            //�S�łł͖����ꍇ
            if (_table.isLast()) {
                //�ŏI�p�[�g�͎����Ȃ��̂łȂɂ����Ȃ�
                end(FORMATION_END_DELAY); //0.5����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
                //����end() �ɂ��A�{�����擪�� wasDeclaredEnd() ���^�ƂȂ�
            } else {
                //max_delay_offset�߂���Ύ���
                if (getActivePartFrame() >= e->_max_delay_offset+_frame_of_current_part_began) {
                    if (_max_perform_frame <  getActivePartFrame()) {
                        //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė������ꋤ���I��
                        _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() ���܂�Ȃ������I���Q�I�I");
                        end(FORMATION_END_DELAY); //0.5����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
                        //����end() �ɂ��A�{�����擪�� wasDeclaredEnd() ���^�ƂȂ�
                    } else {
                        TblElem* n = _table.next(); //�A�N�e�B�u�����̃p�[�g��
                        n->_pFormationActor->activate();
                        _frame_of_current_part_began = getActivePartFrame();
                    }

                }
            }
        }
    }
}

ActorTableScene::~ActorTableScene() {
}
