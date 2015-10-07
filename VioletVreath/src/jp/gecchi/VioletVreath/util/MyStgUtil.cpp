#include "MyStgUtil.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

bool MyStgUtil::_was_MyStgUtil_inited_flg = false;
double MyStgUtil::SMOOTH_DV[3600+1];
angle MyStgUtil::GOLDEN_ANG[1000];

void MyStgUtil::init() {
    StgUtil::init();
    if (MyStgUtil::_was_MyStgUtil_inited_flg) {
        return;
    }

    //�����p�z��
    for (int n = 0; n < 1000; n++) {
        // �Ƃ͉����p
        // 1 : (1+��5) / 2 = 2��-�� : ��
        // 2��-�� = { (1+��5) / 2 } ��
        // (2��-��) / �� = (1+��5) / 2
        // (2��/��) - 1 = (1+��5) / 2
        // 2��/�� = 1 + {(1+��5) / 2}
        // 2�� =  ( 1 + {(1+��5) / 2} ) ��
        // �� = 2��/ ( 1 + {(1+��5) / 2} )
        double n_theta = n * ( PI2 / ( 1.0 + ((1.0+sqrt(5.0))/2.0) ) );
        //�W����
        while (n_theta >= PI2) {
            n_theta -= PI2;
        }
        while (n_theta < 0) {
            n_theta += PI2;
        }
        GOLDEN_ANG[n] = (angle)(D360ANG*n_theta / PI2);
        //_TRACE_("GOLDEN_ANG["<<n<<"]="<<GOLDEN_ANG[n]);
    }

    // v = 1 - cos(2��t)�̉��e�[�u��
    for (int i = 0; i <= 3600; i++) {
        double t = double(i / 3600.0);
        //D = 1 - cos(2��t)
        SMOOTH_DV[i] = 1.0 - cos(2.0*PI*t);
    }


    MyStgUtil::_was_MyStgUtil_inited_flg = true;
}

GgafDxFigureActor* MyStgUtil::shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                               angle prm_rz, angle prm_ry,
                                               GgafActorDepository* prm_pDepo_shot,
                                               coord prm_r,
                                               int prm_way_num,
                                               angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                               velo prm_velo_first, acce prm_acce,
                                               int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                               void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int)) {
    if (prm_way_num <= 0 || prm_set_num <= 0) {  return nullptr;  }
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_way_num];
    angle expanse_rz = (D180ANG - prm_first_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RzRy(GgafDxUtil::simplifyAng(prm_rz-D90ANG),prm_ry, matWorldRot);

    float vx, vy, vz;
    float tx, ty, tz; //�ŏI�����̐�΍��W�̒P�ʃx�N�g��
    for (int i = 0; i < prm_way_num; i++) {
        GgafDxUtil::convRzRyToVector(expanse_rz, GOLDEN_ANG[i], vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                     paGeo[i].rz, paGeo[i].ry);
        expanse_rz -= (prm_inc_expanse_angle/2);
    }
    GgafDxFigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_num; i++) {
            pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->position(prm_x + paGeo[i].x,
                                      prm_y + paGeo[i].y,
                                      prm_z + paGeo[i].z);
                pActor_shot->getKuroko()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getKuroko()->setMvVelo(now_velo);
                pActor_shot->getKuroko()->setMvAcce(now_acce);
//                pActor_shot->_rz = Rz;
//                pActor_shot->_ry = Ry;
                if (pFunc_call_back_dispatched) {
                    pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paGeo);
    return pActor_shot;
}

GgafDxFigureActor* MyStgUtil::shotWayGoldenAng(GgafDxGeometricActor* prm_pFrom,
                                               GgafActorDepository* prm_pDepo_shot,
                                               coord prm_r,
                                               int prm_way_num,
                                               angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                               velo prm_velo_first, acce prm_acce,
                                               int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                               void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int)) {
    return shotWayGoldenAng(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                            prm_pFrom->_rz, prm_pFrom->_ry,
                            prm_pDepo_shot,
                            prm_r,
                            prm_way_num,
                            prm_first_expanse_angle, prm_inc_expanse_angle,
                            prm_velo_first, prm_acce,
                            prm_set_num, prm_interval_frames, prm_attenuated,
                            pFunc_call_back_dispatched);
}



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

