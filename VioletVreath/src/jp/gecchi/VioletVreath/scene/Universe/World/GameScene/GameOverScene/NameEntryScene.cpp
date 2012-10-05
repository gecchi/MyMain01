#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

NameEntryScene::NameEntryScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "NameEntryScene";
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);

    pMenu_ = NEW MenuBoardNameEntry("pMenu_");
    getDirector()->addSubGroup(pMenu_);

    useProgress(10);
}

void NameEntryScene::onReset() {
    pLabel01_->update("");
    _pProg->set(NameEntryScene::PROG_INIT);
}
void NameEntryScene::initialize() {
    _TRACE_("NameEntryScene::initialize()");
}

void NameEntryScene::processBehavior() {

    switch (_pProg->get()) {
        case NameEntryScene::PROG_INIT: {
            _pProg->change(NameEntryScene::PROG_DISP);
            break;
        }

        case NameEntryScene::PROG_DISP: {
            if (_pProg->isJustChanged()) {
                _TRACE_("pMenu_->rise(PX_C(50), PX_C(10));");
                pLabel01_->update(PX_C(32), PX_C(32), "ENTRY!!!!");
                pMenu_->rise(PX_C(50), PX_C(10));
            }
            break;
        }

        case NameEntryScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        default:
            break;
     }
}

NameEntryScene::~NameEntryScene() {
}
