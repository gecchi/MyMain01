#include "jp/ggaf/core/actor/GroupHead.h"

#include "jp/ggaf/core/actor/MainActor.h"
#include "jp/ggaf/core/scene/Spacetime.h"

using namespace GgafCore;

GroupHead::GroupHead(kind_t prm_kind) : Actor("GroupHead") {
    _obj_class |= Obj_ggaf_GroupHead;
    _class_name = "GroupHead";
    _kind = prm_kind;
    setHitAble(false);
    _pSceneChief = nullptr;

#ifdef MY_DEBUG
    //デバッグ用。名前に種別ビットを表示
    GGAF_DELETEARR(_name);
    const int bitnum = 32;
    char aChar_strbit[bitnum+1];
    UTIL::dec2bin(prm_kind, aChar_strbit, bitnum);
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
    //デバッグ用。名前の種別ビット表示を更新
    GGAF_DELETEARR(_name);
    const int bitnum = 32;
    char aChar_strbit[bitnum+1];
    UTIL::dec2bin(prm_kind, aChar_strbit, bitnum);
    std::stringstream ss;
    ss << "kind_t=" << aChar_strbit << "";
    std::string name = ss.str();
    int len = strlen(name.c_str());
    _name = NEW char[len+1];
    strcpy(_name, name.c_str());
#endif
}

SceneChief* GroupHead::getSceneChief() {
    if (_pSceneChief == nullptr) {
        if (_pParent == nullptr) {
            _TRACE_("【警告】GroupHead::getSceneChief 所属していないため、Chiefがとれません！("<<getName()<<")。そこで勝手にこの世(Spacetime)所属のChiefを返しました");
            _pSceneChief = Caretaker::_pCaretaker->_pSpacetime->getSceneChief();
        } else {
            if (_pParent->instanceOf(Obj_ggaf_MainActor)) {
                _pSceneChief = ((MainActor*)(_pParent))->getSceneChief();
            } else if (_pParent->instanceOf(Obj_ggaf_GroupHead)) {
                _pSceneChief = ((GroupHead*)(_pParent))->getSceneChief();
            } else if (_pParent->instanceOf(Obj_ggaf_SceneChief)) {
                return (SceneChief*)_pParent; //Actorツリー頂点
            }
            _TRACE_("【警告】GroupHead::getSceneChief このツリーにはChiefがいません！("<<getName()<<")。そこで勝手にこの世(Spacetime)所属のChiefを返しました");
            _pSceneChief = Caretaker::_pCaretaker->_pSpacetime->getSceneChief();
        }
    }
    return _pSceneChief;
}

void GroupHead::setSceneChief(SceneChief* prm_pSceneChief) {
    _pSceneChief = prm_pSceneChief;
    Actor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_ggaf_MainActor)) {
            ((MainActor*)(pActor))->setSceneChief(prm_pSceneChief);
        } else if (pActor->instanceOf(Obj_ggaf_GroupHead)) {
            ((GroupHead*)(pActor))->setSceneChief(prm_pSceneChief);
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
        throwCriticalException("_is_active_in_the_tree_flg 更新できません。 this="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }
}

Caretaker* GroupHead::askCaretaker() {
    if (_pCaretaker == nullptr) {
#ifdef MY_DEBUG
        if (getParent() == nullptr) {
            throwCriticalException("管理者はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
#endif
        _pCaretaker = getParent()->askCaretaker();
    }
    return _pCaretaker;
}

GroupHead::~GroupHead() {
}
