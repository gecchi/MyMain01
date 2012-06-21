#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyStraightLaserChip001", STATUS(MyStraightLaserChip001)) {
    _class_name = "MyStraightLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    _veloMv = 100000;
}

void MyStraightLaserChip001::initialize() {
    _pKurokoA->setRzRyMvAng(0,0);
    registHitAreaCube(60000);
    setHitAble(true);
    _SX = _SY = _SZ = 5 * 1000;
    _alpha = 0.99;
    _bounding_sphere_radius = 20.0;
}

void MyStraightLaserChip001::processBehavior() {
    StraightLaserChip::processBehavior();
    //�������烌�[�U�[�\���̂��ߋ��G�ɍ��W�␳
    if (onChangeToActive()) {
        locateWith(P_MYSHIP);
    }
}

void MyStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}


void MyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    _pKurokoA->setMvVelo(80000);
    _pKurokoA->setMvAcce(300);
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
}

void MyStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;


    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        int stamina = UTIL::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����

            //�j�󂳂ꂽ�G�t�F�N�g
            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
            if (pExplo001) {
                pExplo001->locateWith(this);
            }
            sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            _pStatus->set(STAT_Stamina, default_stamina_);
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        //�j�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locateWith(this);
        }
        sayonara();
    }

}


MyStraightLaserChip001::~MyStraightLaserChip001() {
}

