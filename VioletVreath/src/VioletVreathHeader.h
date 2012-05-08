#ifndef VIOLETVREATHHEADER_H_
#define VIOLETVREATHHEADER_H_

//「DirectX9ライブラリ」を利用する場合（利用者は俺）
//次の"GgafLibHeader.h"ヘッダをインクルードします。

#include "GgafLibHeader.h"


#define KIND_EFFECT                  (0x0)       //0b 00000000000000000000000000000000
#define KIND_MY_SHOT_NOMAL           (0x8)       //0b 00000000000000000000000000001000
#define KIND_MY_SHOT_GU              (0x11)      //0b 00000000000000000000000000010001
#define KIND_MY_SHOT_CHOKI           (0x22)      //0b 00000000000000000000000000100010
#define KIND_MY_SHOT_PA              (0x44)      //0b 00000000000000000000000001000100
#define KIND_ENEMY_SHOT_NOMAL        (0x80)      //0b 00000000000000000000000010000000
#define KIND_ENEMY_SHOT_GU           (0x101)     //0b 00000000000000000000000100000001
#define KIND_ENEMY_SHOT_CHOKI        (0x202)     //0b 00000000000000000000001000000010
#define KIND_ENEMY_SHOT_PA           (0x404)     //0b 00000000000000000000010000000100
#define KIND_MY_BODY_NOMAL           (0x800)     //0b 00000000000000000000100000000000
#define KIND_MY_BODY_GU              (0x1001)    //0b 00000000000000000001000000000001
#define KIND_MY_BODY_CHOKI           (0x2002)    //0b 00000000000000000010000000000010
#define KIND_MY_BODY_PA              (0x4004)    //0b 00000000000000000100000000000100
#define KIND_ENEMY_BODY_NOMAL        (0x8000)    //0b 00000000000000001000000000000000
#define KIND_ENEMY_BODY_GU           (0x10001)   //0b 00000000000000010000000000000001
#define KIND_ENEMY_BODY_CHOKI        (0x20002)   //0b 00000000000000100000000000000010
#define KIND_ENEMY_BODY_PA           (0x40004)   //0b 00000000000001000000000000000100
#define KIND_ENEMY_BODY_CHIKEI_NOMAL (0x80000)   //0b 00000000000010000000000000000000
#define KIND_ENEMY_BODY_CHIKEI_GU    (0x100001)  //0b 00000000000100000000000000000001
#define KIND_ENEMY_BODY_CHIKEI_CHOKI (0x200002)  //0b 00000000001000000000000000000010
#define KIND_ENEMY_BODY_CHIKEI_PA    (0x400004)  //0b 00000000010000000000000000000100
#define KIND_CHIKEI                  (0x800000)  //0b 00000000100000000000000000000000
#define KIND_OTHER                   (0x1000000) //0b 00000001000000000000000000000000
#define KIND_ITEM                    (0x2000000) //0b 00000010000000000000000000000000

#define KIND_MY     (KIND_MY_SHOT_NOMAL|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA|KIND_MY_BODY_NOMAL|KIND_MY_BODY_GU|KIND_MY_BODY_CHOKI|KIND_MY_BODY_PA)
#define KIND_ENEMY  (KIND_ENEMY_SHOT_NOMAL|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_ENEMY_BODY_NOMAL|KIND_ENEMY_BODY_GU|KIND_ENEMY_BODY_CHOKI|KIND_ENEMY_BODY_PA|KIND_ENEMY_BODY_CHIKEI_NOMAL|KIND_ENEMY_BODY_CHIKEI_GU|KIND_ENEMY_BODY_CHIKEI_CHOKI|KIND_ENEMY_BODY_CHIKEI_PA)
#define KIND_MY_SHOT     (KIND_MY_SHOT_NOMAL|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA)
#define KIND_MY_BODY     (KIND_MY_BODY_NOMAL|KIND_MY_BODY_GU|KIND_MY_BODY_CHOKI|KIND_MY_BODY_PA)
#define KIND_ENEMY_SHOT  (KIND_ENEMY_SHOT_NOMAL|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA)
#define KIND_ENEMY_BODY  (KIND_ENEMY_BODY_NOMAL|KIND_ENEMY_BODY_GU|KIND_ENEMY_BODY_CHOKI|KIND_ENEMY_BODY_PA|KIND_ENEMY_BODY_CHIKEI_NOMAL|KIND_ENEMY_BODY_CHIKEI_GU|KIND_ENEMY_BODY_CHIKEI_CHOKI|KIND_ENEMY_BODY_CHIKEI_PA)

