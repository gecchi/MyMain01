#include "stdafx.h"
using namespace GgafCore;

GgafTreeFormation::GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafTreeFormation";
    _pIte = nullptr;
    _can_call_up = true;
}

void GgafTreeFormation::addFormationMember(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        throwGgafCriticalException("GgafTreeFormation::addSubLast("<<prm_pSub->getName()<<") ���Ɏ��ɂ䂭��߂�Formation�ł��B�T�u�ɒǉ����邱�Ƃ͂��������ł��傤�Bthis="<<getName());
    }
#endif
    _num_formation_member++;
    if (_pSubFirst == nullptr) {
        //�c���Ɏ�ʂ𐳂����`���邽�߂Ɏ�ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafTreeFormation::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
//        _listFllower.addLast((GgafActor*)prm_pSub, false); //�t�H�[���[�V���������o�[�Ƃ��ē����ێ�
    GgafFormation::addSubLast(prm_pSub);
    prm_pSub->inactivateImmed(); //�t�H�[���[�V�����Ȃ̂�
}

void GgafTreeFormation::processFinal() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        if (getSubFirst() == nullptr) {  //�z�����Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I��
            sayonara(_offset_frames_end);
        }
    }

}
void GgafTreeFormation::onEnd() {
    GgafFormation::onEnd();
}

GgafActor* GgafTreeFormation::callUpMember() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return nullptr;
    }

    if (_can_call_up) {
        if (_pIte) {
            _pIte = _pIte->getNext();
            if (_pIte == getSubFirst()) { //�P������
                _can_call_up = nullptr;
                return nullptr;
            }
        } else {
            _pIte = getSubFirst(); //����̓T�u�擪
        }
        _pIte->activate();
        return _pIte;
    } else {
        return nullptr;
    }
}

GgafTreeFormation::~GgafTreeFormation() {

}
