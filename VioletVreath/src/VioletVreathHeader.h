#ifndef VIOLETVREATHHEADER_H_
#define VIOLETVREATHHEADER_H_

//「DirectX9ライブラリ」を利用する（利用者は俺！）場合
//次の"GgafLibHeader.h"ヘッダをインクルードします。

#include "GgafLibHeader.h"

//種別定数
//意味は資料「種別相関定義コピペツール.xls」を参照
#define KIND_EFFECT (0x0)                     // 00000000000000000000000000000000
#define KIND_MY_SHOT_CHIKEI_HIT     (0x8)     // 00000000000000000000000000001000
#define KIND_MY_SHOT_CHIKEI_THRU    (0x10)    // 00000000000000000000000000010000
#define KIND_MY_BODY_CHIKEI_HIT     (0x20)    // 00000000000000000000000000100000
#define KIND_MY_BODY_CHIKEI_THRU    (0x40)    // 00000000000000000000000001000000
#define KIND_ENEMY_SHOT_CHIKEI_HIT  (0x80)    // 00000000000000000000000010000000
#define KIND_ENEMY_SHOT_CHIKEI_THRU (0x100)   // 00000000000000000000000100000000
#define KIND_ENEMY_BODY_CHIKEI_HIT  (0x200)   // 00000000000000000000001000000000
#define KIND_ENEMY_BODY_CHIKEI_THRU (0x400)   // 00000000000000000000010000000000
#define KIND_ITEM_CHIKEI_HIT        (0x800)   // 00000000000000000000100000000000
#define KIND_ITEM_CHIKEI_THRU       (0x1000)  // 00000000000000000001000000000000
#define KIND_CHIKEI_CHIKEI_HIT      (0x2000)  // 00000000000000000010000000000000
#define KIND_CHIKEI_CHIKEI_THRU     (0x4000)  // 00000000000000000100000000000000
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

#define ATTRIBUTE_NOMAL       (0x0)    //000
#define ATTRIBUTE_GU          (0x1)    //001
#define ATTRIBUTE_CHOKI       (0x2)    //010
#define ATTRIBUTE_PA          (0x4)    //100

//VirtualButton.h の define の別名を定義
#define VB_SHOT1    VB_BUTTON1
#define VB_SHOT2    VB_BUTTON2
#define VB_OPTION   VB_BUTTON3
#define VB_VIEW     VB_BUTTON4
#define VB_TURBO    VB_BUTTON5
#define VB_POWERUP  VB_BUTTON6
//#define VB_VIEW_01  VB_BUTTON7
//#define VB_VIEW_02  VB_BUTTON8


//STAT_DEFAULT_ACTOR_KINDは0
/** アクターステータス：属性(ATTRIBUTE_NOMAL/ATTRIBUTE_GU/ATTRIBUTE_CHOKI/ATTRIBUTE_PA) */
#define STAT_Attribute              (1)
/** アクターステータス：加算スコア(int) */
#define STAT_AddScorePoint          (2)
/** アクターステータス：加算ランクポイント(double) */
#define STAT_AddRankPoint           (3)
/** アクターステータス：加算ランクポイントの、フレーム毎減少率(double) */
#define STAT_AddRankPoint_Reduction (4)
/** アクターステータス：アクターの残り体力(int) */
#define STAT_Stamina                (5)
/** アクターステータス：アクターの攻撃力(int) */
#define STAT_Attack                 (6)
/** アクターステータス：アクターの基本防御能力(double) 。相手のSTAT_Attackに乗じる(1.0で0%防御,0.9で10%防御) */
#define STAT_DefaultDefenceRate     (7)
/** アクターステータス：アクターの優性属性時防御能力(double) */
#define STAT_DominantDefenceRate    (8)
/** アクターステータス：アクターの劣性属性時防御能力(double) */
#define STAT_RecessiveDefenceRate   (9)
/** アクターステータス：ロックオン可否(0:不可 1:可) */
#define STAT_LockonAble             (10)
/** アクターステータス：登場エフェクト種類(int) */
#define STAT_EntryEffectKind        (11)
/** アクターステータス：退出エフェクト種類(int) */
#define STAT_LeaveEffectKind        (12)
/** アクターステータス：爆発エフェクト種類(int) */
#define STAT_ExplosionEffectKind    (13)
/** アクターステータス：やられたエフェクト(スコア表示等) (int) */
#define STAT_DestroyedEffectKind    (14)
/** アクターステータス：弾アクター(int) */
#define STAT_ShotKind               (15)
/** アクターステータス：保持アイテム種類(int) */
#define STAT_ItemKind               (16)
/** アクターステータス：編隊全滅時加算得点(int) */
#define STAT_FormationDestroyedAddScorePoint (17)
/** アクターステータス：編隊全滅時エフェクト(ボーナス表示等)  (int) */
#define STAT_FormationDestroyedEffectKind (18)
/** アクターステータス：編隊全滅時アイテム種別(int) */
#define STAT_FormationDestroyedItemKind      (19)
/** アクターステータス：その他固有エフェクト０１(int) */
#define STAT_ProperEffect01Kind      (20)
/** アクターステータス：番兵（配列要素数に使用される、STAT_Sentry は一番最後の数値を持ってくること）*/
#define STAT_Sentry                 (21)


