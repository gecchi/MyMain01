#ifndef MYSTG2NDHEADER_H_
#define MYSTG2NDHEADER_H_

//「俺DirectX9ライブラリ」を利用する場合（自分だけだけど；）
//次の"GgafDx9LibStgHeader.h"ヘッダをインクルードします。

#include "GgafDx9LibStgHeader.h"


//#define KIND_EFFECT            (0x0)
//#define KIND_MY_BODY           (0x1)
//#define KIND_MY_SHOT_GU        (0x2)
//#define KIND_MY_SHOT_CHOKI     (0x4)
//#define KIND_MY_SHOT_PA        (0x8)
//#define KIND_MY_SHOT_NOMAL     (0x10)
//#define KIND_ENEMY_BODY        (0x20)
//#define KIND_ENEMY_SHOT_GU     (0x40)
//#define KIND_ENEMY_SHOT_CHOKI  (0x80)
//#define KIND_ENEMY_SHOT_PA     (0x100)
//#define KIND_ENEMY_SHOT_NOMAL  (0x200)
//#define KIND_OTHER             (0x400)
//#define KIND_CHIKEI            (0x800)
//
//#define KIND_MY                (KIND_MY_BODY|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA|KIND_MY_SHOT_NOMAL)
//#define KIND_ENEMY             (KIND_ENEMY_BODY|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_ENEMY_SHOT_NOMAL)



#define KIND_EFFECT              (0x0)     //00000000000000000000000000000000
#define KIND_MY_SHOT_NOMAL       (0x4)     //00000000000000000000000000000100
#define KIND_MY_SHOT_GU          (0x9)     //00000000000000000000000000001001
#define KIND_MY_SHOT_CHOKI       (0x12)    //00000000000000000000000000010010
#define KIND_MY_SHOT_PA          (0x23)    //00000000000000000000000000100011
#define KIND_ENEMY_SHOT_NOMAL    (0x40)    //00000000000000000000000001000000
#define KIND_ENEMY_SHOT_GU       (0x81)    //00000000000000000000000010000001
#define KIND_ENEMY_SHOT_CHOKI    (0x102)   //00000000000000000000000100000010
#define KIND_ENEMY_SHOT_PA       (0x203)   //00000000000000000000001000000011
#define KIND_MY_BODY_NOMAL       (0x400)   //00000000000000000000010000000000
#define KIND_MY_BODY_GU          (0x801)   //00000000000000000000100000000001
#define KIND_MY_BODY_CHOKI       (0x1002)  //00000000000000000001000000000010
#define KIND_MY_BODY_PA          (0x2003)  //00000000000000000010000000000011
#define KIND_ENEMY_BODY_NOMAL    (0x4000)  //00000000000000000100000000000000
#define KIND_ENEMY_BODY_GU       (0x8001)  //00000000000000001000000000000001
#define KIND_ENEMY_BODY_CHOKI    (0x10002) //00000000000000010000000000000010
#define KIND_ENEMY_BODY_PA       (0x20003) //00000000000000100000000000000011
#define KIND_OTHER               (0x40000) //00000000000001000000000000000000
#define KIND_CHIKEI              (0x80000) //00000000000010000000000000000000

#define KIND_MY     (KIND_MY_SHOT_NOMAL|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA|KIND_MY_BODY_NOMAL|KIND_MY_BODY_GU|KIND_MY_BODY_CHOKI|KIND_MY_BODY_PA)
#define KIND_ENEMY  (KIND_ENEMY_SHOT_NOMAL|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_ENEMY_BODY_NOMAL|KIND_ENEMY_BODY_GU|KIND_ENEMY_BODY_CHOKI|KIND_ENEMY_BODY_PA)
#define KIND_MY_SHOT     (KIND_MY_SHOT_NOMAL|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA)
#define KIND_MY_BODY     (KIND_MY_BODY_NOMAL|KIND_MY_BODY_GU|KIND_MY_BODY_CHOKI|KIND_MY_BODY_PA)
#define KIND_ENEMY_SHOT  (KIND_ENEMY_SHOT_NOMAL|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA)
#define KIND_ENEMY_BODY  (KIND_ENEMY_BODY_NOMAL|KIND_ENEMY_BODY_GU|KIND_ENEMY_BODY_CHOKI|KIND_ENEMY_BODY_PA)
#define KIND_NOMAL       (0x0)    //00
#define KIND_GU          (0x1)    //01
#define KIND_CHOKI       (0x2)    //10
#define KIND_PA          (0x3)    //11







