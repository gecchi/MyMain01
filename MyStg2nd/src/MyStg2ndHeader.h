#ifndef MYSTG2NDHEADER_H_
#define MYSTG2NDHEADER_H_

//「DirectX9ライブラリ」を利用する場合（利用者は俺）
//次の"GgafDx9LibStgHeader.h"ヘッダをインクルードします。

#include "GgafDx9LibStgHeader.h"

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




#define _RANK_ (GameGlobal::_rank)
#define _SCORE_ (GameGlobal::_score)


#define R_Shot001_MvVelo (5000+_RANK_*5000)       //移動速度
#define R_Shot001_AngVelo (6000+_RANK_*6000)  //きりもみ具合

#define R_Shot002_MvVelo (8000+_RANK_*8000)       //移動速度
#define R_Shot002_AngVelo (1000+_RANK_*1000)  //きりもみ具合

#define R_EnemyEunomia_ShotWay (10+_RANK_*10) //ショットWAY数

#define R_FormationEunomia001_Col (5 + _RANK_*2)    //編隊列数
#define R_FormationEunomia001_Num (20 + _RANK_*10)  //１列の編隊数
#define R_FormationEunomia001_LaunchInterval (2  + (10 - (_RANK_>1.0?1.0:_RANK_)*10))  //出現間隔(frame)
#define R_FormationEunomia001_MvVelo (10000 + _RANK_*10000) //移動速度

#define R_FormationEunomia002_Col (5 + _RANK_*2)    //編隊列数
#define R_FormationEunomia002_FormationNum (20 + _RANK_*10)  //１列の編隊数
#define R_FormationEunomia002_LaunchInterval (2  + (10 - (_RANK_>1.0?1.0:_RANK_)*10))  //出現間隔(frame)
#define R_FormationEunomia002_MvVelo (10000 + _RANK_*10000) //移動速度

#define R_EnemyIris_ShotWay (10+_RANK_*10) //ショットWAY数
#define R_FormationIris001_Num   (7 + _RANK_*7)    //編隊数
#define R_FormationIris001_LaunchInterval (5 + (20 - (_RANK_>1.0?1.0:_RANK_) *20))   //出現間隔(frame)
#define R_FormationIris001_MvVelo (8000+_RANK_*8000) //移動速度
#define R_FormationIris002_Num   (10 +_RANK_*10)    //編隊数
#define R_FormationIris002_LaunchInterval (5  + (20 - (_RANK_>1.0?1.0:_RANK_) *20))   //出現間隔(frame)
#define R_FormationIris002_MvVelo (16000+_RANK_*1600) //移動速度

#define R_EnemyPallas_ShotWay (10+_RANK_*10) //ショットWAY数
#define R_FormationPallas001_Num   (7 + _RANK_*7)    //編隊数
#define R_FormationPallas001_LaunchInterval (5 + (20 - (_RANK_>1.0?1.0:_RANK_) *20))   //出現間隔(frame)
#define R_FormationPallas001_MvVelo (8000+_RANK_*8000) //移動速度
#define R_FormationPallas002_Num   (12+_RANK_*8)    //編隊数
#define R_FormationPallas002_LaunchInterval (5  + (20 - (_RANK_>1.0?1.0:_RANK_) *20))   //出現間隔(frame)
#define R_FormationPallas002_MvVelo (10000+_RANK_*10000) //移動速度

#define R_EnemyThalia_ShotWay (20+_RANK_*10)  //やられ
#define R_FormationThalia_Num   (7+_RANK_*4)    //編隊数
#define R_FormationThalia_LaunchInterval (5 + (20 - (_RANK_>1.0?1.0:_RANK_) *20))   //出現間隔(frame)
#define R_FormationThalia_MvVelo (14000+_RANK_*10000) //移動速度

#define R_EnemyVesta_ShotInterval (2 + (25 - (_RANK_>1.0?1.0:_RANK_) * 25))
// gen01 start

// gen02 end

//1/√2
#define NANAME 0.70710

