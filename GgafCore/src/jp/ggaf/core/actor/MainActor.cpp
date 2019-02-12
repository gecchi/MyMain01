#include "jp/ggaf/core/actor/MainActor.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/scene/Spacetime.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

MainActor::MainActor(const char* prm_name, Status* prm_pStat) :
    Actor(prm_name, prm_pStat),
    _pGroupHead(nullptr),
    _pSceneMediator(nullptr)
{
    _obj_class |= Obj_ggaf_MainActor;
    _class_name = "MainActor";
    setHitAble(false);
}

MainActor* MainActor::extract() {
    MainActor* pActor = (MainActor*)Actor::extract();
    pActor->setMySceneMediator(nullptr);
    pActor->setMyGroupHead(nullptr);
    return pActor;
}

void MainActor::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent == nullptr) {
        throwCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���Bthis="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }

}

void MainActor::setMySceneMediator(SceneMediator* prm_pSceneMediator) {
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

void MainActor::setMyGroupHead(GroupHead* prm_pGroupHead) {
    _pGroupHead = prm_pGroupHead;
    Actor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_ggaf_MainActor)) {
            ((MainActor*)(pActor))->setMyGroupHead(prm_pGroupHead);
        } else if (pActor->instanceOf(Obj_ggaf_GroupHead)) {
            //�X���[����
            //���ʃc���[��GroupHead������΁A���̃c���[�ɂ͉e�������Ȃ����ƂƂ���
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}


GroupHead* MainActor::getMyGroupHead() {
    if (_pGroupHead) {
        return _pGroupHead;
    } else {
        if (_pParent == nullptr) {
            return nullptr;
        } else if (_pParent->instanceOf(Obj_ggaf_MainActor)) {
            _pGroupHead = ((MainActor*)(_pParent))->getMyGroupHead();
            return _pGroupHead;
        } else if (_pParent->instanceOf(Obj_ggaf_GroupHead)) {
            return (GroupHead*)_pParent;
        } else {
            return nullptr;
        }
    }
}


SceneMediator* MainActor::getMySceneMediator() {
    if (_pSceneMediator) {
        return _pSceneMediator;
    } else {
        if (_pParent) {
            if (_pParent->instanceOf(Obj_ggaf_MainActor)) {
                _pSceneMediator = ((MainActor*)(_pParent))->getMySceneMediator();
                return _pSceneMediator;
            } else if (_pParent->instanceOf(Obj_ggaf_GroupHead)) {
                _pSceneMediator = ((GroupHead*)(_pParent))->getMySceneMediator();
                return _pSceneMediator;
            } else if (_pParent->instanceOf(Obj_ggaf_SceneMediator)) { //���肦�񂩂�
                _pSceneMediator = (SceneMediator*)_pParent;
                return _pSceneMediator;
            } else {
                _pSceneMediator = nullptr;
                return _pSceneMediator;
            }
        } else {
            _pSceneMediator = nullptr;
            return _pSceneMediator;
        }
    }
}


GroupHead* MainActor::appendGroupChild(kind_t prm_kind, MainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        //_TRACE_("�y�x���zSceneMediator::appendGroupChild("<<getName()<<") ���ł�"<<prm_pMainActor->_pSceneMediator->_pScene_platform->getName()<<"�V�[���̒���҂ɏ������Ă��܂��B���A"<<_pScene_platform->getName()<<"�V�[���̒���҂ɏ�芷���܂�");
        prm_pMainActor->extract();
    }
    GroupHead* pMyGroupHead = getMyGroupHead();
    if (pMyGroupHead != nullptr && pMyGroupHead->_kind == prm_kind) {
        //���g�̏����ςݒc����ʂƈ����̃A�N�^�[�̎�ʂ������ꍇ
        appendChild(prm_pMainActor); //�P���Ɏ����̎q�ɒǉ���OK
        prm_pMainActor->setMyGroupHead(pMyGroupHead);             //�c���𔽉f
        prm_pMainActor->setMySceneMediator(getMySceneMediator()); //����҂𔽉f
        return pMyGroupHead;
    } else {
        //���g�̏����ςݒc����ʂƈ����̃A�N�^�[�̎�ʂ��قȂ�ꍇ
        GroupHead* pChildGroupActor = searchChildGroupHead(prm_kind); //�ł́A�����̎q�Ɉ����̃A�N�^�[�Ɠ�����ʂ̒c�������邩�T��
        if (pChildGroupActor) {
            //�q�ɓ�����ʒc���������ꍇ�A���̒c���̎q��
            pChildGroupActor->appendChild(prm_pMainActor);                //�q�ɋ�������c���̔z���ɒǉ�
            prm_pMainActor->setMyGroupHead(pChildGroupActor);            //�c���𔽉f
            prm_pMainActor->setMySceneMediator(getMySceneMediator());  //����҂𔽉f
            return pChildGroupActor;
        } else {
            //�q�ɓ�����ʒc�������Ȃ��ꍇ�A�c����V���ɍ쐬�����g�̎q�ցA
            //�����̃A�N�^�[�͒c���̂��̎q��
            GroupHead* pNewChildGroupActor = NEW GroupHead(prm_kind);
            appendChild(pNewChildGroupActor);                          //���g�̔z���ɐV�c����ǉ���
            pNewChildGroupActor->appendChild(prm_pMainActor);          //�V�c���̔z���Ɉ����̃A�N�^�[
            prm_pMainActor->setMyGroupHead(pNewChildGroupActor);            //�c���𔽉f
            pNewChildGroupActor->setMySceneMediator(getMySceneMediator());  //�V�c���z���ɒ���҂𔽉f
            return pNewChildGroupActor;
        }
    }
}

GroupHead* MainActor::appendGroupChild(MainActor* prm_pMainActor) {
    //getStatus()->get() ��int �^�����A�Ⴆ���̐��ɂȂ��Ă����Ƃ��Ă��A�r�b�g�̏��ɉe���͂Ȃ�
    return appendGroupChild(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GroupHead* MainActor::searchChildGroupHead(kind_t prm_kind) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        Actor* pChildActor = _pChildFirst;
        GroupHead* pChildGroupHead_ret = nullptr;
        do {
            if (pChildActor->instanceOf(Obj_ggaf_GroupHead)) {
                pChildGroupHead_ret = (GroupHead*)pChildActor;
                if (pChildGroupHead_ret->_kind == prm_kind && pChildGroupHead_ret->_frame_of_life_when_end == 0) {
                    return pChildGroupHead_ret;
                }
            }
            if (pChildActor->_is_last_flg) {
                return nullptr;
            } else {
                pChildActor = pChildActor->_pNext;
            }
        } while (true);
    }
}

God* MainActor::askGod() {
    if (_pGod == nullptr) {
        if (_pParent == nullptr) {
            throwCriticalException("�_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

kind_t MainActor::lookUpKind() {
    GroupHead* pMyGroupHead = getMyGroupHead();
#ifdef MY_DEBUG
    if (pMyGroupHead == nullptr) {
        throwCriticalException("MainActor::lookUpKind() GroupHead�ɏ������Ă��Ȃ��̂� ��ʂ��킩��܂���Bthis="<<NODE_INFO);
    }
#endif
    return pMyGroupHead->_kind;
}

MainActor::~MainActor() {
}
