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
            //���΂炭���i
            if (_pProg->getFrameInProgress() == 60) {
                //�J�����Ɍ������ĕ����]��1
                _pKurokoA->turnMvAngTwd(P_CAM,
                                        D_ANG(3), 0, TURN_CLOSE_TO, true);
            }
            if (_pProg->getFrameInProgress() == 60+30) {
                //�J�����Ɍ������ĕ����]��2
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