// 以下の gen01 start 〜 end はExcelマクロにより自動生成されたコードです。
// コード変更は「ランク定義Creater.xls」から行うこと。
// gen01 start
// EnemyEunomia のランク式
#define RR_EnemyEunomia_ShotWay(X)  (10+(X)*10)  //発射弾(Way)数
// FormationEunomia001 のランク式
#define RR_FormationEunomia001_Col(X)  (5 + ((X)>1.0?1.0:(X))*2)  //列数
#define RR_FormationEunomia001_Num(X)  (20 + (X)*10)  //隊数
#define RR_FormationEunomia001_LaunchInterval(X)  (2  + (10 - ((X)>1.0?1.0:(X))*10))  //出現間隔
#define RR_FormationEunomia001_MvVelo(X)  (10000 + (X)*10000)  //移動速度
// FormationEunomia002 のランク式
#define RR_FormationEunomia002_Col(X)  (5 + ((X)>1.0?1.0:(X))*2)  //列数
#define RR_FormationEunomia002_Num(X)  (20 + (X)*10)  //隊数
#define RR_FormationEunomia002_LaunchInterval(X)  (2  + (10 - ((X)>1.0?1.0:(X))*10))  //出現間隔
#define RR_FormationEunomia002_MvVelo(X)  (10000 + (X)*10000)  //移動速度
// EnemyIris のランク式
#define RR_EnemyIris_ShotWay(X)  (10+(X)*10)  //発射弾(Way)数
// FormationIris001 のランク式
#define RR_FormationIris001_Num(X)  (7 + (X)*7)  //隊数
#define RR_FormationIris001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RR_FormationIris001_MvVelo(X)  (16000+(X)*1600)  //移動速度
// FormationIris002 のランク式
#define RR_FormationIris002_Num(X)  (7 + (X)*7)  //隊数
#define RR_FormationIris002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RR_FormationIris002_MvVelo(X)  (16000+(X)*1600)  //移動速度
// EnemyPallas のランク式
#define RR_EnemyPallas_ShotWay(X)  (10+(X)*10)  //発射弾(Way)数
// FormationPallas001 のランク式
#define RR_FormationPallas001_Num(X)  (12+(X)*8)  //隊数
#define RR_FormationPallas001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RR_FormationPallas001_MvVelo(X)  (10000 + (X)*10000)  //移動速度
// FormationPallas002 のランク式
#define RR_FormationPallas002_Num(X)  (12+(X)*8)  //隊数
#define RR_FormationPallas002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RR_FormationPallas002_MvVelo(X)  (10000 + (X)*10000)  //移動速度
// EnemyThalia のランク式
#define RR_EnemyThalia_ShotWay(X)  (20+(X)*10)  //発射弾(Way)数
// FormationThalia のランク式
#define RR_FormationThalia_Num(X)  (7+(X)*4)  //隊数
#define RR_FormationThalia_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X)) *20))  //出現間隔
#define RR_FormationThalia_MvVelo(X)  (14000+(X)*10000)  //移動速度
// EnemyRomulus のランク式
#define RR_EnemyRomulus_ShotMvVelo(X)  (10 + (10 - ((X)>1.0?1.0:(X)) * 10))  //発射弾速度
#define RR_EnemyRomulus_ShotInterval(X)  (10 + (10 - ((X)>1.0?1.0:(X)) * 10))  //発射弾間隔
// Shot001 のランク式
#define RR_Shot001_MvVelo(X)  (5000+(X)*5000)  //移動速度
#define RR_Shot001_AngVelo(X)  (6000+(X)*6000)  //角速度
// Shot002 のランク式
#define RR_Shot002_MvVelo(X)  (8000+(X)*8000)  //移動速度
#define RR_Shot002_AngVelo(X)  (1000+(X)*1000)  //角速度
// EnemyMassalia のランク式
#define RR_EnemyMassalia_ShotWay(X)  (4+(X)*4)  //発射弾(Way)数
// EnemyMassaliaFragment のランク式
// EnemyMassaliaFragment2 のランク式
// EnemyMassaliaFragment3 のランク式
// FormationMassalia のランク式
#define RR_FormationMassalia_LaunchInterval(X)  (10  + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RR_FormationMassalia_MvVelo(X)  (8000+(X)*8000)  //移動速度
#define RR_FormationMassalia_DurationFrames(X)  (60*20)  //持続時間
// FormationHebe のランク式
#define RR_FormationHebe_Num(X)  (12+(X)*8)  //隊数
#define RR_FormationHebe_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
#define RR_FormationHebe_MvVelo(X)  (10000 + (X)*10000)  //移動速度
#define RR_FormationHebe_ShotWay(X)  (4+(X)*4)  //発射弾(Way)数
// EnemyHesperia のランク式
#define RR_EnemyHesperia_ShotWay(X)  (7 + (((X)>1.0?1.0:(X)) * 4))  //発射弾(Way)数
#define RR_EnemyHesperia_Density(X)  (90000 - (((X)>1.0?1.0:(X)) * 50000))  //密度
// EnemySappho のランク式
#define RR_EnemySappho_MvVelo(X)  (15000 + (X)*10000)  //移動速度
#define RR_EnemySappho_ShotWay(X)  (2+(X)*4)  //発射弾(Way)数
#define RR_EnemySappho_ShotMvVelo(X)  (1000+(X)*5000)  //発射弾速度
// FormationSappho001 のランク式
#define RR_FormationSappho001_Num(X)  (10+(X)*5)  //隊数
#define RR_FormationSappho001_LaunchInterval(X)  (3 + (20 - ((X)>1.0?1.0:(X))*20))  //出現間隔
// EnemyAntiope のランク式
#define RR_EnemyAntiope_MvVelo(X)  (15000 + (X)*10000)  //移動速度
#define RR_EnemyAntiope_ShotWay(X)  (2+(X)*4)  //発射弾(Way)数
#define RR_EnemyAntiope_ShotMvVelo(X)  (1000+(X)*5000)  //発射弾速度
// FormationAntiope001 のランク式
#define RR_FormationAntiope001_Num(X)  (300+(X)*300)  //隊数
#define RR_FormationAntiope001_LaunchInterval(X)  (2 + (2 - ((X)>1.0?1.0:(X))*2))  //出現間隔
// FormationAdelheid のランク式
#define RR_FormationAdelheid_Num(X)  (30+(X)*10)  //隊数
#define RR_FormationAdelheid_MvVelo(X)  (10000 + (X)*10000)  //移動速度
#define RR_FormationAdelheid_ShotWay(X)  (7+(X)*5)  //発射弾(Way)数
// gen02 end

