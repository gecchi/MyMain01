#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafHeadActor::GgafHeadActor(actorkind prm_kind) : GgafActor("HEAD") {
    stringstream ss;
    ss <<  "kind=" << prm_kind << "";
    string name = ss.str();
    strcpy(_name, name.c_str());
	_class_name = "GgafHeadActor";
    _kind = prm_kind;
    setBumpable(false);
}

void GgafHeadActor::processJudgement() {
    //サブが無ければ自殺
    if (getSubFirst() == NULL) {
        arigatou_sayounara();
    }
}

GgafGod* GgafHeadActor::askGod() {
    if (_pGod == NULL) {
        if (getParent() == NULL) {
            throwGgafCriticalException("GgafHeadActor::askGod 神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        } else {
            _pGod = getParent()->askGod();
        }
    }
    return _pGod;
}

GgafHeadActor::~GgafHeadActor() {
}
