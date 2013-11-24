#include "stdafx.h"
#include "SpriteLabelBonus001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelBonus001::SpriteLabelBonus001(const char* prm_name) :
        StringSpriteActor(prm_name, "Ranking_16Font")
{
    _class_name = "SpriteLabelBonus001";
    setZEnable(false);      //Zバッファは考慮無しに強制
    setZWriteEnable(false); //Zバッファは書き込み無しに強制
    setSpecialDrawDepth(1); //描画順序を最前面描画に強制。
    setHitAble(false);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_BxyzMv); //XYZ軸ビルボード
    useProgress(PROG_BANPEI);
}

void SpriteLabelBonus001::onCreateModel() {
}

void SpriteLabelBonus001::initialize() {

}

void SpriteLabelBonus001::onDispatched(GgafDxGeometricActor* prm_pOrgActor) {
    positionAs(prm_pOrgActor);
    _pKurokoA->takeoverMvFrom(prm_pOrgActor->_pKurokoA);
    _pKurokoA->setMvAcce(300);
    setAlpha(0.7);
    _pProg->reset(PROG_INIT);
}

void SpriteLabelBonus001::processBehavior() {

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->changeNext();
            break;
        }
        case PROG_MOVE01: {
            //しばらく直進
            if (_pProg->getFrameInProgress() == 60) {
                //カメラに向かって方向転換1
                _pKurokoA->turnMvAngTwd(P_CAM,
                                        D_ANG(3), 0, TURN_CLOSE_TO, true);
            }
            if (_pProg->getFrameInProgress() == 60+30) {
                //カメラに向かって方向転換2
                _pKurokoA->turnMvAngTwd(P_CAM,
                                        D_ANG(1), 0, TURN_CLOSE_TO, true);
            }

            if (ABS(P_CAM->_x - _x) < PX_C(200) ||  _pProg->getFrameInProgress() >= 60+30+120) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE02: {
            if (_pProg->isJustChanged()) {
            }
            addAlpha(-0.01);
            if (getAlpha() <= 0.0) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (_pProg->isJustChanged()) {
                sayonara();
                _pProg->changeNothing();
            }
            break;
        }
        default :
            break;
    }

    _pKurokoA->behave();
}

SpriteLabelBonus001::~SpriteLabelBonus001() {
}