#undef P_GOD
#define P_GOD ((MyStg2nd::God*)MyStg2nd::God::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((MyStg2nd::Universe*)(P_GOD->_pUniverse))

#define FADE_FRAMES 60

enum MoveWay {
    WAY_ZRIGHT_DOWN_BEHIND = 0,   //0    TN(-1,-1,-1)
    WAY_DOWN_BEHIND,              //1    TN(-1,-1, 0)
    WAY_ZLEFT_DOWN_BEHIND,        //2    TN(-1,-1, 1)
    WAY_ZRIGHT_BEHIND,            //3    TN(-1, 0,-1)
    WAY_BEHIND,                   //4    TN(-1, 0, 0)
    WAY_ZLEFT_BEHIND,             //5    TN(-1, 0, 1)
    WAY_ZRIGHT_UP_BEHIND,         //6    TN(-1, 1,-1)
    WAY_UP_BEHIND,                //7    TN(-1, 1, 0)
    WAY_ZLEFT_UP_BEHIND,          //8    TN(-1, 1, 1)
    WAY_ZRIGHT_DOWN,              //9    TN( 0,-1,-1)
    WAY_DOWN,                     //10   TN( 0,-1, 0)
    WAY_ZLEFT_DOWN,               //11   TN( 0,-1, 1)
    WAY_ZRIGHT,                   //12   TN( 0, 0,-1)
    WAY_NONE,                     //13   TN( 0, 0, 0)
    WAY_ZLEFT,                    //14   TN( 0, 0, 1)
    WAY_ZRIGHT_UP,                //15   TN( 0, 1,-1)
    WAY_UP,                       //16   TN( 0, 1, 0)
    WAY_ZLEFT_UP,                 //17   TN( 0, 1, 1)
    WAY_ZRIGHT_DOWN_FRONT,        //18   TN( 1,-1,-1)
    WAY_DOWN_FRONT,               //19   TN( 1,-1, 0)
    WAY_ZLEFT_DOWN_FRONT,         //20   TN( 1,-1, 1)
    WAY_ZRIGHT_FRONT,             //21   TN( 1, 0,-1)
    WAY_FRONT,                    //22   TN( 1, 0, 0)
    WAY_ZLEFT_FRONT,              //23   TN( 1, 0, 1)
    WAY_ZRIGHT_UP_FRONT,          //24   TN( 1, 1,-1)
    WAY_UP_FRONT,                 //25   TN( 1, 1, 0)
    WAY_ZLEFT_UP_FRONT            //26   TN( 1, 1, 1)
};
//イベント用 UINT32 数値宣言
DECLARE_CONST(EVENT_GOD_WILL_DIE);

DECLARE_CONST(EVENT_PREPARE_NEXT_STAGE);
DECLARE_CONST(EVENT_JUST_GAME_OVER);
DECLARE_CONST(EVENT_STG01_01_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_02_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_03_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_CLIMAX_WAS_BROKEN);
DECLARE_CONST(EVENT_STAGE01CONTROLLER_WAS_END);
DECLARE_CONST(EVENT_STG02_01_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_02_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_03_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_CLIMAX_WAS_BROKEN);
DECLARE_CONST(EVENT_STAGE02CONTROLLER_WAS_END);
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


namespace MyStg2nd {

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
class StageController;
class StageScene;
class Stage01Scene;
class Stage02Scene;
class Stage03Scene;
class Stage04Scene;
class Stage05Scene;
class TamagoScene;

class Stage01Controller;
class Stage01_01;
class Stage01_02;
class Stage01_03;
class Stage01_Climax;

class Stage01WalledSection001;
class Stage01WalledScene;
class Wall001;
class Wall001Prism;

class Stage02Controller;
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

class HoshiBoshi001;
class HoshiBoshi002;
class WorldBoundSpace001;
class WorldBoundSpace002;
class TurboMeter;
class LabelGecchi8Font;
class LabelGecchi16Font;
class LabelRankFont;

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


class DepositoryConnection;
class DepositoryManager;


class Spline3DConnection;
class Spline3DManager;


class CameraWorkerManager;
class CameraWorkerConnection;


class TestDepository;
class MagicMeter;
class EnagyBar;

class Magic;
class OptionMagic;
class LaserMagic;
class SpeedMagic;
class LockonMagic;
class TorpedoMagic;
class TractorMagic;
class EffectMagic001;

class Item;
class MagicPointItem001;
class Item001;

class Properties;
class MyStgUtil;

template<class T>
class Formation001;



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

class MagicMeter;

}

