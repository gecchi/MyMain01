#include "stdafx.h"
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
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //XYZ軸ビルボード
}

void SpriteLabelBonus001::onCreateModel() {
}

void SpriteLabelBonus001::initialize() {

}

void SpriteLabelBonus001::onActive() {
    _pKurokoA->turnMvAngTwd(P_CAM,
                            D_ANG(5), 0, TURN_CLOSE_TO, true);
    _pKurokoA->setMvAcce(300);
    setAlpha(0.99);
}

void SpriteLabelBonus001::processBehavior() {
    if (getActivePartFrame() > 60*10) {
        addAlpha(-0.01);
        if (getAlpha() <= 0.0) {
            sayonara();
        }
    }
    _pKurokoA->behave();
}

SpriteLabelBonus001::~SpriteLabelBonus001() {
}

