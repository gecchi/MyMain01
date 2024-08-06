#include "SpriteLabelBonus002.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT ,
    PHASE_FADE ,
    PHASE_BANPEI,
};

SpriteLabelBonus002::SpriteLabelBonus002(const char* prm_name) :
        FontSpriteActor(prm_name, "Font32x64")
{
    _class_name = "SpriteLabelBonus002";
    setZEnableDraw(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //自身のZバッファを書き込みしないに強制
    setSpecialRenderDepthIndex(1); //描画順序を最前面描画に強制。
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setHitAble(false);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_AlignAppScBxyzMv); //見かけ上の大きさを揃えるビルボード
}

void SpriteLabelBonus002::onCreateModel() {
}

void SpriteLabelBonus002::initialize() {
}

void SpriteLabelBonus002::onDispatched(GgafDx::GeometricActor* prm_pOrgActor) {
    setPositionAt(prm_pOrgActor);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->takeoverFrom(prm_pOrgActor->getLocusVehicle());
    getPhase()->reset(PHASE_INIT);
}

void SpriteLabelBonus002::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setAlpha(0.9);
            pLocusVehicle->setMvAcceByT(60, 100);
            if(pPhase->getFrame() >= 60) {
                pLocusVehicle->stop();
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_FADE: {
            addAlpha(-0.01);
            if (getAlpha() <= 0.0) {
                sayonara();
                pPhase->changeNext();
            }
            break;
        }
        default:
            break;
    }
    pLocusVehicle->behave();
}

SpriteLabelBonus002::~SpriteLabelBonus002() {
}

