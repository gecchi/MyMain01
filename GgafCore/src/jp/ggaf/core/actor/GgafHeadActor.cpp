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
    //�T�u��������Ύ��E
    if (getSubFirst() == NULL) {
        arigatou_sayounara();
    }
}

GgafGod* GgafHeadActor::askGod() {
    if (_pGod == NULL) {
        if (getParent() == NULL) {
            throwGgafCriticalException("GgafHeadActor::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        } else {
            _pGod = getParent()->askGod();
        }
    }
    return _pGod;
}

GgafHeadActor::~GgafHeadActor() {
}
