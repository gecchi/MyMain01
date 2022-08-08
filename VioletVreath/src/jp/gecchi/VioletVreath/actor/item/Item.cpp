#include "Item.h"

#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"



using namespace GgafLib;
using namespace VioletVreath;

Item::Item(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset)
               : VvItemActor<DefaultMassMeshActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "Item";
    pTractorMagic_ = nullptr;
}

TractorMagic* Item::getTractorMagic() {
    if (pTractorMagic_ == nullptr) {
        pTractorMagic_ = pMAGICMETER->pTractorMagic_;
    }
    return pTractorMagic_;
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