#define KIND_NOMAL       (0x0)    //000
#define KIND_GU          (0x1)    //001
#define KIND_CHOKI       (0x2)    //010
#define KIND_PA          (0x4)    //100

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
#define STAT_AddScorePoint          1
#define STAT_AddRankPoint           2
#define STAT_AddRankPoint_Reduction 3
#define STAT_Stamina                4
#define STAT_Attack                 5
#define STAT_DefaultDefenceRate     6
#define STAT_DominantDefenceRate    7
#define STAT_RecessiveDefenceRate   8
#define STAT_LockonAble             9

// 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
// コード変更は「RankAdjuster.xls」から行っていただきたい。
// gen01 start
// EnemyEunomia のランク式
#define R_EnemyEunomia_ShotWay  (10+_RANK_*10)  //発射WAY数
// FormationEunomia001 のランク式
#define R_FormationEunomia001_Col  (5 + (_RANK_>1.0?1.0:_RANK_)*2)  //列数
#define R_FormationEunomia001_Num  (20 + _RANK_*10)  //隊数
#define R_FormationEunomia001_LaunchInterval  (2  + (10 - (_RANK_>1.0?1.0:_RANK_)*10))  //出現間隔
#define R_FormationEunomia001_MvVelo  (10000 + _RANK_*10000)  //移動速度
// FormationEunomia002 のランク式
#define R_FormationEunomia002_Col  (5 + (_RANK_>1.0?1.0:_RANK_)*2)  //列数
#define R_FormationEunomia002_Num  (20 + _RANK_*10)  //隊数
#define R_FormationEunomia002_LaunchInterval  (2  + (10 - (_RANK_>1.0?1.0:_RANK_)*10))  //出現間隔
#define R_FormationEunomia002_MvVelo  (10000 + _RANK_*10000)  //移動速度
// EnemyIris のランク式
#define R_EnemyIris_ShotWay  (10+_RANK_*10)  //発射WAY数
// FormationIris001 のランク式
#define R_FormationIris001_Num  (7 + _RANK_*7)  //隊数
#define R_FormationIris001_LaunchInterval  (5 + (20 - (_RANK_>1.0?1.0:_RANK_)*20))  //出現間隔
#define R_FormationIris001_MvVelo  (16000+_RANK_*1600)  //移動速度
// FormationIris002 のランク式
#define R_FormationIris002_Num  (7 + _RANK_*7)  //隊数
#define R_FormationIris002_LaunchInterval  (5 + (20 - (_RANK_>1.0?1.0:_RANK_)*20))  //出現間隔
#define R_FormationIris002_MvVelo  (16000+_RANK_*1600)  //移動速度
// EnemyPallas のランク式
#define R_EnemyPallas_ShotWay  (10+_RANK_*10)  //発射WAY数
// FormationPallas001 のランク式
#define R_FormationPallas001_Num  (12+_RANK_*8)  //隊数
#define R_FormationPallas001_LaunchInterval  (5 + (20 - (_RANK_>1.0?1.0:_RANK_)*20))  //出現間隔
#define R_FormationPallas001_MvVelo  (10000 + _RANK_*10000)  //移動速度
// FormationPallas002 のランク式
#define R_FormationPallas002_Num  (12+_RANK_*8)  //隊数
#define R_FormationPallas002_LaunchInterval  (5 + (20 - (_RANK_>1.0?1.0:_RANK_)*20))  //出現間隔
#define R_FormationPallas002_MvVelo  (10000 + _RANK_*10000)  //移動速度
// EnemyThalia のランク式
#define R_EnemyThalia_ShotWay  (20+_RANK_*10)  //発射WAY数
// FormationThalia のランク式
#define R_FormationThalia_Num  (7+_RANK_*4)  //隊数
#define R_FormationThalia_LaunchInterval  (5 + (20 - (_RANK_>1.0?1.0:_RANK_) *20))  //出現間隔
#define R_FormationThalia_MvVelo  (14000+_RANK_*10000)  //移動速度
// EnemyVesta のランク式
#define R_EnemyVesta_ShotInterval  (2 + (25 - (_RANK_>1.0?1.0:_RANK_) * 25))  //発射間隔
// Shot001 のランク式
#define R_Shot001_MvVelo  (5000+_RANK_*5000)  //移動速度
#define R_Shot001_AngVelo  (6000+_RANK_*6000)  //角速度
// Shot002 のランク式
#define R_Shot002_MvVelo  (8000+_RANK_*8000)  //移動速度
#define R_Shot002_AngVelo  (1000+_RANK_*1000)  //角速度
// EnemyMassalia のランク式
#define R_EnemyMassalia_ShotWay  (4+_RANK_*4)  //発射WAY数
// EnemyMassaliaFragment のランク式
// EnemyMassaliaFragment2 のランク式
// EnemyMassaliaFragment3 のランク式
// FormationMassalia のランク式
#define R_FormationMassalia_LaunchInterval  (10  + (20 - (_RANK_>1.0?1.0:_RANK_)*20))  //出現間隔
#define R_FormationMassalia_MvVelo  (8000+_RANK_*8000)  //移動速度
#define R_FormationMassalia_DurationFrames  (60*20)  //持続時間
// gen02 end

