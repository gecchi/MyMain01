#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Item::Item(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat)
               : DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "Item";
    _pTractorMagic = NULL;
}

TractorMagic* Item::getTractorMagic() {
    if (_pTractorMagic == NULL) {
		_pTractorMagic = dynamic_cast<TractorMagic*>(P_MAGICMETER->_ringMagics.getNextFromFirst(0));
		if (_pTractorMagic == NULL) {
			throwGgafCriticalException("Item::Item TractorMagicのメーター位置がおかしいです。");
		}
    }
	return _pTractorMagic;
}

void Item::initialize() {

}

void Item::onReset() {
}

void Item::onActive() {
}

void Item::processBehavior() {
}

void Item::processJudgement() {
}

void Item::onInactive() {
}

Item::~Item() {
}
