#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafLordActor::GgafLordActor(GgafScene* prm_pScene_Platform) : GgafActor(prm_pScene_Platform->getName()) {
    _pScene_Platform = prm_pScene_Platform;
    _class_name = "GgafLordActor";
    setBumpable(false);
}

void GgafLordActor::remove() {
    throwGgafCriticalException("[GgafLordActor::remove] Error! GgafLordActor��remove()�ɂ���č폜�͍s���܂���I");
}

void GgafLordActor::accept(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pLordActor != NULL) {
        //_TRACE_("�y�x���zGgafLordActor::accept("<<getName()<<") ���ł�"<<prm_pMainActor->_pLordActor->_pScene_Platform->getName()<<"�V�[���̊Ǘ��҂ɏ������Ă��܂��B���A"<<_pScene_Platform->getName()<<"�V�[���̊Ǘ��҂ɏ�芷���܂�");
        prm_pMainActor->breakAwayFromTree();
    }
    GgafHeadActor* pHeadActor = NULL;
    if (hasSubHeadActor(prm_kind)) {
        pHeadActor = getSubHeadActor(prm_kind);
    } else {
        pHeadActor = NEW GgafHeadActor(prm_kind);
        addSubLast(pHeadActor);
    }
    prm_pMainActor->setLordActor(this);
    prm_pMainActor->setHeadActor(pHeadActor);
    prm_pMainActor->setScenePlatform(_pScene_Platform);
    pHeadActor->addSubLast(prm_pMainActor);
}

void GgafLordActor::accept(GgafMainActor* prm_pMainActor) {
    accept(0, prm_pMainActor);
}

bool GgafLordActor::hasSubHeadActor(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return false;
    } else {
        GgafHeadActor* pHeadActor = (GgafHeadActor*)_pSubFirst;
        do {
            if (pHeadActor->_kind == prm_kind) {
                return true;
            }
            if (pHeadActor->_is_last_flg) {
                return false;
            } else {
                pHeadActor = (GgafHeadActor*)(pHeadActor->_pNext);
            }
        } while (true);
    }

}

GgafHeadActor* GgafLordActor::getSubHeadActor(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        throwGgafCriticalException("[GgafLordActor::getSubHeadActor] Error! _pSubFirst��NULL�ł��B");
    }
    GgafHeadActor* pHeadActor = (GgafHeadActor*)_pSubFirst;
    do {
        if (pHeadActor->_kind == prm_kind) {
            break;
        }
        if (pHeadActor->_is_last_flg) {
            throwGgafCriticalException("[GgafLordActor::getSubHeadActor] Error! �q�m�[�h�͑��݂��܂���B(actorkind="<<prm_kind<<")");
        } else {
            pHeadActor = (GgafHeadActor*)(pHeadActor->_pNext);
        }
    } while (true);
    return pHeadActor;
}

/*
 GgafHeadActor* GgafLordActor::getHeadActor(string prm_kind) {

 }
 */

GgafGod* GgafLordActor::askGod() {
    if (_pGod == NULL) {
        if (getPlatformScene() == NULL) {
            throwGgafCriticalException("GgafLordActor::askGod �_�͐��E����̂݉y���ł��܂��B�܂��͐��E�ɑ����Ȃ����I�I("<<getName()<<")");
        } else {
            _pGod = getPlatformScene()->askGod();
        }
    }
    return _pGod;
}

GgafLordActor::~GgafLordActor() {
}
