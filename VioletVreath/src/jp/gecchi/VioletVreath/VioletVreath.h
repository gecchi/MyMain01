#ifndef VIOLETVREATHHEADER_H_
#define VIOLETVREATHHEADER_H_
//「DirectXライブラリ」を利用する（利用者は俺！）場合
//次の"GgafLib::LibCommonHeader.h"ヘッダをインクルードします。
#include "jp/ggaf/GgafLibCommonHeader.h"

//種別定数
//意味は資料「種別相関定義コピペツール.xls」を参照
#define KIND_EFFECT                    (0x0U)  // 00000000 00000000 00000000 00000000

#define KIND_MY_SHOT_CHIKEI_HIT        (0x8U)  // 00000000 00000000 00000000 00001000
#define KIND_MY_SHOT_CHIKEI_THRU      (0x10U)  // 00000000 00000000 00000000 00010000
#define KIND_MY_BODY_CHIKEI_HIT       (0x20U)  // 00000000 00000000 00000000 00100000
#define KIND_MY_BODY_CHIKEI_THRU      (0x40U)  // 00000000 00000000 00000000 01000000
#define KIND_ENEMY_SHOT_CHIKEI_HIT    (0x80U)  // 00000000 00000000 00000000 10000000
#define KIND_ENEMY_SHOT_CHIKEI_THRU  (0x100U)  // 00000000 00000000 00000001 00000000
#define KIND_ENEMY_BODY_CHIKEI_HIT   (0x200U)  // 00000000 00000000 00000010 00000000
#define KIND_ENEMY_BODY_CHIKEI_THRU  (0x400U)  // 00000000 00000000 00000100 00000000
#define KIND_ITEM_CHIKEI_HIT         (0x800U)  // 00000000 00000000 00001000 00000000
#define KIND_ITEM_CHIKEI_THRU       (0x1000U)  // 00000000 00000000 00010000 00000000
#define KIND_CHIKEI_CHIKEI_HIT      (0x2000U)  // 00000000 00000000 00100000 00000000
#define KIND_CHIKEI_CHIKEI_THRU     (0x4000U)  // 00000000 00000000 01000000 00000000

#define KIND_MENU_ITEM             (0x10000U)  // 00000000 00000001 00000000 00000000
#define KIND_CURSOR                (0x20000U)  // 00000000 00000010 00000000 00000000

#define KIND_FORMATION           (0x1000000U)  // 00000001 00000000 00000000 00000000
//種別定数（自機・敵、小分類別）
#define KIND_MY_SHOT    (KIND_MY_SHOT_CHIKEI_HIT|KIND_MY_SHOT_CHIKEI_THRU)
#define KIND_MY_BODY    (KIND_MY_BODY_CHIKEI_HIT|KIND_MY_BODY_CHIKEI_THRU)
#define KIND_ENEMY_SHOT (KIND_ENEMY_SHOT_CHIKEI_HIT|KIND_ENEMY_SHOT_CHIKEI_THRU)
#define KIND_ENEMY_BODY (KIND_ENEMY_BODY_CHIKEI_HIT|KIND_ENEMY_BODY_CHIKEI_THRU)
//種別定数（自機・敵、大分類別）
#define KIND_MY (KIND_MY_SHOT|KIND_MY_BODY)
#define KIND_ENEMRY (KIND_ENEMY_SHOT|KIND_ENEMY_BODY)
//種別定数（その他、分類別）
#define KIND_MY_CHIKEI_HIT  (KIND_MY_SHOT_CHIKEI_HIT|KIND_MY_BODY_CHIKEI_HIT)
#define KIND_MY_CHIKEI_THRU (KIND_MY_SHOT_CHIKEI_THRU|KIND_MY_BODY_CHIKEI_THRU)
#define KIND_ENEMY_CHIKEI_HIT   (KIND_ENEMY_SHOT_CHIKEI_HIT|KIND_ENEMY_BODY_CHIKEI_HIT)
#define KIND_ENEMY_CHIKEI_THRU  (KIND_ENEMY_SHOT_CHIKEI_THRU|KIND_ENEMY_BODY_CHIKEI_THRU)
#define KIND_ITEM   (KIND_ITEM_CHIKEI_HIT|KIND_ITEM_CHIKEI_THRU)
#define KIND_CHIKEI (KIND_CHIKEI_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_THRU)


