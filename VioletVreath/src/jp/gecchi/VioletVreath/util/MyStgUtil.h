#ifndef MYSTGUTIL_H_
#define MYSTGUTIL_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/util/Status.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL VioletVreath::MyStgUtil

#define STATUS(X) (NEW GgafCore::Status(VioletVreath::MyStgUtil::reset##X##Status))
#define StatusReset(X) ((void*)(VioletVreath::MyStgUtil::reset##X##Status))

//イベント用 eventval 数値宣言
DECLARE_EVENT_VAL(EVENT_CARETAKER_WILL_DEMISE);
DECLARE_EVENT_VAL(EVENT_PREPARE_TRANSIT_STAGE);
DECLARE_EVENT_VAL(EVENT_PREPARE_NEXT_STAGE);
DECLARE_EVENT_VAL(EVENT_JUST_GAME_OVER);

DECLARE_EVENT_VAL(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
DECLARE_EVENT_VAL(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
DECLARE_EVENT_VAL(EVENT_ALL_MY_SHIP_WAS_DESTROYED);

DECLARE_EVENT_VAL(EVENT_PREGAMETITLESCENE_FINISH);
DECLARE_EVENT_VAL(EVENT_GAMETITLESCENE_FINISH);
DECLARE_EVENT_VAL(EVENT_GAMEDEMOSCENE_FINISH);
DECLARE_EVENT_VAL(EVENT_GAMESTART);
DECLARE_EVENT_VAL(EVENT_GAMEMODE_DECIDE);
DECLARE_EVENT_VAL(EVENT_GAMEOVERSCENE_FINISH);
DECLARE_EVENT_VAL(EVENT_GO_TO_TITLE);
DECLARE_EVENT_VAL(EVENT_NAMEENTRYSCENE_FINISH);

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
    static int calcEnemyStamina(GgafCore::MainActor* const prm_pEnemy, const GgafCore::MainActor* prm_pOpp);

    /**
     * 対象アクターに紐ついた保持アイテムを、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_ItemKind の値によってアイテム種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの保持アイテム（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDx::FigureActor* activateItemOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた消滅エフェクトを、取得できれば有効にし、それを返す .
     * タイミング的には、爆発エフェクトと同じであることが多い。<BR>
     * 破壊時の変動スコアボーナス表示や、通常の爆発エフェクト以外の特殊なエフェクト等に使用される。<BR>
     * ステータス(getStatus())の STAT_DestroyedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクタ
     * @return 対象アクターの消滅エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDx::FigureActor* activateDestroyedEffectOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * 打ち返し弾 .
     * @param prm_pActor
     * @return
     */
    static GgafDx::FigureActor* activateRevengeShotOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついたダメージ時エフェクトを、取得できれば発動し、それを返す .
     * ステータス(getStatus())の STAT_DamagedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのダメージ時エフェクト（活動済み）。又は、取得できない場合 nullptr。
     * @return
     */
    static GgafDx::FigureActor* activateDamagedEffectOf(GgafDx::GeometricActor* prm_pActor);


    /**
     * 対象アクターの紐ついた、フォーメーション全滅エフェクトとスコア加算処理 .
     * ステータス(getStatus())の STAT_FormationDestroyedEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのフォーメーション全滅エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDx::FigureActor* activateFormationDestroyedEffectOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * 対象アクターのに紐ついたフォーメーション全滅アイテムを、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_FormationDestroyedItemKind の値によってアイテム種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターのフォーメーション全滅アイテム（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDx::FigureActor* activateFormationDestroyedItemOf(GgafDx::GeometricActor* prm_pActor);


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
     * 攻撃力の威力率 .
     * 近距離ショットのほうが攻撃力が高くなるようにしたいための配列。
     * 要素は出現フレーム数、値は攻撃力に乗じられる補正率。
     */
    static double SHOT_POWER[300+1];

    /**
     * 黄金角拡散放射状弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
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
     * @param prm_draw_set_num         撃つ放射状WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                                  angle prm_rz, angle prm_ry,
                                                  GgafCore::ActorDepository* prm_pDepo_shot,
                                                  coord prm_r,
                                                  int prm_way_num,
                                                  angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                  velo prm_velo_first, acce prm_acce,
                                                  int prm_draw_set_num, frame prm_interval_frames, float prm_attenuated,
                                                  void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);

    /**
     * 発射元が向いている方向（_rz > _ry）に向かって黄金角拡散放射状弾を複数セット同時に撃つ .
     * 発射するショットに、次の項目が設定されます。<BR>
     * ・ショットの _x, _y, _z 座標 <BR>
     * ・ショットの GgafDx::VecVehicle の移動方向、移動速度、加速度<BR>
     * @param prm_pFrom           発射元
     * @param prm_pDepo_shot      発射するショットのデポジトリ
     * @param prm_r               発射元と発射するショットの初期表示位置距離(発射元からの半径)。0より大きい値の必要有り。
     * @param prm_way_num         １セット発射数(1～999)
     * @param prm_first_expanse_angle   発射弾の初期照射角(0 ～ D180ANG。懐中電灯の光の広がり角のようなイメージ。小さいと弾の間隔が狭い)
     * @param prm_inc_expanse_angle     1弾毎に加算する照射角差分(0 ～ D180ANG)
     * @param prm_velo_first      初弾セットのショット初期速度。初弾セット以降の初期速度は prm_attenuated を乗じていく。
     * @param prm_acce            各セットのショット初期加速度
     * @param prm_draw_set_num         撃つ放射状WAY弾の合計セット数
     * @param prm_interval_frames 弾セットと弾セットの出現フレーム間隔。(0より大きい設定値で、時間差打ち返しのような演出になる。0 指定は全セット一斉発射。）
     * @param prm_attenuated      初弾セット以降のセット毎のショット初期速度へ乗率。速度減衰(< 1.0)或いは速度増加(>1.0)。1.0は全セット速度が同じ。
     * @param pFunc_call_back_dispatched
     * @return 最後の発射弾のアクター(撃てなかった場合は nullptr)
     */
    static GgafDx::FigureActor* shotWayGoldenAng(GgafDx::GeometricActor* prm_pFrom,
                                                  GgafCore::ActorDepository* prm_pDepo_shot,
                                                  coord prm_r,
                                                  int prm_way_num,
                                                  angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                  velo prm_velo_first, acce prm_acce,
                                                  int prm_draw_set_num, frame prm_interval_frames, float prm_attenuated,
                                                  void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);



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
    static int judgeMyAdvantage(kind_t attribute_my, kind_t attribute_enemy);

    static int judgeEnemyAdvantage(kind_t kattribute_enemy, kind_t attribute_my);

    /**
     * 自分(自機)の体力計算 .
     * @param prm_pMy  自分(自機)
     * @param prm_pOpp 相手(自機以外)
     * @return 自分(自機)の体力
     */
    static int calcMyStamina(GgafCore::MainActor* prm_pMy, const GgafCore::MainActor* const prm_pOpp);


    /**
     * 対象アクターに紐ついた爆発エフェクトを、取得できれば発動し、それを返す .
     * ステータス(getStatus())の STAT_ExplosionEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの爆発エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDx::FigureActor* activateExplosionEffectOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * 通常ショット .
     * @param prm_pActor
     * @return
     */
    static GgafDx::FigureActor* activateAttackShotOf(GgafDx::GeometricActor* prm_pActor);

    /**     */
    static GgafCore::ActorDepository* getDepositoryOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた入場エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_EntryEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの入場エフェクト（活動済み、nullptrは返らない)
     */
    static EffectBlink* activateEntryEffectOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた退場エフェクトを、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_LeaveEffectKind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの退場エフェクト（活動済み、nullptrは返らない)
     */
    static EffectBlink* activateLeaveEffectOf(GgafDx::GeometricActor* prm_pActor);

    /**
     * 対象アクターに紐ついた固有エフェクト（その１）を、取得できれば有効にし、それを返す .
     * ステータス(getStatus())の STAT_ProperEffect01Kind の値によって種類が振り分けられる。
     * @param prm_pActor 対象アクター
     * @return 対象アクターの入場エフェクト（活動済み）。又は、取得できない場合 nullptr。
     */
    static GgafDx::FigureActor* activateProperEffect01Of(GgafDx::GeometricActor* prm_pActor);

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
    static bool performEnemyHit(GgafDx::FigureActor* prm_this, const GgafDx::GeometricActor* const prm_pOther);

    /**
     * 編隊全破壊時の標準的な処理 .
     * @param prm_pActor_last_destroyed 編隊の最後に破壊されたアクターを渡す
     * @return 編隊全滅時エフェクト
     */
    static GgafDx::FigureActor* performFormationDestroyAll(GgafDx::FigureActor* prm_pActor_last_destroyed);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「ステータスCreater.xls」から行うこと。
    // gen01 start
    //自機
    static GgafCore::Status* resetMyShipStatus(GgafCore::Status* p);
    //自機ショット
    static GgafCore::Status* resetMyShot001Status(GgafCore::Status* p);
    //自機スナイプショット
    static GgafCore::Status* resetMySnipeShot001Status(GgafCore::Status* p);
    //マジックエネルギー核
    static GgafCore::Status* resetMyMagicEnergyCoreStatus(GgafCore::Status* p);
    //自機レーザー
    static GgafCore::Status* resetMyStraightLaserChip001Status(GgafCore::Status* p);
    //分身
    static GgafCore::Status* resetMyBunshinStatus(GgafCore::Status* p);
    //分身ションショット
    static GgafCore::Status* resetMyBunshinShot001Status(GgafCore::Status* p);
    //分身スナイプションショット
    static GgafCore::Status* resetMyBunshinSnipeShot001Status(GgafCore::Status* p);
    //分身カーブレーザー
    static GgafCore::Status* resetMyBunshinWateringLaserChip001Status(GgafCore::Status* p);
    //トゥピード
    static GgafCore::Status* resetMyTorpedoStatus(GgafCore::Status* p);
    //トゥピード爆風
    static GgafCore::Status* resetMyTorpedoBlastStatus(GgafCore::Status* p);
    //汎用ショット001
    static GgafCore::Status* resetShot001Status(GgafCore::Status* p);
    //汎用ショット002
    static GgafCore::Status* resetShot002Status(GgafCore::Status* p);
    //汎用ショット003ミニレーザー
    static GgafCore::Status* resetShot003Status(GgafCore::Status* p);
    //汎用ミニレーザーショット
    static GgafCore::Status* resetShot004Status(GgafCore::Status* p);
    //汎用敵ストレートレーザー001
    static GgafCore::Status* resetEnemyStraightLaserChip001Status(GgafCore::Status* p);
    //汎用敵カーブレーザー001
    static GgafCore::Status* resetEnemyWateringLaserChip001Status(GgafCore::Status* p);
    //エレス
    static GgafCore::Status* resetEnemyEresStatus(GgafCore::Status* p);
    //エレスショット001
    static GgafCore::Status* resetEnemyEresShot001Status(GgafCore::Status* p);
    //ストラエア
    static GgafCore::Status* resetEnemyStraeaStatus(GgafCore::Status* p);
    //ストラエアレーザー
    static GgafCore::Status* resetEnemyStraeaLaserChip001Status(GgafCore::Status* p);
    //ストラエアレーザー
    static GgafCore::Status* resetEnemyStraeaLaserChip002Status(GgafCore::Status* p);
    //ストラエアレーザー
    static GgafCore::Status* resetEnemyStraeaLaserChip003Status(GgafCore::Status* p);
    //ストラエアレーザー
    static GgafCore::Status* resetEnemyStraeaLaserChip004Status(GgafCore::Status* p);
    //オムルス（ラティスラヴィアのハッチ）
    static GgafCore::Status* resetEnemyOmulusStatus(GgafCore::Status* p);
    //エムス（ラティスラヴィアのハッチ）
    static GgafCore::Status* resetEnemyEmusStatus(GgafCore::Status* p);
    //エムスのレーザー
    static GgafCore::Status* resetEnemyEmusLaserChip001Status(GgafCore::Status* p);
    //エティス
    static GgafCore::Status* resetEnemyEtisStatus(GgafCore::Status* p);
    //リス
    static GgafCore::Status* resetEnemyRisStatus(GgafCore::Status* p);
    //ゲリア
    static GgafCore::Status* resetEnemyGeriaStatus(GgafCore::Status* p);
    //ハリア
    static GgafCore::Status* resetEnemyHaliaStatus(GgafCore::Status* p);
    //たまご１
    static GgafCore::Status* resetEnemyTamago01Status(GgafCore::Status* p);
    //イルケ
    static GgafCore::Status* resetEnemyIrceStatus(GgafCore::Status* p);
    //ラティスラヴィア（トーラス）
    static GgafCore::Status* resetEnemyRatislaviaStatus(GgafCore::Status* p);
    //アラス
    static GgafCore::Status* resetEnemyAllasStatus(GgafCore::Status* p);
    //ウーノミア
    static GgafCore::Status* resetEnemyUnomiaStatus(GgafCore::Status* p);
    //エミリア
    static GgafCore::Status* resetEnemyEmiliaStatus(GgafCore::Status* p);
    //エミリア断片
    static GgafCore::Status* resetEnemyEmiliaFragmentStatus(GgafCore::Status* p);
    //エミリア断片の断片
    static GgafCore::Status* resetEnemyEmiliaFragment2Status(GgafCore::Status* p);
    //エミリア断片の断片の断片
    static GgafCore::Status* resetEnemyEmiliaFragment3Status(GgafCore::Status* p);
    //MPアイテム小
    static GgafCore::Status* resetMagicPointItem001Status(GgafCore::Status* p);
    //MPアイテム中
    static GgafCore::Status* resetMagicPointItem002Status(GgafCore::Status* p);
    //MPアイテム大
    static GgafCore::Status* resetMagicPointItem003Status(GgafCore::Status* p);
    //スコアアイテム
    static GgafCore::Status* resetScoreItem001Status(GgafCore::Status* p);
    //Vreathアイテム
    static GgafCore::Status* resetVreathItem001Status(GgafCore::Status* p);
    //エーベ
    static GgafCore::Status* resetEnemyEbeStatus(GgafCore::Status* p);
    //ヒズビー
    static GgafCore::Status* resetEnemyHisbeStatus(GgafCore::Status* p);
    //ヒズビー2
    static GgafCore::Status* resetEnemyHisbe002Status(GgafCore::Status* p);
    //ヒズビーレーザー
    static GgafCore::Status* resetEnemyHisbeLaserChip001Status(GgafCore::Status* p);
    //ヒズビーレーザー
    static GgafCore::Status* resetEnemyHisbeLaserChip002Status(GgafCore::Status* p);
    //ヒズビーレーザー
    static GgafCore::Status* resetEnemyHisbeLaserChip003Status(GgafCore::Status* p);
    //ドラステア
    static GgafCore::Status* resetEnemyDrasteaStatus(GgafCore::Status* p);
    //タランテ
    static GgafCore::Status* resetEnemyTalanteStatus(GgafCore::Status* p);
    //エスペリア
    static GgafCore::Status* resetEnemyEsperiaStatus(GgafCore::Status* p);
    //エスペリアアレーザー
    static GgafCore::Status* resetEnemyEsperiaLaserChip001Status(GgafCore::Status* p);
    //グーテスト
    static GgafCore::Status* resetTestGuStatus(GgafCore::Status* p);
    //チョキーテスト
    static GgafCore::Status* resetTestChokiStatus(GgafCore::Status* p);
    //パーテスト
    static GgafCore::Status* resetTestPaStatus(GgafCore::Status* p);
    //ノーマルーテスト
    static GgafCore::Status* resetTestNomalStatus(GgafCore::Status* p);
    //グーショット
    static GgafCore::Status* resetTestGuShotStatus(GgafCore::Status* p);
    //チョキーショット
    static GgafCore::Status* resetTestChokiShotStatus(GgafCore::Status* p);
    //パーショット
    static GgafCore::Status* resetTestPaShotStatus(GgafCore::Status* p);
    //ノーマルーショット
    static GgafCore::Status* resetTestNomalShotStatus(GgafCore::Status* p);
    //ラティスラヴィアアイ
    static GgafCore::Status* resetEnemyRatislaviaEyeStatus(GgafCore::Status* p);
    //ラティスラヴィアアイ用ストレートレーザー001
    static GgafCore::Status* resetEnemyRatislaviaEyeStraightLaserChip001Status(GgafCore::Status* p);
    //エルミオネ
    static GgafCore::Status* resetEnemyErmioneStatus(GgafCore::Status* p);
    //エルミオネ腕の頭
    static GgafCore::Status* resetEnemyErmioneArmHeadStatus(GgafCore::Status* p);
    //エルミオネ腕の胴体
    static GgafCore::Status* resetEnemyErmioneArmBodyStatus(GgafCore::Status* p);
    //エルミオネ腕の弱点
    static GgafCore::Status* resetEnemyErmioneArmWeakStatus(GgafCore::Status* p);
    //アッポー
    static GgafCore::Status* resetEnemyApphoStatus(GgafCore::Status* p);
    //アンティオペ
    static GgafCore::Status* resetEnemyAntiopeStatus(GgafCore::Status* p);
    //デルヘイド
    static GgafCore::Status* resetEnemyDelheidStatus(GgafCore::Status* p);
    //アリサナ
    static GgafCore::Status* resetEnemyAlisanaStatus(GgafCore::Status* p);
    //イーダ
    static GgafCore::Status* resetEnemyIdaStatus(GgafCore::Status* p);
    //タゴラス
    static GgafCore::Status* resetEnemyThagorasStatus(GgafCore::Status* p);
    //オルトゥナ
    static GgafCore::Status* resetEnemyOrtunaStatus(GgafCore::Status* p);
    //グラヤ
    static GgafCore::Status* resetEnemyGlajaStatus(GgafCore::Status* p);
    //グラヤ槍弾
    static GgafCore::Status* resetEnemyGlajaLance001Status(GgafCore::Status* p);
    //ドゥーナ
    static GgafCore::Status* resetEnemyDunaStatus(GgafCore::Status* p);
    //オーツァルティア
    static GgafCore::Status* resetEnemyOzartiaStatus(GgafCore::Status* p);
    //オーツァルティアショット０１(壁ブロック)
    static GgafCore::Status* resetEnemyOzartiaShot01Status(GgafCore::Status* p);
    //オーツァルティアレーザーチップ
    static GgafCore::Status* resetEnemyOzartiaLaserChip01Status(GgafCore::Status* p);
    //オーツァルティア氷柱
    static GgafCore::Status* resetEnemyOzartiaPillar01Status(GgafCore::Status* p);
    //エビウス
    static GgafCore::Status* resetEnemyOebiusStatus(GgafCore::Status* p);
    //エビウスコア
    static GgafCore::Status* resetEnemyOebiusCoreStatus(GgafCore::Status* p);
    //エレルマン
    static GgafCore::Status* resetEnemyErelmanStatus(GgafCore::Status* p);
    //エレルマンコア
    static GgafCore::Status* resetEnemyErelmanCoreStatus(GgafCore::Status* p);
    //ウリュディケ
    static GgafCore::Status* resetEnemyUrydikeStatus(GgafCore::Status* p);
    //弾幕アリス用ショット
    static GgafCore::Status* resetAliceShotStatus(GgafCore::Status* p);
    //地形ボックス01
    static GgafCore::Status* resetWall01Status(GgafCore::Status* p);
    // gen01 end
};

}
#endif /*MYSTGUTIL_H_*/
