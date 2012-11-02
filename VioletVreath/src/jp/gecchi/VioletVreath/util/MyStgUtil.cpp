#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

// 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
// コード変更は「ステータスCreater.xls」から行うこと。
// gen02 start
	GgafStatus* MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, (int)(105+((MyStraightLaserChip001::tex_no_*0.5)*100)));  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMyOptionWateringLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 105 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMyOptionStraightLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 105 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMyTorpedoStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 1000 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMyTorpedoBlastStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMyShipStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 1000000 );  //体力
		p->set(STAT_Attack, 2500 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 105 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyCurveLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 105 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyCeresStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 99 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 1 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 2 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyCeresShot001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 10 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 300 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 3000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip002Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip003Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip004Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyRomulusStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 2000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyRemusStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 2000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyRemusLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyMetisStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 30000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 20000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyIrisStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 20 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 99 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 200 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 1 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 2 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyJunoStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 20 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 1000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyThaliaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 300 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 1000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetShot001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 2 );  //加算得点
		p->set(STAT_AddRankPoint, 0.01000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetShot002Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 3 );  //加算得点
		p->set(STAT_AddRankPoint, 0.01000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyCirceStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 99 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetShot003Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetShot004Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemySylviaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 9999999 );  //体力
		p->set(STAT_Attack, 9999999 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 9999999 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 9999999 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 9999999 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetWall001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 9999999 );  //体力
		p->set(STAT_Attack, 9999999 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 9999999 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 9999999 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 9999999 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetWall001PrismStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 9999999 );  //体力
		p->set(STAT_Attack, 9999999 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 9999999 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 9999999 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 9999999 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyPallasStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 99 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 1 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 2 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyEunomiaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 99 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 1 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 2 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMyShot001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 205 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyMassaliaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 1000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 4000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyMassaliaFragmentStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 300 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 2000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyMassaliaFragment2Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 1000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyMassaliaFragment3Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMyOptionStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 0 );  //体力
		p->set(STAT_Attack, 0 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMagicPointItem001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 500 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 0 );  //体力
		p->set(STAT_Attack, 0 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetMagicPointItem002Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 500 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 0 );  //体力
		p->set(STAT_Attack, 0 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 0.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.00000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 0.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyHebeStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 10000 );  //体力
		p->set(STAT_Attack, 99 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 1000 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 1 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 2 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyThisbeStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 99 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyThisbeLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAdrasteaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_THRU);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 30000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 20000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAtalanteStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyHesperiaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 1000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 3000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 2 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyHesperiaLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetTestGuStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_GU);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 30000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 1000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetTestChokiStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 30000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 1000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetTestPaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_PA);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 30000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 1000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetTestNomalStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 30000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 1000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetTestGuShotStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_GU);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetTestChokiShotStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_CHOKI);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetTestPaShotStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_PA);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetTestNomalShotStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemySylviaEyeStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 1 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 2000 );  //加算得点
		p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
		p->set(STAT_Stamina, 3000 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemySylviaEyeStraightLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_CHIKEI_HIT);  //種別(デフォルト)
		p->set(STAT_Attribute , ATTRIBUTE_NOMAL);  //属性
		p->set(STAT_LockonAble, 0 );  //ロックオン可否
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 105 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
		p->set(STAT_EntryEffectKind, 1 );  //出現エフェクト種別
		p->set(STAT_LeaveEffectKind, 1 );  //退出エフェクト種別
		p->set(STAT_ExplosionEffectKind, 1 );  //爆発エフェクト種別
		p->set(STAT_ItemKind, 1 );  //やられアイテム種別
		p->set(STAT_FormationDestroyedAddScorePoint, 0 );  //編隊全滅時加算得点
		p->set(STAT_FormationDestroyedEffectKind, 0 );  //編隊全滅時エフェクト
		p->set(STAT_FormationDestroyedItemKind, 0 );  //編隊全滅時アイテム種別
		return p;
	}
// gen02 end