#define KIND_2DFIX_MOUSE_POINTER             (0x4U)   // 00000000 00000000 00000000 00000100
#define KIND_2DFIX_MENU_ITEM                 (0x8U)   // 00000000 00000000 00000000 00001000




#define ATTRIBUTE_NOMAL       (0x0U)    //000
#define ATTRIBUTE_GU          (0x1U)    //001
#define ATTRIBUTE_CHOKI       (0x2U)    //010
#define ATTRIBUTE_PA          (0x4U)    //100

//VirtualButton.h の define の別名を定義
#define VV_VB_SHOT1    VB_BUTTON1
#define VV_VB_SHOT2    VB_BUTTON2
#define VV_VB_OPTION   VB_BUTTON3
#define VV_VB_VIEW     VB_BUTTON4
#define VV_VB_TURBO    VB_BUTTON5
#define VV_VB_POWERUP  VB_BUTTON6

#define VV_VB_PAUSE  VB_PAUSE
#define VV_VB_UP     VB_UP
#define VV_VB_DOWN   VB_DOWN
#define VV_VB_LEFT   VB_LEFT
#define VV_VB_RIGHT  VB_RIGHT

#define VV_VB_VIEW_UP    VB_S1_UP
#define VV_VB_VIEW_DOWN  VB_S1_DOWN
#define VV_VB_VIEW_LEFT  VB_S1_LEFT
#define VV_VB_VIEW_RIGHT VB_S1_RIGHT

#define VV_VB_UI_UP      VB_UI_UP
#define VV_VB_UI_DOWN    VB_UI_DOWN
#define VV_VB_UI_LEFT    VB_UI_LEFT
#define VV_VB_UI_RIGHT   VB_UI_RIGHT
#define VV_VB_UI_EXECUTE VB_UI_EXECUTE
#define VV_VB_UI_CANCEL  VB_UI_CANCEL
#define VV_VB_UI_DEBUG   VB_UI_DEBUG


//STAT_DEFAULT_ACTOR_KINDは0
enum {
    STAT_Attribute = 1,                   //属性(uint)
    STAT_LockonAble,                      //ロックオン可否
    STAT_AddDestroyScorePoint,            //破壊時加算得点
    STAT_AddDamagedScorePoint,            //ダメージ時加算得点
    STAT_FlushAble,                       //ダメージ時フラッシュ要否
    STAT_AddRankPoint,                    //破壊時加算ランク
    STAT_AddRankPoint_Reduction,          //破壊時加算ランク減少率
    STAT_Stamina,                         //体力
    STAT_Attack,                          //攻撃力
    STAT_AttackPowerRate,                 //攻撃力に乗じられる率
    STAT_DefaultDefenceRate,              //基準防御率
    STAT_DominantDefenceRate,             //優性時の防御率
    STAT_RecessiveDefenceRate,            //劣性時の防御率
    STAT_EntryEffectKind,                 //出現エフェクト種別
    STAT_LeaveEffectKind,                 //退出エフェクト種別
    STAT_ExplosionEffectKind,             //爆発エフェクト種別
    STAT_ExplosionSeKind,                 //爆発SE種別
    STAT_DamagedEffectKind,               //ダメージ時エフェクト種別
    STAT_DamagedSeKind,                   //ダメージ時Se種別
    STAT_DestroyedEffectKind,             //やられエフェクト種別
    STAT_ItemKind,                        //やられアイテム種別
    STAT_ProperEffect01Kind,              //その他固有エフェクト０１
    STAT_AttackShotKind,                  //ショット種別
    STAT_DepositoryKind,                  //ショット種別
    STAT_RevengeShotKind,                 //打ち返し種別
};


