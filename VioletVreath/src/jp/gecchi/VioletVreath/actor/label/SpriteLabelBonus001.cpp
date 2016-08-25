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
    setZEnableDraw(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ��ɋ���
    setSpecialRenderDepthIndex(1); //�`�揇�����őO�ʕ`��ɋ����B
    setHitAble(false);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_BxyzMv); //XYZ���r���{�[�h
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
            //���΂炭���i
            if (pProg->hasArrivedAt(60)) {
                //�J�����Ɍ������ĕ����]��1
                pKuroko->turnMvAngTwd(pCam,
                                      D_ANG(3), 0, TURN_CLOSE_TO, true);
            }
            if (pProg->hasArrivedAt(60+30)) {
                //�J�����Ɍ������ĕ����]��2
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

