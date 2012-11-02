#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelBonus001::SpriteLabelBonus001(const char* prm_name) :
        StringSpriteActor(prm_name, "Gecchi_16Font")
{
    _class_name = "SpriteLabelBonus001";
    setZEnable(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //Z�o�b�t�@�͏������ݖ����ɋ���
    setSpecialDrawDepth(1); //�`�揇�����őO�ʕ`��ɋ����B
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //XYZ���r���{�[�h
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

