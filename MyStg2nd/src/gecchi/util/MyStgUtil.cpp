#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

char MyStgUtil::RANK_1stDeg[10][6] = {
                   "A"    ,
                   "AA"   ,
                   "AAA"  ,
                   "AAAA" ,
                   "B"    ,
                   "BA"   ,
                   "BAA"  ,
                   "BAAA" ,
                   "BAAAA"
            };

char MyStgUtil::RANK_10thDeg[10][5] = {
                   "CD"  ,
                   "EF"  ,
                   "GH"  ,
                   "IJ"  ,
                   "KL"  ,
                   "KLCD",
                   "KLEF",
                   "KLGH",
                   "KLIJ"
            };

char MyStgUtil::RANK_100thDeg[10][7] = {
                   "MNO"   ,
                   "PQR"   ,
                   "STU"   ,
                   "VWX"   ,
                   "YZ["   ,
                   "YZ[MNO",
                   "YZ[PQR",
                   "YZ[STU",
                   "YZ[VWX"
            };

char MyStgUtil::RANK_1000thDeg[10][9] = {
                   "\]^_"    ,
                   "`abc"    ,
                   "defg"    ,
                   "hijk"    ,
                   "lmno"    ,
                   "lmno\]^_",
                   "lmno`abc",
                   "lmnodefg",
                   "lmnohijk"
            };

char MyStgUtil::RANK_10000thDeg[10][46] = {
                   "pqrst"                                        ,
                   "pqrstpqrst"                                   ,
                   "pqrstpqrstpqrst"                              ,
                   "pqrstpqrstpqrstpqrst"                         ,
                   "pqrstpqrstpqrstpqrstpqrst"                    ,
                   "pqrstpqrstpqrstpqrstpqrstpqrst"               ,
                   "pqrstpqrstpqrstpqrstpqrstpqrstpqrst"          ,
                   "pqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrst"     ,
                   "pqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrst"
            };

char MyStgUtil::RANK_INF[] = "uvwxyz";


void MyStgUtil::getRankStr(int prm_rank, char* out) {
    if (prm_rank <= 0) {
        strcat(out, "");
        return;
    }
    if (prm_rank > 100000) {
        strcat(out, RANK_INF);
        return;
    }
    int idx_rank_10000thDeg = prm_rank/10000;
    if (idx_rank_10000thDeg > 0) {
        strcat(out, RANK_10000thDeg[idx_rank_10000thDeg-1]);
        prm_rank -= idx_rank_10000thDeg*10000;
    }
    int idx_rank_1000thDeg = prm_rank/1000;
    if (idx_rank_1000thDeg > 0) {
        strcat(out, RANK_1000thDeg[idx_rank_1000thDeg-1]);
        prm_rank -= idx_rank_1000thDeg*1000;
    }
    int idx_rank_100thDeg = prm_rank/100;
    if (idx_rank_100thDeg > 0) {
        strcat(out, RANK_100thDeg[idx_rank_100thDeg-1]);
        prm_rank -= idx_rank_100thDeg*100;
    }
    int idx_rank_10thDeg = prm_rank/10;
    if (idx_rank_10thDeg > 0) {
        strcat(out, RANK_10thDeg[idx_rank_10thDeg-1]);
        prm_rank -= idx_rank_10thDeg*10;
    }
    int idx_rank_1stDeg = prm_rank;
    if (idx_rank_1stDeg > 0) {
        strcat(out, RANK_1stDeg[idx_rank_1stDeg-1]);
        prm_rank -= idx_rank_1stDeg;
    }

//    1     A 10   CD 100    MNO 1000     \]^_ 10000                                         pqrst  無限大 uvwxyz
//    2    AA 20   EF 200    PQR 2000     `abc 20000                                    pqrstpqrst
//    3   AAA 30   GH 300    STU 3000     defg 30000                               pqrstpqrstpqrst
//    4  AAAA 40   IJ 400    VWX 4000     hijk 40000                          pqrstpqrstpqrstpqrst
//    5     B 50   KL 500    YZ[ 5000     lmno 50000                     pqrstpqrstpqrstpqrstpqrst
//    6    BA 60 KLCD 600 YZ[MNO 6000 lmno\]^_ 60000                pqrstpqrstpqrstpqrstpqrstpqrst
//    7   BAA 70 KLEF 700 YZ[PQR 7000 lmno`abc 70000           pqrstpqrstpqrstpqrstpqrstpqrstpqrst
//    8  BAAA 80 KLGH 800 YZ[STU 8000 lmnodefg 80000      pqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrst
//    9 BAAAA 90 KLIJ 900 YZ[VWX 9000 lmnohijk 90000 pqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrst
}


// 以下の gen02 start 〜 end はExcelマクロにより自動生成されたコードです。
// コード変更は「シーンCreater.xls」から行っていただきたい。
// gen02 start
	void MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetMyShipStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetEnemyCeresStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 100 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetEnemyCeresShot001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 10 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetEnemyAstraeaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 300 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetEnemyAstraeaLaserChip001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 0 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetEnemyVestaStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 1000 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetEnemyIrisStatus(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 20 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetShot001Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 2 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
	void MyStgUtil::resetShot002Status(GgafStatus* p) {
		p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
		p->set(STAT_AddScorePoint, 3 );  //加算得点
		p->set(STAT_AddRankPoint_Reduction, 0.10000 );  //加算ランク
		p->set(STAT_AddRankPoint, 0.99000 );  //加算ランク減少率
		p->set(STAT_Stamina, 100 );  //体力
		p->set(STAT_Attack, 100 );  //攻撃力
		p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
		p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
		p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
	}
// gen02 end

