#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

char MyStgUtil::RANK_1stDeg[10][6] = {
                                      "!"    ,
                                      "!!"   ,
                                      "!!!"  ,
                                      "!!!!" ,
                                      "\""    ,
                                      "\"!"   ,
                                      "\"!!"  ,
                                      "\"!!!" ,
                                      "\"!!!!"
            };

char MyStgUtil::RANK_10thDeg[10][5] = {
                                       "#$"  ,
                                       "%&"  ,
                                       "'("  ,
                                       ")*"  ,
                                       "+,"  ,
                                       "+,#$",
                                       "+,%&",
                                       "+,'(",
                                       "+,)*"
            };

char MyStgUtil::RANK_100thDeg[10][7] = {
                                        "-./"   ,
                                        "012"   ,
                                        "345"   ,
                                        "678"   ,
                                        "9:;"   ,
                                        "9:;-./",
                                        "9:;012",
                                        "9:;345",
                                        "9:;678"
                                 };



char MyStgUtil::RANK_1000thDeg[10][9] = {
                                         ",-./"    ,
                                         "@ABC"    ,
                                         "DEFG"    ,
                                         "HIJK"    ,
                                         "LMNO"    ,
                                         "LMNO,-./",
                                         "LMNO@ABC",
                                         "LMNODEFG",
                                         "LMNOHIJK"
                                  };


char MyStgUtil::RANK_10000thDeg[10][46] = {
                                           "PQRST"                                        ,
                                           "PQRSTPQRST"                                   ,
                                           "PQRSTPQRSTPQRST"                              ,
                                           "PQRSTPQRSTPQRSTPQRST"                         ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRST"                    ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRST"               ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"          ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"     ,
                                           "PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST"
            };

char MyStgUtil::RANK_INF[] = "UVWXYZ";


void MyStgUtil::cnvRankStr(int prm_rank, char* out) {
    if (prm_rank <= 0) {
        strcat(out, " ");
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

//    1      !   10   #$   100    -./   1000     ,-./    10000                                         PQRST
//    2     !!   20   %&   200    012   2000     @ABC    20000                                    PQRSTPQRST
//    3    !!!   30   '(   300    345   3000     DEFG    30000                               PQRSTPQRSTPQRST
//    4   !!!!   40   )*   400    678   4000     HIJK    40000                          PQRSTPQRSTPQRSTPQRST
//    5     \"   50   +,   500    9:;   5000     LMNO    50000                     PQRSTPQRSTPQRSTPQRSTPQRST
//    6    \"!   60 +,#$   600 9:;-./   6000 LMNO,-./    60000                PQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    7   \"!!   70 +,%&   700 9:;012   7000 LMNO@ABC    70000           PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    8  \"!!!   80 +,'(   800 9:;345   8000 LMNODEFG    80000      PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//    9 \"!!!!   90 +,)*   900 9:;678   9000 LMNOHIJK    90000 PQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRSTPQRST
//無限大 UVWXYZ
}



// 以下の gen02 start 〜 end はExcelマクロにより自動生成されたコードです。
// コード変更は「ステータスCreater.xls」から行っていただきたい。
// gen02 start
    void MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 105 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetMyOptionWateringLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 105 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetMyOptionStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 105 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetMyTorpedoStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 1000 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetMyTorpedoBlastStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetMyShipStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 9999999 );  //体力
        p->set(STAT_Attack, 2500 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 105 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyCurveLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 105 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyCeresStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 100 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 99 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyCeresShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 10 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyAstraeaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 300 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 3000 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyAstraeaLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyAstraeaLaserChip002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyVestaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 100 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 2000 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyMetisStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 30000 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 20000 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyIrisStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 20 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 99 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyJunoStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 20 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 1000 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyThaliaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 300 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 1000 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 2 );  //加算得点
        p->set(STAT_AddRankPoint, 0.01000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetShot002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 3 );  //加算得点
        p->set(STAT_AddRankPoint, 0.01000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 100 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyCirceStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 1 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 100 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 99 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetShot003Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetShot004Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetTorusStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 9999999 );  //体力
        p->set(STAT_Attack, 9999999 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 9999999 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 9999999 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 9999999 );  //劣性時の防御率
    }
    void MyStgUtil::resetWall001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 9999999 );  //体力
        p->set(STAT_Attack, 9999999 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 9999999 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 9999999 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 9999999 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyPallasStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 100 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 99 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetEnemyEunomiaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 100 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 99 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetMyShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 0 );  //加算得点
        p->set(STAT_AddRankPoint, 0.00000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 205 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
    void MyStgUtil::resetMagicPointItem001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM);  //種別(デフォルト)
        p->set(STAT_LockonAble, 0 );  //ロックオン可否
        p->set(STAT_AddScorePoint, 500 );  //加算得点
        p->set(STAT_AddRankPoint, 0.10000 );  //加算ランク
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //加算ランク減少率
        p->set(STAT_Stamina, 100 );  //体力
        p->set(STAT_Attack, 100 );  //攻撃力
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //基準防御率
        p->set(STAT_DominantDefenceRate, 0.50000 );  //優性時の防御率
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //劣性時の防御率
    }
// gen02 end

