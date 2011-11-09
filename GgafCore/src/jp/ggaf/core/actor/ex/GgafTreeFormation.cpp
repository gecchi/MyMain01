#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafTreeFormation::GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafTreeFormation";
}

void GgafTreeFormation::addSubLast(GgafActor* prm_pSub) {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        throwGgafCriticalException("GgafTreeFormation::addSubLast("<<prm_pSub->getName()<<") ���Ɏ��ɂ䂭��߂�Formation�ł��B�T�u�ɒǉ����邱�Ƃ͂��������ł��傤�Bthis="<<getName());
    }
    _num_sub++;
    if (_pSubFirst == NULL) {
        //�c���Ɏ�ʂ𐳂����`���邽�߂Ɏ�ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafTreeFormation::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    prm_pSub->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
//        _listFllower.addLast((GgafActor*)prm_pSub, false); //�t�H�[���[�V���������o�[�Ƃ��ē����ێ�
    GgafFormation::addSubLast(prm_pSub);
}


void GgafTreeFormation::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        if (getSubFirst() == NULL) {          //�z�����Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I��
            sayonara(_offset_frames_end);
        }
    }

}
void GgafTreeFormation::onGarbaged() {
    GgafFormation::onGarbaged();
}


GgafTreeFormation::~GgafTreeFormation() {

}