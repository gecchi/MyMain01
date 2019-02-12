#include "jp/ggaf/core/actor/GroupHead.h"

#include "jp/ggaf/core/actor/MainActor.h"
#include "jp/ggaf/core/scene/Spacetime.h"

using namespace GgafCore;

GroupHead::GroupHead(kind_t prm_kind, Status* prm_pStat) : Actor("GROUP", prm_pStat) {
    _obj_class |= Obj_ggaf_GroupHead;
    _class_name = "GroupHead";
    _kind = prm_kind;
    setHitAble(false);
    _pSceneMediator = nullptr;

#ifdef MY_DEBUG
    //�f�o�b�O�p�B���O�Ɏ�ʃr�b�g��\��
    GGAF_DELETEARR(_name);
    const int bitnum = 32;
    char aChar_strbit[bitnum+1];
    UTIL::strbin(prm_kind, aChar_strbit, bitnum);
    std::stringstream ss;
    ss << "kind_t=" << aChar_strbit << "";
    std::string name = ss.str();
    int len = strlen(name.c_str());
    _name = NEW char[len+1];
    strcpy(_name, name.c_str());
#endif
}

void GroupHead::setKind(kind_t prm_kind) {
    _kind = prm_kind;

#ifdef MY_DEBUG
    //�f�o�b�O�p�B���O�̎�ʃr�b�g�\�����X�V
    GGAF_DELETEARR(_name);
    const int bitnum = 32;
    char aChar_strbit[bitnum+1];
    UTIL::strbin(prm_kind, aChar_strbit, bitnum);
    std::stringstream ss;
    ss << "kind_t=" << aChar_strbit << "";
    std::string name = ss.str();
    int len = strlen(name.c_str());
    _name = NEW char[len+1];
    strcpy(_name, name.c_str());
#endif
}

SceneMediator* GroupHead::getMySceneMediator() {
    if (_pSceneMediator == nullptr) {
        if (_pParent == nullptr) {
            _TRACE_("�y�x���zGroupHead::getSceneMediator �������Ă��Ȃ����߁AMediator���Ƃ�܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(Spacetime)������Mediator��Ԃ��܂���");
            _pSceneMediator = God::_pGod->_pSpacetime->bringSceneMediator();
        } else {
            if (_pParent->instanceOf(Obj_ggaf_MainActor)) {
                _pSceneMediator = ((MainActor*)(_pParent))->getMySceneMediator();
            } else if (_pParent->instanceOf(Obj_ggaf_GroupHead)) {
                _pSceneMediator = ((GroupHead*)(_pParent))->getMySceneMediator();
            } else if (_pParent->instanceOf(Obj_ggaf_SceneMediator)) {
                return (SceneMediator*)_pParent; //Actor�c���[���_
            }
            _TRACE_("�y�x���zGroupHead::getSceneMediator ���̃c���[�ɂ�Mediator�����܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(Spacetime)������Mediator��Ԃ��܂���");
            _pSceneMediator = God::_pGod->_pSpacetime->bringSceneMediator();
        }
    }
    return _pSceneMediator;
}

void GroupHead::setMySceneMediator(SceneMediator* prm_pSceneMediator) {
    _pSceneMediator = prm_pSceneMediator;
    Actor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_ggaf_MainActor)) {
            ((MainActor*)(pActor))->setMySceneMediator(prm_pSceneMediator);
        } else if (pActor->instanceOf(Obj_ggaf_GroupHead)) {
            ((GroupHead*)(pActor))->setMySceneMediator(prm_pSceneMediator);
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}

void GroupHead::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent) {
    } else {
        throwCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���B this="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }
}

God* GroupHead::askGod() {
    if (_pGod == nullptr) {
#ifdef MY_DEBUG
        if (getParent() == nullptr) {
            throwCriticalException("�_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

GroupHead::~GroupHead() {
}