//1/√2
#define NANAME2D_RATE 0.70710
//1/√3
#define NANAME3D_RATE 0.57735

#undef P_GOD
#define P_GOD ((VioletVreath::God*)VioletVreath::God::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((VioletVreath::Universe*)(P_GOD->_pUniverse))

#define FADE_FRAMES 60

#define DRAW_DEPTH_LEVEL_HOSHIBOSHI (MAX_DRAW_DEPTH_LEVEL-1)
#define DRAW_DEPTH_LEVEL_BIGOBJ     (MAX_DRAW_DEPTH_LEVEL-2)


#define VV_DEFAULT_CONFIG_FILE ".\\default_config.properties"
#define VV_CONFIG_FILE         ".\\config.properties"


#define Obj_RankUpStage              (0x81000000)     //0b 10000001 00000000 00000000 00000000


//イベント用 hashval 数値宣言
HASHVAL(EVENT_GOD_WILL_DIE);
HASHVAL(EVENT_PREPARE_TRANSIT_STAGE);
HASHVAL(EVENT_PREPARE_NEXT_STAGE);
HASHVAL(EVENT_JUST_GAME_OVER);

HASHVAL(EVENT_TRANSIT_WAS_END);
HASHVAL(EVENT_RANKUP_WAS_END);
HASHVAL(EVENT_RANKUP_ON_GARBAGED);

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
HASHVAL(EVENT_BACK_TO_TITLE);
HASHVAL(EVENT_NAMEENTRYSCENE_FINISH);
HASHVAL(EVENT_MENU_NAMEENTRY_DONE);

