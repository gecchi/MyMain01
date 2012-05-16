#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_

#define STATUS(X) (NEW GgafCore::GgafStatus(12, VioletVreath::MyStgUtil::reset##X##Status))

namespace VioletVreath {

class MyStgUtil: public GgafLib::StgUtil {
public:


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
        //相手(敵)攻撃力
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
            //相手(敵)と同格時
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
        //相手(自機)攻撃力
        int opp_attack = pStatOpp->get(STAT_Attack);
        //優性劣性に応じて防御率を乗ずる
        int enemy_stamina;
        if (enemy_domi > 0) {
            //自分（敵）が優性時
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DominantDefenceRate)));
        } else if (enemy_domi < 0) {
            //自分（敵）が劣性時
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->get(STAT_RecessiveDefenceRate)));

        } else {
            //相手(自機)と同格時
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DefaultDefenceRate)));
        }
        if (enemy_stamina <= 0 && (kind_opp & KIND_MY)) {
            //相手(自機)の種別が MY*** （自機関連） ならば得点&ランク加算
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
	static GgafCore::GgafStatus* resetMyStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//オプションカーブレーザー
	static GgafCore::GgafStatus* resetMyOptionWateringLaserChip001Status(GgafCore::GgafStatus* p);
	//オプションストレートレーザー
	static GgafCore::GgafStatus* resetMyOptionStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//トゥピード
	static GgafCore::GgafStatus* resetMyTorpedoStatus(GgafCore::GgafStatus* p);
	//トゥピード爆風
	static GgafCore::GgafStatus* resetMyTorpedoBlastStatus(GgafCore::GgafStatus* p);
	//自機
	static GgafCore::GgafStatus* resetMyShipStatus(GgafCore::GgafStatus* p);
	//敵ストレートレーザー001
	static GgafCore::GgafStatus* resetEnemyStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//敵カーブレーザー001
	static GgafCore::GgafStatus* resetEnemyCurveLaserChip001Status(GgafCore::GgafStatus* p);
	//ケレス
	static GgafCore::GgafStatus* resetEnemyCeresStatus(GgafCore::GgafStatus* p);
	//ケレスショット001
	static GgafCore::GgafStatus* resetEnemyCeresShot001Status(GgafCore::GgafStatus* p);
	//アストラエア
	static GgafCore::GgafStatus* resetEnemyAstraeaStatus(GgafCore::GgafStatus* p);
	//アストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyAstraeaLaserChip001Status(GgafCore::GgafStatus* p);
	//アストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyAstraeaLaserChip002Status(GgafCore::GgafStatus* p);
	//アストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyAstraeaLaserChip003Status(GgafCore::GgafStatus* p);
	//アストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyAstraeaLaserChip004Status(GgafCore::GgafStatus* p);
	//ヴェスタ
	static GgafCore::GgafStatus* resetEnemyVestaStatus(GgafCore::GgafStatus* p);
	//メティス
	static GgafCore::GgafStatus* resetEnemyMetisStatus(GgafCore::GgafStatus* p);
	//イリス
	static GgafCore::GgafStatus* resetEnemyIrisStatus(GgafCore::GgafStatus* p);
	//ジュノー
	static GgafCore::GgafStatus* resetEnemyJunoStatus(GgafCore::GgafStatus* p);
	//タエラ
	static GgafCore::GgafStatus* resetEnemyThaliaStatus(GgafCore::GgafStatus* p);
	//汎用ショット001
	static GgafCore::GgafStatus* resetShot001Status(GgafCore::GgafStatus* p);
	//汎用ショット002
	static GgafCore::GgafStatus* resetShot002Status(GgafCore::GgafStatus* p);
	//たまご１
	static GgafCore::GgafStatus* resetEnemyTamago01Status(GgafCore::GgafStatus* p);
	//キルケ
	static GgafCore::GgafStatus* resetEnemyCirceStatus(GgafCore::GgafStatus* p);
	//汎用ショット003ミニレーザー
	static GgafCore::GgafStatus* resetShot003Status(GgafCore::GgafStatus* p);
	//ミニレーザーショット
	static GgafCore::GgafStatus* resetShot004Status(GgafCore::GgafStatus* p);
	//地形トーラス
	static GgafCore::GgafStatus* resetTorusStatus(GgafCore::GgafStatus* p);
	//地形ボックス001
	static GgafCore::GgafStatus* resetWall001Status(GgafCore::GgafStatus* p);
	//地形プリズム001
	static GgafCore::GgafStatus* resetWall001PrismStatus(GgafCore::GgafStatus* p);
	//パラス
	static GgafCore::GgafStatus* resetEnemyPallasStatus(GgafCore::GgafStatus* p);
	//エウノミア
	static GgafCore::GgafStatus* resetEnemyEunomiaStatus(GgafCore::GgafStatus* p);
	//自機ショット
	static GgafCore::GgafStatus* resetMyShot001Status(GgafCore::GgafStatus* p);
	//マッサリア
	static GgafCore::GgafStatus* resetEnemyMassaliaStatus(GgafCore::GgafStatus* p);
	//マッサリア断片
	static GgafCore::GgafStatus* resetEnemyMassaliaFragmentStatus(GgafCore::GgafStatus* p);
	//マッサリア断片の断片
	static GgafCore::GgafStatus* resetEnemyMassaliaFragment2Status(GgafCore::GgafStatus* p);
	//マッサリア断片の断片の断片
	static GgafCore::GgafStatus* resetEnemyMassaliaFragment3Status(GgafCore::GgafStatus* p);
	//
	static GgafCore::GgafStatus* resetMyOptionStatus(GgafCore::GgafStatus* p);
	//アイテム
	static GgafCore::GgafStatus* resetMagicPointItem001Status(GgafCore::GgafStatus* p);
	//編隊全滅アイテム
	static GgafCore::GgafStatus* resetMagicPointItem002Status(GgafCore::GgafStatus* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
