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
//1/√2
#define NANAME 0.70710

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
AVAILABLE_EVENT(PREPARE_NEXT_STAGE)
AVAILABLE_EVENT(JUST_GAME_OVER)
AVAILABLE_EVENT(STG01_01_WAS_BROKEN)
AVAILABLE_EVENT(STG01_02_WAS_BROKEN)
AVAILABLE_EVENT(STG01_03_WAS_BROKEN)
AVAILABLE_EVENT(STG01_CLIMAX_WAS_BROKEN)
AVAILABLE_EVENT(STAGE01CONTROLLER_WAS_END)
AVAILABLE_EVENT(STG02_01_WAS_BROKEN)
AVAILABLE_EVENT(STG02_02_WAS_BROKEN)
AVAILABLE_EVENT(STG02_03_WAS_BROKEN)
AVAILABLE_EVENT(STG02_CLIMAX_WAS_BROKEN)
AVAILABLE_EVENT(STAGE02CONTROLLER_WAS_END)
namespace MyStg2nd {

//その他のヘッダファイルはここに記述

class God;
class World;

class CommonScene;

class BackGround01;
class BackGroundChipBoard;




class PreDrawScene;
class GameScene;
class MyShipScene;
class GameDemoScene;
class GameBeginningScene;
class GameMainScene;
class GameEndingScene;
class GameOverScene;
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

class GroundBoxScene;
class WalledScene;
class GroundBoxActor;

class Stage02Controller;
class Stage02_01;
class Stage02_Climax;






class Camera;
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
class EnemyCurveLaserChip001;
class EnemyStraightLaserChip001;

class VamSysCamWorker;
class PauseCamWorker;
class MyCurveLaserChip001;
class MyStraightLaserChip001;
class MyShip;
class MyOptionController;
class MyOptionControllerGizmo;
class MyOptionControllerDirectionVector;
class MyOption;
class MyOptionLockonController;
class MyOptionTorpedoController;
class MyTorpedoTail;
class MyTorpedo;
class MyTorpedoBlast;
class MyShot001;
class MyWave001;
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

class EnemyJuno;
class FormationJuno;
class FormationJuno001;

class EnemyMetis;
class FormationMetis001;

class EnemyAstraea;
class EnemyAstraeaLaserChip001;
class EnemyAstraeaLaserChip002;

class EnemyIris;
class FormationIris001;
class FormationIris002;

class EnemyVesta;

class EnemyCirce;

class EnemyThalia;
class FormationThalia;


class DispatcherConnection;
class DispatcherManager;
class Spline3DConnection;
class Spline3DManager;
class CameraWorkerManager;
class CameraWorkerConnection;


class TestDispatcher;

class Magic;
class DefaultMagic;
class OptionMagic;
class Properties;
class MyStgUtil;
class MyFactory;

template<class T>
class Formation001;


class LaserChipEffectActor;

}

#include "gecchi/God.h"
#include "gecchi/actor/common/CameraWorker.h"
#include "gecchi/scene/Universe.h"
#include "gecchi/scene/Universe/World.h"
#include "gecchi/scene/Universe/World/PreDrawScene.h"
#include "gecchi/scene/Universe/World/GameScene.h"

#include "gecchi/scene/Universe/World/GameScene/MyShipScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameDemoScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameBeginningScene.h"
#include "gecchi/scene/Universe/World/GameScene/CommonScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameEndingScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameOverScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage02Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage03Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage04Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage05Scene.h"
#include "gecchi/scene/Universe/World/GameScene/TamagoScene.h"

#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene/Stage01Controller.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene/part/Stage01_01.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene/part/Stage01_02.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene/part/Stage01_03.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene/part/Stage01_Climax.h"

#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage02Scene/Stage02Controller.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage02Scene/part/Stage02_01.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage02Scene/part/Stage02_Climax.h"

#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene/part/WalledScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene/part/GroundBoxScene.h"

#include "gecchi/actor/Camera.h"
#include "gecchi/actor/camera_worker/TestCamWorker.h"


#include "gecchi/actor/common/DefaultCamWorker.h"
#include "gecchi/actor/common/mesh/GroundMeshActor.h"
#include "gecchi/actor/common/shot/Shot001.h"
#include "gecchi/actor/common/shot/Shot002.h"
#include "gecchi/actor/common/shot/Shot003.h"
#include "gecchi/actor/common/shot/Shot004.h"
#include "gecchi/actor/common/laserchip/EnemyCurveLaserChip001.h"
#include "gecchi/actor/common/laserchip/EnemyStraightLaserChip001.h"

