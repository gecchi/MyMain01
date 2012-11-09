#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int MyStgUtil::judgeMyDomination(actorkind attribute_my, actorkind attribute_enemy) {
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

int MyStgUtil::judgeEnemyDomination(actorkind kattribute_enemy, actorkind attribute_my) {
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
    int my_domi = MyStgUtil::judgeMyDomination(pStatMy->get(STAT_Attribute), pStatOpp->get(STAT_Attribute));
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
    int enemy_domi = MyStgUtil::judgeEnemyDomination(pStatEnemy->get(STAT_Attribute), pStatOpp->get(STAT_Attribute));
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
    if (enemy_stamina <= 0 && (prm_pOpp->getKind() & KIND_MY)) {
        //����(���@)�̎�ʂ� MY*** �i���@�֘A�j �Ȃ��
        _SCORE_ += pStatEnemy->get(STAT_AddScorePoint);      //���_
        _RANK_  += pStatEnemy->getDouble(STAT_AddRankPoint); //�����N���Z
        prm_pEnemy->notifyDestroyedToFormation(); //�ґ��S�Ŕ���ɗL���Ȕj��̂�����ł�����ʒm

        if (prm_pEnemy->getPlatformScene()->instanceOf(Obj_RankUpStage)) {
            //�����N�A�b�v�X�e�[�W�̓G�Ȃ�΁A
            RankUpStage* pRankUpStage = (RankUpStage*)(prm_pEnemy->getPlatformScene());
            pRankUpStage->hit_enemy_num_ ++; //�����N�A�b�v�X�e�[�W�̓G�|������I�J�E���g�A�b�v
        }
    }
    return enemy_stamina;
}

GgafDxDrawableActor* MyStgUtil::activateExplosionEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = NULL;
    switch (prm_pActor->_pStatus->get(STAT_ExplosionEffectKind)) {
        case 0: {
            pE = NULL; //�����G�t�F�N�g����
            break;
        }
        case 1: {
            pE = employFromCommon(EffectExplosion001);
            break;
        }
        case 2: {
            pE = employFromCommon(EffectExplosion002);
            break;
        }
        case 3: {
            pE = employFromCommon(EffectExplosion003);
            break;
        }
        default: {
            _TRACE_("���x���� �Ή� ExplosionEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName());
            pE = NULL;
            break;
        }
    }

    if (pE) {
        //�o�����W��ݒ�
        pE->locateWith(prm_pActor);
        pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
    }
    return pE;
}

GgafDxDrawableActor* MyStgUtil::activateItemOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = NULL;
    switch (prm_pActor->_pStatus->get(STAT_ItemKind)) {
        case 0: {
            pI = NULL; //�A�C�e������
            break;
        }
        case 1: {
            pI = employFromCommon(MagicPointItem001);
            break;
        }
        case 2: {
            pI = employFromCommon(MagicPointItem002);
            break;
        }
        default: {
            _TRACE_("���x���� �Ή� ExplosionEffect ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName());
            pI = NULL;
            break;
        }
    }
    if (pI) {
        //�o�����W��ݒ�
        pI->locateWith(prm_pActor);
    }
    return pI;
}

GgafDxDrawableActor* MyStgUtil::activateEntryEffectOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pE = NULL;
    switch (prm_pActor->_pStatus->get(STAT_EntryEffectKind)) {
        case 0: {
            pE = NULL; //����G�t�F�N�g����
            break;
        }
        case 1: {
            pE = employFromCommon(EffectEntry001);
            break;
        }
        case 2: {
            pE = employFromCommon(EffectEntry002);
            break;
        }
        case 3: {
            pE = employFromCommon(EffectEntry003);
            break;
        }
        default: {
            pE = NULL;
            break;
        }
    }
    if (pE) {
        //�o�����W��ݒ�
        pE->locateWith(prm_pActor);
    }
    return pE;
}

GgafDxDrawableActor* MyStgUtil::activateFormationDestroyedEffectOf(GgafDxGeometricActor* prm_pActor) {
    int addscore = prm_pActor->_pStatus->get(STAT_FormationDestroyedAddScorePoint); //�t�H�[���[�V�����S�œ��_���Z
    _SCORE_ += addscore;
    GgafDxDrawableActor* pE = NULL;
    switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedEffectKind)) {
        case 0: {
            pE = NULL; //�G�t�F�N�g����
            break;
        }
        case 1: {
            //1�͒ʏ�̃t�H�[���[�V�����{�[�i�X�X�R�A�\���G�t�F�N�g
            SpriteLabelBonus001* pLabel = employForceFromCommon(SpriteLabelBonus001);
            pLabel->locateWith(prm_pActor);
            pLabel->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
            std::string s = ITOS(addscore);
            pLabel->update(s.c_str());
            pE = pLabel;
            break;
        }
//            case 2: {
//                pE = employFromCommon(EffectExplosion002);
//                break;
//            }
//            case 3: {
//                pE = employFromCommon(EffectExplosion003);
//                break;
//            }
        default: {
            _TRACE_("���x���� �Ή� STAT_FormationDestroyedEffectKind ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName());
            pE = NULL;
            break;
        }
    }

//        if (pE) {
//            //�o�����W��ݒ�
//            pE->locateWith(prm_pActor);
//            pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
//        }
    return pE;
}

