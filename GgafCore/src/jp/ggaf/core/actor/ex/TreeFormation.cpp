#include "jp/ggaf/core/actor/ex/TreeFormation.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

TreeFormation::TreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        Formation(prm_name, prm_offset_frames_end)
{
    _class_name = "TreeFormation";
    _pIte = nullptr;
    _can_call_up = true;
    _is_append_member_experienced = false;
}

void TreeFormation::appendFormationMember(Actor* prm_pChild) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd()) {
        //�I����҂̂�
        _TRACE_("���x���� TreeFormation::appendChild("<<NODE_INFO_P(prm_pChild)<<") ���Ɏ��ɂ䂭��߂�Formation�ł��B�q�ɒǉ����邱�Ƃ͂��������̂ł͂Ȃ����H�����̂��H�Bthis="<<NODE_INFO);
    }
#endif
    _num_formation_member++;
    if (_pChildFirst == nullptr) {
        //�c���Ɏ�ʂ𐳂����`���邽�߂ɁA����ǉ��̎�ʂ��A���g�̎�ʂɏ㏑�iTreeFormation�j������
        kind_t kind = prm_pChild->getDefaultKind();
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, kind);
        //�����o�[������ TreeFormation ���AappendGroupChild ������� appendFormationMember ���s�����ꍇ�A
        //�܂������o�[������ TreeFormation ���AappendGroupChild ��������́A���=0�Ȃ̂ŁA�쐬���ꂽ�c���̎�ʂ�0�ō쐬����Ă��܂��B
        //���̌��appendFormationMember���s���Ă��A���0�ɑ����Ă��܂��Ƃ�����肪�L��B
        //�����ŁA�c���̎��0�������ꍇ�A��ʂ𖳗����X�V����B
        GroupHead* myGroupHead = getGroupHead(); //�c��
        if (myGroupHead) {
            //���ɏ������Ă��܂��Ă���B�i�V�[���ɑ����Ă���j
            if (myGroupHead->_kind == kind) {
                //�����A��ʂɐ�����������̂Ŗ��Ȃ��B
            } else {
                //��ʂ��ς���Ă���B���̒c���̎�ʂ𖳗����ύX�ł��邩�H
                if (myGroupHead->_kind == 0) {
                    //���0�������̂Ŗ������c���̎�ʂ����������Ă��܂����B
                    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<" �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�܂��B\n"
                            "�K���ɂ��A�c����ʂ� 0 �������̂ŁA�������X�V���܂����B���c�����="<<myGroupHead->_kind<<" �� �V�c�����="<<kind<<"");
                    myGroupHead->setKind(kind);
                } else {
                    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<" �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�܂��B");
                    _TRACE_("�����ςݒc���z���̏�Ԃ͈ȉ��ł�");
                    myGroupHead->dump();
                    throwCriticalException(NODE_INFO<<" �́A�����ςݒc���̎��(�����g�̎��)"<<myGroupHead->_kind<<"�ƁA�ǉ������o�[�̎��"<<kind<<"���قȂ�܂��B");
                }
            }
        } else {
            //�c�������Ȃ����V�[���ɂ͖������Ȃ̂ŁA
            //�V�[���ɏ������Ɏ��g�̎�ʂŒc�����쐬�����̂ł悵�B
        }
    } else {
#ifdef MY_DEBUG
        if (getDefaultKind() != prm_pChild->getDefaultKind()) {
            throwCriticalException("�قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"
                                       "�z��="<<getDefaultKind()<<"[_pChildFirst="<<_pChildFirst->getName()<<"] \n"
                                       "����="<<prm_pChild->getDefaultKind()<<"["<<prm_pChild->getName()<<"]");
        }
#endif
    }
    prm_pChild->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
    Formation::appendChild(prm_pChild);
    prm_pChild->inactivate(); //�t�H�[���[�V�����Ȃ̂�callUp�܂Ŕ񊈓��B
    _is_append_member_experienced = true;
}

void TreeFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || willInactivateAfter()) {
        //�I����҂̂�
    } else {
        if (getChildFirst() == nullptr) {  //�z�����Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I�����ȁH
            if (_is_append_member_experienced) {
                onSayonaraAll(); //�R�[���o�b�N
                sayonara(_offset_frames_end);
                _was_all_sayonara = true;
            } else {
                //�����������A�܂�����appendFormationMember()���o�����Ă��Ȃ��̂ŏI�����Ȃ��B
                //TreeFormation�Ƃ��Ă̖������ʂ����܂ł͎��˂Ȃ��B
            }
        }
    }
}

void TreeFormation::onEnd() {
    Formation::onEnd();
}

Actor* TreeFormation::callUpMember() {
    if (wasDeclaredEnd() || willInactivateAfter()) {
        //�I����҂̂�
        return nullptr;
    }
    if (_can_call_up) {
        if (_pIte) {
            _pIte = _pIte->getNext();
            if (_pIte == getChildFirst()) { //�P������
                _can_call_up = false;
                return nullptr;
            }
        } else {
            _pIte = getChildFirst(); //����͎q�擪
        }
        _pIte->activate();
        if (_pIte->getNext() == getChildFirst()) {
            //�Ō�̂P��
            _can_call_up = false;
        }
        return _pIte;
    } else {
        return nullptr;
    }
}

TreeFormation::~TreeFormation() {

}