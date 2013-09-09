#include "stdafx.h"
#include "MyStgUtil.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionWateringLaserChip001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int MyStgUtil::judgeMyAdvantage(actorkind attribute_my, actorkind attribute_enemy) {
    int ret = 0;
    if (attribute_my & ATTRIBUTE_GU) {
        if (attribute_enemy & ATTRIBUTE_CHOKI) {
            ret++;
        }
        if (attribute_enemy & ATTRIBUTE_PA) {
            ret--;
        }
    }

    if (attribute_my & ATTRIBUTE_CHOKI) {
        if (attribute_enemy & ATTRIBUTE_PA) {
            ret++;
        }
        if (attribute_enemy & ATTRIBUTE_GU) {
            ret--;
        }
    }

    if (attribute_my & ATTRIBUTE_PA) {
        if (attribute_enemy & ATTRIBUTE_GU) {
            ret++;
        }
        if (attribute_enemy & ATTRIBUTE_CHOKI) {
            ret--;
        }
    }
    return ret;
}

int MyStgUtil::judgeEnemyAdvantage(actorkind kattribute_enemy, actorkind attribute_my) {
    int ret = 0;
    if (kattribute_enemy & ATTRIBUTE_GU) {
        if (attribute_my & ATTRIBUTE_CHOKI) {
            ret++;
        }
        if (attribute_my & ATTRIBUTE_PA) {
            ret--;
        }
    }

    if (kattribute_enemy & ATTRIBUTE_CHOKI) {
        if (attribute_my & ATTRIBUTE_PA) {
            ret++;
        }
        if (attribute_my & ATTRIBUTE_GU) {
            ret--;
        }
    }

    if (kattribute_enemy & ATTRIBUTE_PA) {
        if (attribute_my & ATTRIBUTE_GU) {
            ret++;
        }
        if (attribute_my & ATTRIBUTE_CHOKI) {
            ret--;
        }
    }
    return ret;
}

int MyStgUtil::calcMyStamina(GgafMainActor* prm_pMy, GgafMainActor* prm_pOpp) {
    GgafStatus* pStatMy = prm_pMy->_pStatus;
    GgafStatus* pStatOpp = prm_pOpp->_pStatus;

    //�D���򐫔���
    int my_domi = MyStgUtil::judgeMyAdvantage(pStatMy->getUint(STAT_Attribute),
                                              pStatOpp->getUint(STAT_Attribute));
    //����(�G)�U����
    int opp_attack = pStatOpp->get(STAT_Attack);
    //�D���򐫂ɉ����Ėh�䗦���悸��
    if (my_domi > 0) {
        //�������D����
        return pStatMy->minus(STAT_Stamina,
                              (int)(opp_attack * pStatMy->getDouble(STAT_DominantDefenceRate)));
    } else if (my_domi < 0) {
        //�������򐫎�
        return pStatMy->minus(STAT_Stamina,
                              (int)(opp_attack * pStatMy->getDouble(STAT_RecessiveDefenceRate)));
    } else {
        //����(�G)�Ɠ��i��
        return pStatMy->minus(STAT_Stamina,
                              (int)(opp_attack * pStatMy->getDouble(STAT_DefaultDefenceRate)));
    }
}

int MyStgUtil::calcEnemyStamina(GgafMainActor* prm_pEnemy, GgafMainActor* prm_pOpp) {
    GgafStatus* pStatEnemy = prm_pEnemy->_pStatus;
    GgafStatus* pStatOpp = prm_pOpp->_pStatus;
    //�D���򐫔���
    int enemy_domi = MyStgUtil::judgeEnemyAdvantage(pStatEnemy->getUint(STAT_Attribute),
                                                    pStatOpp->getUint(STAT_Attribute));
    //����(���@)�U����
    int opp_attack = pStatOpp->get(STAT_Attack);
    //�D���򐫂ɉ����Ėh�䗦���悸��
    int enemy_stamina;
    if (enemy_domi > 0) {
        //�����i�G�j���D����
        enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                          (int)(opp_attack * pStatEnemy->getDouble(STAT_DominantDefenceRate)));
    } else if (enemy_domi < 0) {
        //�����i�G�j���򐫎�
        enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                          (int)(opp_attack * pStatEnemy->getDouble(STAT_RecessiveDefenceRate)));
    } else {
        //����(���@)�Ɠ��i��
        enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                          (int)(opp_attack * pStatEnemy->getDouble(STAT_DefaultDefenceRate)));
    }
    return enemy_stamina;
}