int MyStgUtil::calcMyStamina(GgafMainActor* prm_pMy, const GgafMainActor* const prm_pOpp) {
    GgafStatus* pStatMy = prm_pMy->getStatus();
    const GgafStatus* pStatOpp = prm_pOpp->getStatus();

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

int MyStgUtil::calcEnemyStamina(GgafMainActor* prm_pEnemy, const GgafMainActor* const prm_pOpp) {
    GgafStatus* pStatEnemy = prm_pEnemy->getStatus();
    const GgafStatus* pStatOpp = prm_pOpp->getStatus();
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

GgafDxFigureActor* MyStgUtil::activateExplosionEffectOf(const GgafDxGeometricActor* const prm_pActor) {
    GgafDxFigureActor* pE = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_ExplosionEffectKind)) {
        case 0: {
            pE = nullptr; //�����G�t�F�N�g����
            break;
        }
        case EF_EXPLOSION001: {
            pE = dispatchForceFromCommon(EffectExplosion001);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->getKuroko()->takeoverMvFrom(prm_pActor->getKuroko());
            }
            break;
        }
        case EF_EXPLOSION002: {
            pE = dispatchForceFromCommon(EffectExplosion002);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->getKuroko()->takeoverMvFrom(prm_pActor->getKuroko());
            }
            break;
        }
        case EF_EXPLOSION003: {
            pE = dispatchForceFromCommon(EffectExplosion003);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->getKuroko()->takeoverMvFrom(prm_pActor->getKuroko());
            }
            break;
        }
        case EF_EXPLOSION001_STAY: {
            pE = dispatchForceFromCommon(EffectExplosion001);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->getKuroko()->setMvVelo(0);
                pE->getKuroko()->setMvAcce(0);
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


GgafDxFigureActor* MyStgUtil::activateDamagedEffectOf(const GgafDxGeometricActor* const prm_pActor) {
    GgafDxFigureActor* pE = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_DamagedEffectKind)) {
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
        pE->getKuroko()->takeoverMvFrom(prm_pActor->getKuroko());
    }
    return pE;
}
GgafDxFigureActor* MyStgUtil::activateAttackShotOf(const GgafDxGeometricActor* const prm_pActor) {
    GgafDxFigureActor* pI = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_AttackShotKind)) {
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

GgafActorDepository* MyStgUtil::getDepositoryOf(const GgafDxGeometricActor* const prm_pActor) {
    GgafActorDepository* pDepo = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_DepositoryKind)) {
        case 0: {
            pDepo = nullptr; //����
            break;
        }
        case DEPO_LASER001: {
            pDepo = (GgafActorDepository*)(P_COMMON_SCENE->pStore_EnemyWateringLaser001_->dispatch());
            break;
        }
        case DEPO_LASER002: {
            pDepo = (GgafActorDepository*)(P_COMMON_SCENE->pStore_EnemyStraightLaser001_->dispatch());
            break;
        }
        default: {
            throwGgafCriticalException("�Ή� DepositoryKind ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pDepo = nullptr;
            break;
        }
    }
    return pDepo;
}


