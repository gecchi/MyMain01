#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

NameEntryScene::NameEntryScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "NameEntryScene";
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);
    useProgress(10);
}

void NameEntryScene::onReset() {
    fadeoutScene(0);
    pLabel01_->update("");
    _pProg->set(NameEntryScene::PROG_INIT);
}
void NameEntryScene::initialize() {
    _TRACE_("NameEntryScene::initialize()");
}

void NameEntryScene::processBehavior() {

    switch (_pProg->getPrev_WhenJustChanged()) {
        case NameEntryScene::PROG_DISP: {
            fadeoutScene(FADE_FRAMES);
            inactivateDelay(FADE_FRAMES);
            break;
        }

        default:
            break;
    }


    switch (_pProg->get()) {
        case NameEntryScene::PROG_INIT: {
            _pProg->change(NameEntryScene::PROG_DISP);
            break;
        }

        case NameEntryScene::PROG_DISP: {
            if (_pProg->isJustChanged()) {
                pLabel01_->update(500*1000, 300*1000, "GAME OVER (-_-;)");
                fadeinScene(FADE_FRAMES);
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