GgafDxDrawableActor* MyStgUtil::activateExplosionEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_ExplosionEffectKind)) {
        case 0: {
            pE = nullptr; //�����G�t�F�N�g����
            break;
        }
        case EF_EXPLOSION001: {
            pE = dispatchForceFromCommon(EffectExplosion001);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->_pKurokoA->takeoverMvFrom(prm_pActor->_pKurokoA);
            }
            break;
        }
        case EF_EXPLOSION002: {
            pE = dispatchForceFromCommon(EffectExplosion002);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->_pKurokoA->takeoverMvFrom(prm_pActor->_pKurokoA);
            }
            break;
        }
        case EF_EXPLOSION003: {
            pE = dispatchForceFromCommon(EffectExplosion003);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->_pKurokoA->takeoverMvFrom(prm_pActor->_pKurokoA);
            }
            break;
        }
        case EF_EXPLOSION001_STAY: {
            pE = dispatchForceFromCommon(EffectExplosion001);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->_pKurokoA->setMvVelo(0);
                pE->_pKurokoA->setMvAcce(0);
            }
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� ExplosionEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }
    if (pE) {
        //�o�����W��ݒ�

    }
    return pE;
}


GgafDxDrawableActor* MyStgUtil::activateDamagedEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_DamagedEffectKind)) {
        case 0: {
            pE = nullptr; //�����G�t�F�N�g����
            break;
        }
        case EF_DAMAGED001: {
            pE = dispatchFromCommon(EffectExplosion001);
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� DamagedEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

    if (pE) {
        //�o�����W��ݒ�
        pE->positionAs(prm_pActor);
        pE->_pKurokoA->takeoverMvFrom(prm_pActor->_pKurokoA);
    }
    return pE;
}
GgafDxDrawableActor* MyStgUtil::activateAttackShotOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_AttackShotKind)) {
        case 0: {
            pI = nullptr; //�V���b�g����
            break;
        }
        case SHOT_SMALL001: {
            pI = dispatchFromCommon(Shot004);
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� AttackShot ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //�o�����W��ݒ�
        pI->positionAs(prm_pActor);
    }
    return pI;
}


GgafDxDrawableActor* MyStgUtil::activateRevengeShotOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_RevengeShotKind)) {
        case 0: {
            pI = nullptr; //�V���b�g����
            break;
        }
        case SHOT_RV_NOMAL001: {
            pI = UTIL::shotWay002(
                   prm_pActor,
                   getCommonDepository(Shot004),
                   PX_C(20),       //r
                   RF_SHOT_RV_NOMAL001_ShotWay(G_RANK),    //way��
                   RF_SHOT_RV_NOMAL001_Density(G_RANK),    //way��way�̊Ԋu
                   RF_SHOT_RV_ShotMvVelo(G_RANK),          //�������x
                   RF_SHOT_RV_ShotMvAcce(G_RANK),          //�����x
                   RF_SHOT_RV_NOMAL001_ShotSetNum(G_RANK), //way�̃Z�b�g��
                   8, //�Z�b�g�ƃZ�b�g�̊Ԋu�t���[��
                   0.0f,
                   nullptr
                 );

            break;
        }

        case SHOT_RV_NOMAL002: {

            pI = UTIL::shotWay004(prm_pActor,
                                  getCommonDepository(Shot004),
                                  PX_C(20),
                                  8,
                                  D_ANG(10),
                                  RF_SHOT_RV_ShotMvVelo(G_RANK),
                                  RF_SHOT_RV_ShotMvAcce(G_RANK),
                                  12,
                                  3,
                                  0.9);


            break;
        }

        case SHOT_RV_GOLDEN_ANG_WAY: {
            MyShip* pM = P_MYSHIP;
            angle rz,ry;
            UTIL::convVectorToRzRy(pM->_X - prm_pActor->_X,
                                   pM->_Y - prm_pActor->_Y,
                                   pM->_Z - prm_pActor->_Z,
                                   rz, ry);

            pI = UTIL::shotWayGoldenAng(prm_pActor->_X,
                                        prm_pActor->_Y,
                                        prm_pActor->_Z,
                                        rz, ry,
                                        getCommonDepository(Shot004),
                                        PX_C(20),
                                        300,
                                        D_ANG(1), 100,
                                        2000, 200,
                                        2, 4, 0.9);

            break;
        }

        default: {
            throwGgafCriticalException("�Ή� RevengeShot ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
    }
    return pI;
}

GgafDxDrawableActor* MyStgUtil::activateItemOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_ItemKind)) {
        case 0: {
            pI = nullptr; //�A�C�e������
            break;
        }
        case ITEM_MP_SMALL: {
            pI = dispatchFromCommon(MagicPointItem001);
            break;
        }
        case ITEM_MP_MIDDLE: {
            pI = dispatchFromCommon(MagicPointItem002);
            break;
        }
        case ITEM_MP_LARGE: {
            pI = dispatchFromCommon(MagicPointItem003);
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� Item ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //�o�����W��ݒ�
        pI->positionAs(prm_pActor);
    }
    return pI;
}