namespace VioletVreath {

//その他のヘッダファイルはここに記述

class God;
class World;

class CommonScene;

class TitleBoard;
class Cursor001;

class PreDrawScene;
class LaserChipTestActor;
class DefaultMeshTestActor;



class GameScene;
class MyShipScene;
class GamePreTitleScene;
class GameTitleScene;
class GameDemoScene;
class GameBeginningScene;
class GameMainScene;
class GameEndingScene;
class GameOverScene;
class NameEntryScene;

class RankUpStage;
class RankUp001;
class RankUp002;
class RankUp003;
class RankUp004;
class RankUp005;
class RankUp006;
class RankUp007;


class StageWorld;
class StageController;
class Stage;
class Stage01;
class Stage02;
class Stage03;
class Stage04;
class Stage05;
class TransitStage;
class RankUpStageController;
class RankUpStage;
class RankUp001;
class RankUp002;
class RankUp100;
class TamagoScene;

class StagePartController;
class Stage01PartController;
class Stage01_01;
class Stage01_02;
class Stage01_03;
class Stage01_Climax;
class Stage01WalledSection001;
class Stage01WalledScene;
class Wall001;
class Wall001Prism;

class Stage02PartController;
class Stage02_01;
class Stage02_Climax;

class Camera;
class ViewPointGuide;
class CameraWorker;
class DefaultCamWorker;
class TestCamWorker;

class GroundMeshActor;
class Sylvia;
class VarietySylvia001;
class VarietySylvia002;
class VarietySylvia003;
class VarietySylvia004;
class EnemySylviaEye;
class EnemySylviaEyeStraightLaserChip001;
class EffectSylviaEye001;


class SingleLaser;
class Shot001;
class Shot002;
class Shot003;
class Shot004;
class Shot004Blue;
class Shot004Yellow;
class EnemyWateringLaserChip001;
class EnemyStraightLaserChip001;

class VamSysCamWorker;
class PauseCamWorker;
class MyShipDivingCamWorker;
class MyOptionWateringLaserChip001;
class MyOptionStraightLaserChip001;
class MyStraightLaserChip001;
class MyShip;
class MyLockonController;
class MyOptionController;
class MyOptionControllerGizmo;
class MyOptionControllerDirectionVector;
class MyOption;
class EffectMyOption;
class MyTorpedoController;
class MyTorpedoTail;
class MyTorpedo;
class MyTorpedoBlast;
class MyShot001;
class MyWave001;
class MyVreath;
class EffectMyShipExplosion;

class TestGuShot;
class TestChokiShot;
class TestPaShot;
class TestNomalShot;

class MagicMeter;
class MagicMeterStatus;
class MagicMeterCursor001;
class MagicLvCursor;
class MagicLvCursor001;
class MagicLvCursor002;
class MagicLvCursor003;
class GraphBar;
class EnergyBar;
class CostDispBar;
class VreathBar;
class DamageDispBar;

class Magic;
class OptionMagic;
class LaserMagic;
class SpeedMagic;
class LockonMagic;
class TorpedoMagic;
class TractorMagic;
class VreathMagic;
class SmileMagic;
class EffectMagic001;
class EffectSpeedMagic;
class EffectTorpedoMagic;
class EffectLockonMagic;
class EffectVreathMagic001;
class EffectSmileMagic001;

class EffectExplosion001;
class EffectExplosion002;
class EffectExplosion003;
class EffectExplosion004;
class EffectLockon001;
class EffectLockon001_Main;
class EffectLockon001_Sub;
class EffectTurbo001;
class EffectTurbo002;
class EffectCondensation001;
class EffectLaserRefraction001;
class EffectWormhole;
class EffectWormhole001;
class EffectEntry001;
class EffectEntry002;
class EffectEntry003;

class HoshiBoshiTransit;
class HoshiBoshiRankUp;
class HoshiBoshi001;
class HoshiBoshi002;
class HoshiBoshiTitle;
class WorldBoundSpaceTransit;
class WorldBoundSpace001;
class WorldBoundSpace002;
class WorldBoundSpaceRankUp;
class WorldBoundTitle;
class WorldBoundNameEntry;

class TurboMeter;
class LabelFix16Font01;
class LabelGecchi8Font;
class LabelGecchi16Font;
class LabelGecchi32Font;
class LabelMenuTitleFont01;
class LabelRankFont;
class LabelRankingFont;
class SpriteLabelTest;
class SpriteLabelGecchi32Font;
class SpriteLabelBonus001;
class LabelSceneSymbol;

class TamagoActor;
class TestEnemy;
class TestGu;
class TestChoki;
class TestPa;
class TestNomal;

class EnemyTamago01Actor;
class GameGlobal;



class EnemyCeres;
class EnemyCeresShot001;
class FormationCeres001;
class FormationCeres002;

class EnemyPallas;
class FormationPallas001;
class FormationPallas001a;
class FormationPallas001b;
class FormationPallas001c;
class FormationPallas001d;
class FormationPallas002;

class EnemyEunomia;
class FormationEunomia;
class FormationEunomia001;
class FormationEunomia001a;
class FormationEunomia001b;
class FormationEunomia002;
class FormationEunomia002a;
class FormationEunomia002b;

class EnemyJuno;
class FormationJuno;
class FormationJuno001;

class EnemyMetis;
class FormationMetis001;
class EnemyAdrastea;
class FormationAdrastea001;

class EnemyAstraea;
class EnemyAstraeaLaserChip001;
class EnemyAstraeaLaserChip002;
class EnemyAstraeaLaserChip003;
class EnemyAstraeaLaserChip004;

class EnemyIris;
class FormationIris001;
class FormationIris002;

class EnemyRomulus;
class EnemyRemus;
class EnemyRemusLaserChip001;

class EnemyCirce;

class EnemyThalia;
class FormationThalia;

class EnemyMassaliaBase;
class EnemyMassalia;
class EnemyMassaliaFragment;
class EnemyMassaliaFragment2;
class EnemyMassaliaFragment3;
class FormationMassalia;

class EnemyHebe;
class FormationHebe;
class FormationHebe001;

class EnemyThisbe;
class EnemyThisbe002;
class EnemyThisbeLaserChip001;
class EnemyThisbeLaserChip002;
class EnemyThisbeLaserChip003;

class EnemyHesperia;
class EnemyHesperiaLaserChip001;

class EnemyAtalante;

class EnemyHermione;
class EnemyHermioneArm;
class EnemyHermioneArmBody;
class EnemyHermioneArmHead;
class EnemyHermioneArmWeak;

class EnemySappho;
class FormationSappho001;
class FormationSappho001a;
class FormationSappho001b;

class EnemyAntiope;
class EnemyAntiopeP;
class EnemyAntiopeN;
class FormationAntiope001;

class EnemyAdelheid;
class FormationAdelheid;
class FormationAdelheid001;

class EnemyPalisana;

class DepositoryConnection;
class DepositoryManager;


class SplineLineConnection;
class SplineLineManager;


class CameraWorkerManager;
class CameraWorkerConnection;

class TestDepository;

class Item;
class MagicPointItem;
class MagicPointItem001;
class MagicPointItem002;
class ScoreItem;
class ScoreItem001;
class VreathItem;
class VreathItem001;

class Properties;
class QueryRanking;
class MyStgUtil;

template<class T>
class Formation001;


class Planet001;
class Planet001Atmosphere;

class CubeMapMeshTestActor;
class CubeMapMeshSetTestActor;
class CubeMapMorphMeshTestActor;
class DefaultD3DXAniMeshTestActor;
class DefaultBoardTestActor;
class DefaultBoardSetTestActor;
class DefaultMeshTestActor;
class DefaultD3DXMeshTestActor;
class DefaultMeshSetTestActor;
class DefaultMorphMeshTestActor;
class DefaultPointSpriteTestActor;
class DefaultSpriteTestActor;
class DefaultSpriteSetTestActor;
class GroundMeshTestActor;
class HoshiBoshiTestActor;
class LaserChipTestActor;
class SingleLaserTestActor;
class SpriteMeshTestActor;
class SpriteMeshSetTestActor;
class StringBoardTestActor;
class WallAABTestActor;
class WallAAPrismTestActor;

class VamSysCamPosition;
class MenuBoard;
class CursorCofirmMenu;
class MenuBoardConfirm;
class CursorPauseMenu;
class MenuBoardPause;
class CursorTitleMenu;
class MenuBoardTitle;

class CursorConfigMenu;
class MenuBoardConfig;
class CursorKeyConfigMenu;
class MenuBoardKeyConfig;
class CursorSoundConfigMenu;
class MenuBoardSoundConfig;

class MenuBoardNameEntry;
class CursorNameEntryMenu;
}

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerManager.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"

