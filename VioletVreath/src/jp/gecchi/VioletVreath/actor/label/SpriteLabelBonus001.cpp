#include <jp/ggaf/dxcore/util/GgafDxUtil.h>
#include "SpriteLabelBonus001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelBonus001::SpriteLabelBonus001(const char* prm_name) :
        FontSpriteActor(prm_name, "Ranking_16Font")
{
    _class_name = "SpriteLabelBonus001";
    setZEnableDraw(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //自身のZバッファを書き込みしないに強制
    setSpecialRenderDepthIndex(1); //描画順序を最前面描画に強制。
    setHitAble(false);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_BxyzMv); //XYZ軸ビルボード
    useProgress(PROG_BANPEI);
}

void SpriteLabelBonus001::onCreateModel() {
}

void SpriteLabelBonus001::initialize() {

}

void SpriteLabelBonus001::onDispatched(const GgafDxGeometricActor* prm_pOrgActor) {
    positionAs(prm_pOrgActor);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->takeoverMvFrom(prm_pOrgActor->getKuroko());
    pKuroko->setMvAcce(300);
    setAlpha(0.7);
    getProgress()->reset(PROG_INIT);
}

void SpriteLabelBonus001::processBehavior() {
    const Camera* const pCam = P_GOD->getSpacetime()->getCamera();
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_MOVE01: {
            //しばらく直進
            if (pProg->hasArrivedAt(60)) {
                //カメラに向かって方向転換1
                pKuroko->turnMvAngTwd(pCam,
                                      D_ANG(3), 0, TURN_CLOSE_TO, true);
            }
            if (pProg->hasArrivedAt(60+30)) {
                //カメラに向かって方向転換2
                pKuroko->turnMvAngTwd(pCam,
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

    pKuroko->behave();
}

SpriteLabelBonus001::~SpriteLabelBonus001() {
}

