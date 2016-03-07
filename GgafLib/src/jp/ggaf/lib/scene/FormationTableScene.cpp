#include "jp/ggaf/lib/scene/FormationTableScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/actor/ex/GgafFormation.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FormationTableScene::FormationTableScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "FormationTableScene";
    _max_perform_frame = 0xffffffff;
    _frame_of_current_part_began = 0;
}


GgafGroupHead* FormationTableScene::addToTable(GgafFormation* prm_pFormationActor, frame prm_max_delay_offset) {
    if (prm_pFormationActor->instanceOf(Obj_GgafFormation)) {
        //OK
    } else {
        throwGgafCriticalException("GgafFormation �ȊO���o�^����Ă��܂��B");
    }
    prm_pFormationActor->_offset_frames_end = FORMATION_END_DELAY;
    prm_pFormationActor->inactivate();
    _table.addLast(NEW TblElem(prm_pFormationActor, prm_max_delay_offset), true);

    return bringDirector()->addSubGroup(prm_pFormationActor);
}

void FormationTableScene::onActive() {
    if (_table.length() > 0) {
        _frame_of_current_part_began = getActiveFrame();
        _table.first();
        _table.getCurrent()->_pFormationActor->activate();
        //OK
        //_frame_of_current_part_began = getActiveFrame(); todo:��΂ɂO�ɂȂ邵�B���΃t���[���ł��������E�E�E
        _TRACE_(FUNC_NAME<<" ["<<getName()<<"] ���܂����B");
    } else {
        throwGgafCriticalException("["<<getName()<<"] �e�[�u���ɃA�N�^�[����������܂���");
    }
}


void FormationTableScene::processBehavior() {

    if (wasDeclaredEnd()) {
        //�I����҂̂�
    } else {

        if (!bringDirector()->getSubFirst()) {
            sayonara(FORMATION_END_DELAY);
            return;
        }

        TblElem* e = _table.getCurrent();
        GgafFormation* pF = e->_pFormationActor;
        //�S�Ŕ���
        if (pF->_was_all_destroyed) {
            //�S�ł̏ꍇ
            if (_table.isLast()) {
                //�ŏI�p�[�g��������TABLE�I��
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] end() �S�p�[�g�I���I�I");
                sayonara(FORMATION_END_DELAY);
            } else {
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] pActiveActor="<<pF->getName()<<" ���łɂ�葁�񂵂����[�I�I");
                //�ŏI�p�[�g�ł͂Ȃ��ꍇ�A�e�[�u���S�̂̋��e�t���[�������f
                if (_max_perform_frame <  getActiveFrame()) {
                    //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė�������ăV�[���I��
                    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] end() ���܂�Ȃ������I���P�I�I");
                    sayonara(FORMATION_END_DELAY); //0.5����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
                    //����sayonara() �ɂ��A�{�����擪�� wasDeclaredEnd() ���^�ƂȂ�
                } else {
                    //�]�T�����邽�ߎ��̃p�[�g���A�N�e�B�u�ɂ���B
                    TblElem* n = _table.next(); //�A�N�e�B�u�����̃p�[�g��
                    n->_pFormationActor->activate();     //�G�A�N�e�B�u
                    _frame_of_current_part_began = getActiveFrame();
                }
            }
        } else {
            //�S�łł͖����ꍇ
            if (_table.isLast()) {
                //�ŏI�p�[�g�͎����Ȃ��̂łȂɂ����Ȃ�
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] end() �S�łł͖������A�ŏI�p�[�g�Ŏ��������̂łȂɂ����Ȃ�");
                sayonara(FORMATION_END_DELAY); //0.5����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
                //����sayonara() �ɂ��A�{�����擪�� wasDeclaredEnd() ���^�ƂȂ�
            } else {
                //max_delay_offset�߂���Ύ���
                if (getActiveFrame() >= e->_max_delay_offset+_frame_of_current_part_began) {
                    if (_max_perform_frame <  getActiveFrame()) {
                        //���܂�Ȃ��ƌ����킯�ŁA�ȍ~�͑S�Ė������ꋤ���I��
                        _TRACE_(FUNC_NAME<<" ["<<getName()<<"] end() ���܂�Ȃ������I���Q�I�I");
                        sayonara(FORMATION_END_DELAY); //0.5����j��(�O�p�[�g���c�����Ă��邩���m��Ȃ����ߗ]�T����������)
                        //����sayonara() �ɂ��A�{�����擪�� wasDeclaredEnd() ���^�ƂȂ�
                    } else {
                        TblElem* n = _table.next(); //�A�N�e�B�u�����̃p�[�g��
                        n->_pFormationActor->activate();
                        _frame_of_current_part_began = getActiveFrame();
                    }

                }
            }
        }
    }
}

FormationTableScene::~FormationTableScene() {
}
