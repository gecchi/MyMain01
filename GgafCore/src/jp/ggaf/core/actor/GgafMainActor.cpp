#include "jp/ggaf/core/actor/GgafMainActor.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/scene/GgafUniverse.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name, GgafStatus* prm_pStat) :
    GgafActor(prm_name, prm_pStat),
    _pGroupHead(nullptr),
    _pSceneDirector(nullptr)
{
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setPlatformScene(nullptr);
    pActor->setMySceneDirector(nullptr);
    pActor->setMyGroupHead(nullptr);
    return pActor;
}

void GgafMainActor::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent) {
    } else {
        throwGgafCriticalException("GgafMainActor::updateActiveInTheTree() _is_active_in_the_tree_flg �X�V�ł��܂���Bthis="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }

}

void GgafMainActor::setMySceneDirector(GgafSceneDirector* prm_pSceneDirector) {
    _pSceneDirector = prm_pSceneDirector;
    GgafActor* pActor = getSubFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_GgafMainActor)) {
            ((GgafMainActor*)(pActor))->setMySceneDirector(prm_pSceneDirector);
        } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
            ((GgafGroupHead*)(pActor))->setMySceneDirector(prm_pSceneDirector);
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}

void GgafMainActor::setMyGroupHead(GgafGroupHead* prm_pGroupHead) {
    _pGroupHead = prm_pGroupHead;
    GgafActor* pActor = getSubFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_GgafMainActor)) {
            ((GgafMainActor*)(pActor))->setMyGroupHead(prm_pGroupHead);
        } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
            //�X���[����
            //���ʃc���[��GgafGroupHead������΁A���̃c���[�ɂ͉e�������Ȃ����ƂƂ���
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}


GgafGroupHead* GgafMainActor::getMyGroupHead() {
    if (_pGroupHead) {
        return _pGroupHead;
    } else {
        if (_pParent == nullptr) {
            return nullptr;
        } else if (_pParent->instanceOf(Obj_GgafMainActor)) {
            _pGroupHead = ((GgafMainActor*)(_pParent))->getMyGroupHead();
            return _pGroupHead;
        } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
            return (GgafGroupHead*)_pParent;
        } else {
            return nullptr;
        }
    }
}


GgafSceneDirector* GgafMainActor::getMySceneDirector() {
    if (_pSceneDirector) {
        return _pSceneDirector;
    } else {
        if (_pParent) {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pSceneDirector = ((GgafMainActor*)(_pParent))->getMySceneDirector();
                return _pSceneDirector;
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pSceneDirector = ((GgafGroupHead*)(_pParent))->getMySceneDirector();
                return _pSceneDirector;
            } else if (_pParent->instanceOf(Obj_GgafSceneDirector)) { //���肦�񂩂�
                _pSceneDirector = (GgafSceneDirector*)_pParent;
                return _pSceneDirector;
            } else {
                _pSceneDirector = nullptr;
                return _pSceneDirector;
            }
        } else {
            _pSceneDirector = nullptr;
            return _pSceneDirector;
        }
    }
}


GgafGroupHead* GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneDirector) {
        //_TRACE_("�y�x���zGgafSceneDirector::addSubGroup("<<getName()<<") ���ł�"<<prm_pMainActor->_pSceneDirector->_pScene_platform->getName()<<"�V�[���̊ēɏ������Ă��܂��B���A"<<_pScene_platform->getName()<<"�V�[���̊ēɏ�芷���܂�");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pMyGroupHead = getMyGroupHead();
    if (pMyGroupHead != nullptr && pMyGroupHead->_kind == prm_kind) {
        //���g�̏����ςݒc����ʂƈ����̃A�N�^�[�̎�ʂ������ꍇ
        addSubLast(prm_pMainActor); //�P���Ɏ����̃T�u�ɒǉ���OK
        prm_pMainActor->setMyGroupHead(pMyGroupHead);             //�c���𔽉f
        prm_pMainActor->setMySceneDirector(getMySceneDirector()); //�ē𔽉f
        prm_pMainActor->setPlatformScene(getPlatformScene());     //�����V�[���𔽉f
        return pMyGroupHead;
    } else {
        //���g�̏����ςݒc����ʂƈ����̃A�N�^�[�̎�ʂ��قȂ�ꍇ
        GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //�ł́A�����̃T�u�Ɉ����̃A�N�^�[�Ɠ�����ʂ̒c�������邩�T��
        if (pSubGroupActor) {
            //�T�u�ɓ�����ʒc���������ꍇ�A���̒c���̃T�u��
            pSubGroupActor->addSubLast(prm_pMainActor);                //�T�u�ɋ�������c���̔z���ɒǉ�
            prm_pMainActor->setMyGroupHead(pSubGroupActor);            //�c���𔽉f
            prm_pMainActor->setMySceneDirector(getMySceneDirector());  //�ē𔽉f
            prm_pMainActor->setPlatformScene(getPlatformScene());      //�����V�[���𔽉f
            return pSubGroupActor;
        } else {
            //�T�u�ɓ�����ʒc�������Ȃ��ꍇ�A�c����V���ɍ쐬�����g�̃T�u�ցA
            //�����̃A�N�^�[�͒c���̂��̃T�u��
            GgafGroupHead* pNewSubGroupActor = NEW GgafGroupHead(prm_kind);
            addSubLast(pNewSubGroupActor);                          //���g�̔z���ɐV�c����ǉ���
            pNewSubGroupActor->addSubLast(prm_pMainActor);          //�V�c���̔z���Ɉ����̃A�N�^�[
            prm_pMainActor->setMyGroupHead(pNewSubGroupActor);            //�c���𔽉f
            pNewSubGroupActor->setMySceneDirector(getMySceneDirector());  //�V�c���z���Ɋē𔽉f
            pNewSubGroupActor->setPlatformScene(getPlatformScene());      //�V�c���z���ɏ����V�[���Z�b�g
            return pNewSubGroupActor;
        }
    }
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    //getStatus()->get() ��int �^�����A�Ⴆ���̐��ɂȂ��Ă����Ƃ��Ă��A�r�b�g�̏��ɉe���͂Ȃ�
    return addSubGroup(prm_pMainActor->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}

GgafGroupHead* GgafMainActor::searchSubGroupHead(actorkind prm_kind) {
    if (_pSubFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupHead_ret = nullptr;
        do {
            if (pSubActor->instanceOf(Obj_GgafGroupHead)) {
                pSubGroupHead_ret = (GgafGroupHead*)pSubActor;
                if (pSubGroupHead_ret->_kind == prm_kind && pSubGroupHead_ret->_frame_of_life_when_end == 0) {
                    return pSubGroupHead_ret;
                }
            }
            if (pSubActor->_is_last_flg) {
                return nullptr;
            } else {
                pSubActor = pSubActor->_pNext;
            }
        } while (true);
    }
}

GgafGod* GgafMainActor::askGod() {
    if (_pGod == nullptr) {
        if (_pParent == nullptr) {
            throwGgafCriticalException("GgafMainActor::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

actorkind GgafMainActor::getKind() {
    return getMyGroupHead()->_kind;
}



GgafMainActor::~GgafMainActor() {
}