#include "gecchi/God.h"
#include "gecchi/manager/CameraWorkerManager.h"
#include "gecchi/manager/CameraWorkerConnection.h"
#include "gecchi/actor/common/CameraWorker.h"
#include "gecchi/scene/Universe.h"
#include "gecchi/scene/Universe/World.h"
#include "gecchi/scene/Universe/World/PreDrawScene.h"
#include "gecchi/scene/Universe/World/GameScene.h"

#include "gecchi/scene/Universe/World/GameScene/MyShipScene.h"
#include "gecchi/scene/Universe/World/GameScene/GamePreTitleScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameTitleScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameDemoScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameBeginningScene.h"
#include "gecchi/scene/Universe/World/GameScene/CommonScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameEndingScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameOverScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/StageScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage01Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage02Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage03Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage04Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage05Scene.h"
#include "gecchi/scene/Universe/World/GameScene/TamagoScene.h"

#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage01Scene/Stage01Controller.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage01Scene/part/Stage01_01.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage01Scene/part/Stage01_02.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage01Scene/part/Stage01_03.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage01Scene/part/Stage01_Climax.h"

#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage02Scene/Stage02Controller.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage02Scene/part/Stage02_01.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage02Scene/part/Stage02_Climax.h"

#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage01Scene/part/Stage01WalledScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageController/Stage01Scene/part/Stage01WalledSection001.h"
#include "gecchi/actor/chikei/wall/Wall001.h"
#include "gecchi/actor/chikei/wall/Wall001Prism.h"

#include "gecchi/actor/Camera.h"
#include "gecchi/actor/ViewPointGuide.h"
#include "gecchi/actor/camera_worker/TestCamWorker.h"


#include "gecchi/actor/common/DefaultCamWorker.h"
#include "gecchi/actor/common/mesh/GroundMeshActor.h"
#include "gecchi/actor/common/shot/Shot001.h"
#include "gecchi/actor/common/shot/Shot002.h"
#include "gecchi/actor/common/shot/Shot003.h"
#include "gecchi/actor/common/shot/Shot004.h"
#include "gecchi/actor/common/laserchip/EnemyWateringLaserChip001.h"
#include "gecchi/actor/common/laserchip/EnemyStraightLaserChip001.h"

#include "gecchi/actor/camera_worker/VamSysCamWorker.h"
#include "gecchi/actor/camera_worker/PauseCamWorker.h"
#include "gecchi/actor/camera_worker/MyShipDivingCamWorker.h"
#include "gecchi/actor/my/MyShip.h"
#include "gecchi/actor/my/MyOptionController.h"
#include "gecchi/actor/my/MyOptionControllerGizmo.h"
#include "gecchi/actor/my/MyOptionControllerDirectionVector.h"

#include "gecchi/actor/my/MyShot001.h"
#include "gecchi/actor/my/MyWave001.h"

#include "gecchi/actor/my/MyStraightLaserChip001.h"
#include "gecchi/actor/my/EffectMyShipExplosion.h"

#include "gecchi/actor/effect/EffectExplosion001.h"
#include "gecchi/actor/effect/EffectExplosion002.h"
#include "gecchi/actor/effect/EffectExplosion003.h"
#include "gecchi/actor/effect/EffectTurbo001.h"
#include "gecchi/actor/effect/EffectTurbo002.h"
#include "gecchi/actor/effect/EffectCondensation001.h"
#include "gecchi/actor/effect/EffectLaserRefraction001.h"