//1/√2
#define NANAME 0.70710

#undef P_GOD
#define P_GOD ((VioletVreath::God*)VioletVreath::God::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((VioletVreath::Universe*)(P_GOD->_pUniverse))

#define FADE_FRAMES 60

#define DRAW_DEPTH_LEVEL_HOSHIBOSHI (MAX_DRAW_DEPTH_LEVEL-1)
#define DRAW_DEPTH_LEVEL_BIGOBJ     (MAX_DRAW_DEPTH_LEVEL-2)

/** int32ランダム関数マクロ。__FROM__と__TO__が逆転してはいけない(負の%演算はVC++で不定) */
#define RND(__FROM__,__TO__) ((GgafCore::CmRandomNumberGenerator::getInstance()->genrand_int32() % ((__TO__) - (__FROM__)) ) + (__FROM__) )

//イベント用 UINT32 数値宣言
DECLARE_CONST(EVENT_GOD_WILL_DIE);
DECLARE_CONST(EVENT_PREPARE_TRANSIT_STAGE);
DECLARE_CONST(EVENT_PREPARE_NEXT_STAGE);
DECLARE_CONST(EVENT_JUST_GAME_OVER);
DECLARE_CONST(EVENT_STG01_01_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_02_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_03_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_CLIMAX_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_CTRLER_WAS_END);
DECLARE_CONST(EVENT_STG01_WAS_END);

DECLARE_CONST(EVENT_TRANSIT_WAS_END);
DECLARE_CONST(EVENT_RANKUP_WAS_END);
DECLARE_CONST(EVENT_RANKUP_ON_GARBAGED);

DECLARE_CONST(EVENT_STG02_01_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_02_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_03_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_CLIMAX_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_CTRLER_WAS_END);
DECLARE_CONST(EVENT_STG02_WAS_END);

