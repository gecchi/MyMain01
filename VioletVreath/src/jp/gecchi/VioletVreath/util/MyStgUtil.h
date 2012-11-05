#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_




#ifdef UTIL
    #undef UTIL
#endif
#define UTIL VioletVreath::MyStgUtil

#define STATUS(X) (NEW GgafCore::GgafStatus(STAT_Sentry+1, VioletVreath::MyStgUtil::reset##X##Status))

namespace VioletVreath {

class MyStgUtil : public GgafLib::StgUtil {
public:


    /**
     * 優位性を調べる
     * @param kind_my
     * @param kind_enemy
     * @return 以下の表参照。
     * <table>
     * <tr><th>0より小さい         </th><th>0   </th><th>0より大きい         </th></tr>
     * <tr><td>attribute_myの方が劣性   </td><td>同格</td><td>kind_myの方が優性   </td></tr>
     * <tr><td>attribute_enemyの方が優性</td><td>同格</td><td>kind_enemyの方が劣性</td></tr>
     * </table>
     */
    static int judgeMyDomination(actorkind attribute_my, actorkind attribute_enemy) {
        int ret = 0;
        if (attribute_my & ATTRIBUTE_GU) {
            if (attribute_enemy & ATTRIBUTE_CHOKI) {
                ret++;
            }
            if (attribute_enemy & ATTRIBUTE_PA) {
                ret--;
            }
        }

        if (attribute_my & ATTRIBUTE_CHOKI) {
            if (attribute_enemy & ATTRIBUTE_PA) {
                ret++;
            }
            if (attribute_enemy & ATTRIBUTE_GU) {
                ret--;
            }
        }

        if (attribute_my & ATTRIBUTE_PA) {
            if (attribute_enemy & ATTRIBUTE_GU) {
                ret++;
            }
            if (attribute_enemy & ATTRIBUTE_CHOKI) {
                ret--;
            }
        }
        return ret;
    }


    static int judgeEnemyDomination(actorkind kattribute_enemy, actorkind attribute_my) {
        int ret = 0;
        if (kattribute_enemy & ATTRIBUTE_GU) {
            if (attribute_my & ATTRIBUTE_CHOKI) {
                ret++;
            }
            if (attribute_my & ATTRIBUTE_PA) {
                ret--;
            }
        }

        if (kattribute_enemy & ATTRIBUTE_CHOKI) {
            if (attribute_my & ATTRIBUTE_PA) {
                ret++;
            }
            if (attribute_my & ATTRIBUTE_GU) {
                ret--;
            }
        }

        if (kattribute_enemy & ATTRIBUTE_PA) {
            if (attribute_my & ATTRIBUTE_GU) {
                ret++;
            }
            if (attribute_my & ATTRIBUTE_CHOKI) {
                ret--;
            }
        }
        return ret;
    }

