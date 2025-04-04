#include "SpriteLabelBonus001.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_DISP ,
    PHASE_FADE ,
    PHASE_BANPEI,
};

SpriteLabelBonus001::SpriteLabelBonus001(const char* prm_name) :
        FontSpriteActor(prm_name, "Ranking_16Font")
{
    _class_name = "SpriteLabelBonus001";
    useZBufferDrawing(false);      //Zバッファは考慮無しに強制
    setZBufferWriteEnable(false); //自身のZバッファを書き込みしないに強制
    setSpecialRenderDepthIndex(1); //描画順序を最前面描画に強制。
    setHitAble(false);
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_AlignAppScBxyzMv); //見かけ上の大きさを揃えるビルボード
}

void SpriteLabelBonus001::onCreateModel() {
}

void SpriteLabelBonus001::initialize() {
}

void SpriteLabelBonus001::onDispatched(GgafDx::GeometricActor* prm_pOrgActor) {
    setPositionAt(prm_pOrgActor);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->takeoverFrom(prm_pOrgActor->getLocusVehicle());

    getPhase()->reset(PHASE_DISP);
    setAlpha(0.9);

    //スローを考慮したスピードに補正する
    GgafCore::Scene* pOrgActorPlatformScene = prm_pOrgActor->getSceneChief()->getPlatformScene();
    VvScene<GgafLib::DefaultScene>* pOrgActorScene = (VvScene<GgafLib::DefaultScene>*)pOrgActorPlatformScene;
    pLocusVehicle->setMvVelo((pLocusVehicle->getMvVelo()*1.0)/(pOrgActorScene->_once_in_n_frame) );

    if (pLocusVehicle->getMvVelo() > PX_C(0.5)) {
        pLocusVehicle->setMvAcceByT(60, PX_C(0.5));
    } else {
        pLocusVehicle->setMvAcce(0);
    }

}

void SpriteLabelBonus001::processBehavior() {
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_DISP: {
            if(pPhase->getFrame() >= 60) {
                pLocusVehicle->setMvAcce(0); //setMvAcceByT() の PX_C(0.5) 速度のまま
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

SpriteLabelBonus001::~SpriteLabelBonus001() {
}

