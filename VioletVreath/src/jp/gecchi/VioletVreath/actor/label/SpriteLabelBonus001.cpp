#include "stdafx.h"
#include "SpriteLabelBonus001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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
    setZEnable(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //Z�o�b�t�@�͏������ݖ����ɋ���
    setSpecialDrawDepth(1); //�`�揇�����őO�ʕ`��ɋ����B
    setHitAble(false);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_BxyzMv); //XYZ���r���{�[�h
    useProgress(PROG_BANPEI);
}

void SpriteLabelBonus001::onCreateModel() {
}

void SpriteLabelBonus001::initialize() {

}

void SpriteLabelBonus001::onDispatched(GgafDxGeometricActor* prm_pOrgActor) {
    positionAs(prm_pOrgActor);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->takeoverMvFrom(prm_pOrgActor->getKuroko());
    pKuroko->setMvAcce(300);
    setAlpha(0.7);
    getProgress()->reset(PROG_INIT);
}

void SpriteLabelBonus001::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_MOVE01: {
            //���΂炭���i
            if (pProg->getFrameInProgress() == 60) {
                //�J�����Ɍ������ĕ����]��1
                pKuroko->turnMvAngTwd(P_CAM,
                                        D_ANG(3), 0, TURN_CLOSE_TO, true);
            }
            if (pProg->getFrameInProgress() == 60+30) {
                //�J�����Ɍ������ĕ����]��2
                pKuroko->turnMvAngTwd(P_CAM,
                                        D_ANG(1), 0, TURN_CLOSE_TO, true);
            }

            if (ABS(P_CAM->_x - _x) < PX_C(200) ||  pProg->getFrameInProgress() >= 60+30+120) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE02: {
            if (pProg->isJustChanged()) {
            }
            addAlpha(-0.01);
            if (getAlpha() <= 0.0) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
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

