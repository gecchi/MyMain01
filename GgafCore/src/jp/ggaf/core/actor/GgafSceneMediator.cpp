#include "jp/ggaf/core/actor/GgafSceneMediator.h"

#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafSceneMediator::GgafSceneMediator(GgafScene* prm_pScene_platform) : GgafActor("SceneMediator", nullptr),
_pScene_platform(nullptr)
{
    _obj_class |= Obj_GgafSceneMediator;
    _class_name = "GgafSceneMediator";
    _pScene_platform = prm_pScene_platform;
    setHitAble(false);
}

void GgafSceneMediator::throwEventUpperTree(hashval prm_no, void* prm_pSource) {
    GgafScene* s = getPlatformScene();
    if (s) {
        s->throwEventUpperTree(prm_no, this); //��������ʂ͋��Ȃ��B�����ŏ����V�[���֓�����
    }
}

void GgafSceneMediator::remove() {
    throwGgafCriticalException("Error! GgafSceneMediator��remove()�ɂ���č폜�͍s���܂���I");
}

GgafGroupHead* GgafSceneMediator::addSubGroup(kind_t prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        throwGgafCriticalException("Error! GgafSceneMediator::addSubGroup �����ς݂𖳗����ړ������悤�Ƃ��Ă��܂��B\n"
                " extract() ���s���Ă���o���Ȃ��ł����H prm_pMainActor="<<NODE_INFO_P(prm_pMainActor)<<"/this="<<NODE_INFO);
    }
    GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //�T�u�ɓ�����ʒc�������邩�T��
    if (!pSubGroupActor) {
        //�T�u�ɓ�����ʒc�������Ȃ��ꍇ�A�c����V���ɍ쐬
        pSubGroupActor = NEW GgafGroupHead(prm_kind);
        addSubLast(pSubGroupActor);
        pSubGroupActor->setMySceneMediator(this);
    }
    pSubGroupActor->addSubLast(prm_pMainActor);
    prm_pMainActor->setMyGroupHead(pSubGroupActor);
    prm_pMainActor->setMySceneMediator(this);
    return pSubGroupActor;
}

GgafGroupHead* GgafSceneMediator::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GgafGroupHead* GgafSceneMediator::searchSubGroupHead(kind_t prm_kind) {
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
                break;
            } else {
                pSubActor = pSubActor->_pNext;
            }
        } while (true);

        return nullptr;
    }
}

void GgafSceneMediator::updateActiveInTheTree() {
    if (getPlatformScene()) {
        if (_pScene_platform->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        throwGgafCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���B this="<<NODE_INFO);
    }
}

GgafGod* GgafSceneMediator::askGod() {
    if (_pGod == nullptr) {
#ifdef MY_DEBUG
        if (getPlatformScene() == nullptr) {
            throwGgafCriticalException("�_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getPlatformScene()->askGod();
    }
    return _pGod;
}
GgafActor* GgafSceneMediator::bring(hashval prm_name_hash) {
    if (_pSubFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pPrev = this;
        GgafActor* pCur = getSubFirst();

        while (pCur != this) {
            if (pCur->_name_hash == prm_name_hash) {
                return pCur; //�����܂�
            } else {
                pPrev = pCur;
            }
            if (pPrev == pCur->getParent()) {
                //�ォ��~��ė����ꍇ
                goto susume;
            } else if (pPrev == pCur->getPrev()) {
                //������ɐi��ŗ����ꍇ
                goto susume;
            } else {
                //������オ���Ă����ꍇ
                //�E�֍s���������݂�
                if (pCur->_is_last_flg) {
                    //�Ǝv������E�[�������̂ŁA��ɖ߂�
                    pCur = pCur->getParent();
                } else {
                    //�E�֍s����̂ŁA�s���I
                    pCur = pCur->getNext();
                }
                continue;
            }
susume:
            //�~����Ȃ�΍~���
            if (pCur->getSubFirst()) {
                pCur = pCur->getSubFirst();
            } else {
                //�~���Ȃ��ꍇ�͉E�֍s���������݂�
                if (pCur->_is_last_flg) {
                    //�Ǝv������E�[�������̂ŁA��ɖ߂�
                    pCur = pCur->getParent();
                } else {
                    //�E�֍s����̂ŁA�s���I
                    pCur = pCur->getNext();
                }
            }
        }
        return nullptr;
    }
}
GgafSceneMediator::~GgafSceneMediator() {
}