#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/PreDrawScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GamePreTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameDemoScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameBeginningScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameEndingScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameOverScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameOverScene/NameEntryScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/TamagoScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp001.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp002.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp003.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp100.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage03.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage04.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage05.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/TransitStage.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01_01.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01_02.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01_03.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01_Climax.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02/Stage02PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02/part/Stage02_01.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02/part/Stage02_Climax.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01WalledScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01WalledSection001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/wall/Wall001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/wall/Wall001Prism.h"

#include "jp/gecchi/VioletVreath/actor/Camera.h"
#include "jp/gecchi/VioletVreath/actor/ViewPointGuide.h"


#include "jp/gecchi/VioletVreath/actor/common/mesh/GroundMeshActor.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot001.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot002.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot003.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004Blue.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004Yellow.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/camera_worker/CameraWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/DefaultCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/VamSysCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/PauseCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/TestCamWorker.h"

#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionControllerGizmo.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionControllerDirectionVector.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001_Main.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001_Sub.h"

#include "jp/gecchi/VioletVreath/actor/my/MyShot001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyWave001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyVreath.h"

#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectMyShipExplosion.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedo.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoTail.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoBlast.h"

#include "jp/gecchi/VioletVreath/actor/my/_Test/TestGuShot.h"
#include "jp/gecchi/VioletVreath/actor/my/_Test/TestChokiShot.h"
#include "jp/gecchi/VioletVreath/actor/my/_Test/TestPaShot.h"
#include "jp/gecchi/VioletVreath/actor/my/_Test/TestNomalShot.h"

