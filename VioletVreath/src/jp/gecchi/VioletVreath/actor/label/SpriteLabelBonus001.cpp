#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelBonus001::SpriteLabelBonus001(const char* prm_name) :
        StringSpriteActor(prm_name, "Gecchi_16Font")
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
    setAlpha(0.9);
}

void SpriteLabelBonus001::onActive() {
    _pKurokoA->setMvAng(P_CAM);
    _pKurokoA->setMvVelo(2000);
    _pKurokoA->setMvAcce(300);
}

void SpriteLabelBonus001::processBehavior() {
    _pKurokoA->behave();
    if (getActivePartFrame() == 60*5) {
        sayonara();
    }
}

void SpriteLabelBonus001::executeEffectBonus(int bonus_point) {
    std::string s = ITOS(bonus_point);
    update(s.c_str());
}

SpriteLabelBonus001::~SpriteLabelBonus001() {
}

