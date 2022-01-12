#include "MyStgUtil.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

bool MyStgUtil::_was_MyStgUtil_inited_flg = false;
double MyStgUtil::SMOOTH_DV[3600+1];
angle MyStgUtil::GOLDEN_ANG[1000];
double MyStgUtil::SHOT_POWER[300+1];

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

    for (int f = 0; f <= 300; f++) {
        double x = (double)f;
        SHOT_POWER[f] = (3.0 / ( (x/5.0) + 1 ) ) + 0.5;
    }


    MyStgUtil::_was_MyStgUtil_inited_flg = true;
}

GgafDx::FigureActor* MyStgUtil::shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                                  angle prm_rz, angle prm_ry,
                                                  GgafCore::ActorDepository* prm_pDepo_shot,
                                                  coord prm_r,
                                                  int prm_way_num,
                                                  angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                  velo prm_velo_first, acce prm_acce,
                                                  int prm_draw_set_num, frame prm_interval_frames, float prm_attenuated,
                                                  void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    if (prm_way_num <= 0 || prm_draw_set_num <= 0) {  return nullptr;  }
    GgafDx::GeoElem* paGeo = NEW GgafDx::GeoElem[prm_way_num];
    angle expanse_rz = (D180ANG - prm_first_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDx::Util::setWorldMatrix_RzRy(GgafDx::Util::simplifyAng(prm_rz-D90ANG),prm_ry, matWorldRot);

    float vx, vy, vz;
    float tx, ty, tz; //�ŏI�����̐�΍��W�̒P�ʃx�N�g��
    for (int i = 0; i < prm_way_num; i++) {
        GgafDx::Util::convRzRyToVector(expanse_rz, GOLDEN_ANG[i], vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDx::Util::convVectorToRzRy(tx, ty, tz,
                                     paGeo[i].rz, paGeo[i].ry);
        expanse_rz -= (prm_inc_expanse_angle/2);
    }
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_draw_set_num; n++) {
        for (int i = 0; i < prm_way_num; i++) {
            pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                      prm_y + paGeo[i].y,
                                      prm_z + paGeo[i].z);
                pActor_shot->getVecDriver()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getVecDriver()->setMvVelo(now_velo);
                pActor_shot->getVecDriver()->setMvAcce(now_acce);
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

GgafDx::FigureActor* MyStgUtil::shotWayGoldenAng(GgafDx::GeometricActor* prm_pFrom,
                                                  GgafCore::ActorDepository* prm_pDepo_shot,
                                                  coord prm_r,
                                                  int prm_way_num,
                                                  angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                  velo prm_velo_first, acce prm_acce,
                                                  int prm_draw_set_num, frame prm_interval_frames, float prm_attenuated,
                                                  void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    return shotWayGoldenAng(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                            prm_pFrom->_rz, prm_pFrom->_ry,
                            prm_pDepo_shot,
                            prm_r,
                            prm_way_num,
                            prm_first_expanse_angle, prm_inc_expanse_angle,
                            prm_velo_first, prm_acce,
                            prm_draw_set_num, prm_interval_frames, prm_attenuated,
                            pFunc_call_back_dispatched);
}



int MyStgUtil::judgeMyAdvantage(kind_t attribute_my, kind_t attribute_enemy) {
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

int MyStgUtil::judgeEnemyAdvantage(kind_t kattribute_enemy, kind_t attribute_my) {
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

int MyStgUtil::calcMyStamina(GgafCore::MainActor* prm_pMy, const GgafCore::MainActor* const prm_pOpp) {
    GgafCore::Status* pStatMy = prm_pMy->getStatus();
    const GgafCore::Status* pStatOpp = prm_pOpp->getStatus();

    //�D���򐫔���
    int my_domi = MyStgUtil::judgeMyAdvantage(pStatMy->getUint(STAT_Attribute),
                                              pStatOpp->getUint(STAT_Attribute));
    //����(�G)�U����
    int opp_attack = pStatOpp->get(STAT_Attack) * pStatOpp->getDouble(STAT_AttackPowerRate);
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

int MyStgUtil::calcEnemyStamina(GgafCore::MainActor* prm_pEnemy, const GgafCore::MainActor* const prm_pOpp) {
    GgafCore::Status* pStatEnemy = prm_pEnemy->getStatus();
    const GgafCore::Status* pStatOpp = prm_pOpp->getStatus();
    //�D���򐫔���
    int enemy_domi = MyStgUtil::judgeEnemyAdvantage(pStatEnemy->getUint(STAT_Attribute),
                                                    pStatOpp->getUint(STAT_Attribute));
    //����(���@)�U����
    int opp_attack = pStatOpp->get(STAT_Attack) * pStatOpp->getDouble(STAT_AttackPowerRate);
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

GgafDx::FigureActor* MyStgUtil::activateExplosionEffectOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pE = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_ExplosionEffectKind)) {
        case 0: {
            pE = nullptr; //�����G�t�F�N�g����
            break;
        }
        case EF_EXPLOSION001: {
            pE = dispatchForceFromCommon(EffectExplosion001);
            if (pE) {
                if (pE->isActiveInTheTree()) {
                    pE->onInactive();
                    pE->_frame_of_behaving_since_onActive = 1;
                    pE->onActive();
                }
                pE->setPositionAt(prm_pActor);
                pE->getVecDriver()->takeoverMvFrom(prm_pActor->getVecDriver());
            }
            break;
        }
        case EF_EXPLOSION002: {
            pE = dispatchForceFromCommon(EffectExplosion002);
            if (pE) {
                pE->setPositionAt(prm_pActor);
                pE->getVecDriver()->takeoverMvFrom(prm_pActor->getVecDriver());
            }
            break;
        }
        case EF_EXPLOSION003: {
            pE = dispatchForceFromCommon(EffectExplosion003);
            if (pE) {
                pE->setPositionAt(prm_pActor);
                pE->getVecDriver()->takeoverMvFrom(prm_pActor->getVecDriver());
            }
            break;
        }
        case EF_EXPLOSION001_STAY: {
            pE = dispatchForceFromCommon(EffectExplosion001);
            if (pE) {
                pE->setPositionAt(prm_pActor);
                pE->getVecDriver()->setMvVelo(0);
                pE->getVecDriver()->setMvAcce(0);
            }
            break;
        }
        default: {
            throwCriticalException("�Ή� ExplosionEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }
    if (pE) {
        //�o�����W��ݒ�

    }
    return pE;
}


GgafDx::FigureActor* MyStgUtil::activateDamagedEffectOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pE = nullptr;
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
            throwCriticalException("�Ή� DamagedEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

    if (pE) {
        //�o�����W��ݒ�
        pE->setPositionAt(prm_pActor);
        pE->getVecDriver()->takeoverMvFrom(prm_pActor->getVecDriver());
    }
    return pE;
}
GgafDx::FigureActor* MyStgUtil::activateAttackShotOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pI = nullptr;
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
            throwCriticalException("�Ή� AttackShot ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //�o�����W��ݒ�
        pI->setPositionAt(prm_pActor);
    }
    return pI;
}

GgafCore::ActorDepository* MyStgUtil::getDepositoryOf(GgafDx::GeometricActor* prm_pActor) {
    GgafCore::ActorDepository* pDepo = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_DepositoryKind)) {
        case 0: {
            pDepo = nullptr; //����
            break;
        }
        case DEPO_LASER001: {
            pDepo = dispatchFromCommonDepositoryStore(EnemyWateringLaserChip001);
            break;
        }
        case DEPO_LASER002: {
            pDepo = dispatchFromCommonDepositoryStore(EnemyStraightLaserChip001);
            break;
        }
        default: {
            throwCriticalException("�Ή� DepositoryKind ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pDepo = nullptr;
            break;
        }
    }
    return pDepo;
}


GgafDx::FigureActor* MyStgUtil::activateRevengeShotOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pI = nullptr;
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
            MyShip* pM = pMYSHIP;
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
            throwCriticalException("�Ή� RevengeShot ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
    }
    return pI;
}

GgafDx::FigureActor* MyStgUtil::activateItemOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pI = nullptr;
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
            throwCriticalException("�Ή� Item ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //�o�����W��ݒ�
        pI->setPositionAt(prm_pActor);
    }
    return pI;
}

GgafDx::FigureActor* MyStgUtil::activateDestroyedEffectOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pE = nullptr;
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
            throwCriticalException("�Ή� DestroyedEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

    if (pE) {
        //�o�����W��ݒ�
        pE->setPositionAt(prm_pActor);
        pE->getVecDriver()->takeoverMvFrom(prm_pActor->getVecDriver());
    }
    return pE;
}

EffectBlink* MyStgUtil::activateEntryEffectOf(GgafDx::GeometricActor* prm_pActor) {
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
                pE->setPositionAt(prm_pActor);
                pE->blink(12, 6, 12, nullptr);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_STAY_F60: {  //EffectBlink001��60F�B���̏�ɂƂǂ܂�A�A�N�^�[�Ǐ]�����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->setPositionAt(prm_pActor);
                pE->blink(25, 10, 25, nullptr);
            }
            pRet = pE;
            break;
        }
        case EF_ENTRY_SMALL001_STAY_F90: {  //EffectBlink001��60F�B���̏�ɂƂǂ܂�A�A�N�^�[�Ǐ]�����B
            EffectBlink001* pE = dispatchForceFromCommon(EffectBlink001);
            if (pE) {
                pE->setPositionAt(prm_pActor);
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
            throwCriticalException("�Ή� EntryEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pRet = nullptr;
            break;
        }
    }
    if (!pRet) {
        throwCriticalException("�G�t�F�N�g���擾�ł��Ă��Ȃ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
    }
    return pRet;
}

EffectBlink* MyStgUtil::activateLeaveEffectOf(GgafDx::GeometricActor* prm_pActor) {
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
            throwCriticalException("�Ή� LeaveEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pRet = nullptr;
            break;
        }
    }
    if (!pRet) {
        throwCriticalException("�G�t�F�N�g���擾�ł��Ă��Ȃ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
    }
    return pRet;
}

GgafDx::FigureActor* MyStgUtil::activateFormationDestroyedEffectOf(GgafDx::GeometricActor* prm_pActor) {

    GgafDx::FigureActor* pE = nullptr;
    switch (prm_pActor->getStatus()->get(STAT_FormationDestroyedEffectKind)) {
        case 0: {
            pE = nullptr; //�G�t�F�N�g����
            break;
        }
        case EF_EXPLO_AND_BONUS001: {
            //1�͒ʏ�̃t�H�[���[�V�����{�[�i�X�X�R�A�\���G�t�F�N�g
            SpriteLabelBonus001* pLabel = dispatchForceFromCommon(SpriteLabelBonus001);
            pLabel->onDispatched(prm_pActor); //�����ݒ肪�s����
            pLabel->setPositionAt(prm_pActor);
            pLabel->getVecDriver()->takeoverMvFrom(prm_pActor->getVecDriver());
            int addscore = prm_pActor->getStatus()->get(STAT_FormationDestroyedAddScorePoint); //�t�H�[���[�V�����S�œ��_
            std::string s = XTOS(addscore);
            pLabel->update(s.c_str());
            pE = pLabel;

            EffectTurbo002* pTurbo002 = dispatchForceFromCommon(EffectTurbo002);
            pTurbo002->setPositionAt(prm_pActor);
            pTurbo002->getVecDriver()->takeoverMvFrom(prm_pActor->getVecDriver());
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
            throwCriticalException("�Ή� FormationDestroyedEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }

//        if (pE) {
//            //�o�����W��ݒ�
//            pE->setPositionAt(prm_pActor);
//            pE->getVecDriver()->takeoverMvFrom(prm_pActor->getVecDriver());
//        }
    return pE;
}

GgafDx::FigureActor* MyStgUtil::activateFormationDestroyedItemOf(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pI = nullptr;
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
            throwCriticalException("�Ή� FormationDestroyedItem ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pI = nullptr;
            break;
        }
    }
    if (pI) {
        //�o�����W��ݒ�
        pI->setPositionAt(prm_pActor);
    }
    return pI;
}

GgafDx::FigureActor* MyStgUtil::activateProperEffect01Of(GgafDx::GeometricActor* prm_pActor) {
    GgafDx::FigureActor* pE = nullptr;
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
            throwCriticalException("�Ή� ProperEffect01 ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName()<<"("<<prm_pActor<<")");
            pE = nullptr;
            break;
        }
    }
    if (pE) {
        //�o�����W��ݒ�
        pE->setPositionAt(prm_pActor);
    }
    return pE;

}

bool MyStgUtil::performEnemyHit(GgafDx::FigureActor* prm_this, const GgafDx::GeometricActor* const prm_pOther) {
    GgafCore::Status* pThisStatus  = prm_this->getStatus();
    if (UTIL::calcEnemyStamina(prm_this, prm_pOther) <= 0) { //�̗͂������Ȃ�����
        //���j�󂳂ꂽ�ꍇ��
        prm_this->setHitAble(false); //�����蔻�����
        if (prm_pOther->_pGroupHead->_kind & KIND_MY) {
            //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
            G_SCORE += pThisStatus->get(STAT_AddDestroyScorePoint);   //�j�󎞓��_
            double rp = pThisStatus->getDouble(STAT_AddRankPoint);    //���Z���������N�l
            if (!ZEROd_EQ(rp)) {
                double rp_r = pThisStatus->getDouble(STAT_AddRankPoint_Reduction); //���t���[���̃����N�{��
                if (ZEROd_EQ(rp_r)) { //�{����0.0�Ȃ��
                    //�Ȃɂ����Ȃ�
                } else if (ONEd_EQ(rp_r)) {
                    G_RANK += rp; //�{����1.0�Ȃ�΁A���̂܂܉��Z���������N�l���v���X
                    if (G_RANK > G_MAX_RANK) {
                        G_RANK = G_MAX_RANK;
                    }
                    if (G_RANK < G_MIN_RANK) {
                        G_RANK = G_MIN_RANK;
                    }
                } else if (rp_r > 0) {
                    frame n = prm_this->getActiveFrame();   //�ғ��t���[��
                    G_RANK += (rp * pow(rp_r, (double)n)); //rp * (rp_r ^ n)  �����N���Z
                    if (G_RANK > G_MAX_RANK) {
                        G_RANK = G_MAX_RANK;
                    }
                    if (G_RANK < G_MIN_RANK) {
                        G_RANK = G_MIN_RANK;
                    }
                } else {
                    //�Ȃɂ����Ȃ�
                }

            }
            prm_this->notifyDestroyedToFormation();     //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����A�ƒʒm
            UTIL::activateItemOf(prm_this);             //�A�C�e���o��
            UTIL::activateDestroyedEffectOf(prm_this);  //���ꂽ�G�t�F�N�g
            GgafCore::Scene* pThisPlatformScene = prm_this->getSceneMediator()->getPlatformScene();
            if (pThisPlatformScene->instanceOf(Obj_RankUpStage)) {
                //�����N�A�b�v�X�e�[�W�̓G�Ȃ�΁A
                RankUpStage* pRankUpStage = (RankUpStage*)(pThisPlatformScene);
                pRankUpStage->onDestroyedEnemy(prm_this, prm_pOther);
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

GgafDx::FigureActor* MyStgUtil::performFormationDestroyAll(GgafDx::FigureActor* prm_pActor_last_destroyed) {
    //�ґ��S�Ŏ��{�[�i�X���Z
    G_SCORE += prm_pActor_last_destroyed->getStatus()->get(STAT_FormationDestroyedAddScorePoint);
    //�ґ��S�Ŏ��G�t�F�N�g�o��
    GgafDx::FigureActor* pEffect = UTIL::activateFormationDestroyedEffectOf(prm_pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(prm_pActor_last_destroyed);
    return pEffect;
}


// �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
// �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s�����ƁB
// gen02 start
GgafCore::Status* MyStgUtil::resetMyShipStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 6000000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 205 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMySnipeShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 305 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyMagicEnergyCoreStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyStraightLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, (int)(105+((MyStraightLaserChip001::tex_no_*0.5)*100)));  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //�̗�
    p->set(STAT_Attack, 0 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 205 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinSnipeShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 305 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyBunshinWateringLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, (int)(105+((MyBunshinWateringLaserChip001::tex_no_*0.5)*100)));  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyTorpedoStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 1000 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMyTorpedoBlastStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 2 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetShot002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 3 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetShot003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetShot004Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraightLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 105 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyWateringLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 105 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEresStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEresShot001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 10 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 3000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaLaserChip002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaLaserChip003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyStraeaLaserChip004Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOmulusStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 2000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmusStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 2000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmusLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEtisStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 20000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyRisStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 20 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyGeriaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 20 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHaliaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyTamago01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyIrceStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyRatislaviaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 9999999 );  //�̗�
    p->set(STAT_Attack, 9999999 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyAllasStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyUnomiaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmiliaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 4000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmiliaFragmentStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 2000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmiliaFragment2Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEmiliaFragment3Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMagicPointItem001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //�̗�
    p->set(STAT_Attack, 0 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMagicPointItem002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //�̗�
    p->set(STAT_Attack, 0 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetMagicPointItem003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //�̗�
    p->set(STAT_Attack, 0 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetScoreItem001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //�̗�
    p->set(STAT_Attack, 0 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 500 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetVreathItem001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 0 );  //�̗�
    p->set(STAT_Attack, 0 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 500 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEbeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 10000 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbe002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbeLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbeLaserChip002Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyHisbeLaserChip003Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyDrasteaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 20000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyTalanteStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEsperiaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 3000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyEsperiaLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestGuStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_GU);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestChokiStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestPaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestNomalStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 30000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestGuShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_GU);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestChokiShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestPaShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetTestNomalShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyRatislaviaEyeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 3000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 2000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyRatislaviaEyeStraightLaserChip001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 105 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErmioneStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 4000 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErmioneArmHeadStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 9999999 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErmioneArmBodyStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 9999999 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErmioneArmWeakStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 400 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyApphoStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyAntiopeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyDelheidStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyAlisanaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyIdaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 10000 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyThagorasStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOrtunaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyGlajaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 1000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 10 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyGlajaLance001Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyDunaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 400 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOzartiaStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 50000 );  //�̗�
    p->set(STAT_Attack, 300 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 5000 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 100 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOzartiaShot01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 5000 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 100 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 1 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOzartiaLaserChip01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 105 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOzartiaPillar01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 1000 );  //�̗�
    p->set(STAT_Attack, 1000 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOebiusStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyOebiusCoreStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 5000 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErelmanStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, EF_ENTRY_SMALL001_STAY_F60);  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, EF_LEAVE_SMALL001_F30);  //�ޏo�G�t�F�N�g���
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyErelmanCoreStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 5000 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetEnemyUrydikeStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 99 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 300 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00001 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.95000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetAliceShotStatus(GgafCore::Status* p) {
    p->set(STAT_Stamina, 100 );  //�̗�
    p->set(STAT_Attack, 100 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
GgafCore::Status* MyStgUtil::resetWall01Status(GgafCore::Status* p) {
    p->set(STAT_Stamina, 9999999 );  //�̗�
    p->set(STAT_Attack, 9999999 );  //��{�U����
    if (!p->hasBeenReset()) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����(1:��/0:�s��)
        p->set(STAT_AddDestroyScorePoint, 0 );  //�j�󎞉��Z���_
        p->set(STAT_AddDamagedScorePoint, 0 );  //�_���[�W�����Z���_
        p->set(STAT_FlushAble, 0 );  //�_���[�W���t���b�V���v��
        p->set(STAT_AddRankPoint, 0.00000 );  //�j�󎞉��Z�����N�����l
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //�t���[���������N�k���{��
        p->set(STAT_AttackPowerRate, 1.00000 );  //�U���͂ɏ悶���闦
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
    }
    return p;
}
// gen02 end