#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion002.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion003.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion004.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectCondensation001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectLaserRefraction001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectWormhole.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectWormhole001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectEntry001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectEntry002.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectEntry003.h"

#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/actor/my/option/EffectMyOption.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionStraightLaserChip001.h"



#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicMeterStatus.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicMeterCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor002.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor003.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/GraphBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/EnergyBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/CostDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/VreathBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/DamageDispBar.h"

#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/OptionMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/SpeedMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/VreathMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/SmileMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectSpeedMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectTorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectLockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectVreathMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectSmileMagic001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestGu.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestChoki.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestPa.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestNomal.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Tamago/TamagoActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Tamago/EnemyTamago01.h"

#include "jp/gecchi/VioletVreath/actor/title/TitleBoard.h"
#include "jp/gecchi/VioletVreath/actor/title/Cursor001.h"

#include "jp/gecchi/VioletVreath/actor/background/board/TurboMeter.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiTransit.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiRankUp.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi001.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi002.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiTitle.h"

#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpaceTransit.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpace001.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpace002.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpaceRankUp.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundTitle.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundNameEntry.h"

#include "jp/gecchi/VioletVreath/actor/label/LabelFix16Font01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi8Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi32Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelMenuTitleFont01.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelRankFont.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelRankingFont.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteLabelTest.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteLabelGecchi32Font.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteLabelBonus001.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelSceneSymbol.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/EnemyCeres.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/EnemyCeresShot001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/FormationCeres001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/FormationCeres002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/EnemyPallas.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001a.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001b.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001c.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001d.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/EnemyEunomia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia001a.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia001b.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia002.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia002a.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia002b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Juno/EnemyJuno.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Juno/FormationJuno.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Juno/FormationJuno001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Metis/EnemyMetis.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Metis/FormationMetis001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adrastea/EnemyAdrastea.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adrastea/FormationAdrastea001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraea.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip002.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip003.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip004.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Iris/EnemyIris.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Iris/FormationIris001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Iris/FormationIris002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Romulus/EnemyRomulus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Remus/EnemyRemus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Remus/EnemyRemusLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Circe/EnemyCirce.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Thalia/EnemyThalia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thalia/FormationThalia.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaBase.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassalia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment2.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment3.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/FormationMassalia.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/EnemyHebe.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/FormationHebe.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/FormationHebe001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Thisbe/EnemyThisbe.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thisbe/EnemyThisbe002.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thisbe/EnemyThisbeLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thisbe/EnemyThisbeLaserChip002.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thisbe/EnemyThisbeLaserChip003.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Hesperia/EnemyHesperia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hesperia/EnemyHesperiaLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Atalante/EnemyAtalante.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Hermione/EnemyHermione.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hermione/EnemyHermioneArm.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hermione/EnemyHermioneArmBody.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hermione/EnemyHermioneArmHead.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hermione/EnemyHermioneArmWeak.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/EnemySylvia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/VarietySylvia001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/VarietySylvia002.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/VarietySylvia003.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/VarietySylvia004.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/EnemySylviaEye.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/EnemySylviaEyeStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sylvia/EffectSylviaEye001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Sappho/EnemySappho.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sappho/FormationSappho001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sappho/FormationSappho001a.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Sappho/FormationSappho001b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Antiope/EnemyAntiope.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Antiope/EnemyAntiopeP.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Antiope/EnemyAntiopeN.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Antiope/FormationAntiope001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Adelheid/EnemyAdelheid.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adelheid/FormationAdelheid.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adelheid/FormationAdelheid001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Palisana/EnemyPalisana.h"

