#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafHeadActor::GgafHeadActor(actorkind prm_kind) : GgafActor("HEAD") {
//    stringstream cname;
//    cname <<  "GgafHeadActor[_kind=" << prm_kind << "]";
//    string cname2 = cname.str();
	_class_name = "GgafHeadActor";
    _kind = prm_kind;
    setBumpable(false);
}

void GgafHeadActor::processJudgement() {
    //�T�u��������Ύ��E
    if (getSubFirst() == NULL) {
        arigatou_sayounara();
    }
}

GgafGod* GgafHeadActor::askGod() {
    if (_pGod == NULL) {
        if (getParent() == NULL) {
            throwGgafCriticalException("GgafHeadActor::askGod �_�͐��E����̂݉y���ł��܂��B�܂��͐��E�ɑ����Ȃ����I�I("<<getName()<<")");
        } else {
            _pGod = getParent()->askGod();
        }
    }
    return _pGod;
}

GgafHeadActor::~GgafHeadActor() {
}
