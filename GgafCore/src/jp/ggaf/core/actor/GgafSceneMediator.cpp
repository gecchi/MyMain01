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

GgafGroupHead* GgafSceneMediator::appendGroupChild(kind_t prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        throwGgafCriticalException("Error! GgafSceneMediator::appendGroupChild �����ς݂𖳗����ړ������悤�Ƃ��Ă��܂��B\n"
                " extract() ���s���Ă���o���Ȃ��ł����H prm_pMainActor="<<NODE_INFO_P(prm_pMainActor)<<"/this="<<NODE_INFO);
    }
    GgafGroupHead* pChildGroupActor = searchChildGroupHead(prm_kind); //�q�ɓ�����ʒc�������邩�T��
    if (!pChildGroupActor) {
        //�q�ɓ�����ʒc�������Ȃ��ꍇ�A�c����V���ɍ쐬
        pChildGroupActor = NEW GgafGroupHead(prm_kind);
        appendChild(pChildGroupActor);
        pChildGroupActor->setMySceneMediator(this);
    }
    pChildGroupActor->appendChild(prm_pMainActor);
    prm_pMainActor->setMyGroupHead(pChildGroupActor);
    prm_pMainActor->setMySceneMediator(this);
    return pChildGroupActor;
}

GgafGroupHead* GgafSceneMediator::appendGroupChild(GgafMainActor* prm_pMainActor) {
    return appendGroupChild(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GgafGroupHead* GgafSceneMediator::searchChildGroupHead(kind_t prm_kind) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pChildActor = _pChildFirst;
        GgafGroupHead* pChildGroupHead_ret = nullptr;
        do {
            if (pChildActor->instanceOf(Obj_GgafGroupHead)) {
                pChildGroupHead_ret = (GgafGroupHead*)pChildActor;
                if (pChildGroupHead_ret->_kind == prm_kind && pChildGroupHead_ret->_frame_of_life_when_end == 0) {
                    return pChildGroupHead_ret;
                }
            }
            if (pChildActor->_is_last_flg) {
                break;
            } else {
                pChildActor = pChildActor->_pNext;
            }
        } while (true);

        return nullptr;
    }
}

void GgafSceneMediator::updateActiveInTheTree() {
    GgafScene* pPlatform = getPlatformScene();
    if (pPlatform) {
        if (pPlatform->_is_active_in_the_tree_flg) {
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

GgafActor* GgafSceneMediator::search(hashval prm_name_hash) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pPrev = this;
        GgafActor* pCur = getChildFirst();

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
            if (pCur->getChildFirst()) {
                pCur = pCur->getChildFirst();
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
