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
//ñ≥å¿ëÂ UVWXYZ
}



// à»â∫ÇÃ gen02 start Å` end ÇÕExcelÉ}ÉNÉçÇ…ÇÊÇËé©ìÆê∂ê¨Ç≥ÇÍÇΩÉRÅ[ÉhÇ≈Ç∑ÅB
// ÉRÅ[ÉhïœçXÇÕÅuÉXÉeÅ[É^ÉXCreater.xlsÅvÇ©ÇÁçsÇ¡ÇƒÇ¢ÇΩÇæÇ´ÇΩÇ¢ÅB
// gen02 start
    void MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 105 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetMyOptionWateringLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 105 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetMyOptionStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 105 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetMyTorpedoStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 1000 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetMyTorpedoBlastStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetMyShipStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 9999999 );  //ëÃóÕ
        p->set(STAT_Attack, 2500 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 105 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyCurveLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 105 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyCeresStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 100 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 99 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyCeresShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 10 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyAstraeaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 300 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 3000 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyAstraeaLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyAstraeaLaserChip002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyVestaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 100 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 2000 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyMetisStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 30000 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 20000 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyIrisStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 20 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 99 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyJunoStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 20 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 1000 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyThaliaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 300 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 1000 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 2 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.01000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetShot002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 3 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.01000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 100 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyCirceStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 1 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 100 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 99 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetShot003Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetShot004Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetTorusStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 9999999 );  //ëÃóÕ
        p->set(STAT_Attack, 9999999 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 9999999 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 9999999 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 9999999 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetWall001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 9999999 );  //ëÃóÕ
        p->set(STAT_Attack, 9999999 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 9999999 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 9999999 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 9999999 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyPallasStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 100 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 99 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetEnemyEunomiaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 100 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 99 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetMyShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 0 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.00000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 205 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
    void MyStgUtil::resetMagicPointItem001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ITEM);  //éÌï (ÉfÉtÉHÉãÉg)
        p->set(STAT_LockonAble, 0 );  //ÉçÉbÉNÉIÉìâ¬î€
        p->set(STAT_AddScorePoint, 500 );  //â¡éZìæì_
        p->set(STAT_AddRankPoint, 0.10000 );  //â¡éZÉâÉìÉN
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //â¡éZÉâÉìÉNå∏è≠ó¶
        p->set(STAT_Stamina, 100 );  //ëÃóÕ
        p->set(STAT_Attack, 100 );  //çUåÇóÕ
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //äÓèÄñhå‰ó¶
        p->set(STAT_DominantDefenceRate, 0.50000 );  //óDê´éûÇÃñhå‰ó¶
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //óÚê´éûÇÃñhå‰ó¶
    }
// gen02 end

