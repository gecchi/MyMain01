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

void ActorTableScene::onActive() {
    if (_table.length() > 0) {
        _frame_of_current_part_began = getActivePartFrame();
        _table.first();
        _table.get()->_pActor->activate();
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
                _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] pActiveActor="<<pActiveActor->getName()<<" ���łɂ�葁�񂵂����[�I�I");
                //�ŏI�p�[�g�ł͂Ȃ��ꍇ�A�e�[�u���S�̂̋��e�t���[�������f
                if (_max_perform_frame <  getActivePartFrame()) {
                    //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė�������ăV�[���I��
                    _TRACE_("ActorTableScene::processBehavior() ["<<getName()<<"] end() ���܂�Ȃ������I���P�I�I");
                    end(60*60); //1����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
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
                        end(60*60); //1����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
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
    _TRACE_("ActorTableScene::~ActorTableScene() ["<<getName()<<"] ����I�I�I�I");
}
