#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;







// 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
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