GgafDxDrawableActor* MyStgUtil::activateDestroyedEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_DestroyedEffectKind)) {
        case 0: {
            pE = nullptr; //�����G�t�F�N�g����
            break;
        }
        case EF_BONUS001: {
            //�X�R�A���\���������ŃG�t�F�N�g
            SpriteLabelBonus001* pLabel = dispatchForceFromCommon(SpriteLabelBonus001);
            pLabel->onDispatched(prm_pActor); //�����ݒ肪�s����
            std::string s = XTOS(prm_pActor->_pStatus->get(STAT_AddDestroyScorePoint));
            pLabel->update(s.c_str()); //�j�󎞓��_���\�������
            pE = pLabel;
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� DestroyedEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

    if (pE) {
        //�o�����W��ݒ�
        pE->positionAs(prm_pActor);
        pE->_pKurokoA->takeoverMvFrom(prm_pActor->_pKurokoA);
    }
    return pE;
}

GgafDxDrawableActor* MyStgUtil::activateEntryEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pRet = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_EntryEffectKind)) {
        case 0: {
            pRet = nullptr; //����G�t�F�N�g����
            break;
        }
        case EF_ENTRY_SMALL001_LONG: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->positionFollow(prm_pActor);
                pE->config(30,120,60);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F30: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->positionFollow(prm_pActor);
                pE->config(15,1,15);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F60: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->positionFollow(prm_pActor);
                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_STAY_F30: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->positionFollow(nullptr);//�Ǐ]���������ɂƂǂ܂�
                pE->positionAs(prm_pActor);
                pE->config(15,1,15);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_STAY_F60: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->positionFollow(nullptr);//�Ǐ]���������ɂƂǂ܂�
                pE->positionAs(prm_pActor);
                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_MIDDLE001: {
            EffectEntry002* pE = dispatchFromCommon(EffectEntry002);
            if (pE) {
                pE->positionAs(prm_pActor);
//                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_LARGE001: {
            EffectEntry003* pE = dispatchFromCommon(EffectEntry003);
            if (pE) {
                pE->positionAs(prm_pActor);
//                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� EntryEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pRet = nullptr;
            break;
        }
    }
    if (pRet) {
    }
    return pRet;
}

GgafDxDrawableActor* MyStgUtil::activateLeaveEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pRet = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_LeaveEffectKind)) {
        case 0: {
            pRet = nullptr; //�ޏ�G�t�F�N�g����
            break;
        }
        case EF_LEAVE_SMALL001_F30: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->positionFollow(prm_pActor);
                pE->config(15,1,15);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_SMALL001_F60: {
            EffectEntry001* pE = dispatchFromCommon(EffectEntry001);
            if (pE) {
                pE->positionFollow(prm_pActor);
                pE->config(30,1,30);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_MIDDLE001: {
            EffectEntry002* pE = dispatchFromCommon(EffectEntry002);
            if (pE) {
                pE->positionFollow(prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_LARGE001: {
            EffectEntry003* pE = dispatchFromCommon(EffectEntry003);
            if (pE) {
                pE->positionFollow(prm_pActor);
            }
            pRet = pE;
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� LeaveEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pRet = nullptr;
            break;
        }
    }
    if (pRet) {
    }
    return pRet;
}

GgafDxDrawableActor* MyStgUtil::activateFormationDestroyedEffectOf(GgafDxGeometricActor* prm_pActor) {

    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedEffectKind)) {
        case 0: {
            pE = nullptr; //�G�t�F�N�g����
            break;
        }
        case EF_EXPLO_AND_BONUS001: {
            //1�͒ʏ�̃t�H�[���[�V�����{�[�i�X�X�R�A�\���G�t�F�N�g
            SpriteLabelBonus001* pLabel = dispatchForceFromCommon(SpriteLabelBonus001);
            pLabel->positionAs(prm_pActor);
            pLabel->_pKurokoA->takeoverMvFrom(prm_pActor->_pKurokoA);
            int addscore = prm_pActor->_pStatus->get(STAT_FormationDestroyedAddScorePoint); //�t�H�[���[�V�����S�œ��_
            std::string s = XTOS(addscore);
            pLabel->update(s.c_str());
            pE = pLabel;

            EffectTurbo002* pTurbo002 = dispatchForceFromCommon(EffectTurbo002);
            pTurbo002->positionAs(prm_pActor);
            pTurbo002->_pKurokoA->takeoverMvFrom(prm_pActor->_pKurokoA);
            break;
        }
//            case 2: {
//                pE = dispatchFromCommon(EffectExplosion002);
//                break;
//            }
//            case 3: {
//                pE = dispatchFromCommon(EffectExplosion003);
//                break;
//            }
        default: {
            throwGgafCriticalException("�Ή� FormationDestroyedEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

//        if (pE) {
//            //�o�����W��ݒ�
//            pE->positionAs(prm_pActor);
//            pE->_pKurokoA->takeoverMvFrom(prm_pActor->_pKurokoA);
//        }
    return pE;
}

GgafDxDrawableActor* MyStgUtil::activateFormationDestroyedItemOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedItemKind)) {
        case 0: {
            pI = nullptr; //�A�C�e������
            break;
        }
        case ITEM_MP_SMALL: {
            pI = dispatchFromCommon(MagicPointItem001);
            break;
        }
        case ITEM_MP_MIDDLE: {
            pI = dispatchFromCommon(MagicPointItem002);
            break;
        }
        case ITEM_MP_LARGE: {
            pI = dispatchFromCommon(MagicPointItem003);
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� FormationDestroyedItem ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //�o�����W��ݒ�
        pI->positionAs(prm_pActor);
    }
    return pI;
}

GgafDxDrawableActor* MyStgUtil::activateProperEffect01Of(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = nullptr;
    switch (prm_pActor->_pStatus->get(STAT_ProperEffect01Kind)) {
        case 0: {
            pE = nullptr; //�G�t�F�N�g����
            break;
        }
        case EF_TURBO: {
            //�^�[�{�G�t�F�N�g
            pE = dispatchFromCommon(EffectTurbo002);
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� ProperEffect01 ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }
    if (pE) {
        //�o�����W��ݒ�
        pE->positionAs(prm_pActor);
    }
    return pE;

}

bool MyStgUtil::proceedEnemyHit(GgafDxDrawableActor* prm_this, GgafDxGeometricActor* prm_pOther) {
    if (UTIL::calcEnemyStamina(prm_this, prm_pOther) <= 0) { //�̗͂������Ȃ�����
        //���j�󂳂ꂽ�ꍇ��
        prm_this->setHitAble(false); //�����蔻�����
        if (prm_pOther->getKind() & KIND_MY) {
            //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
            G_SCORE += prm_this->_pStatus->get(STAT_AddDestroyScorePoint);   //�j�󎞓��_
            G_RANK  += prm_this->_pStatus->getDouble(STAT_AddRankPoint);     //�����N���Z

            prm_this->notifyDestroyedToFormation();     //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����A�ƒʒm
            UTIL::activateItemOf(prm_this);             //�A�C�e���o��
            UTIL::activateDestroyedEffectOf(prm_this);  //���ꂽ�G�t�F�N�g
            if (prm_this->getPlatformScene()->instanceOf(Obj_RankUpStage)) {
                //�����N�A�b�v�X�e�[�W�̓G�Ȃ�΁A
                RankUpStage* pRankUpStage = (RankUpStage*)(prm_this->getPlatformScene());
                pRankUpStage->hit_enemy_num_ ++; //�����N�A�b�v�X�e�[�W�̓G�|������I�J�E���g�A�b�v
            }
        }
        UTIL::activateRevengeShotOf(prm_this);     //�ł��Ԃ��e
        UTIL::activateExplosionEffectOf(prm_this); //�����G�t�F�N�g
        prm_this->sayonara();
        return true;
    } else {
        //����j�󎞁A�_���[�W���󂯂��ꍇ��
        if (prm_pOther->getKind() & KIND_MY) { //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
            G_SCORE += prm_this->_pStatus->get(STAT_AddDamagedScorePoint);   //�_���[�W�����_
        }
        if (prm_this->_pStatus->get(STAT_FlushAble)) { //�_���[�W�t���b�V�����邩�ǂ���
            prm_this->effectFlush(2); //�t���b�V���I
        }
        UTIL::activateDamagedEffectOf(prm_this); //�_���[�W�G�t�F�N�g
        return false;
    }
}

GgafDxDrawableActor* MyStgUtil::proceedFormationDestroyAll(GgafDxDrawableActor* prm_pActor_last_destroyed) {
    //�ґ��S�Ŏ��{�[�i�X���Z
    G_SCORE += prm_pActor_last_destroyed->_pStatus->get(STAT_FormationDestroyedAddScorePoint);
    //�ґ��S�Ŏ��G�t�F�N�g�o��
    GgafDxDrawableActor* pEffect = UTIL::activateFormationDestroyedEffectOf(prm_pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(prm_pActor_last_destroyed);
    return pEffect;
}


// �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
// �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s�����ƁB
// gen02 start
GgafStatus* MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, (int)(105+((MyStraightLaserChip001::tex_no_*0.5)*100)));  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMyOptionWateringLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, (int)(105+((MyOptionWateringLaserChip001::tex_no_*0.5)*100)));  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMyOptionStraightLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 105 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMyTorpedoStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 1000 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMyTorpedoBlastStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMyShipStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000000000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 105 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyCurveLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 105 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEresStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEresShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 10 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 3000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaLaserChip002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaLaserChip003Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaLaserChip004Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOmulusStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 2000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmusStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 2000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmusLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEtisStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 20000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_GOLDEN_ANG_WAY);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyRisStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 20 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 200 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyGeriaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 20 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHaliaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL002);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 2 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetShot002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 3 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyIrceStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetShot003Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetShot004Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyRatislaviaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 9999999 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 1.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 1.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetWall001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 9999999 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 1.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 1.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetWall001PrismStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 9999999 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 1.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 1.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyAllasStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyUnomiaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMyShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 205 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmiliaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 4000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmiliaFragmentStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 2000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmiliaFragment2Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmiliaFragment3Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMyOptionStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMagicPointItem001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMagicPointItem002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetMagicPointItem003Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetScoreItem001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 500 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetVreathItem001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 500 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEbeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 10000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbe002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbeLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbeLaserChip002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbeLaserChip003Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyDrasteaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 20000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyTalanteStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEsperiaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 3000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION002);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEsperiaLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetTestGuStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_GU);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetTestChokiStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetTestPaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_PA);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetTestNomalStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetTestGuShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_GU);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetTestChokiShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetTestPaShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_PA);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetTestNomalShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyRatislaviaEyeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 2000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 3000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_LARGE);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyRatislaviaEyeStraightLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 105 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyErmioneStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 5000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 4000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyErmioneArmHeadStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyErmioneArmBodyStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyErmioneArmWeakStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 400 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyApphoStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyAntiopeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyDelheidStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 8000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyAlisanaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_LARGE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_LARGE001);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyIdaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 10000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 3000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyThagorasStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 10000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_LARGE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOrtunaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyGlajaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyGlajaLance001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyDunaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N
	p->set(STAT_AddRankPoint_Reduction, 0.50000 );  //�j�󎞉��Z�����N������
	p->set(STAT_Stamina, 400 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //����G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ��G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	return p;
}
// gen02 end