    /**
     * 自分(自機)の体力計算 .
     * @param prm_pMy  自分(自機)
     * @param prm_pOpp 相手(自機以外)
     * @return 自分(自機)の体力
     */
    static int calcMyStamina(GgafCore::GgafMainActor* prm_pMy, GgafCore::GgafMainActor* prm_pOpp) {
        GgafCore::GgafStatus* pStatMy = prm_pMy->_pStatus;
        GgafCore::GgafStatus* pStatOpp = prm_pOpp->_pStatus;

        //優性劣性判定
        int my_domi = MyStgUtil::judgeMyDomination(pStatMy->get(STAT_Attribute), pStatOpp->get(STAT_Attribute));
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

    /**
     * 自分(敵機)の体力計算 .
     * 体力が0になった場合、相手が自機関連だった場合
     * ゲームスコア、ゲームランク、自分(敵機)の所属フォーメーションへの破壊されました通知、の
     * 処理も行ってしまう。
     * @param prm_pMy  自分(敵機)
     * @param prm_pOpp 相手(敵機以外)
     * @return 自分(敵機)の体力
     */
    static int calcEnemyStamina(GgafCore::GgafMainActor* prm_pEnemy, GgafCore::GgafMainActor* prm_pOpp) {
        GgafCore::GgafStatus* pStatEnemy = prm_pEnemy->_pStatus;
        GgafCore::GgafStatus* pStatOpp = prm_pOpp->_pStatus;
        //優性劣性判定
        int enemy_domi = MyStgUtil::judgeEnemyDomination(pStatEnemy->get(STAT_Attribute), pStatOpp->get(STAT_Attribute));
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
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_RecessiveDefenceRate)));
        } else {
            //相手(自機)と同格時
            enemy_stamina = pStatEnemy->minus(STAT_Stamina,
                                              (int)(opp_attack * pStatEnemy->getDouble(STAT_DefaultDefenceRate)));
        }
        if (enemy_stamina <= 0 && (prm_pOpp->getKind() & KIND_MY)) {
            //相手(自機)の種別が MY*** （自機関連） ならば
            _SCORE_ += pStatEnemy->get(STAT_AddScorePoint);      //得点
            _RANK_  += pStatEnemy->getDouble(STAT_AddRankPoint); //ランク加算
            prm_pEnemy->notifyDestroyedToFormation(); //編隊全滅判定に有効な破壊のされ方でしたよ通知

            if (prm_pEnemy->getPlatformScene()->instanceOf(Obj_RankUpStage)) {
                //ランクアップステージの敵ならば、
                RankUpStage* pRankUpStage = (RankUpStage*)(prm_pEnemy->getPlatformScene());
                pRankUpStage->hit_enemy_num_ ++; //ランクアップステージの敵倒したよ！カウントアップ
            }
        }
        return enemy_stamina;
    }


    /**
     * 対象アクターに紐ついた爆発エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_ExplosionEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの爆発エフェクト（活動済み）。又は、取得できない場合 NULL。
     */
    static GgafDxCore::GgafDxDrawableActor* activateExplosionEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        GgafDxCore::GgafDxDrawableActor* pE = NULL;
        switch (prm_pActor->_pStatus->get(STAT_ExplosionEffectKind)) {
            case 0: {
                pE = NULL; //爆発エフェクト無し
                break;
            }
            case 1: {
                pE = employFromCommon(EffectExplosion001);
                break;
            }
            case 2: {
                pE = employFromCommon(EffectExplosion002);
                break;
            }
            case 3: {
                pE = employFromCommon(EffectExplosion003);
                break;
            }
            default: {
                _TRACE_("＜警告＞ 対応 ExplosionEffect が定義されてない。prm_pActor="<<prm_pActor->getName());
                pE = NULL;
                break;
            }
        }

        if (pE) {
            //出現座標を設定
            pE->locateWith(prm_pActor);
            pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
        }
        return pE;
    }

    /**
     * 対象アクターに紐ついた保持アイテムを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_ItemKind の値によってアイテム種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの保持アイテム（活動済み）。又は、取得できない場合 NULL。
     */
    static GgafDxCore::GgafDxDrawableActor* activateItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        GgafDxCore::GgafDxDrawableActor* pI = NULL;
        switch (prm_pActor->_pStatus->get(STAT_ItemKind)) {
            case 0: {
                pI = NULL; //アイテム無し
                break;
            }
            case 1: {
                pI = employFromCommon(MagicPointItem001);
                break;
            }
            case 2: {
                pI = employFromCommon(MagicPointItem002);
                break;
            }
            default: {
                _TRACE_("＜警告＞ 対応 ExplosionEffect が定義されてない。prm_pActor="<<prm_pActor->getName());
                pI = NULL;
                break;
            }
        }
        if (pI) {
            //出現座標を設定
            pI->locateWith(prm_pActor);
        }
        return pI;
    }

    /**
     * 対象アクターに紐ついた入場エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_EntryEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの入場エフェクト（活動済み）。又は、取得できない場合 NULL。
     */
    static GgafDxCore::GgafDxDrawableActor* activateEntryEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        GgafDxCore::GgafDxDrawableActor* pE = NULL;
        switch (prm_pActor->_pStatus->get(STAT_EntryEffectKind)) {
            case 0: {
                pE = NULL; //入場エフェクト無し
                break;
            }
            case 1: {
                pE = employFromCommon(EffectEntry001);
                break;
            }
            case 2: {
                pE = employFromCommon(EffectEntry002);
                break;
            }
            case 3: {
                pE = employFromCommon(EffectEntry003);
                break;
            }
            default: {
                pE = NULL;
                break;
            }
        }
        if (pE) {
            //出現座標を設定
            pE->locateWith(prm_pActor);
        }
        return pE;
    }

    /**
     * 対象アクターの紐ついた、フォーメーション全滅エフェクトとスコア加算処理 .
     * ステータス(_pStatus)の STAT_FormationDestroyedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのフォーメーション全滅エフェクト（活動済み）。又は、取得できない場合 NULL。
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        int addscore = prm_pActor->_pStatus->get(STAT_FormationDestroyedAddScorePoint); //フォーメーション全滅得点加算
        _SCORE_ += addscore;
        GgafDxCore::GgafDxDrawableActor* pE = NULL;
        switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedEffectKind)) {
            case 0: {
                pE = NULL; //エフェクト無し
                break;
            }
            case 1: {
                //1は通常のフォーメーションボーナススコア表示エフェクト
                SpriteLabelBonus001* pLabel = employForceFromCommon(SpriteLabelBonus001);
                pLabel->locateWith(prm_pActor);
                pLabel->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
                std::string s = ITOS(addscore);
                pLabel->update(s.c_str());
                pE = pLabel;
                break;
            }
//            case 2: {
//                pE = employFromCommon(EffectExplosion002);
//                break;
//            }
//            case 3: {
//                pE = employFromCommon(EffectExplosion003);
//                break;
//            }
            default: {
                _TRACE_("＜警告＞ 対応 STAT_FormationDestroyedEffectKind が定義されてない。prm_pActor="<<prm_pActor->getName());
                pE = NULL;
                break;
            }
        }

//        if (pE) {
//            //出現座標を設定
//            pE->locateWith(prm_pActor);
//            pE->_pKurokoA->followMvFrom(prm_pActor->_pKurokoA);
//        }
        return pE;
    }

    /**
     * 対象アクターのに紐ついたフォーメーション全滅アイテムを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_FormationDestroyedItemKind の値によってアイテム種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのフォーメーション全滅アイテム（活動済み）。又は、取得できない場合 NULL。
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor) {
        GgafDxCore::GgafDxDrawableActor* pI = NULL;
        switch (prm_pActor->_pStatus->get(STAT_FormationDestroyedItemKind)) {
            case 0: {
                pI = NULL; //アイテム無し
                break;
            }
            case 1: {
                pI = employFromCommon(MagicPointItem001);
                break;
            }
            case 2: {
                pI = employFromCommon(MagicPointItem002);
                break;
            }
            default: {
                _TRACE_("＜警告＞ 対応 STAT_FormationDestroyedItemKind が定義されてない。prm_pActor="<<prm_pActor->getName());
                pI = NULL;
                break;
            }
        }
        if (pI) {
            //出現座標を設定
            pI->locateWith(prm_pActor);
        }
        return pI;
    }


    static int nextRepeatVal(int prm_id) {
        return 0;
    }

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「ステータスCreater.xls」から行うこと。
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
	//ロムルス（シルヴィアのハッチ）
	static GgafCore::GgafStatus* resetEnemyRomulusStatus(GgafCore::GgafStatus* p);
	//レムス（シルヴィアのハッチ）
	static GgafCore::GgafStatus* resetEnemyRemusStatus(GgafCore::GgafStatus* p);
	//レムスのレーザー
	static GgafCore::GgafStatus* resetEnemyRemusLaserChip001Status(GgafCore::GgafStatus* p);
	//メティス
	static GgafCore::GgafStatus* resetEnemyMetisStatus(GgafCore::GgafStatus* p);
	//イリス
	static GgafCore::GgafStatus* resetEnemyIrisStatus(GgafCore::GgafStatus* p);
	//ジュノー
	static GgafCore::GgafStatus* resetEnemyJunoStatus(GgafCore::GgafStatus* p);
	//タリラ
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
	//シルヴィア（トーラス）
	static GgafCore::GgafStatus* resetEnemySylviaStatus(GgafCore::GgafStatus* p);
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
	//オプション
	static GgafCore::GgafStatus* resetMyOptionStatus(GgafCore::GgafStatus* p);
	//アイテム
	static GgafCore::GgafStatus* resetMagicPointItem001Status(GgafCore::GgafStatus* p);
	//編隊全滅アイテム
	static GgafCore::GgafStatus* resetMagicPointItem002Status(GgafCore::GgafStatus* p);
	//ヘーベ
	static GgafCore::GgafStatus* resetEnemyHebeStatus(GgafCore::GgafStatus* p);
	//シズビー
	static GgafCore::GgafStatus* resetEnemyThisbeStatus(GgafCore::GgafStatus* p);
	//シズビーレーザー
	static GgafCore::GgafStatus* resetEnemyThisbeLaserChip001Status(GgafCore::GgafStatus* p);
	//アドラステア
	static GgafCore::GgafStatus* resetEnemyAdrasteaStatus(GgafCore::GgafStatus* p);
	//アタランテ
	static GgafCore::GgafStatus* resetEnemyAtalanteStatus(GgafCore::GgafStatus* p);
	//アストラエア
	static GgafCore::GgafStatus* resetEnemyHesperiaStatus(GgafCore::GgafStatus* p);
	//アストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyHesperiaLaserChip001Status(GgafCore::GgafStatus* p);
	//グーテスト
	static GgafCore::GgafStatus* resetTestGuStatus(GgafCore::GgafStatus* p);
	//チョキーテスト
	static GgafCore::GgafStatus* resetTestChokiStatus(GgafCore::GgafStatus* p);
	//パーテスト
	static GgafCore::GgafStatus* resetTestPaStatus(GgafCore::GgafStatus* p);
	//ノーマルーテスト
	static GgafCore::GgafStatus* resetTestNomalStatus(GgafCore::GgafStatus* p);
	//グーショット
	static GgafCore::GgafStatus* resetTestGuShotStatus(GgafCore::GgafStatus* p);
	//チョキーショット
	static GgafCore::GgafStatus* resetTestChokiShotStatus(GgafCore::GgafStatus* p);
	//パーショット
	static GgafCore::GgafStatus* resetTestPaShotStatus(GgafCore::GgafStatus* p);
	//ノーマルーショット
	static GgafCore::GgafStatus* resetTestNomalShotStatus(GgafCore::GgafStatus* p);
	//シルヴィアアイ
	static GgafCore::GgafStatus* resetEnemySylviaEyeStatus(GgafCore::GgafStatus* p);
	//シルヴィアアイ用ストレートレーザー001
	static GgafCore::GgafStatus* resetEnemySylviaEyeStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//ヘルミオネ
	static GgafCore::GgafStatus* resetEnemyHermioneStatus(GgafCore::GgafStatus* p);
	//ヘルミオネ腕の頭
	static GgafCore::GgafStatus* resetEnemyHermioneArmHeadStatus(GgafCore::GgafStatus* p);
	//ヘルミオネ腕の胴体
	static GgafCore::GgafStatus* resetEnemyHermioneArmBodyStatus(GgafCore::GgafStatus* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
