#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelBonus001::SpriteLabelBonus001(const char* prm_name) :
        StringSpriteActor(prm_name, "Ranking_16Font")
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

