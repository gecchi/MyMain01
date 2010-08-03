#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_
namespace MyStg2nd {

class MyStgUtil: public GgafDx9LibStg::StgUtil {
public:

    static char RANK_1stDeg[10][6];
    static char RANK_10thDeg[10][5];
    static char RANK_100thDeg[10][7];
    static char RANK_1000thDeg[10][9];
    static char RANK_10000thDeg[10][46];
    static char RANK_INF[7];

    /**
     * ランク数値から文字列変換
     * @param prm_rank ランク数値(1～100000)
     * @param out 結果出力[80]必要
     * @return
     */
    static void getRankStr(int prm_rank, char* out);

    /**
     * 優位性を調べる
     * @param kind_my
     * @param kind_enemy
     * @return 以下の表参照。
     * <table>
     * <tr><th>0より小さい         </th><th>0   </th><th>0より大きい         </th></tr>
     * <tr><td>kind_myの方が劣性   </td><td>同格</td><td>kind_myの方が優性   </td></tr>
     * <tr><td>kind_enemyの方が優性</td><td>同格</td><td>kind_enemyの方が劣性</td></tr>
     * </table>
     */
    static int judgeMyDominant(actorkind kind_my, actorkind kind_enemy) {
        int ret = 0;
        if (kind_my & KIND_GU) {
            if (kind_enemy & KIND_CHOKI) {
                ret++;
            }
            if (kind_enemy & KIND_PA) {
                ret--;
            }
        }

        if (kind_my & KIND_CHOKI) {
            if (kind_enemy & KIND_PA) {
                ret++;
            }
            if (kind_enemy & KIND_GU) {
                ret--;
            }
        }

        if (kind_my & KIND_PA) {
            if (kind_enemy & KIND_GU) {
                ret++;
            }
            if (kind_enemy & KIND_CHOKI) {
                ret--;
            }
        }
        return ret;
    }


    static int judgeEnemyDominant(actorkind kind_enemy, actorkind kind_my) {
        int ret = 0;
        if (kind_enemy & KIND_GU) {
            if (kind_my & KIND_CHOKI) {
                ret++;
            }
            if (kind_my & KIND_PA) {
                ret--;
            }
        }

        if (kind_enemy & KIND_CHOKI) {
            if (kind_my & KIND_PA) {
                ret++;
            }
            if (kind_my & KIND_GU) {
                ret--;
            }
        }

        if (kind_enemy & KIND_PA) {
            if (kind_my & KIND_GU) {
                ret++;
            }
            if (kind_my & KIND_CHOKI) {
                ret--;
            }
        }
        return ret;
    }

    /**
     * 自分(自機)の体力計算 .
     * @param pStatMy  自分(自機)のステータス
     * @param kind_my  自分(自機)の種別
     * @param pStatOpp 相手(敵機)のステータス
     * @param kind_opp 相手(敵機)の種別
     * @return
     */
    static int calcMyStatus(GgafCore::GgafStatus* pStatMy,
                             actorkind kind_my,
                             GgafCore::GgafStatus* pStatOpp,
                             actorkind kind_opp) {
        //優性劣性判定
        int my_domi = MyStgUtil::judgeMyDominant(kind_my, kind_opp);
        //相手攻撃力
        int opp_attack = pStatOpp->get(STAT_Attack);
        //優性劣性に応じて防御率を乗ずる
        if (my_domi > 0) {
            //自分が優性時
            return pStatMy->minus(STAT_Stamina,
                                  (int)(opp_attack * pStatMy->getDouble(STAT_DominantDefenceRate)));
        } else if (my_domi < 0) {
            //自分が劣性時
            return pStatMy->minus(STAT_Stamina,
                                  (int)(opp_attack * pStatMy->getDouble(STAT_RecessiveDefenceRate)));
        } else {
            //相手と同格時
            return pStatMy->minus(STAT_Stamina,
                                  (int)(opp_attack * pStatMy->getDouble(STAT_DefaultDefenceRate)));
        }
    }