GgafDxFigureActor* MyStgUtil::activateRevengeShotOf(const GgafDxGeometricActor* const prm_pActor) {
    GgafDxFigureActor* pI = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_RevengeShotKind)) {
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
            UTIL::convVectorToRzRy(pM->_x - prm_pActor->_x,
                                   pM->_y - prm_pActor->_y,
                                   pM->_z - prm_pActor->_z,
                                   rz, ry);

            pI = UTIL::shotWayGoldenAng(prm_pActor->_x,
                                        prm_pActor->_y,
                                        prm_pActor->_z,
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

GgafDxFigureActor* MyStgUtil::activateItemOf(const GgafDxGeometricActor* const prm_pActor) {
    GgafDxFigureActor* pI = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_ItemKind)) {
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

GgafDxFigureActor* MyStgUtil::activateDestroyedEffectOf(const GgafDxGeometricActor* const prm_pActor) {
    GgafDxFigureActor* pE = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_DestroyedEffectKind)) {
        case 0: {
            pE = nullptr; //�����G�t�F�N�g����
            break;
        }
        case EF_BONUS001: {
            //�X�R�A���\���������ŃG�t�F�N�g
            SpriteLabelBonus001* pLabel = dispatchForceFromCommon(SpriteLabelBonus001);
            pLabel->onDispatched(prm_pActor); //�����ݒ肪�s����
            std::string s = XTOS(prm_pActor->getStatus()->get(STAT_AddDestroyScorePoint));
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
        pE->getKuroko()->takeoverMvFrom(prm_pActor->getKuroko());
    }
    return pE;
}

EffectBlink* MyStgUtil::activateEntryEffectOf(const GgafDxGeometricActor* const prm_pActor) {
    EffectBlink* pRet = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_EntryEffectKind)) {
        case EF_ENTRY_SMALL001_LONG: { //EffectBlink001��210F�B�A�N�^�[�ɒǏ]����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->blink(30, 120, 60, prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F30: { //EffectBlink001��30F�B�A�N�^�[�ɒǏ]����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->blink(12, 6, 12, prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F60: { //EffectBlink001��60F�B�A�N�^�[�ɒǏ]����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->blink(25, 10, 25, prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_F90: { //EffectBlink001��60F�B�A�N�^�[�ɒǏ]����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->blink(35, 20, 35, prm_pActor);
            }
            pRet = pE;
            break;
        }

        case EF_ENTRY_SMALL001_STAY_F30: { //EffectBlink001��60F�B���̏�ɂƂǂ܂�A�A�N�^�[�Ǐ]�����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->blink(12, 6, 12, nullptr);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_STAY_F60: {  //EffectBlink001��60F�B���̏�ɂƂǂ܂�A�A�N�^�[�Ǐ]�����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->blink(25, 10, 25, nullptr);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_STAY_F90: {  //EffectBlink001��60F�B���̏�ɂƂǂ܂�A�A�N�^�[�Ǐ]�����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->positionAs(prm_pActor);
                pE->blink(35, 20, 35, nullptr);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_MIDDLE001: {  //EffectBlink002��180F�B�A�N�^�[�ɒǏ]����B
            EffectBlink002* pE = dispatchForceFromCommon(EffectBlink002);
            if (pE) {
                pE->blink(60, 60, 60, prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_LARGE001: {
            EffectBlink003* pE = dispatchForceFromCommon(EffectBlink003);
            if (pE) {
                pE->blink(60, 60, 60, prm_pActor);
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
    if (!pRet) {
        throwGgafCriticalException("MyStgUtil::activateEntryEffectOf() �G�t�F�N�g���擾�ł��Ă��Ȃ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
    }
    return pRet;
}

EffectBlink* MyStgUtil::activateLeaveEffectOf(const GgafDxGeometricActor* const prm_pActor) {
    EffectBlink* pRet = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_LeaveEffectKind)) {
        case EF_LEAVE_SMALL001_F30: {
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->blink(10, 1, 20, prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_SMALL001_F60: {
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->blink(20, 0, 40, prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_SMALL001_F90: {
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->blink(30, 0, 60, prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_MIDDLE001: {
            EffectBlink002* pE = dispatchForceFromCommon(EffectBlink002);
            if (pE) {
                pE->blink(20, 0, 40, prm_pActor);
            }
            pRet = pE;
            break;
        }
        case EF_LEAVE_LARGE001: {
            EffectBlink003* pE = dispatchForceFromCommon(EffectBlink003);
            if (pE) {
                pE->blink(20, 0, 40, prm_pActor);
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
    if (!pRet) {
        throwGgafCriticalException("MyStgUtil::activateLeaveEffectOf() �G�t�F�N�g���擾�ł��Ă��Ȃ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
    }
    return pRet;
}

GgafDxFigureActor* MyStgUtil::activateFormationDestroyedEffectOf(const GgafDxGeometricActor* const prm_pActor) {

    GgafDxFigureActor* pE = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_FormationDestroyedEffectKind)) {
        case 0: {
            pE = nullptr; //�G�t�F�N�g����
            break;
        }
        case EF_EXPLO_AND_BONUS001: {
            //1�͒ʏ�̃t�H�[���[�V�����{�[�i�X�X�R�A�\���G�t�F�N�g
            SpriteLabelBonus001* pLabel = dispatchForceFromCommon(SpriteLabelBonus001);
            pLabel->onDispatched(prm_pActor); //�����ݒ肪�s����
            pLabel->positionAs(prm_pActor);
            pLabel->getKuroko()->takeoverMvFrom(prm_pActor->getKuroko());
            int addscore = prm_pActor->getStatus()->get(STAT_FormationDestroyedAddScorePoint); //�t�H�[���[�V�����S�œ��_
            std::string s = XTOS(addscore);
            pLabel->update(s.c_str());
            pE = pLabel;

            EffectTurbo002* pTurbo002 = dispatchForceFromCommon(EffectTurbo002);
            pTurbo002->positionAs(prm_pActor);
            pTurbo002->getKuroko()->takeoverMvFrom(prm_pActor->getKuroko());
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
//            pE->getKuroko()->takeoverMvFrom(prm_pActor->getKuroko());
//        }
    return pE;
}

GgafDxFigureActor* MyStgUtil::activateFormationDestroyedItemOf(const GgafDxGeometricActor* const prm_pActor) {
    GgafDxFigureActor* pI = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_FormationDestroyedItemKind)) {
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

GgafDxFigureActor* MyStgUtil::activateProperEffect01Of(const GgafDxCore::GgafDxGeometricActor* const prm_pActor) {
    GgafDxFigureActor* pE = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_ProperEffect01Kind)) {
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

bool MyStgUtil::transactEnemyHit(GgafDxFigureActor* prm_this, const GgafDxGeometricActor* const prm_pOther) {
    GgafStatus* pThisStatus  = prm_this->getStatus();
    if (UTIL::calcEnemyStamina(prm_this, prm_pOther) <= 0) { //�̗͂������Ȃ�����
        //���j�󂳂ꂽ�ꍇ��
        prm_this->setHitAble(false); //�����蔻�����
        if (prm_pOther->_pGroupHead->_kind & KIND_MY) {
            //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
            G_SCORE += pThisStatus->get(STAT_AddDestroyScorePoint);   //�j�󎞓��_
            double rp = pThisStatus->getDouble(STAT_AddRankPoint);    //���Z���������N�l
            if (!ZEROd_EQ(rp)) {
                double rp_r = pThisStatus->getDouble(STAT_AddRankPoint_Reduction); //���t���[���̃����N������
                if (ZEROd_EQ(rp_r)) {
                    //�Ȃɂ����Ȃ�
                } else if (ONEd_EQ(rp_r)) {
                    G_RANK  += rp; //��������1.0�Ȃ�΁A���̂܂܉��Z���������N�l���v���X
                } else if (rp_r > 0) {
                    frame n = prm_this->getActiveFrame();   //�ғ��t���[��
                    G_RANK  += (rp * pow(rp_r, (double)n)); //rp * (rp_r ^ n)  �����N���Z
                } else {
                    //�Ȃɂ����Ȃ�
                }
            }
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
        return true;
    } else {
        //����j�󎞁A�_���[�W���󂯂��ꍇ��
        if (prm_pOther->_pGroupHead->_kind & KIND_MY) { //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
            G_SCORE += pThisStatus->get(STAT_AddDamagedScorePoint);   //�_���[�W�����_
        }
        if (pThisStatus->get(STAT_FlushAble)) { //�_���[�W�t���b�V�����邩�ǂ���
            prm_this->effectFlush(2); //�t���b�V���I
        }
        UTIL::activateDamagedEffectOf(prm_this); //�_���[�W�G�t�F�N�g
        return false;
    }
}

GgafDxFigureActor* MyStgUtil::transactFormationDestroyAll(const GgafDxFigureActor* const prm_pActor_last_destroyed) {
    //�ґ��S�Ŏ��{�[�i�X���Z
    G_SCORE += prm_pActor_last_destroyed->getStatus()->get(STAT_FormationDestroyedAddScorePoint);
    //�ґ��S�Ŏ��G�t�F�N�g�o��
    GgafDxFigureActor* pEffect = UTIL::activateFormationDestroyedEffectOf(prm_pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(prm_pActor_last_destroyed);
    return pEffect;
}


// �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
// �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s�����ƁB
// gen02 start
GgafStatus* MyStgUtil::resetMyShipStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 600000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 205 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMySnipeShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 305 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyMagicEnergyCoreStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_NOTHING);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, (int)(105+((MyStraightLaserChip001::tex_no_*0.5)*100)));  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyBunshinStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyBunshinShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 205 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyBunshinSnipeShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 305 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyBunshinWateringLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, (int)(105+((MyBunshinWateringLaserChip001::tex_no_*0.5)*100)));  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyTorpedoStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 1000 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMyTorpedoBlastStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_EXPLOSION001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 2 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetShot002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 3 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetShot003Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetShot004Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 105 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyWateringLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 105 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEresStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEresShot001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 10 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 3000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_MIDDLE001);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaLaserChip002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaLaserChip003Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyStraeaLaserChip004Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOmulusStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 2000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmusStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 2000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_LASER001);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmusLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEtisStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 20000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_MIDDLE);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_GOLDEN_ANG_WAY);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyRisStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 20 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 200 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyGeriaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 20 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F60);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHaliaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F90);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL002);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyIrceStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyRatislaviaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 9999999 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 1.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 1.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetWall001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 9999999 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 1.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 1.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetWall001PrismStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 9999999 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 1.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 1.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyAllasStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyUnomiaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmiliaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 4000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmiliaFragmentStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 2000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmiliaFragment2Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEmiliaFragment3Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMagicPointItem001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMagicPointItem002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetMagicPointItem003Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetScoreItem001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 500 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetVreathItem001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 500 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 0 );  //�̗�
	p->set(STAT_Attack, 0 );  //�U����
	p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEbeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 10000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbe002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbeLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbeLaserChip002Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyHisbeLaserChip003Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyDrasteaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 20000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyTalanteStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEsperiaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 3000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_MIDDLE001);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION002);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyEsperiaLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetTestGuStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_GU);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetTestChokiStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetTestPaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_PA);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetTestNomalStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetTestGuShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_GU);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetTestChokiShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetTestPaShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_PA);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetTestNomalShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyRatislaviaEyeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 2000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 3000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_LARGE);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyRatislaviaEyeStraightLaserChip001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 105 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyErmioneStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 5000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 4000 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyErmioneArmHeadStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_LASER001);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyErmioneArmBodyStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 9999999 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyErmioneArmWeakStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 400 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_TURBO);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyApphoStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_LONG);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyAntiopeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyDelheidStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 8000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyAlisanaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_LARGE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_LARGE001);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyIdaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 10000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 3000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyThagorasStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 10000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_LARGE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOrtunaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyGlajaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyGlajaLance001Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyDunaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 400 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_MIDDLE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_SMALL001);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_RV_NOMAL001);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOzartiaStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 5000 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 100 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 50000 );  //�̗�
	p->set(STAT_Attack, 300 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_LARGE001);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_DAMAGED001);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_LARGE);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOzartiaShot01Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 5000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_MP_SMALL);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOzartiaLaserChip01Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 105 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001_STAY);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOzartiaPillar01Status(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 1000 );  //�̗�
	p->set(STAT_Attack, 1000 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_NOTHING);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOebiusStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 10000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_LARGE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyOebiusCoreStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 5000 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_MIDDLE001);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_MIDDLE001);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION003);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 10000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_LARGE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetEnemyUrydikeStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 99 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_BONUS001);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 10000 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_EXPLO_AND_BONUS001);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_MP_LARGE);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
