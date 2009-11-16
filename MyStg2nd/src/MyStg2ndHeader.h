#ifndef MYSTG2NDHEADER_H_
#define MYSTG2NDHEADER_H_

//「俺DirectX9ライブラリ」を利用する場合（自分だけだけど；）
//次の"GgafDx9LibStgHeader.h"ヘッダをインクルードします。
#include "GgafDx9LibStgHeader.h"

#define KIND_EFFECT            (0x0)
#define KIND_MY_BODY           (0x1)
#define KIND_MY_SHOT_GU        (0x2)
#define KIND_MY_SHOT_CHOKI     (0x4)
#define KIND_MY_SHOT_PA        (0x8)
#define KIND_MY_SHOT_NOMAL     (0x10)
#define KIND_ENEMY_BODY        (0x20)
#define KIND_ENEMY_SHOT_GU     (0x40)
#define KIND_ENEMY_SHOT_CHOKI  (0x80)
#define KIND_ENEMY_SHOT_PA     (0x100)
#define KIND_ENEMY_SHOT_NOMAL  (0x200)
#define KIND_OTHER             (0x400)
#define KIND_CHIKEI            (0x800)

#define KIND_MY                (KIND_MY_BODY|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA|KIND_MY_SHOT_NOMAL)
#define KIND_ENEMY             (KIND_ENEMY_BODY|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_ENEMY_SHOT_NOMAL)

#define VB_SHOT1    VB_BUTTON1
#define VB_SHOT2    VB_BUTTON2
#define VB_OPTION   VB_BUTTON3
#define VB_ZMOVE    VB_BUTTON4
#define VB_TURBO    VB_BUTTON5
#define VB_SHOT1_R  VB_BUTTON6

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
class BackGroundStar;
class BackGroundStar001;

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



class LaserChip;
class CurveLaserChip;
class HomingLaserChip;
class StraightLaserChip;
class LaserChipDispatcher;
class MyCurveLaserChip001;
class MyStraightLaserChip001;
class Stage01MainScene;
class MyShip;
class MyOptionParent;
class MyDummyOption;
class MyShot001;
class MyWave001;
class EffectExplosion001;
class TamagoActor;
class MyUtil;
class GameGlobal;

class DefaultSpriteMyActor;
class DefaultMeshEnemyActor;
class DefaultSpriteEnemyActor;
class DefaultSpriteEffectActor;

class EnemyMeshShot001;
class EnemyLaserChip001;

class EnemyCeres;
class EnemyCeresShot001;
class FormationCeres001;
class FormationCeres002;

class EnemyPallas;

class EnemyJuno;
class FormationJuno001;

class EnemyVesta;
class FormationVesta001;

class EnemyAstraea;
class EnemyAstraeaLaserChip001;






class Magic;
class DefaultMagic;
class OptionMagic;
class Properties;
class MyFactory;




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

#include "gecchi/actor/my/sprite/DefaultSpriteMyActor.h"
#include "gecchi/actor/enemy/mesh/DefaultMeshEnemyActor.h"
#include "gecchi/actor/enemy/sprite/DefaultSpriteEnemyActor.h"
#include "gecchi/actor/effect/sprite/DefaultSpriteEffectActor.h"

#include "gecchi/actor/common/mesh/LaserChip.h"
#include "gecchi/actor/common/mesh/CurveLaserChip.h"
#include "gecchi/actor/common/mesh/HomingLaserChip.h"
#include "gecchi/actor/common/mesh/StraightLaserChip.h"
#include "gecchi/actor/common/mesh/LaserChipDispatcher.h"
#include "gecchi/actor/my/mesh/MyShip.h"
#include "gecchi/actor/my/mesh/MyOptionParent.h"
#include "gecchi/actor/my/mesh/MyDummyOption.h"
#include "gecchi/actor/my/sprite/MyShot001.h"
#include "gecchi/actor/my/mesh/MyWave001.h"
#include "gecchi/actor/my/mesh/MyCurveLaserChip001.h"
#include "gecchi/actor/my/mesh/MyStraightLaserChip001.h"
#include "gecchi/actor/effect/sprite/EffectExplosion001.h"
#include "gecchi/actor/enemy/Tamago/TamagoActor.h"
#include "gecchi/actor/enemy/sprite/EnemyShotSpriteActor.h"
#include "gecchi/actor/enemy/sprite/EnemyShot001.h"
#include "gecchi/actor/_debug/DispFpsActor.h"
#include "gecchi/actor/background/BackGround01.h"
#include "gecchi/actor/background/board/BackGroundChipBoard.h"
#include "gecchi/actor/background/BackGroundStar.h"
#include "gecchi/actor/background/mesh/BackGroundStar001.h"

#include "gecchi/GameGlobal.h"

#include "gecchi/actor/enemy/Ceres/EnemyCeres.h"
#include "gecchi/actor/enemy/Ceres/EnemyCeresShot001.h"
#include "gecchi/actor/enemy/Ceres/FormationCeres001.h"
#include "gecchi/actor/enemy/Ceres/FormationCeres002.h"
#include "gecchi/actor/enemy/Pallas/EnemyPallas.h"
#include "gecchi/actor/enemy/Juno/EnemyJuno.h"
#include "gecchi/actor/enemy/Juno/FormationJuno001.h"
#include "gecchi/actor/enemy/Vesta/EnemyVesta.h"
#include "gecchi/actor/enemy/Vesta/FormationVesta001.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraea.h"
#include "gecchi/actor/enemy/Astraea/EnemyAstraeaLaserChip001.h"
#include "gecchi/actor/enemy/mesh/EnemyMeshShot001.h"
#include "gecchi/actor/enemy/mesh/EnemyLaserChip001.h"




#include "gecchi/magic/Magic.h"
#include "gecchi/magic/DefaultMagic.h"
#include "gecchi/magic/OptionMagic.h"
#include "gecchi/util/Properties.h"
#include "gecchi/MyFactory.h"




#endif /*MYSTG2NDHEADER_H_*/
