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

//    1     A 10   CD 100    MNO 1000     \]^_ 10000                                         pqrst  –³ŒÀ‘å uvwxyz
//    2    AA 20   EF 200    PQR 2000     `abc 20000                                    pqrstpqrst
//    3   AAA 30   GH 300    STU 3000     defg 30000                               pqrstpqrstpqrst
//    4  AAAA 40   IJ 400    VWX 4000     hijk 40000                          pqrstpqrstpqrstpqrst
//    5     B 50   KL 500    YZ[ 5000     lmno 50000                     pqrstpqrstpqrstpqrstpqrst
//    6    BA 60 KLCD 600 YZ[MNO 6000 lmno\]^_ 60000                pqrstpqrstpqrstpqrstpqrstpqrst
//    7   BAA 70 KLEF 700 YZ[PQR 7000 lmno`abc 70000           pqrstpqrstpqrstpqrstpqrstpqrstpqrst
//    8  BAAA 80 KLGH 800 YZ[STU 8000 lmnodefg 80000      pqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrst
//    9 BAAAA 90 KLIJ 900 YZ[VWX 9000 lmnohijk 90000 pqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrst


    void MyStgUtil::resetEnemyIrisStatus(GgafActor* p) {
        p->_pStatus->set(STAT_AddScorePoint, 50);
        p->_pStatus->set(STAT_AddRankPoint , 100);
        p->_pStatus->set(STAT_StaminaPoint , 1);
        p->_pStatus->set(STAT_DefensePoint , 0);
        p->_pStatus->set(STAT_AttackPoint  , 1);
    }




}
