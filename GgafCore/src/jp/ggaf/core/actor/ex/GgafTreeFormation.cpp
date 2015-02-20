#include "jp/ggaf/core/actor/ex/GgafTreeFormation.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafTreeFormation::GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafTreeFormation";
    _pIte = nullptr;
    _can_call_up = true;
    _is_addmember_experienced = false;
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
        //�c���Ɏ�ʂ𐳂����`���邽�߂ɁA����ǉ��̎�ʂ��A���g�̎�ʂɏ㏑�iGgafTreeFormation�j������
        actorkind kind = prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND);
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, kind);
        //�����o�[������ GgafTreeFormation ���AaddSubGroup ������� addFormationMember ���s�����ꍇ�A
        //�܂������o�[������ GgafTreeFormation ���AaddSubGroup ��������́A���=0�Ȃ̂ŁA�쐬���ꂽ�c���̎�ʂ�0�ō쐬����Ă��܂��B
        //���̌��addFormationMember���s���Ă��A���0�ɑ����Ă��܂��Ƃ�����肪�L��B
        //�����ŁA���g�iGgafTreeFormation�j�����ɒc���ɑ����Ă���ꍇ�B��ʂ��قȂ�΁A�V���Ȓc���̔z���ɏ����������B
        GgafGroupHead* myGroupHead = getMyGroupHead(); //�c��
        if (myGroupHead) {
            //���ɏ������Ă��܂��Ă���B�i�V�[���ɑ����Ă���j
            if (myGroupHead->_kind != kind) {
                //��ʂ��ς�����̂ŁA���̒c���̔z���ɂ͂��������Ȃ��I
                GgafActor* pGroupHeadParent = myGroupHead->getParent();
                if (pGroupHeadParent->instanceOf(Obj_GgafMainActor)) {
                    this->extract();
                    GgafMainActor* pGroupHeadParentMainActor = (GgafMainActor*)pGroupHeadParent;
                    pGroupHeadParentMainActor->addSubGroup(this);
                    _TRACE_("GgafTreeFormation::addFormationMember "<<getName()<<"("<<this<<") �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�̂ŁA"<<
                            "�c���������ւ��܂����B���c��="<<myGroupHead->getName()<<"("<<myGroupHead<<") �� �V�c��="<<getMyGroupHead()->getName()<<"("<<getMyGroupHead()<<")�B�i���Ȃ݂ɐe��GgafMainActor�ł����B)");
                } else if (pGroupHeadParent->instanceOf(Obj_GgafSceneDirector)) {
                    this->extract();
                    GgafSceneDirector* pMySceneDirector = (GgafSceneDirector*)pGroupHeadParent;
                    pMySceneDirector->addSubGroup(this);
                    _TRACE_("GgafTreeFormation::addFormationMember "<<getName()<<"("<<this<<") �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�̂ŁA"<<
                            "�c���������ւ��܂����B���c��="<<myGroupHead->getName()<<"("<<myGroupHead<<") �� �V�c��="<<getMyGroupHead()->getName()<<"("<<getMyGroupHead()<<")�B�i���Ȃ݂ɐe��GgafSceneDirector�ł����B)");
                } else {
                    throwGgafCriticalException(
                            "GgafTreeFormation::addFormationMember "<<getName()<<"("<<this<<") �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�̂ŁA"<<
                            "�c���̕ύX�����݂܂������A�c���̐e�� GgafMainActor �ł� GgafSceneDirector �ł������̂ŁA���߂܂����B");
                }
            }
        } else {
            //�c�������Ȃ����V�[���ɂ͖������Ȃ̂ŁA
            //�V�[���ɏ������Ɏ��g�̎�ʂŒc�����쐬�����̂ł悵�B
        }
    } else {
#ifdef MY_DEBUG
        if (getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafTreeFormation::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
    GgafFormation::addSubLast(prm_pSub);
    prm_pSub->inactivate(); //�t�H�[���[�V�����Ȃ̂�callUp�܂Ŕ񊈓��B
    _is_addmember_experienced = true;
}

void GgafTreeFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        if (getSubFirst() == nullptr) {  //�z�����Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I�����ȁH
            if (_is_addmember_experienced) {
                onSayonaraAll(); //�R�[���o�b�N
                sayonara(_offset_frames_end);
                _was_all_sayonara = true;
            } else {
                //�����������A�܂�����addFormationMember()���o�����Ă��Ȃ��̂ŏI�����Ȃ��B
                //TreeFormation�Ƃ��Ă̖������ʂ����܂ł͎��˂Ȃ��B
            }
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
                _can_call_up = false;
                return nullptr;
            }
        } else {
            _pIte = getSubFirst(); //����̓T�u�擪
        }
        _pIte->activate();
        if (_pIte->getNext() == getSubFirst()) {
            //�Ō�̂P��
            _can_call_up = false;
        }
        return _pIte;
    } else {
        return nullptr;
    }
}

GgafTreeFormation::~GgafTreeFormation() {

}
