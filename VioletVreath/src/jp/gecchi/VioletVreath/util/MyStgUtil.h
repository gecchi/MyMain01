#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/util/GgafStatus.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL VioletVreath::MyStgUtil

#define STATUS(X) (NEW GgafCore::GgafStatus(STAT_BANPEI+1, VioletVreath::MyStgUtil::reset##X##Status))

//イベント用 hashval 数値宣言
HASHVAL(EVENT_GOD_WILL_DIE);
HASHVAL(EVENT_PREPARE_TRANSIT_STAGE);
HASHVAL(EVENT_PREPARE_NEXT_STAGE);
HASHVAL(EVENT_JUST_GAME_OVER);

HASHVAL(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
HASHVAL(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
HASHVAL(EVENT_ALL_MY_SHIP_WAS_DESTROYED);

HASHVAL(EVENT_PREGAMETITLESCENE_FINISH);
HASHVAL(EVENT_GAMETITLESCENE_FINISH);
HASHVAL(EVENT_GAMEDEMOSCENE_FINISH);
HASHVAL(EVENT_GAMESTART);
HASHVAL(EVENT_GOTO_GAMETITLE);
HASHVAL(EVENT_GAMEMODE_DECIDE);
HASHVAL(EVENT_GAMEOVERSCENE_FINISH);
HASHVAL(EVENT_GO_TO_TITLE);
HASHVAL(EVENT_NAMEENTRYSCENE_FINISH);
HASHVAL(EVENT_MENU_NAMEENTRY_DONE);


namespace VioletVreath {


/**
 * 本アプリのユーティリティ .
 * @version 1.00
 * @since 2010/01/06
 * @author Masatoshi Tsuge
 */
class MyStgUtil : public GgafLib::StgUtil {

private:
    /**
     * 自分(敵機)の体力計算 .
     * さらに、体力が0になった場合は、もし相手が自機関連だったならば、
     * ゲームスコア、ゲームランク、自分(敵機)の所属フォーメーションへの破壊されました通知、の
     * 処理も同時に行ってしまう便利メソッドになりつつある！
     * @param prm_pMy  自分(敵機)
     * @param prm_pOpp 相手(敵機以外)
     * @return 自分(敵機)の体力
     */
    static int calcEnemyStamina(GgafCore::GgafMainActor* const prm_pEnemy, const GgafCore::GgafMainActor* prm_pOpp);

    /**
     * 対象アクターに紐ついた保持アイテムを、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_ItemKind の値によってアイテム種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの保持アイテム（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxFigureActor* activateItemOf(const GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた消滅エフェクトを、取得できれば有効にし、それを返す .
     * タイミング的には、爆発エフェクトと同じであることが多い。<BR>
     * 破壊時の変動スコアボーナス表示や、通常の爆発エフェクト以外の特殊なエフェクト等に使用される。<BR>
     * ステータス(getStatus())の STAT_DestroyedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクタ
     * @return 対象アクターの消滅エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxFigureActor* activateDestroyedEffectOf(const GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 打ち返し弾 .
     * @param prm_pActor
     * @return
     */
    static GgafDxCore::GgafDxFigureActor* activateRevengeShotOf(const GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついたダメージ時エフェクトを、取得できれば発動し、それを返す .
     * ステータス(getStatus())の STAT_DamagedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのダメージ時エフェクト（活動済み）。又は、取得できない場合 nullptr。
     * @return
     */
    static GgafDxCore::GgafDxFigureActor* activateDamagedEffectOf(const GgafDxCore::GgafDxGeometricActor* prm_pActor);


    /**
     * 対象アクターの紐ついた、フォーメーション全滅エフェクトとスコア加算処理 .
     * ステータス(getStatus())の STAT_FormationDestroyedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのフォーメーション全滅エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxFigureActor* activateFormationDestroyedEffectOf(const GgafDxCore::GgafDxGeometricActor* prm_pActor);

    /**
     * 対象アクターのに紐ついたフォーメーション全滅アイテムを、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_FormationDestroyedItemKind の値によってアイテム種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのフォーメーション全滅アイテム（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxFigureActor* activateFormationDestroyedItemOf(const GgafDxCore::GgafDxGeometricActor* prm_pActor);


public:
    enum EffectKind {
        EF_NOTHING,
        EF_ENTRY_SMALL001_F90,
        EF_ENTRY_SMALL001_F60,
        EF_ENTRY_SMALL001_F30,
        EF_ENTRY_SMALL001_STAY_F90,
        EF_ENTRY_SMALL001_STAY_F60,
        EF_ENTRY_SMALL001_STAY_F30,
        EF_ENTRY_SMALL001_LONG,
        EF_ENTRY_MIDDLE001,
        EF_ENTRY_LARGE001,
        EF_LEAVE_SMALL001_F60,
        EF_LEAVE_SMALL001_F30,
        EF_LEAVE_SMALL001_F90,
        EF_LEAVE_MIDDLE001,
        EF_LEAVE_LARGE001,
        EF_EXPLOSION001,
        EF_EXPLOSION001_STAY,
        EF_EXPLOSION002,
        EF_EXPLOSION003,
        EF_BONUS001,
        EF_EXPLO_AND_BONUS001,
        EF_TURBO,
        EF_DAMAGED001,
    };

    enum ItemKind {
        ITEM_NOTHING,
        ITEM_MP_SMALL,
        ITEM_MP_MIDDLE,
        ITEM_MP_LARGE,
    };

    enum ShotKind {
        SHOT_NOTHING,

        SHOT_SMALL001,
        SHOT_SMALL002,

        SHOT_RV_NOMAL001,
        SHOT_RV_NOMAL002,
        SHOT_RV_GOLDEN_ANG_WAY,
    };

    enum DepoKind {
        DEPO_NOTHING,
        DEPO_LASER001,
        DEPO_LASER002,
    };

    static bool _was_MyStgUtil_inited_flg;

    static void init();

    /**
     * 黄金角 .
     * 要素[x](0～999) は x 番目の黄金角。
     */
    static angle GOLDEN_ANG[1000];

    /**
     * v = 1 - cos(2πt)の解テーブル .
     * 【説明】
     * t:時間(フレーム)
     * v:速度
     * 面積＝移動距離
     * t = 0.0→0.5→1.0 対してなめらかに v = 0.0～2.0～0.0 と変化し、距離1.0を移動
     */
    static double SMOOTH_DV[3600+1];



    /**
     * 黄金角拡散放射状弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_x               発射元X座標
     * @param prm_y               発射元Y座標
     * @param prm_z               発射元Z座標
     * @param prm_rz              発射方向Rz
     * @param prm_ry              発射方向Ry
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_num         １セット発射数(1～999)
     * @param prm_first_expanse_angle   発射弾の初期照射角(0 ～ D180ANG。懐中電灯の光の広がり角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_inc_expanse_angle     1弾毎に加算する照射角差分(0 ～ D180ANG)
     * @param prm_velo_first      初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            各セットのショット初期加速度
     * @param prm_set_num         撃つ放射状WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxFigureActor* shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                                             angle prm_rz, angle prm_ry,
                                                             GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                             coord prm_r,
                                                             int prm_way_num,
                                                             angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                             velo prm_velo_first, acce prm_acce,
                                                             int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                             void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxFigureActor*, int, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって黄金角拡散放射状弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDxKuroko の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom           発射元
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_num         １セット発射数(1～999)
     * @param prm_first_expanse_angle   発射弾の初期照射角(0 ～ D180ANG。懐中電灯の光の広がり角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_inc_expanse_angle     1弾毎に加算する照射角差分(0 ～ D180ANG)
     * @param prm_velo_first      初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            各セットのショット初期加速度
     * @param prm_set_num         撃つ放射状WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDxCore::GgafDxFigureActor* shotWayGoldenAng(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                           GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                           coord prm_r,
                                                           int prm_way_num,
                                                           angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                           velo prm_velo_first, acce prm_acce,
                                                           int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                           void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxFigureActor*, int, int, int) = nullptr);



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
     * 破壊時に加算されるランクポイントをSTAT_AddRankPoint_Reductionにより減少させる .
     * @param prm_pEnemy 敵
     */
    static void updateEnemyRankPoint(GgafCore::GgafMainActor* prm_pEnemy);

    /**
     * 自分(自機)の体力計算 .
     * @param prm_pMy  自分(自機)
     * @param prm_pOpp 相手(自機以外)
     * @return 自分(自機)の体力
     */
    static int calcMyStamina(GgafCore::GgafMainActor* prm_pMy, const GgafCore::GgafMainActor* const prm_pOpp);


    /**
     * 対象アクターに紐ついた爆発エフェクトを、取得できれば発動し、それを返す .
     * ステータス(getStatus())の STAT_ExplosionEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの爆発エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxFigureActor* activateExplosionEffectOf(const GgafDxCore::GgafDxGeometricActor* const prm_pActor);

    /**
     * 通常ショット .
     * @param prm_pActor
     * @return
     */
    static GgafDxCore::GgafDxFigureActor* activateAttackShotOf(const GgafDxCore::GgafDxGeometricActor* const prm_pActor);

    /**     */
    static GgafCore::GgafActorDepository* getDepositoryOf(const GgafDxCore::GgafDxGeometricActor* const prm_pActor);

    /**
     * 対象アクターに紐ついた入場エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_EntryEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの入場エフェクト（活動済み、nullptrは返らない)
     */
    static EffectBlink* activateEntryEffectOf(const GgafDxCore::GgafDxGeometricActor* const prm_pActor);

    /**
     * 対象アクターに紐ついた退場エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_LeaveEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの退場エフェクト（活動済み、nullptrは返らない)
     */
    static EffectBlink* activateLeaveEffectOf(const GgafDxCore::GgafDxGeometricActor* const prm_pActor);

    /**
     * 対象アクターに紐ついた固有エフェクト（その１）を、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_ProperEffect01Kind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの入場エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDxCore::GgafDxFigureActor* activateProperEffect01Of(const GgafDxCore::GgafDxGeometricActor* const prm_pActor);

    /**
     * 敵キャラヒット時の標準的な処理 .
     * ＜破壊された場合＞<br>
     * ・破壊時得点加算<br>
     * ・ランク加算<br>
     * ・アイテム出現             activateItemOf()<br>
     * ・消滅時特殊エフェクト開始 activateDestroyedEffectOf()<br>
     * ・打ち返し弾出現           activateRevengeShotOf()<br>
     * ・爆発エフェクト出現       activateExplosionEffectOf()<br>
     * ・編隊全滅判定<br>
     * ・編隊全滅時アイテム出現(STAT_ItemKind)<br>
     * ＜破壊されなかった場合＞<br>
     * ・ダメージを与えた得点加算<br>
     * ・ダメージフラッシュ表示       STAT_FlushAble<br>
     * ・ダメージ時特殊エフェクト出現 activateDamagedEffectOf()<br>
     * @param prm_this ヒットした自身（敵キャラ）のアクターを渡す
     * @param prm_pOther ヒットした相手のアクターを渡す
     * @return true:破壊された/false:破壊されてない
     */
    static bool transactEnemyHit(GgafDxCore::GgafDxFigureActor* prm_this, const GgafDxCore::GgafDxGeometricActor* const prm_pOther);

    /**
     * 編隊全破壊時の標準的な処理 .
     * @param prm_pActor_last_destroyed 編隊の最後に破壊されたアクターを渡す
     * @return 編隊全滅時エフェクト
     */
    static GgafDxCore::GgafDxFigureActor* transactFormationDestroyAll(const GgafDxCore::GgafDxFigureActor* const prm_pActor_last_destroyed);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「ステータスCreater.xls」から行うこと。
    // gen01 start
	//自機
	static GgafCore::GgafStatus* resetMyShipStatus(GgafCore::GgafStatus* p);
	//自機ショット
	static GgafCore::GgafStatus* resetMyShot001Status(GgafCore::GgafStatus* p);
	//自機スナイプショット
	static GgafCore::GgafStatus* resetMySnipeShot001Status(GgafCore::GgafStatus* p);
	//マジックエネルギー核
	static GgafCore::GgafStatus* resetMyMagicEnergyCoreStatus(GgafCore::GgafStatus* p);
	//自機レーザー
	static GgafCore::GgafStatus* resetMyStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//分身
	static GgafCore::GgafStatus* resetMyBunshinStatus(GgafCore::GgafStatus* p);
	//分身ションショット
	static GgafCore::GgafStatus* resetMyBunshinShot001Status(GgafCore::GgafStatus* p);
	//分身スナイプションショット
	static GgafCore::GgafStatus* resetMyBunshinSnipeShot001Status(GgafCore::GgafStatus* p);
	//分身カーブレーザー
	static GgafCore::GgafStatus* resetMyBunshinWateringLaserChip001Status(GgafCore::GgafStatus* p);
	//トゥピード
	static GgafCore::GgafStatus* resetMyTorpedoStatus(GgafCore::GgafStatus* p);
	//トゥピード爆風
	static GgafCore::GgafStatus* resetMyTorpedoBlastStatus(GgafCore::GgafStatus* p);
	//汎用ショット001
	static GgafCore::GgafStatus* resetShot001Status(GgafCore::GgafStatus* p);
	//汎用ショット002
	static GgafCore::GgafStatus* resetShot002Status(GgafCore::GgafStatus* p);
	//汎用ショット003ミニレーザー
	static GgafCore::GgafStatus* resetShot003Status(GgafCore::GgafStatus* p);
	//汎用ミニレーザーショット
	static GgafCore::GgafStatus* resetShot004Status(GgafCore::GgafStatus* p);
	//汎用敵ストレートレーザー001
	static GgafCore::GgafStatus* resetEnemyStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//汎用敵カーブレーザー001
	static GgafCore::GgafStatus* resetEnemyWateringLaserChip001Status(GgafCore::GgafStatus* p);
	//エレス
	static GgafCore::GgafStatus* resetEnemyEresStatus(GgafCore::GgafStatus* p);
	//エレスショット001
	static GgafCore::GgafStatus* resetEnemyEresShot001Status(GgafCore::GgafStatus* p);
	//ストラエア
	static GgafCore::GgafStatus* resetEnemyStraeaStatus(GgafCore::GgafStatus* p);
	//ストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyStraeaLaserChip001Status(GgafCore::GgafStatus* p);
	//ストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyStraeaLaserChip002Status(GgafCore::GgafStatus* p);
	//ストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyStraeaLaserChip003Status(GgafCore::GgafStatus* p);
	//ストラエアレーザー
	static GgafCore::GgafStatus* resetEnemyStraeaLaserChip004Status(GgafCore::GgafStatus* p);
	//オムルス（ラティスラヴィアのハッチ）
	static GgafCore::GgafStatus* resetEnemyOmulusStatus(GgafCore::GgafStatus* p);
	//エムス（ラティスラヴィアのハッチ）
	static GgafCore::GgafStatus* resetEnemyEmusStatus(GgafCore::GgafStatus* p);
	//エムスのレーザー
	static GgafCore::GgafStatus* resetEnemyEmusLaserChip001Status(GgafCore::GgafStatus* p);
	//エティス
	static GgafCore::GgafStatus* resetEnemyEtisStatus(GgafCore::GgafStatus* p);
	//リス
	static GgafCore::GgafStatus* resetEnemyRisStatus(GgafCore::GgafStatus* p);
	//ゲリア
	static GgafCore::GgafStatus* resetEnemyGeriaStatus(GgafCore::GgafStatus* p);
	//ハリア
	static GgafCore::GgafStatus* resetEnemyHaliaStatus(GgafCore::GgafStatus* p);
	//たまご１
	static GgafCore::GgafStatus* resetEnemyTamago01Status(GgafCore::GgafStatus* p);
	//イルケ
	static GgafCore::GgafStatus* resetEnemyIrceStatus(GgafCore::GgafStatus* p);
	//ラティスラヴィア（トーラス）
	static GgafCore::GgafStatus* resetEnemyRatislaviaStatus(GgafCore::GgafStatus* p);
	//地形ボックス001
	static GgafCore::GgafStatus* resetWall001Status(GgafCore::GgafStatus* p);
	//地形プリズム001
	static GgafCore::GgafStatus* resetWall001PrismStatus(GgafCore::GgafStatus* p);
	//アラス
	static GgafCore::GgafStatus* resetEnemyAllasStatus(GgafCore::GgafStatus* p);
	//ウーノミア
	static GgafCore::GgafStatus* resetEnemyUnomiaStatus(GgafCore::GgafStatus* p);
	//エミリア
	static GgafCore::GgafStatus* resetEnemyEmiliaStatus(GgafCore::GgafStatus* p);
	//エミリア断片
	static GgafCore::GgafStatus* resetEnemyEmiliaFragmentStatus(GgafCore::GgafStatus* p);
	//エミリア断片の断片
	static GgafCore::GgafStatus* resetEnemyEmiliaFragment2Status(GgafCore::GgafStatus* p);
	//エミリア断片の断片の断片
	static GgafCore::GgafStatus* resetEnemyEmiliaFragment3Status(GgafCore::GgafStatus* p);
	//MPアイテム小
	static GgafCore::GgafStatus* resetMagicPointItem001Status(GgafCore::GgafStatus* p);
	//MPアイテム中
	static GgafCore::GgafStatus* resetMagicPointItem002Status(GgafCore::GgafStatus* p);
	//MPアイテム大
	static GgafCore::GgafStatus* resetMagicPointItem003Status(GgafCore::GgafStatus* p);
	//スコアアイテム
	static GgafCore::GgafStatus* resetScoreItem001Status(GgafCore::GgafStatus* p);
	//Vreathアイテム
	static GgafCore::GgafStatus* resetVreathItem001Status(GgafCore::GgafStatus* p);
	//エーベ
	static GgafCore::GgafStatus* resetEnemyEbeStatus(GgafCore::GgafStatus* p);
	//ヒズビー
	static GgafCore::GgafStatus* resetEnemyHisbeStatus(GgafCore::GgafStatus* p);
	//ヒズビー2
	static GgafCore::GgafStatus* resetEnemyHisbe002Status(GgafCore::GgafStatus* p);
	//ヒズビーレーザー
	static GgafCore::GgafStatus* resetEnemyHisbeLaserChip001Status(GgafCore::GgafStatus* p);
	//ヒズビーレーザー
	static GgafCore::GgafStatus* resetEnemyHisbeLaserChip002Status(GgafCore::GgafStatus* p);
	//ヒズビーレーザー
	static GgafCore::GgafStatus* resetEnemyHisbeLaserChip003Status(GgafCore::GgafStatus* p);
	//ドラステア
	static GgafCore::GgafStatus* resetEnemyDrasteaStatus(GgafCore::GgafStatus* p);
	//タランテ
	static GgafCore::GgafStatus* resetEnemyTalanteStatus(GgafCore::GgafStatus* p);
	//エスペリア
	static GgafCore::GgafStatus* resetEnemyEsperiaStatus(GgafCore::GgafStatus* p);
	//エスペリアアレーザー
	static GgafCore::GgafStatus* resetEnemyEsperiaLaserChip001Status(GgafCore::GgafStatus* p);
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
	//ラティスラヴィアアイ
	static GgafCore::GgafStatus* resetEnemyRatislaviaEyeStatus(GgafCore::GgafStatus* p);
	//ラティスラヴィアアイ用ストレートレーザー001
	static GgafCore::GgafStatus* resetEnemyRatislaviaEyeStraightLaserChip001Status(GgafCore::GgafStatus* p);
	//エルミオネ
	static GgafCore::GgafStatus* resetEnemyErmioneStatus(GgafCore::GgafStatus* p);
	//エルミオネ腕の頭
	static GgafCore::GgafStatus* resetEnemyErmioneArmHeadStatus(GgafCore::GgafStatus* p);
	//エルミオネ腕の胴体
	static GgafCore::GgafStatus* resetEnemyErmioneArmBodyStatus(GgafCore::GgafStatus* p);
	//エルミオネ腕の弱点
	static GgafCore::GgafStatus* resetEnemyErmioneArmWeakStatus(GgafCore::GgafStatus* p);
	//アッポー
	static GgafCore::GgafStatus* resetEnemyApphoStatus(GgafCore::GgafStatus* p);
	//アンティオペ
	static GgafCore::GgafStatus* resetEnemyAntiopeStatus(GgafCore::GgafStatus* p);
	//デルヘイド
	static GgafCore::GgafStatus* resetEnemyDelheidStatus(GgafCore::GgafStatus* p);
	//アリサナ
	static GgafCore::GgafStatus* resetEnemyAlisanaStatus(GgafCore::GgafStatus* p);
	//イーダ
	static GgafCore::GgafStatus* resetEnemyIdaStatus(GgafCore::GgafStatus* p);
	//タゴラス
	static GgafCore::GgafStatus* resetEnemyThagorasStatus(GgafCore::GgafStatus* p);
	//オルトゥナ
	static GgafCore::GgafStatus* resetEnemyOrtunaStatus(GgafCore::GgafStatus* p);
	//グラヤ
	static GgafCore::GgafStatus* resetEnemyGlajaStatus(GgafCore::GgafStatus* p);
	//グラヤ槍弾
	static GgafCore::GgafStatus* resetEnemyGlajaLance001Status(GgafCore::GgafStatus* p);
	//ドゥーナ
	static GgafCore::GgafStatus* resetEnemyDunaStatus(GgafCore::GgafStatus* p);
	//オーツァルティア
	static GgafCore::GgafStatus* resetEnemyOzartiaStatus(GgafCore::GgafStatus* p);
	//オーツァルティアショット０１(壁ブロック)
	static GgafCore::GgafStatus* resetEnemyOzartiaShot01Status(GgafCore::GgafStatus* p);
	//オーツァルティアレーザーチップ
	static GgafCore::GgafStatus* resetEnemyOzartiaLaserChip01Status(GgafCore::GgafStatus* p);
	//オーツァルティア氷柱
	static GgafCore::GgafStatus* resetEnemyOzartiaPillar01Status(GgafCore::GgafStatus* p);
	//エビウス
	static GgafCore::GgafStatus* resetEnemyOebiusStatus(GgafCore::GgafStatus* p);
	//エビウスコア
	static GgafCore::GgafStatus* resetEnemyOebiusCoreStatus(GgafCore::GgafStatus* p);
	//ウリュディケ
	static GgafCore::GgafStatus* resetEnemyUrydikeStatus(GgafCore::GgafStatus* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
