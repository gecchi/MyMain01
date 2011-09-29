#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;







// ˆÈ‰º‚Ì gen02 start ` end ‚ÍExcelƒ}ƒNƒ‚É‚æ‚è©“®¶¬‚³‚ê‚½ƒR[ƒh‚Å‚·B
// ƒR[ƒh•ÏX‚ÍuƒXƒe[ƒ^ƒXCreater.xlsv‚©‚çs‚Á‚Ä‚¢‚½‚¾‚«‚½‚¢B
// gen02 start
	GgafStatus* MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 105 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetMyOptionWateringLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 105 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetMyOptionStraightLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 105 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetMyTorpedoStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 1000 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetMyTorpedoBlastStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetMyShipStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 9999999 );  //‘Ì—Í
		p->set(STAT_Attack, 2500 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 105 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyCurveLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 105 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyCeresStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 100 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 99 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyCeresShot001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 10 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 300 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 3000 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip002Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip003Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyAstraeaLaserChip004Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyVestaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 100 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 2000 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyMetisStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 30000 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 20000 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyIrisStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 20 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 99 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyJunoStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 20 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 1000 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyThaliaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 300 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 1000 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetShot001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 2 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.01000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetShot002Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 3 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.01000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 100 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyCirceStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 100 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 99 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetShot003Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetShot004Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetTorusStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 9999999 );  //‘Ì—Í
		p->set(STAT_Attack, 9999999 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 9999999 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 9999999 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 9999999 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetWall001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 9999999 );  //‘Ì—Í
		p->set(STAT_Attack, 9999999 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 9999999 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 9999999 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 9999999 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetWall001PrismStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 9999999 );  //‘Ì—Í
		p->set(STAT_Attack, 9999999 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 9999999 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 9999999 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 9999999 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyPallasStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 100 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 99 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyEunomiaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 100 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 99 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetMyShot001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 205 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetMagicPointItem001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 500 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 100 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetEnemyMassaliaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 1 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 300 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.10000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 3000 );  //‘Ì—Í
		p->set(STAT_Attack, 100 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.50000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
	GgafStatus* MyStgUtil::resetMyOptionStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_EFFECT);  //í•Ê(ƒfƒtƒHƒ‹ƒg)
		p->set(STAT_LockonAble, 0 );  //ƒƒbƒNƒIƒ“‰Â”Û
		p->set(STAT_AddScorePoint, 0 );  //‰ÁZ“¾“_
		p->set(STAT_AddRankPoint, 0.00000 );  //‰ÁZƒ‰ƒ“ƒN
		p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //‰ÁZƒ‰ƒ“ƒNŒ¸­—¦
		p->set(STAT_Stamina, 0 );  //‘Ì—Í
		p->set(STAT_Attack, 0 );  //UŒ‚—Í
		p->set(STAT_DefaultDefenceRate, 0.00000 );  //Šî€–hŒä—¦
		p->set(STAT_DominantDefenceRate, 0.00000 );  //—D«‚Ì–hŒä—¦
		p->set(STAT_RecessiveDefenceRate, 0.00000 );  //—ò«‚Ì–hŒä—¦
		return p;
	}
// gen02 end