// 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
// コード変更は「ランク定義Creater.xls」から行うこと。
// gen01 start
// ウノミア(EnemyUnomia) のランク式
#define RF_EnemyUnomia_ShotWay(X)  (10+(X)*10)  //発射弾(Way)数
// ウノミア編隊001(FormationUnomia001) のランク式
#define RF_FormationUnomia001_Col(X)  (RF_LL(X, 5, 10))  //列数
#define RF_FormationUnomia001_Num(X)  (RF_LL(X, 20, 30))  //隊数
#define RF_FormationUnomia001_LaunchInterval(X)  (RF_UL(X, 12, 2))  //出現間隔
#define RF_FormationUnomia001_MvVelo(X)  (RF_ULL(X, 10000, 20000))  //移動速度
// ウノミア編隊002(FormationUnomia002) のランク式
#define RF_FormationUnomia002_Col(X)  (RF_LL(X, 5, 7))  //列数
#define RF_FormationUnomia002_Num(X)  (RF_LL(X, 20, 30))  //隊数
#define RF_FormationUnomia002_LaunchInterval(X)  (RF_UL(X, 12, 2))  //出現間隔
#define RF_FormationUnomia002_MvVelo(X)  (RF_ULL(X, 10000, 20000))  //移動速度
// リス(EnemyRis) のランク式
#define RF_EnemyRis_ShotWay(X)  (10+(X)*10)  //発射弾(Way)数
// リス編隊001(FormationRis001) のランク式
#define RF_FormationRis001_Num(X)  (7 + (X)*7)  //隊数
#define RF_FormationRis001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RF_FormationRis001_MvVelo(X)  (16000+(X)*1600)  //移動速度
// リス編隊002(FormationRis002) のランク式
#define RF_FormationRis002_Num(X)  (7 + (X)*7)  //隊数
#define RF_FormationRis002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RF_FormationRis002_MvVelo(X)  (16000+(X)*1600)  //移動速度
// アラス(EnemyAllas) のランク式
#define RF_EnemyAllas_ShotWay(X)  (10+(X)*10)  //発射弾(Way)数
// アラス編隊001(FormationAllas001) のランク式
#define RF_FormationAllas001_Num(X)  (12+(X)*8)  //隊数
#define RF_FormationAllas001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RF_FormationAllas001_MvVelo(X)  (10000 + (X)*10000)  //移動速度
// アラス編隊002(FormationAllas002) のランク式
#define RF_FormationAllas002_Num(X)  (12+(X)*8)  //隊数
#define RF_FormationAllas002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RF_FormationAllas002_MvVelo(X)  (10000 + (X)*10000)  //移動速度
// ハリア(EnemyHalia) のランク式
#define RF_EnemyHalia_ShotWay(X)  (20+(X)*10)  //発射弾(Way)数
// ハリア編隊(FormationHalia) のランク式
#define RF_FormationHalia_Num(X)  (7+(X)*4)  //隊数
#define RF_FormationHalia_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X)) *20))  //出現間隔
#define RF_FormationHalia_MvVelo(X)  (14000+(X)*10000)  //移動速度
// オムルス(EnemyOmulus) のランク式
#define RF_EnemyOmulus_ShotMvVelo(X)  (10 + (10 - ((X)>1.0?1.0:(X)) * 10))  //発射弾速度
#define RF_EnemyOmulus_ShotInterval(X)  (10 + (10 - ((X)>1.0?1.0:(X)) * 10))  //発射弾間隔
// 汎用ショット001(Shot001) のランク式
#define RF_Shot001_MvVelo(X)  (5000+(X)*5000)  //移動速度
#define RF_Shot001_AngVelo(X)  (6000+(X)*6000)  //角速度
// 汎用ショット002(Shot002) のランク式
#define RF_Shot002_MvVelo(X)  (8000+(X)*8000)  //移動速度
#define RF_Shot002_AngVelo(X)  (1000+(X)*1000)  //角速度
// エミリア(EnemyEmilia) のランク式
#define RF_EnemyEmilia_ShotWay(X)  (4+(X)*4)  //発射弾(Way)数
// エミリア断片(EnemyEmiliaFragment) のランク式
// エミリア断片の断片(EnemyEmiliaFragment2) のランク式
// エミリア断片の断片の断片(EnemyEmiliaFragment3) のランク式
// エミリア群(FormationEmilia) のランク式
#define RF_FormationEmilia_LaunchInterval(X)  (10  + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RF_FormationEmilia_MvVelo(X)  (8000+(X)*8000)  //移動速度
#define RF_FormationEmilia_DurationFrames(X)  (60*20)  //持続時間
// エーベ編隊(FormationEbe) のランク式
#define RF_FormationEbe_Num(X)  (12+(X)*8)  //隊数
#define RF_FormationEbe_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RF_FormationEbe_MvVelo(X)  (10000 + (X)*10000)  //移動速度
#define RF_FormationEbe_ShotWay(X)  (4+(X)*4)  //発射弾(Way)数
// エスペリア(EnemyEsperia) のランク式
#define RF_EnemyEsperia_Density(X)  (90000 - (((X)>1.0?1.0:(X)) * 50000))  //密度
#define RF_EnemyEsperia_ShotWay(X)  (7 + (((X)>1.0?1.0:(X)) * 4))  //発射弾(Way)数
// アッフォー(EnemyAppho) のランク式
#define RF_EnemyAppho_MvVelo(X)  (15000 + (X)*10000)  //移動速度
#define RF_EnemyAppho_ShotWay(X)  (2+(X)*4)  //発射弾(Way)数
#define RF_EnemyAppho_ShotMvVelo(X)  (1000+(X)*5000)  //発射弾速度
// アッフォー編隊001(FormationAppho001) のランク式
#define RF_FormationAppho001_Num(X)  (10+(X)*5)  //隊数
#define RF_FormationAppho001_LaunchInterval(X)  (3 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
// アテンティオペ(EnemyAntiope) のランク式
#define RF_EnemyAntiope_MvVelo(X)  (15000 + (X)*10000)  //移動速度
#define RF_EnemyAntiope_ShotWay(X)  (2+(X)*4)  //発射弾(Way)数
#define RF_EnemyAntiope_ShotMvVelo(X)  (1000+(X)*5000)  //発射弾速度
// アテンティオペ編隊001(FormationAntiope001) のランク式
#define RF_FormationAntiope001_Num(X)  (300+(X)*300)  //隊数
#define RF_FormationAntiope001_LaunchInterval(X)  (2 + (2 - ((X)>1.0?1.0:(X))*2))  //出現間隔
// デルヘイド編隊(FormationDelheid) のランク式
#define RF_FormationDelheid_Num(X)  (30+(X)*10)  //隊数
#define RF_FormationDelheid_MvVelo(X)  (10000 + (X)*10000)  //移動速度
#define RF_FormationDelheid_ShotWay(X)  (7+(X)*5)  //発射弾(Way)数
// 打ち返し弾共通(SHOT_RV) のランク式
#define RF_SHOT_RV_ShotMvVelo(X)  (3000+((X)*5000))  //発射弾速度
#define RF_SHOT_RV_ShotMvAcce(X)  (100+((X)*400))  //発射弾加速度
// ノーマル打ち返し弾001(SHOT_RV_NOMAL001) のランク式
#define RF_SHOT_RV_NOMAL001_Density(X)  (D_ANG(15)-((X)*D_ANG(5)))  //密度
#define RF_SHOT_RV_NOMAL001_ShotWay(X)  (3+(2*((X)*2)))  //発射弾(Way)数
#define RF_SHOT_RV_NOMAL001_ShotSetNum(X)  (1+((X)*3))  //発射弾(Way)弾のセット数
// オルトゥナ(EnemyOrtuna) のランク式
#define RF_EnemyOrtuna_MvVelo(X)  (15000 + (X)*10000)  //移動速度
#define RF_EnemyOrtuna_ShotWay(X)  (2+(X)*4)  //発射弾(Way)数
#define RF_EnemyOrtuna_ShotMvVelo(X)  (1000+(X)*5000)  //発射弾速度
// オルトゥナ編隊001(FormationOrtuna001) のランク式
#define RF_FormationOrtuna001_Num(X)  (10+(X)*5)  //隊数
#define RF_FormationOrtuna001_LaunchInterval(X)  (3 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
// グラヤ(EnemyGlaja) のランク式
#define RF_EnemyGlaja_MvVelo(X)  (15000 + (X)*10000)  //移動速度
#define RF_EnemyGlaja_ShotWay(X)  (16+(X)*16)  //発射弾(Way)数
// ドゥーナ(EnemyDuna) のランク式
#define RF_EnemyDuna_MvVelo(X)  (10000 + (X)*20000)  //移動速度
// gen02 end

