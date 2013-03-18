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
    enum EffectKind {
        EF_NOTHING,
        EF_ENTRY_SMALL001,
        EF_ENTRY_MIDDLE001,
        EF_ENTRY003,
        EF_EXPLOSION001 ,
        EF_EXPLOSION002,
        EF_EXPLOSION003,
        EF_BONUS001,
        EF_EXPLO_AND_BONUS001,
        EF_TURBO,
    };

    enum ItemKind {
        ITEM_MP_SMALL = 1,
        ITEM_MP_MIDDLE,
    };
    enum ShotKind {
        SHOT_SMALL001 = 1,
        SHOT_SMALL002,
    };


    /**
     * 自機側の優位性を調べる
     * @param kind_my
     * @param kind_enemy
     * @return 以下の表参照。
     * <table>
     * <tr><th>0より小さい              </th><th>0   </th><th>0より大きい         </th></tr>
     * <tr><td>attribute_myの方が劣性   </td><td>同格</td><td>kind_myの方が優性   </td></tr>
     * <tr><td>attribute_enemyの方が優性</td><td>同格</td><td>kind_enemyの方が劣性</td></tr>
     * </table>
     */
    static int judgeMyAdvantage(actorkind attribute_my, actorkind attribute_enemy);

    static int judgeEnemyAdvantage(actorkind kattribute_enemy, actorkind attribute_my);

    /**
     * 自分(自機)の体力計算 .
     * @param prm_pMy  自分(自機)
     * @param prm_pOpp 相手(自機以外)
     * @return 自分(自機)の体力
     */
    static int calcMyStamina(GgafCore::GgafMainActor* prm_pMy, GgafCore::GgafMainActor* prm_pOpp);

    /**
     * 自分(敵機)の体力計算 .
     * 体力が0になった場合、相手が自機関連だった場合
     * ゲームスコア、ゲームランク、自分(敵機)の所属フォーメーションへの破壊されました通知、の
     * 処理も行ってしまう。
     * @param prm_pMy  自分(敵機)
     * @param prm_pOpp 相手(敵機以外)
     * @return 自分(敵機)の体力
     */
    static int calcEnemyStamina(GgafCore::GgafMainActor* prm_pEnemy, GgafCore::GgafMainActor* prm_pOpp);

    /**
     * 対象アクターに紐ついた爆発エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_ExplosionEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの爆発エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxDrawableActor* activateExplosionEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    static GgafDxCore::GgafDxDrawableActor* activateShotOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた保持アイテムを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_ItemKind の値によってアイテム種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの保持アイテム（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxDrawableActor* activateItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた消滅エフェクトを、取得できれば有効にし、それを返す .
     * 中型機の場合のスコア表示等に使用される。<BR>
     * ステータス(_pStatus)の STAT_DestroyedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクタ
     * @return 対象アクターの消滅エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxDrawableActor* activateDestroyedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた入場エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_EntryEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの入場エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxDrawableActor* activateEntryEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた退場エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_LeaveEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの退場エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxDrawableActor* activateLeaveEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターの紐ついた、フォーメーション全滅エフェクトとスコア加算処理 .
     * ステータス(_pStatus)の STAT_FormationDestroyedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのフォーメーション全滅エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedEffectOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);
    /**
     * 対象アクターのに紐ついたフォーメーション全滅アイテムを、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_FormationDestroyedItemKind の値によってアイテム種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのフォーメーション全滅アイテム（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxDrawableActor* activateFormationDestroyedItemOf(GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた固有エフェクト（その１）を、取得できれば有効にし、それを返す .
     * ステータス(_pStatus)の STAT_ProperEffect01Kind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの入場エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxDrawableActor* activateProperEffect01Of(GgafDxCore::GgafDxGeometricActor* prm_pActor);

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
	//MPアイテム
	static GgafCore::GgafStatus* resetMagicPointItem001Status(GgafCore::GgafStatus* p);
	//編隊全滅MPアイテム
	static GgafCore::GgafStatus* resetMagicPointItem002Status(GgafCore::GgafStatus* p);
	//スコアアイテム
	static GgafCore::GgafStatus* resetScoreItem001Status(GgafCore::GgafStatus* p);
	//Vreathアイテム
	static GgafCore::GgafStatus* resetVreathItem001Status(GgafCore::GgafStatus* p);
	//ヘーベ
	static GgafCore::GgafStatus* resetEnemyHebeStatus(GgafCore::GgafStatus* p);
	//シズビー
	static GgafCore::GgafStatus* resetEnemyThisbeStatus(GgafCore::GgafStatus* p);
	//シズビー2
	static GgafCore::GgafStatus* resetEnemyThisbe002Status(GgafCore::GgafStatus* p);
	//シズビーレーザー
	static GgafCore::GgafStatus* resetEnemyThisbeLaserChip001Status(GgafCore::GgafStatus* p);
	//シズビーレーザー
	static GgafCore::GgafStatus* resetEnemyThisbeLaserChip002Status(GgafCore::GgafStatus* p);
	//シズビーレーザー
	static GgafCore::GgafStatus* resetEnemyThisbeLaserChip003Status(GgafCore::GgafStatus* p);
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
	//ヘルミオネ腕の弱点
	static GgafCore::GgafStatus* resetEnemyHermioneArmWeakStatus(GgafCore::GgafStatus* p);
	//サッフォー
	static GgafCore::GgafStatus* resetEnemySapphoStatus(GgafCore::GgafStatus* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
