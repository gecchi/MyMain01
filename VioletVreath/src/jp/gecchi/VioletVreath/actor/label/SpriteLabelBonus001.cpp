#include "SpriteLabelBonus001.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT   ,
    PROG_MOVE01 ,
    PROG_MOVE02 ,
    PROG_LEAVE ,
    PROG_BANPEI,
};

SpriteLabelBonus001::SpriteLabelBonus001(const char* prm_name) :
        FontSpriteActor(prm_name, "Ranking_16Font")
{
    _class_name = "SpriteLabelBonus001";
    setZEnableDraw(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //自身のZバッファを書き込みしないに強制
    setSpecialRenderDepthIndex(1); //描画順序を最前面描画に強制。
    setHitAble(false);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_BxyzMv); //XYZ軸ビルボード
}

void SpriteLabelBonus001::onCreateModel() {
}

void SpriteLabelBonus001::initialize() {

}

void SpriteLabelBonus001::onDispatched(GgafDx::GeometricActor* prm_pOrgActor) {
    setPositionAt(prm_pOrgActor);
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->takeoverMvFrom(prm_pOrgActor->callRikisha());
    pRikisha->setMvAcce(300);
    setAlpha(0.7);
    getProgress()->reset(PROG_INIT);
}

void SpriteLabelBonus001::processBehavior() {
    const Camera* const pCam = pGOD->getSpacetime()->getCamera();
    GgafDx::Rikisha* const pRikisha = callRikisha();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_MOVE01: {
            //しばらく直進
            if (pProg->hasArrivedAt(60)) {
                //カメラに向かって方向転換1
                pRikisha->turnMvAngTwd(pCam,
                                      D_ANG(3), 0, TURN_CLOSE_TO, true);
            }
            if (pProg->hasArrivedAt(60+30)) {
                //カメラに向かって方向転換2
                pRikisha->turnMvAngTwd(pCam,
                                      D_ANG(1), 0, TURN_CLOSE_TO, true);
            }

            if (ABS(pCam->_x - _x) < PX_C(200) || pProg->getFrame() >= 60+30+120) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE02: {
            if (pProg->hasJustChanged()) {
            }
            addAlpha(-0.01);
            if (getAlpha() <= 0.0) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (pProg->hasJustChanged()) {
                sayonara();
                pProg->changeNothing();
            }
            break;
        }
        default :
            break;
    }

    pRikisha->behave();
}

SpriteLabelBonus001::~SpriteLabelBonus001() {
}