#include "gecchi/actor/my/option/MyOption.h"
#include "gecchi/actor/my/option/EffectMyOption.h"
#include "gecchi/actor/my/option/MyOptionLockonController.h"
#include "gecchi/actor/my/option/MyOptionTorpedoController.h"
#include "gecchi/actor/my/option/MyTorpedo.h"
#include "gecchi/actor/my/option/MyTorpedoTail.h"
#include "gecchi/actor/my/option/MyTorpedoBlast.h"
#include "gecchi/actor/my/option/MyOptionWateringLaserChip001.h"
#include "gecchi/actor/my/option/MyOptionStraightLaserChip001.h"

#include "gecchi/actor/my/option/EffectLockon001.h"
#include "gecchi/actor/my/option/EffectLockon001_Main.h"
#include "gecchi/actor/my/option/EffectLockon001_Sub.h"

#include "gecchi/actor/enemy/Tamago/TamagoActor.h"
#include "gecchi/actor/enemy/Tamago/EnemyTamago01.h"

#include "gecchi/actor/title/TitleBoard.h"
#include "gecchi/actor/title/Cursor001.h"

#include "gecchi/actor/background/board/TurboMeter.h"
#include "gecchi/actor/background/HoshiBoshi001.h"
#include "gecchi/actor/background/HoshiBoshi002.h"

#include "gecchi/actor/label/LabelGecchi8Font.h"
#include "gecchi/actor/label/LabelGecchi16Font.h"
#include "gecchi/actor/label/LabelRankFont.h"

#include "gecchi/actor/background/WorldBound/WorldBoundSpace001.h"
#include "gecchi/actor/background/WorldBound/WorldBoundSpace002.h"

#include "gecchi/GameGlobal.h"

#include "gecchi/actor/enemy/Ceres/EnemyCeres.h"
#include "gecchi/actor/enemy/Ceres/EnemyCeresShot001.h"
#include "gecchi/actor/enemy/Ceres/FormationCeres001.h"
#include "gecchi/actor/enemy/Ceres/FormationCeres002.h"

#include "gecchi/actor/enemy/Pallas/EnemyPallas.h"
#include "gecchi/actor/enemy/Pallas/FormationPallas001.h"
#include "gecchi/actor/enemy/Pallas/FormationPallas001a.h"
#include "gecchi/actor/enemy/Pallas/FormationPallas001b.h"
#include "gecchi/actor/enemy/Pallas/FormationPallas001c.h"
#include "gecchi/actor/enemy/Pallas/FormationPallas001d.h"
#include "gecchi/actor/enemy/Pallas/FormationPallas002.h"

#include "gecchi/actor/enemy/Eunomia/EnemyEunomia.h"
#include "gecchi/actor/enemy/Eunomia/FormationEunomia.h"
#include "gecchi/actor/enemy/Eunomia/FormationEunomia001.h"
#include "gecchi/actor/enemy/Eunomia/FormationEunomia001a.h"
#include "gecchi/actor/enemy/Eunomia/FormationEunomia001b.h"
#include "gecchi/actor/enemy/Eunomia/FormationEunomia002.h"
#include "gecchi/actor/enemy/Eunomia/FormationEunomia002a.h"
#include "gecchi/actor/enemy/Eunomia/FormationEunomia002b.h"

#include "gecchi/actor/enemy/Juno/EnemyJuno.h"
#include "gecchi/actor/enemy/Juno/FormationJuno.h"
#include "gecchi/actor/enemy/Juno/FormationJuno001.h"
#include "gecchi/actor/enemy/Metis/EnemyMetis.h"
#include "gecchi/actor/enemy/Metis/FormationMetis001.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraea.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip001.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip002.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip003.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip004.h"
#include "gecchi/actor/enemy/Iris/EnemyIris.h"
#include "gecchi/actor/enemy/Iris/FormationIris001.h"
#include "gecchi/actor/enemy/Iris/FormationIris002.h"
#include "gecchi/actor/enemy/Vesta/EnemyVesta.h"
#include "gecchi/actor/enemy/Circe/EnemyCirce.h"
#include "gecchi/actor/enemy/Thalia/EnemyThalia.h"
#include "gecchi/actor/enemy/Thalia/FormationThalia.h"
#include "gecchi/actor/enemy/Massalia/EnemyMassalia.h"

