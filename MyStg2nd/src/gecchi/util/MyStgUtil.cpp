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
                   "\\]^_"    ,
                   "`abc"    ,
                   "defg"    ,
                   "hijk"    ,
                   "lmno"    ,
                   "lmno\\]^_",
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

//    1     A 10   CD 100    MNO 1000     \]^_ 10000                                         pqrst  ������ uvwxyz
//    2    AA 20   EF 200    PQR 2000     `abc 20000                                    pqrstpqrst
//    3   AAA 30   GH 300    STU 3000     defg 30000                               pqrstpqrstpqrst
//    4  AAAA 40   IJ 400    VWX 4000     hijk 40000                          pqrstpqrstpqrstpqrst
//    5     B 50   KL 500    YZ[ 5000     lmno 50000                     pqrstpqrstpqrstpqrstpqrst
//    6    BA 60 KLCD 600 YZ[MNO 6000 lmno\]^_ 60000                pqrstpqrstpqrstpqrstpqrstpqrst
//    7   BAA 70 KLEF 700 YZ[PQR 7000 lmno`abc 70000           pqrstpqrstpqrstpqrstpqrstpqrstpqrst
//    8  BAAA 80 KLGH 800 YZ[STU 8000 lmnodefg 80000      pqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrst
//    9 BAAAA 90 KLIJ 900 YZ[VWX 9000 lmnohijk 90000 pqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrstpqrst
}


// �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
// �R�[�h�ύX�́u�X�e�[�^�XCreater.xls�v����s���Ă������������B
// gen02 start
    void MyStgUtil::resetMyStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetMyCurveLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetMyShipStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 9999999 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyStraightLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyCurveLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 105 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyCeresStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyCeresShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 10 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyAstraeaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 300 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 3000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyAstraeaLaserChip001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyAstraeaLaserChip002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyVestaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_CHIKEI_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 2000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyMetisStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 30000 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 20000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyIrisStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 20 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyJunoStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 20 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyThaliaStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 20 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 1000 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 2 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.01000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetShot002Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 3 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.01000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyTamago01Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyCirceStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 1 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetShot003Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetShot004Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 100 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetTorusStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_CHIKEI);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 9999999 );  //�̗�
        p->set(STAT_Attack, 9999999 );  //�U����
        p->set(STAT_DefaultDefenceRate, 9999999 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 9999999 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 9999999 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetEnemyPallasStatus(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_ENEMY_BODY_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 100 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.10000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.90000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 99 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
    void MyStgUtil::resetMyShot001Status(GgafStatus* p) {
        p->set(STAT_DEFAULT_ACTOR_KIND, KIND_MY_SHOT_NOMAL);  //���(�f�t�H���g)
        p->set(STAT_LockonAble, 0 );  //���b�N�I����
        p->set(STAT_AddScorePoint, 0 );  //���Z���_
        p->set(STAT_AddRankPoint, 0.00000 );  //���Z�����N
        p->set(STAT_AddRankPoint_Reduction, 0.00000 );  //���Z�����N������
        p->set(STAT_Stamina, 100 );  //�̗�
        p->set(STAT_Attack, 205 );  //�U����
        p->set(STAT_DefaultDefenceRate, 1.00000 );  //��h�䗦
        p->set(STAT_DominantDefenceRate, 0.50000 );  //�D�����̖h�䗦
        p->set(STAT_RecessiveDefenceRate, 2.00000 );  //�򐫎��̖h�䗦
    }
// gen02 end

