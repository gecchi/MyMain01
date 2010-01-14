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
     * <tr><th>0より小さい                        </th><th>0  </th><th>0より大きい                  </th></tr>
     * <tr><td>kind_myの方が劣性       </td><td>同格</td><td>kind_myの方が優性</td></tr>
     * <tr><td>kind_enemyの方が優性</td><td>同格</td><td>kind_enemyの方が劣性</td></tr>
     * <table>
     */
    static int judgeMyDominant(actorkint kind_my, actorkint kind_enemy) {
        ret = 0;
        if (kind_my & KIND_MY_SHOT_GU) {
            if (kind_enemy & KIND_ENEMY_SHOT_CHOKI) {
                ret++;
            }
            if (kind_enemy & KIND_ENEMY_SHOT_PA) {
                ret--;
            }
        }

        if (kind_my & KIND_MY_SHOT_CHOKI) {
            if (kind_enemy & KIND_ENEMY_SHOT_PA) {
                ret++;
            }
            if (kind_enemy & KIND_ENEMY_SHOT_GU) {
                ret--;
            }
        }

        if (kind_my & KIND_MY_SHOT_PA) {
            if (kind_enemy & KIND_ENEMY_SHOT_GU) {
                ret++;
            }
            if (kind_enemy & KIND_ENEMY_SHOT_CHOKI) {
                ret--;
            }
        }
        return ret;
    }


    static int judgeEnemyDominant(actorkint kind_enemy, actorkint kind_my) {
        ret = 0;
        if (kind_enemy & KIND_ENEMY_SHOT_GU) {
            if (kind_my & KIND_MY_SHOT_CHOKI) {
                ret++;
            }
            if (kind_my & KIND_MY_SHOT_PA) {
                ret--;
            }
        }

        if (kind_enemy & KIND_ENEMY_SHOT_CHOKI) {
            if (kind_my & KIND_MY_SHOT_PA) {
                ret++;
            }
            if (kind_my & KIND_MY_SHOT_GU) {
                ret--;
            }
        }

        if (kind_enemy & KIND_ENEMY_SHOT_PA) {
            if (kind_my & KIND_MY_SHOT_GU) {
                ret++;
            }
            if (kind_my & KIND_MY_SHOT_CHOKI) {
                ret--;
            }
        }
        return ret;
    }

    /**
     * 自分の体力計算
     * @param pMy
     * @param pEnemy
     * @return
     */
    static int calMyStamina(GgafCore::GgafActor* pMy, GgafCore::GgafActor* pEnemy) {
        int domi = MyStgUtil::judgeMyDominant(pMy->getGroupActor()->_kind, pEnemy->getGroupActor()->_kind);
        if (domi > 0) {
            //自分が優性時
            return pMy->pStatus->minus(STAT_Stamina, pEnemy->_pStatus->get(STAT_AttackRecessive)); //相手の劣性時の攻撃力を受ける
        } else if (domi == 0) {
            //相手と同格時
            return pMy->pStatus->minus(STAT_Stamina, pEnemy->_pStatus->get(STAT_Attack));
        } else if (domi < 0) {
            //自分が劣性時
            return pMy->pStatus->minus(STAT_Stamina, pEnemy->_pStatus->get(STAT_AttackRecessive)); //相手の優性時の攻撃力を受ける
        }
    }



    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」から行っていただきたい。
    // gen01 start
    //自機レーザー
    static void resetMyStraightLaserChip001Status(GgafCore::GgafActor* p);
    //自機
    static void resetMyShipStatus(GgafCore::GgafActor* p);
    //ケレス
    static void resetEnemyCeresStatus(GgafCore::GgafActor* p);
    //ケレスショット001
    static void resetEnemyCeresShot001Status(GgafCore::GgafActor* p);
    //アストラエア
    static void resetEnemyAstraeaStatus(GgafCore::GgafActor* p);
    //アストラエアレーザー
    static void resetEnemyAstraeaLaserChip001Status(GgafCore::GgafActor* p);
    //ヴェスタ
    static void resetEnemyVestaStatus(GgafCore::GgafActor* p);
    //イリス
    static void resetEnemyIrisStatus(GgafCore::GgafActor* p);
    //汎用ショット001
    static void resetShot001Status(GgafCore::GgafActor* p);
    //汎用ショット002
    static void resetShot002Status(GgafCore::GgafActor* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
