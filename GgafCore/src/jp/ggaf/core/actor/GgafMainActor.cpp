#include "jp/ggaf/core/actor/GgafMainActor.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/scene/GgafSpacetime.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name, GgafStatus* prm_pStat) :
    GgafActor(prm_name, prm_pStat),
    _pGroupHead(nullptr),
    _pSceneMediator(nullptr)
{
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setMySceneMediator(nullptr);
    pActor->setMyGroupHead(nullptr);
    return pActor;
}

void GgafMainActor::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent == nullptr) {
        throwGgafCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���Bthis="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }

}

void GgafMainActor::setMySceneMediator(GgafSceneMediator* prm_pSceneMediator) {
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


GgafSceneMediator* GgafMainActor::getMySceneMediator() {
    if (_pSceneMediator) {
        return _pSceneMediator;
    } else {
        if (_pParent) {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pSceneMediator = ((GgafMainActor*)(_pParent))->getMySceneMediator();
                return _pSceneMediator;
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pSceneMediator = ((GgafGroupHead*)(_pParent))->getMySceneMediator();
                return _pSceneMediator;
            } else if (_pParent->instanceOf(Obj_GgafSceneMediator)) { //���肦�񂩂�
                _pSceneMediator = (GgafSceneMediator*)_pParent;
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


GgafGroupHead* GgafMainActor::addSubGroup(kind_t prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        //_TRACE_("�y�x���zGgafSceneMediator::addSubGroup("<<getName()<<") ���ł�"<<prm_pMainActor->_pSceneMediator->_pScene_platform->getName()<<"�V�[���̒���҂ɏ������Ă��܂��B���A"<<_pScene_platform->getName()<<"�V�[���̒���҂ɏ�芷���܂�");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pMyGroupHead = getMyGroupHead();
    if (pMyGroupHead != nullptr && pMyGroupHead->_kind == prm_kind) {
        //���g�̏����ςݒc����ʂƈ����̃A�N�^�[�̎�ʂ������ꍇ
        addSubLast(prm_pMainActor); //�P���Ɏ����̃T�u�ɒǉ���OK
        prm_pMainActor->setMyGroupHead(pMyGroupHead);             //�c���𔽉f
        prm_pMainActor->setMySceneMediator(getMySceneMediator()); //����҂𔽉f
        return pMyGroupHead;
    } else {
        //���g�̏����ςݒc����ʂƈ����̃A�N�^�[�̎�ʂ��قȂ�ꍇ
        GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //�ł́A�����̃T�u�Ɉ����̃A�N�^�[�Ɠ�����ʂ̒c�������邩�T��
        if (pSubGroupActor) {
            //�T�u�ɓ�����ʒc���������ꍇ�A���̒c���̃T�u��
            pSubGroupActor->addSubLast(prm_pMainActor);                //�T�u�ɋ�������c���̔z���ɒǉ�
            prm_pMainActor->setMyGroupHead(pSubGroupActor);            //�c���𔽉f
            prm_pMainActor->setMySceneMediator(getMySceneMediator());  //����҂𔽉f
            return pSubGroupActor;
        } else {
            //�T�u�ɓ�����ʒc�������Ȃ��ꍇ�A�c����V���ɍ쐬�����g�̃T�u�ցA
            //�����̃A�N�^�[�͒c���̂��̃T�u��
            GgafGroupHead* pNewSubGroupActor = NEW GgafGroupHead(prm_kind);
            addSubLast(pNewSubGroupActor);                          //���g�̔z���ɐV�c����ǉ���
            pNewSubGroupActor->addSubLast(prm_pMainActor);          //�V�c���̔z���Ɉ����̃A�N�^�[
            prm_pMainActor->setMyGroupHead(pNewSubGroupActor);            //�c���𔽉f
            pNewSubGroupActor->setMySceneMediator(getMySceneMediator());  //�V�c���z���ɒ���҂𔽉f
            return pNewSubGroupActor;
        }
    }
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    //getStatus()->get() ��int �^�����A�Ⴆ���̐��ɂȂ��Ă����Ƃ��Ă��A�r�b�g�̏��ɉe���͂Ȃ�
    return addSubGroup(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GgafGroupHead* GgafMainActor::searchSubGroupHead(kind_t prm_kind) {
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
            throwGgafCriticalException("�_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

kind_t GgafMainActor::lookUpKind() {
    GgafGroupHead* pMyGroupHead = getMyGroupHead();
#ifdef MY_DEBUG
    if (pMyGroupHead == nullptr) {
        throwGgafCriticalException("GgafMainActor::lookUpKind() GgafGroupHead�ɏ������Ă��Ȃ��̂� ��ʂ��킩��܂���Bthis="<<NODE_INFO);
    }
#endif
    return pMyGroupHead->_kind;
}

GgafMainActor::~GgafMainActor() {
}