DECLARE_CONST(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
DECLARE_CONST(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
DECLARE_CONST(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
DECLARE_CONST(EVENT_GAME_OVER_FINISH);

DECLARE_CONST(EVENT_PREGAMETITLESCENE_FINISH);
DECLARE_CONST(EVENT_GAMETITLESCENE_FINISH);
DECLARE_CONST(EVENT_GAMEDEMOSCENE_FINISH);
DECLARE_CONST(EVENT_GAMESTART);
DECLARE_CONST(EVENT_GOTO_GAMETITLE);
DECLARE_CONST(EVENT_GAMEMODE_DECIDE);


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
class GamePauseScene;


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
class Torus;
class VarietyTorus001;
class VarietyTorus002;
class VarietyTorus003;
class VarietyTorus004;


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
class MyOptionController;
class MyOptionControllerGizmo;
class MyOptionControllerDirectionVector;
class MyOption;
class EffectMyOption;
class MyOptionLockonController;
class MyOptionTorpedoController;
class MyTorpedoTail;
class MyTorpedo;
class MyTorpedoBlast;
class MyShot001;
class MyWave001;
class EffectMyShipExplosion;


class EffectExplosion001;
class EffectExplosion002;
class EffectExplosion003;
class EffectLockon001;
class EffectLockon001_Main;
class EffectLockon001_Sub;
class EffectTurbo001;
class EffectTurbo002;
class EffectCondensation001;
class EffectLaserRefraction001;
class EffectWormhole;
class EffectWormhole001;


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

class TurboMeter;
class LabelGecchi8Font;
class LabelGecchi16Font;
class LabelRankFont;
class LabelRankingFont;

class TamagoActor;
class EnemyTamago01Actor;
class MyUtil;
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

class EnemyAstraea;
class EnemyAstraeaLaserChip001;
class EnemyAstraeaLaserChip002;
class EnemyAstraeaLaserChip003;
class EnemyAstraeaLaserChip004;

class EnemyIris;
class FormationIris001;
class FormationIris002;

class EnemyVesta;

class EnemyCirce;

class EnemyThalia;
class FormationThalia;

class EnemyMassalia;
class EnemyMassaliaFragment;
class EnemyMassaliaFragment2;
class EnemyMassaliaFragment3;
class FormationMassalia;

class DepositoryConnection;
class DepositoryManager;


class SplineLineConnection;
class SplineLineManager;


class CameraWorkerManager;
class CameraWorkerConnection;


class TestDepository;
class MagicMeter;
class MagicMeterStatus;
class MagicMeterCursor001;
class MagicLvCursor;
class MagicLvCursor001;
class MagicLvCursor002;
class MagicLvCursor003;
class EnergyBar;
class CostDispBar;

class Magic;
class OptionMagic;
class LaserMagic;
class SpeedMagic;
class LockonMagic;
class TorpedoMagic;
class TractorMagic;
class EffectMagic001;
class EffectSpeedMagic;
class EffectVreathMagic001;

class Item;
class MagicPointItem;
class MagicPointItem001;
class MagicPointItem002;

class Properties;
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
class MenuBoardConfirm;
class CursorCofirmMenu;
class MenuBoardPause;
class CursorPauseMenu;
class MenuBoardTitle;
class CursorTitleMenu;

}

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerManager.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"
#include "jp/gecchi/VioletVreath/actor/common/CameraWorker.h"
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
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GamePauseScene.h"
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
#include "jp/gecchi/VioletVreath/actor/camera_worker/TestCamWorker.h"


#include "jp/gecchi/VioletVreath/actor/common/DefaultCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/common/mesh/GroundMeshActor.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot001.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot002.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot003.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004Blue.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004Yellow.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/camera_worker/VamSysCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/PauseCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionControllerGizmo.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionControllerDirectionVector.h"

#include "jp/gecchi/VioletVreath/actor/my/MyShot001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyWave001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectMyShipExplosion.h"

#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion002.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion003.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectCondensation001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectLaserRefraction001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectWormhole.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectWormhole001.h"


#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/actor/my/option/EffectMyOption.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionTorpedoController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyTorpedo.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyTorpedoTail.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyTorpedoBlast.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionStraightLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/option/EffectLockon001.h"
#include "jp/gecchi/VioletVreath/actor/my/option/EffectLockon001_Main.h"
#include "jp/gecchi/VioletVreath/actor/my/option/EffectLockon001_Sub.h"

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

#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi8Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelRankFont.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelRankingFont.h"




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

#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraea.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip002.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip003.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip004.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Iris/EnemyIris.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Iris/FormationIris001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Iris/FormationIris002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Vesta/EnemyVesta.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Circe/EnemyCirce.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Thalia/EnemyThalia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thalia/FormationThalia.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassalia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment2.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment3.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/FormationMassalia.h"

#include "jp/gecchi/VioletVreath/actor/chikei/Torus/Torus.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Torus/VarietyTorus001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Torus/VarietyTorus002.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Torus/VarietyTorus003.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Torus/VarietyTorus004.h"


#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter/MagicMeterStatus.h"
#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter/MagicMeterCursor001.h"
#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter/MagicLvCursor.h"
#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter/MagicLvCursor001.h"
#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter/MagicLvCursor002.h"
#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter/MagicLvCursor003.h"
#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter/EnergyBar.h"
#include "jp/gecchi/VioletVreath/actor/system/instrument/MagicMeter/CostDispBar.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/Magic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/OptionMagic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/SpeedMagic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/LockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/TorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/VreathMagic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/effect/EffectMagic001.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/effect/EffectSpeedMagic.h"
#include "jp/gecchi/VioletVreath/actor/system/magic/effect/EffectVreathMagic001.h"

#include "jp/gecchi/VioletVreath/actor/item/Item.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem001.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem002.h"

#include "jp/gecchi/VioletVreath/Properties.h"
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
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/CursorConfirmMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/actor/menu/pause/CursorPauseMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/title/MenuBoardTitle.h"
#include "jp/gecchi/VioletVreath/actor/menu/title/CursorTitleMenu.h"




#endif /*VIOLETVREATHHEADER_H_*/