#define VB_SHOT1    VB_BUTTON1
#define VB_SHOT2    VB_BUTTON2
#define VB_OPTION   VB_BUTTON3
#define VB_ZMOVE    VB_BUTTON4
#define VB_TURBO    VB_BUTTON5
#define VB_SHOT1_R  VB_BUTTON6

//STAT_DEFAULT_ACTOR_KINDは0
#define STAT_AddScorePoint          1
#define STAT_AddRankPoint           2
#define STAT_AddRankPoint_Reduction 3
#define STAT_Stamina                4
#define STAT_Attack                 5
#define STAT_DefaultDefenceRate     6
#define STAT_DominantDefenceRate    7
#define STAT_RecessiveDefenceRate   8

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

namespace MyStg2nd {

//その他のヘッダファイルはここに記述
template<class P>
class GameActor;

class God;
class World;

class CommonScene;

class DispFpsActor;
class BackGround01;
class BackGroundChipBoard;

class GameScene;
class GameDemoScene;
class GameBeginningScene;
class GameMainScene;
class GameEndingScene;
class StageScene;
class Stage01Scene;
class Stage02Scene;
class Stage03Scene;
class Stage04Scene;
class Stage05Scene;
class TamagoScene;

class GroundMeshActor;
class LaserChip;
class CurveLaserChip;
class HomingLaserChip;
class StraightLaserChip;
class RefractionLaserChip;
class LaserChipDispatcher;
class LaserChipDispatcherDispatcher;
class Shot001;
class Shot002;
class MyCurveLaserChip001;
class MyStraightLaserChip001;
class Stage01MainScene;
class MyShip;
class MyOptionParent;
class MyOptionParentGizmo;
class MyOptionParentDirectionVector;
class MyOption;
class MyShot001;
class MyWave001;
class EffectExplosion001;
class EffectExplosion002;
class EffectLockOn001;
class EffectLockOn001_Release;
class EffectTurbo001;
class EffectTurbo002;
class EffectCondensation001;
class HoshiBoshi001;
class HoshiBoshi002;
class TurboMeter;

class TamagoActor;
class EnemyTamago01Actor;
class MyUtil;
class GameGlobal;

class DefaultSpriteMyActor;
class DefaultSpriteEnemyActor;

class EnemyMeshShot001;
class EnemyLaserChip001;

class EnemyCeres;
class EnemyCeresShot001;
class FormationCeres001;
class FormationCeres002;

class EnemyPallas;

class EnemyJuno;
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

class DispatcherManager;
class DispatcherConnection;

class TestDispatcher;

class Magic;
class DefaultMagic;
class OptionMagic;
class Properties;
class MyStgUtil;
class MyFactory;

template<class T>
class Formation001;


}
#include "gecchi/actor/GameActor.h"

#include "gecchi/God.h"
#include "gecchi/scene/Universe.h"
#include "gecchi/scene/Universe/World.h"

#include "gecchi/scene/Universe/World/GameScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameDemoScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameBeginningScene.h"
#include "gecchi/scene/Universe/World/GameScene/CommonScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameEndingScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/StageScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage01Scene/Stage01MainScene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage02Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage03Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage04Scene.h"
#include "gecchi/scene/Universe/World/GameScene/GameMainScene/Stage05Scene.h"
#include "gecchi/scene/Universe/World/GameScene/TamagoScene.h"

#include "gecchi/actor/my/sprite/DefaultSpriteMyActor.h"
#include "gecchi/actor/enemy/sprite/DefaultSpriteEnemyActor.h"
#include "gecchi/actor/common/mesh/GroundMeshActor.h"
#include "gecchi/actor/common/laserchip/LaserChip.h"
#include "gecchi/actor/common/laserchip/CurveLaserChip.h"
#include "gecchi/actor/common/laserchip/HomingLaserChip.h"
#include "gecchi/actor/common/laserchip/StraightLaserChip.h"
#include "gecchi/actor/common/laserchip/RefractionLaserChip.h"
#include "gecchi/actor/common/laserchip/LaserChipDispatcher.h"
#include "gecchi/actor/common/laserchip/LaserChipDispatcherDispatcher.h"
#include "gecchi/actor/common/shot/Shot001.h"
#include "gecchi/actor/common/shot/Shot002.h"