GgafStatus* MyStgUtil::resetAliceShotStatus(GgafStatus* p) {
	p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
	p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
	p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
	p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
	p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
	p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
	p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
	p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���t���[���̉��Z�����N������
	p->set(STAT_Stamina, 100 );  //�̗�
	p->set(STAT_Attack, 100 );  //�U����
	p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
	p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
	p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
	p->set(STAT_EntryEffectKind, EF_NOTHING);  //�o���G�t�F�N�g���
	p->set(STAT_LeaveEffectKind, EF_NOTHING);  //�ޏo�G�t�F�N�g���
	p->set(STAT_ExplosionEffectKind, EF_EXPLOSION001);  //�����G�t�F�N�g���
	p->set(STAT_DamagedEffectKind, EF_NOTHING);  //�_���[�W�G�t�F�N�g���
	p->set(STAT_DestroyedEffectKind, EF_NOTHING);  //�������G�t�F�N�g���
	p->set(STAT_ItemKind, ITEM_NOTHING);  //����A�C�e�����
	p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
	p->set(STAT_FormationDestroyedEffectKind, EF_NOTHING);  //�ґ��S�Ŏ�����G�t�F�N�g
	p->set(STAT_ProperEffect01Kind, EF_NOTHING);  //���̑��ŗL�G�t�F�N�g�O�P
	p->set(STAT_FormationDestroyedItemKind, ITEM_NOTHING);  //�ґ��S�Ŏ��A�C�e�����
	p->set(STAT_AttackShotKind, SHOT_NOTHING);  //�ʏ�V���b�g���
	p->set(STAT_RevengeShotKind, SHOT_NOTHING);  //�ł��Ԃ����
	p->set(STAT_DepositoryKind, DEPO_NOTHING);  //�f�|�W�g�����
	return p;
}
// gen02 end