    static int calcEnemyStatus(GgafCore::GgafStatus* pStatEnemy,
                                actorkind kind_enemy,
                                GgafCore::GgafStatus* pStatOpp,
                                actorkind kind_opp) {
        //優性劣性判定
        int enemy_domi = MyStgUtil::judgeEnemyDominant(kind_enemy, kind_opp);
        //_TRACE_("enemy_domi="<<enemy_domi);
        //相手(自機関連)攻撃力
        int opp_attack = pStatOpp->get(STAT_Attack);
        //_TRACE_("my_attack="<<my_attack);
        //優性劣性に応じて防御率を乗ずる
        int enemy_stamina;
        if (enemy_domi > 0) {
            //自分（敵関連）が優性時
//_TRACE_("pStatEnemy->get(STAT_DominantDefenceRate)="<<pStatEnemy->get(STAT_DominantDefenceRate));

            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DominantDefenceRate)));
        //_TRACE_("enemy_stamina="<<enemy_stamina);
        } else if (enemy_domi < 0) {
            //自分（敵関連）が劣性時
//_TRACE_("pStatEnemy->get(STAT_DominantDefenceRate)="<<pStatEnemy->getDouble(STAT_RecessiveDefenceRate));
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->get(STAT_RecessiveDefenceRate)));

        _TRACE_("enemy_stamina="<<enemy_stamina);
        } else {
//_TRACE_("pStatEnemy->get(STAT_DominantDefenceRate)="<<pStatEnemy->getDouble(STAT_DefaultDefenceRate));

            //相手(自機関連)と同格時
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DefaultDefenceRate)));
        //_TRACE_("enemy_stamina="<<enemy_stamina);
        }
//_TRACE_("enemy_stamina="<<enemy_stamina);
        if (enemy_stamina <= 0 && (kind_opp & KIND_MY)) {
            //相手の種別が My ならば得点加算
            _SCORE_ += pStatEnemy->get(STAT_AddScorePoint);
            _RANK_  += pStatEnemy->getDouble(STAT_AddRankPoint);
        }

        return enemy_stamina;

    }

    static int nextRepeatVal(int prm_id) {
        return 0;
    }



    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「ステータスCreater.xls」から行っていただきたい。
    // gen01 start
	//自機レーザー
	static void resetMyStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//オプションレーザー
	static void resetMyCurveLaserChip001Status(GgafCore::GgafStatus* p);
	//自機
	static void resetMyShipStatus(GgafCore::GgafStatus* p);
	//敵ストレートレーザー001
	static void resetEnemyStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//敵カーブレーザー001
	static void resetEnemyCurveLaserChip001Status(GgafCore::GgafStatus* p);
	//ケレス
	static void resetEnemyCeresStatus(GgafCore::GgafStatus* p);
	//ケレスショット001
	static void resetEnemyCeresShot001Status(GgafCore::GgafStatus* p);
	//アストラエア
	static void resetEnemyAstraeaStatus(GgafCore::GgafStatus* p);
	//アストラエアレーザー
	static void resetEnemyAstraeaLaserChip001Status(GgafCore::GgafStatus* p);
	//アストラエアレーザー
	static void resetEnemyAstraeaLaserChip002Status(GgafCore::GgafStatus* p);
	//ヴェスタ
	static void resetEnemyVestaStatus(GgafCore::GgafStatus* p);
	//メティス
	static void resetEnemyMetisStatus(GgafCore::GgafStatus* p);
	//イリス
	static void resetEnemyIrisStatus(GgafCore::GgafStatus* p);
	//ジュノー
	static void resetEnemyJunoStatus(GgafCore::GgafStatus* p);
	//タエラ
	static void resetEnemyThaliaStatus(GgafCore::GgafStatus* p);
	//汎用ショット001
	static void resetShot001Status(GgafCore::GgafStatus* p);
	//汎用ショット002
	static void resetShot002Status(GgafCore::GgafStatus* p);
	//たまご１
	static void resetEnemyTamago01Status(GgafCore::GgafStatus* p);
	//キルケ
	static void resetEnemyCirceStatus(GgafCore::GgafStatus* p);
	//汎用ショット003ミニレーザー
	static void resetShot003Status(GgafCore::GgafStatus* p);
	//ミニレーザーショット
	static void resetShot004Status(GgafCore::GgafStatus* p);
	//地形トーラス
	static void resetTorusStatus(GgafCore::GgafStatus* p);
	//パラス
	static void resetEnemyPallasStatus(GgafCore::GgafStatus* p);
	//自機ショット
	static void resetMyShot001Status(GgafCore::GgafStatus* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
