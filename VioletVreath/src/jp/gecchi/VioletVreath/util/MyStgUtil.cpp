#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

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
// gen02 end
