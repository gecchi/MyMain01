#include "jp/ggaf/core/actor/GgafGroupHead.h"

#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/scene/GgafSpacetime.h"

using namespace GgafCore;

GgafGroupHead::GgafGroupHead(kind_t prm_kind, GgafStatus* prm_pStat) : GgafActor("GROUP", prm_pStat) {
    _obj_class |= Obj_GgafGroupHead;
    _class_name = "GgafGroupHead";
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

void GgafGroupHead::setKind(kind_t prm_kind) {
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

GgafSceneMediator* GgafGroupHead::getMySceneMediator() {
    if (_pSceneMediator == nullptr) {
        if (_pParent == nullptr) {
            _TRACE_("�y�x���zGgafGroupHead::getSceneMediator �������Ă��Ȃ����߁AMediator���Ƃ�܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(GgafSpacetime)������Mediator��Ԃ��܂���");
            _pSceneMediator = GgafGod::_pGod->_pSpacetime->bringSceneMediator();
        } else {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pSceneMediator = ((GgafMainActor*)(_pParent))->getMySceneMediator();
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pSceneMediator = ((GgafGroupHead*)(_pParent))->getMySceneMediator();
            } else if (_pParent->instanceOf(Obj_GgafSceneMediator)) {
                return (GgafSceneMediator*)_pParent; //Actor�c���[���_
            }
            _TRACE_("�y�x���zGgafGroupHead::getSceneMediator ���̃c���[�ɂ�Mediator�����܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(GgafSpacetime)������Mediator��Ԃ��܂���");
            _pSceneMediator = GgafGod::_pGod->_pSpacetime->bringSceneMediator();
        }
    }
    return _pSceneMediator;
}

void GgafGroupHead::setMySceneMediator(GgafSceneMediator* prm_pSceneMediator) {
    _pSceneMediator = prm_pSceneMediator;
    GgafActor* pActor = getSubFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_GgafMainActor)) {
            ((GgafMainActor*)(pActor))->setMySceneMediator(prm_pSceneMediator);
        } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
            ((GgafGroupHead*)(pActor))->setMySceneMediator(prm_pSceneMediator);
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}

void GgafGroupHead::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent) {
    } else {
        throwGgafCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���B this="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }
}

GgafGod* GgafGroupHead::askGod() {
    if (_pGod == nullptr) {
#ifdef MY_DEBUG
        if (getParent() == nullptr) {
            throwGgafCriticalException("�_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

GgafGroupHead::~GgafGroupHead() {
}