GgafDxDrawableActor* MyStgUtil::activateFormationDestroyedItemOf(GgafDxGeometricActor* prm_pActor) {
    GgafDxDrawableActor* pI = NULL;
    switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedItemKind)) {
        case 0: {
            pI = NULL; //�A�C�e������
            break;
        }
        case 1: {
            pI = employFromCommon(MagicPointItem001);
            break;
        }
        case 2: {
            pI = employFromCommon(MagicPointItem002);
            break;
        }
        default: {
            _TRACE_("���x���� �Ή� STAT_FormationDestroyedItemKind ����`����ĂȂ��Bprm_pActor="<<prm_pActor->getName());
            pI = NULL;
            break;
        }
    }
    if (pI) {
        //�o�����W��ݒ�
        pI->locateWith(prm_pActor);
    }
    return pI;
}
















// �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
// �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s�����ƁB
// gen02 start
    GgafStatus* MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, (int)(105+((MyStraightLaserChip001::tex_no_*0.5)*100)));  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMyOptionWateringLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMyOptionStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMyTorpedoStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 1000 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMyTorpedoBlastStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMyShipStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000000 );  //�̗�
        p->set(STAT_Attack, 2500 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyCurveLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyCeresStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 1 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 2 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyCeresShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 10 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyAstraeaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 300 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 3000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip003Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip004Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyRomulusStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 2000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyRemusStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 2000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyRemusLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyMetisStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 30000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 20000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyIrisStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 20 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 200 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 1 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 2 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyJunoStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 20 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyThaliaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 300 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 2 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.01000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetShot002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 3 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.01000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyCirceStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetShot003Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetShot004Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemySylviaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 9999999 );  //�̗�
        p->set(STAT_Attack, 9999999 );  //�U����
        p->set(STAT_DefaultDefenceRate, 9999999 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 9999999 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 9999999 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetWall001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 9999999 );  //�̗�
        p->set(STAT_Attack, 9999999 );  //�U����
        p->set(STAT_DefaultDefenceRate, 9999999 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 9999999 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 9999999 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetWall001PrismStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 9999999 );  //�̗�
        p->set(STAT_Attack, 9999999 );  //�U����
        p->set(STAT_DefaultDefenceRate, 9999999 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 9999999 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 9999999 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyPallasStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 1 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 2 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyEunomiaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 1 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 2 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMyShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 205 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyMassaliaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 1000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 4000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyMassaliaFragmentStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 300 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 2000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyMassaliaFragment2Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyMassaliaFragment3Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMyOptionStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 0 );  //�̗�
        p->set(STAT_Attack, 0 );  //�U����
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMagicPointItem001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 500 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 0 );  //�̗�
        p->set(STAT_Attack, 0 );  //�U����
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetMagicPointItem002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 500 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 0 );  //�̗�
        p->set(STAT_Attack, 0 );  //�U����
        p->set(STAT_DefaultDefenceRate, 0.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.00000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 0.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyHebeStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 10000 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 1 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 2 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyThisbeStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyThisbeLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyAdrasteaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 30000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 20000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyAtalanteStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyHesperiaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 1000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 3000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 2 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyHesperiaLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetTestGuStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_GU);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 30000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetTestChokiStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 30000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetTestPaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 30000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetTestNomalStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 30000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetTestGuShotStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_GU);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetTestChokiShotStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetTestPaShotStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_PA);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetTestNomalShotStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemySylviaEyeStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 2000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 3000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemySylviaEyeStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyHermioneStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 5000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 4000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyHermioneArmHeadStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyHermioneArmBodyStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
    GgafStatus* MyStgUtil::resetEnemyHermioneArmWeakStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //���(�f�t�H���g)
        p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //����
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 1000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 400 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
        p->set(STAT_EntryEffectKind, 1 );  //�o���G�t�F�N�g���
        p->set(STAT_LeaveEffectKind, 1 );  //�ޏo�G�t�F�N�g���
        p->set(STAT_ExplosionEffectKind, 1 );  //�����G�t�F�N�g���
        p->set(STAT_ItemKind, 1 );  //����A�C�e�����
        p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //�ґ��S�Ŏ����Z���_
        p->set(STAT_FormationDestroyedEffectKind, 0 );  //�ґ��S�Ŏ��G�t�F�N�g
        p->set(STAT_FormationDestroyedItemKind, 0 );  //�ґ��S�Ŏ��A�C�e�����
        return p;
    }
// gen02 end
