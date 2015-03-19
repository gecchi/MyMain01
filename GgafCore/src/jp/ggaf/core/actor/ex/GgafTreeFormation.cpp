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
    if (wasDeclaredEnd()) {
        //�I����҂̂�
        _TRACE_("���x���� GgafTreeFormation::addSubLast("<<NODE_INFO_P(prm_pSub)<<") ���Ɏ��ɂ䂭��߂�Formation�ł��B�T�u�ɒǉ����邱�Ƃ͂��������̂ł͂Ȃ����H�����̂��H�Bthis="<<NODE_INFO);
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
        //�����ŁA�c���̎��0�������ꍇ�A��ʂ𖳗����X�V����B
        GgafGroupHead* myGroupHead = getMyGroupHead(); //�c��
        if (myGroupHead) {
            //���ɏ������Ă��܂��Ă���B�i�V�[���ɑ����Ă���j
            if (myGroupHead->_kind == kind) {
                //�����A��ʂɐ�����������̂Ŗ��Ȃ��B
            } else {
                //��ʂ��ς���Ă���B���̒c���̎�ʂ𖳗����ύX�ł��邩�H
                if (myGroupHead->_kind == 0) {
                    //���0�������̂Ŗ������c���̎�ʂ����������Ă��܂����B
                    _TRACE_("GgafTreeFormation::addFormationMember "<<NODE_INFO<<" �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�܂��B"<<
                            "�K���ɂ��A�c����ʂ� 0 �������̂ŁA�������X�V���܂����B���c�����="<<myGroupHead->_kind<<" �� �V�c�����="<<kind<<"");
                    myGroupHead->setKind(kind);
                } else {
                    _TRACE_("GgafTreeFormation::addFormationMember "<<NODE_INFO<<" �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�܂��B");
                    _TRACE_("�����ςݒc���z���̏�Ԃ͈ȉ��ł�");
                    myGroupHead->dump();
                    throwGgafCriticalException(
                            "GgafTreeFormation::addFormationMember "<<NODE_INFO<<" �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�܂��B");
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
    if (_was_all_sayonara || wasDeclaredEnd() || willInactivateAfter()) {
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
    if (wasDeclaredEnd() || willInactivateAfter()) {
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