#include "gecchi/actor/chikei/Torus/Torus.h"
#include "gecchi/actor/chikei/Torus/VarietyTorus001.h"
#include "gecchi/actor/chikei/Torus/VarietyTorus002.h"
#include "gecchi/actor/chikei/Torus/VarietyTorus003.h"
#include "gecchi/actor/chikei/Torus/VarietyTorus004.h"


#include "gecchi/actor/system/instrument/MagicMeter.h"
#include "gecchi/actor/system/instrument/EnagyBar.h"

#include "gecchi/actor/system/magic/Magic.h"
#include "gecchi/actor/system/magic/OptionMagic.h"
#include "gecchi/actor/system/magic/LaserMagic.h"
#include "gecchi/actor/system/magic/SpeedMagic.h"
#include "gecchi/actor/system/magic/LockonMagic.h"
#include "gecchi/actor/system/magic/TorpedoMagic.h"
#include "gecchi/actor/system/magic/EffectMagic001.h"
#include "gecchi/actor/system/magic/TractorMagic.h"

#include "gecchi/actor/item/Item.h"
#include "gecchi/actor/item/MagicPointItem001.h"
#include "gecchi/actor/item/Item001.h"

#include "gecchi/Properties.h"
#include "gecchi/util/MyStgUtil.h"
#include "gecchi/util/VamSysCamPosition.h"

#include "gecchi/manager/DepositoryManager.h"
#include "gecchi/manager/DepositoryConnection.h"
#include "gecchi/manager/Spline3DManager.h"
#include "gecchi/manager/Spline3DConnection.h"

#include "gecchi/actor/common/template/Formation001.hpp"

#include "gecchi/actor/common/TestDepository.h"

#include "gecchi/actor/_predrawer/CubeMapMeshTestActor.h"
#include "gecchi/actor/_predrawer/CubeMapMeshSetTestActor.h"
#include "gecchi/actor/_predrawer/CubeMapMorphMeshTestActor.h"
#include "gecchi/actor/_predrawer/DefaultD3DXAniMeshTestActor.h"
#include "gecchi/actor/_predrawer/DefaultBoardTestActor.h"
#include "gecchi/actor/_predrawer/DefaultBoardSetTestActor.h"
#include "gecchi/actor/_predrawer/DefaultMeshTestActor.h"
#include "gecchi/actor/_predrawer/DefaultD3DXMeshTestActor.h"
#include "gecchi/actor/_predrawer/DefaultMeshSetTestActor.h"
#include "gecchi/actor/_predrawer/DefaultMorphMeshTestActor.h"
#include "gecchi/actor/_predrawer/DefaultPointSpriteTestActor.h"
#include "gecchi/actor/_predrawer/DefaultSpriteTestActor.h"
#include "gecchi/actor/_predrawer/DefaultSpriteSetTestActor.h"
#include "gecchi/actor/_predrawer/GroundMeshTestActor.h"
#include "gecchi/actor/_predrawer/HoshiBoshiTestActor.h"
#include "gecchi/actor/_predrawer/LaserChipTestActor.h"
#include "gecchi/actor/_predrawer/SingleLaserTestActor.h"
#include "gecchi/actor/_predrawer/SpriteMeshTestActor.h"
#include "gecchi/actor/_predrawer/SpriteMeshSetTestActor.h"
#include "gecchi/actor/_predrawer/StringBoardTestActor.h"
#include "gecchi/actor/_predrawer/WallAABTestActor.h"
#include "gecchi/actor/_predrawer/WallAAPrismTestActor.h"
























#endif /*MYSTG2NDHEADER_H_*/