#include "jp/gecchi/VioletVreath/actor/item/Item.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem001.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem002.h"
#include "jp/gecchi/VioletVreath/actor/item/ScoreItem.h"
#include "jp/gecchi/VioletVreath/actor/item/ScoreItem001.h"
#include "jp/gecchi/VioletVreath/actor/item/VreathItem.h"
#include "jp/gecchi/VioletVreath/actor/item/VreathItem001.h"

#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/util/QueryRanking.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/util/VamSysCamPosition.h"

#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryConnection.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineManager.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineConnection.h"

#include "jp/gecchi/VioletVreath/actor/common/template/Formation001.hpp"

#include "jp/gecchi/VioletVreath/actor/common/TestDepository.h"

#include "jp/gecchi/VioletVreath/actor/chikei/Planet/Planet001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Planet/Planet001Atmosphere.h"


#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMorphMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultD3DXAniMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultBoardTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultBoardSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultD3DXMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMorphMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultPointSpriteTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultSpriteTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultSpriteSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/HoshiBoshiTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/LaserChipTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SingleLaserTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SpriteMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SpriteMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/StringBoardTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/WallAABTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/WallAAPrismTestActor.h"

#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

#include "jp/gecchi/VioletVreath/actor/menu/confirm/CursorConfirmMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"

#include "jp/gecchi/VioletVreath/actor/menu/pause/CursorPauseMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"

#include "jp/gecchi/VioletVreath/actor/menu/title/CursorTitleMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/title/MenuBoardTitle.h"

#include "jp/gecchi/VioletVreath/actor/menu/config/CursorKeyConfigMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardKeyConfig.h"

#include "jp/gecchi/VioletVreath/actor/menu/config/CursorSoundConfigMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardSoundConfig.h"

#include "jp/gecchi/VioletVreath/actor/menu/config/CursorConfigMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/config/MenuBoardConfig.h"

#include "jp/gecchi/VioletVreath/actor/menu/name_entry/MenuBoardNameEntry.h"
#include "jp/gecchi/VioletVreath/actor/menu/name_entry/CursorNameEntryMenu.h"

#endif /*VIOLETVREATHHEADER_H_*/