#include "gecchi/actor/my/mesh/MyShip.h"
#include "gecchi/actor/my/mesh/MyOptionParent.h"
#include "gecchi/actor/my/mesh/MyOptionParentGizmo.h"
#include "gecchi/actor/my/mesh/MyOptionParentDirectionVector.h"
#include "gecchi/actor/my/mesh/MyOption.h"
#include "gecchi/actor/my/sprite/MyShot001.h"
#include "gecchi/actor/my/mesh/MyWave001.h"
#include "gecchi/actor/my/mesh/MyCurveLaserChip001.h"
#include "gecchi/actor/my/mesh/MyStraightLaserChip001.h"
#include "gecchi/actor/effect/EffectExplosion001.h"
#include "gecchi/actor/effect/EffectExplosion002.h"
#include "gecchi/actor/effect/EffectLockOn001.h"
#include "gecchi/actor/effect/EffectLockOn001_Release.h"
#include "gecchi/actor/effect/EffectTurbo001.h"
#include "gecchi/actor/effect/EffectTurbo002.h"
#include "gecchi/actor/effect/EffectCondensation001.h"

#include "gecchi/actor/enemy/Tamago/TamagoActor.h"
#include "gecchi/actor/enemy/Tamago/EnemyTamago01.h"
#include "gecchi/actor/enemy/sprite/EnemyShotSpriteActor.h"
#include "gecchi/actor/enemy/sprite/EnemyShot001.h"
#include "gecchi/actor/_debug/DispFpsActor.h"
#include "gecchi/actor/background/BackGround01.h"
#include "gecchi/actor/background/board/BackGroundChipBoard.h"
#include "gecchi/actor/background/board/TurboMeter.h"
#include "gecchi/actor/background/HoshiBoshi001.h"
#include "gecchi/actor/background/HoshiBoshi002.h"
#include "gecchi/GameGlobal.h"

#include "gecchi/actor/enemy/Ceres/EnemyCeres.h"
#include "gecchi/actor/enemy/Ceres/EnemyCeresShot001.h"
#include "gecchi/actor/enemy/Ceres/FormationCeres001.h"
#include "gecchi/actor/enemy/Ceres/FormationCeres002.h"
#include "gecchi/actor/enemy/Pallas/EnemyPallas.h"
#include "gecchi/actor/enemy/Juno/EnemyJuno.h"
#include "gecchi/actor/enemy/Juno/FormationJuno001.h"
#include "gecchi/actor/enemy/Metis/EnemyMetis.h"
#include "gecchi/actor/enemy/Metis/FormationMetis001.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraea.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip001.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip002.h"
#include "gecchi/actor/enemy/mesh/EnemyMeshShot001.h"
#include "gecchi/actor/enemy/mesh/EnemyLaserChip001.h"
#include "gecchi/actor/enemy/Iris/EnemyIris.h"
#include "gecchi/actor/enemy/Iris/FormationIris001.h"
#include "gecchi/actor/enemy/Iris/FormationIris002.h"
#include "gecchi/actor/enemy/Vesta/EnemyVesta.h"
#include "gecchi/actor/enemy/Circe/EnemyCirce.h"
#include "gecchi/magic/Magic.h"
#include "gecchi/magic/DefaultMagic.h"
#include "gecchi/magic/OptionMagic.h"
#include "gecchi/util/Properties.h"
#include "gecchi/util/MyStgUtil.h"
#include "gecchi/MyFactory.h"
#include "gecchi/manager/DispatcherManager.h"
#include "gecchi/manager/DispatcherConnection.h"
#include "gecchi/actor/common/template/Formation001.hpp"

#include "gecchi/actor/common/TestDispatcher.h"

#endif /*MYSTG2NDHEADER_H_*/