#include "gecchi/actor/my/VamSysCamWorker.h"
#include "gecchi/actor/my/PauseCamWorker.h"
#include "gecchi/actor/my/MyShip.h"
#include "gecchi/actor/my/MyOptionController.h"
#include "gecchi/actor/my/MyOptionControllerGizmo.h"
#include "gecchi/actor/my/MyOptionControllerDirectionVector.h"

#include "gecchi/actor/my/MyShot001.h"
#include "gecchi/actor/my/MyWave001.h"

#include "gecchi/actor/my/MyStraightLaserChip001.h"
#include "gecchi/actor/effect/EffectExplosion001.h"
#include "gecchi/actor/effect/EffectExplosion002.h"
#include "gecchi/actor/effect/EffectExplosion003.h"
#include "gecchi/actor/effect/EffectTurbo001.h"
#include "gecchi/actor/effect/EffectTurbo002.h"
#include "gecchi/actor/effect/EffectCondensation001.h"
#include "gecchi/actor/effect/EffectLaserRefraction001.h"

#include "gecchi/actor/my/option/MyOption.h"
#include "gecchi/actor/my/option/MyOptionLockonController.h"
#include "gecchi/actor/my/option/MyOptionTorpedoController.h"
#include "gecchi/actor/my/option/MyTorpedo.h"
#include "gecchi/actor/my/option/MyTorpedoTail.h"
#include "gecchi/actor/my/option/MyTorpedoBlast.h"
#include "gecchi/actor/my/option/MyCurveLaserChip001.h"
#include "gecchi/actor/my/option/EffectLockon001.h"
#include "gecchi/actor/my/option/EffectLockon001_Main.h"
#include "gecchi/actor/my/option/EffectLockon001_Sub.h"

#include "gecchi/actor/enemy/Tamago/TamagoActor.h"
#include "gecchi/actor/enemy/Tamago/EnemyTamago01.h"
#include "gecchi/actor/background/BackGround01.h"
#include "gecchi/actor/background/board/BackGroundChipBoard.h"
#include "gecchi/actor/background/board/TurboMeter.h"
#include "gecchi/actor/background/HoshiBoshi001.h"
#include "gecchi/actor/background/HoshiBoshi002.h"

#include "gecchi/actor/label/LabelGecchi8Font.h"
#include "gecchi/actor/label/LabelGecchi16Font.h"

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
#include "gecchi/actor/enemy/Juno/EnemyJuno.h"
#include "gecchi/actor/enemy/Juno/FormationJuno.h"
#include "gecchi/actor/enemy/Juno/FormationJuno001.h"
#include "gecchi/actor/enemy/Metis/EnemyMetis.h"
#include "gecchi/actor/enemy/Metis/FormationMetis001.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraea.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip001.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip002.h"
#include "gecchi/actor/enemy/Iris/EnemyIris.h"
#include "gecchi/actor/enemy/Iris/FormationIris001.h"
#include "gecchi/actor/enemy/Iris/FormationIris002.h"
#include "gecchi/actor/enemy/Vesta/EnemyVesta.h"
#include "gecchi/actor/enemy/Circe/EnemyCirce.h"
#include "gecchi/actor/enemy/Thalia/EnemyThalia.h"
#include "gecchi/actor/enemy/Thalia/FormationThalia.h"

#include "gecchi/actor/chikei/Torus/Torus.h"
#include "gecchi/actor/chikei/Torus/VarietyTorus001.h"
#include "gecchi/actor/chikei/Torus/VarietyTorus002.h"
#include "gecchi/actor/chikei/Torus/VarietyTorus003.h"
#include "gecchi/actor/chikei/Torus/VarietyTorus004.h"

#include "gecchi/magic/Magic.h"
#include "gecchi/magic/DefaultMagic.h"
#include "gecchi/magic/OptionMagic.h"
#include "gecchi/Properties.h"
#include "gecchi/util/MyStgUtil.h"
#include "gecchi/MyFactory.h"
#include "gecchi/manager/DispatcherManager.h"
#include "gecchi/manager/DispatcherConnection.h"
#include "gecchi/manager/Spline3DManager.h"
#include "gecchi/manager/Spline3DConnection.h"
#include "gecchi/manager/CameraWorkerManager.h"
#include "gecchi/manager/CameraWorkerConnection.h"
#include "gecchi/actor/common/template/Formation001.hpp"

#include "gecchi/actor/_predrawer/LaserChipEffectActor.h"

#include "gecchi/actor/common/TestDispatcher.h"

#endif /*MYSTG2NDHEADER_H_*/