//1/√2
#define NANAME2D_RATE 0.70710
//1/√3
#define NANAME3D_RATE 0.57735

#define FADE_FRAMES 180

#define VV_DEFAULT_CONFIG_FILE ".\\default_config.properties"
//#define VV_CONFIG_FILE         ".\\config.properties"

#define Obj_RankUpStage     ((0x10000ULL) | Obj_SceneBit)    //0b 10000000 00000000 00000000 00000000 00000000 00000001 00000000 00000000

namespace VioletVreath {

//// forward declaration begin
class AliceShot;
class BunshinMagic;
class Camera;
class CameraUpVector;
class CameraViewPoint;
class Caretaker;
class CommonScene;
class Config;
class CostDispBar;
class Cursor001;
class CursorConfig001;
class CursorConfig002;
class CursorConfig003;
class CursorConfig004;
class CursorConfig005;
class CursorConfirmMenu;
class CursorNameEntryMenu;
class CursorPauseMenu;
class CursorResolutionSelect;
class CursorSelectMenu;
class CursorTitleMenu;
class CurveManufactureManagerEx;
class CurveSourceManagerEx;
class DamageDispBar;
class DanmakuAlice;
class DanmakuAlice001;
class DepositoryConnection;
class DepositoryManager;
class EffectBlink;
class EffectBlink001;
class EffectBlink002;
class EffectBlink003;
class EffectBunshinMagic001;
class EffectCondensation001;
class EffectExplosion001;
class EffectExplosion002;
class EffectExplosion003;
class EffectExplosion004;
class EffectLaserMagic;
class EffectLaserRefraction001;
class EffectLockonMagic;
class EffectMagic001;
class EffectManager;
class EffectMyShipExplosion;
class EffectRatislaviaEye001;
class EffectShotMagic;
class EffectSmileMagic001;
class EffectSpeedMagic;
class EffectTorpedoMagic;
class EffectTurbo001;
class EffectTurbo002;
class EffectVreathMagic001;
class EffectWormhole;
class EffectWormhole001;
class EnemyAlisana;
class EnemyAllas;
class EnemyAntiope;
class EnemyAntiopeN;
class EnemyAntiopeP;
class EnemyAppho;
class EnemyDelheid;
class EnemyDrastea;
class EnemyDuna;
class EnemyEbe;
class EnemyEmilia;
class EnemyEmiliaBase;
class EnemyEmiliaFragment;
class EnemyEmiliaFragment2;
class EnemyEmiliaFragment3;
class EnemyEmus;
class EnemyEmusLaserChip001;
class EnemyErelman;
class EnemyErelmanController;
class EnemyErelmanController001;
class EnemyErelmanController002;
class EnemyErelmanController003;
class EnemyErelmanCore;
class EnemyErelmanCore001;
class EnemyErelmanCore002;
class EnemyErelmanCore003;
class EnemyEres;
class EnemyEresShot001;
class EnemyErmione;
class EnemyErmioneArm;
class EnemyErmioneArmBody;
class EnemyErmioneArmHead;
class EnemyErmioneArmWeak;
class EnemyEsperia;
class EnemyEsperiaLaserChip001;
class EnemyEtis;
class EnemyGeria;
class EnemyGlaja;
class EnemyGlajaLance001;
class EnemyHalia;
class EnemyHisbe;
class EnemyHisbe002;
class EnemyHisbeLaserChip001;
class EnemyHisbeLaserChip002;
class EnemyHisbeLaserChip003;
class EnemyIda;
class EnemyIdaBase;
class EnemyIdaBase001;
class EnemyIrce;
class EnemyOebius;
class EnemyOebiusController;
class EnemyOebiusController001;
class EnemyOebiusController002;
class EnemyOebiusCore;
class EnemyOmulus;
class EnemyOrtuna;
class EnemyOzartia;
class EnemyOzartiaLaserChip01;
class EnemyOzartiaPillar01;
class EnemyOzartiaShot01;
class EnemyRatislavia;
class EnemyRatislaviaEye;
class EnemyRatislaviaEyeStraightLaserChip001;
class EnemyRis;
class EnemyStraea;
class EnemyStraeaLaserChip001;
class EnemyStraeaLaserChip002;
class EnemyStraeaLaserChip003;
class EnemyStraeaLaserChip004;
class EnemyStraightLaserChip001;
class EnemyTalante;
class EnemyTamago01;
class EnemyThagoras;
class EnemyUnomia;
class EnemyUrydike;
class EnemyWateringLaserChip001;
class FormationAllas001;
class FormationAllas001a;
class FormationAllas001b;
class FormationAllas001c;
class FormationAllas001d;
class FormationAllas002;
class FormationAntiope001;
class FormationAppho001;
class FormationAppho001a;
class FormationAppho001b;
class FormationDelheid;
class FormationDelheid001;
class FormationDrastea001;
class FormationEbe;
class FormationEbe001;
class FormationEmilia;
class FormationErelman;
class FormationErelman001;
class FormationErelman002;
class FormationErelman003;
class FormationEres001;
class FormationEres002;
class FormationEtis001;
class FormationGeria;
class FormationGeria001;
class FormationGeria002;
class FormationHalia;
class FormationIda;
class FormationIda001;
class FormationOebius;
class FormationOebius001;
class FormationOebius002;
class FormationOrtuna001;
class FormationOrtuna001a;
class FormationOrtuna001b;
class FormationRis001;
class FormationRis002;
class FormationThagoras;
class FormationThagoras001;
class FormationThagoras002;
class FormationUnomia;
class FormationUnomia001;
class FormationUnomia001a;
class FormationUnomia001b;
class FormationUnomia002;
class FormationUnomia002a;
class FormationUnomia002b;
class FormationUrydike;
class FormationUrydike001;
class FormationUrydike002;
class GameBeginningScene;
class GameDemoScene;
class GameEndingScene;
class GameGlobal;
class GameMainScene;
class GameOverScene;
class GamePreTitleScene;
class GameScene;
class GameTitleScene;
class GroundMeshActor;
class Horizon001;
class HoshiBoshi;
class HoshiBoshi001;
class HoshiboshiEffect;
class HoshiBoshiRankUp;
class HoshiBoshiTitle;
class HoshiBoshiTransit;
class Item;
class LabelBonus001;
class LabelFix16Font01;
class LabelFont16x32;
class LabelFont32x64;
class LabelFont8x16;
class LabelGecchi16Font;
class LabelGecchi32Font;
class LabelGecchi8Font;
class LabelMenuItemFont01;
class LabelMenuTitleFont01;
class LabelRankFont;
class LabelRankingFont;
class LabelSceneSymbol;
class LabelScoreFont;
class LaserMagic;
class LockonCursor001;
class LockonCursor001_Main;
class LockonCursor001_Sub;
class LockonMagic;
class Magic;
class MagicLvCursor;
class MagicLvCursor001;
class MagicLvCursor002;
class MagicLvCursor003;
class MagicMeter;
class MagicMeterCursor001;
class MagicMeterStatus;
class MagicPointItem;
class MagicPointItem001;
class MagicPointItem002;
class MagicPointItem003;
class MenuBoard;
class MenuBoardConfig;
class MenuBoardConfirm;
class MenuBoardKeyConfig;
class MenuBoardNameEntry;
class MenuBoardPause;
class MenuBoardResolutionSelect;
class MenuBoardScreenConfig;
class MenuBoardSelect;
class MenuBoardSoundConfig;
class MenuBoardTitle;
class MousePointer;
class MpBar;
class MyBunshin;
class MyBunshinBase;
class MyBunshinController;
class MyBunshinShot001;
class MyBunshinSnipeShot001;
class MyBunshinStraightLaserChip001;
class MyBunshinWateringLaserChip001;
class MyLockonController;
class MyMagicEnergy;
class MyMagicEnergyCore;
class MyShip;
class MyShipDivingCamWorker;
class MyShipScene;
class MyShot001;
class MySnipeShot001;
class MyStgUtil;
class MyStraightLaserChip001;
class MyTorpedo;
class MyTorpedoBlast;
class MyTorpedoController;
class MyTorpedoTail;
class MyVreath;
class MyWave001;
class NameEntryScene;
class PauseCamWorker;
class Planet001;
class Planet001Atmosphere;
class PreDrawScene;
class RankingTable;
class RankUp001;
class RankUp002;
class RankUp003;
class RankUp100;
class RankUpStage;
class RankUpStageController;
class ScoreItem;
class ScoreItem001;
class Shot001;
class Shot002;
class Shot003;
class Shot004;
class Shot004Blue;
class Shot004Yellow;
class ShotMagic;
class SmileMagic;
class Spacetime;
class SpeedMagic;
class SpriteFont32x64;
class SpriteLabelBonus001;
class SpriteLabelBonus002;
class SpriteLabelGecchi32Font;
class SpriteLabelTest;
class Stage;
class Stage01;
class Stage01Part01;
class Stage01Part02;
class Stage01Part03;
class Stage01PartClimax;
class Stage01PartController;
class Stage01PartWall;
class Stage01PartWallSection001;
class Stage02;
class Stage02_01;
class Stage02_Climax;
class Stage02PartController;
class Stage03;
class Stage04;
class Stage05;
class StageController;
class StageDebug;
class StageDebugPart01;
class StageDebugPart02;
class StageDebugPart03;
class StageDebugPartClimax;
class StageDebugPartController;
class StageDebugPartWall;
class StageDebugPartWallSection001;
class StagePartController;
class StageWorld;
class TamagoActor;
class TamagoScene;
class TestCamWorker;
class TestChoki;
class TestChokiShot;
class TestDepository;
class TestEnemy;
class TestGu;
class TestGuShot;
class TestNomal;
class TestNomalShot;
class TestPa;
class TestPaShot;
class TitleBoard;
class TorpedoMagic;
class TractorMagic;
class TransitStage;
class VamSysCamWorker;
class VarietyRatislavia001;
class VarietyRatislavia002;
class VarietyRatislavia003;
class VarietyRatislavia004;
class ViewPointGuide;
class VreathBar;
class VreathItem;
class VreathItem001;
class VreathMagic;
class VVCameraWorkerChanger;
class Wall01;
class World;
class WorldBound001;
class WorldBound002;
class WorldBoundNameEntry;
class WorldBoundRankUp;
class WorldBoundTitle;
class WorldBoundTransit;
class XpmConnection;
class XpmManager;
//// forward declaration end
}


#endif /*VIOLETVREATHHEADER_H_*/
