#ifndef MYSTG2NDHEADER_H_
#define MYSTG2NDHEADER_H_

//「俺DirectX9ライブラリ」を利用する場合（自分だけだけど；）
//次の"GgafDx9LibStgHeader.h"ヘッダをインクルードします。
#include "GgafDx9LibStgHeader.h"

#define KIND_EFFECT            0
#define KIND_MY                1
#define KIND_MY_SHOT_GU        2
#define KIND_MY_SHOT_CHOKI     4
#define KIND_MY_SHOT_PA        8
#define KIND_MY_SHOT_NOMAL     16
#define KIND_ENEMY             32
#define KIND_ENEMY_SHOT_GU     64
#define KIND_ENEMY_SHOT_CHOKI  128
#define KIND_ENEMY_SHOT_PA     256
#define KIND_ENEMY_SHOT_NOMAL  512
#define KIND_OTHER             1024
#define KIND_CHIKEI            2048

//その他のヘッダファイルはここに記述
class God;
class InterfaceGameActor;
class World;
class GameDemoScene;
class MyShipScene;

class DispFpsActor;
class BackGround01Plate;

class GameScene;
class GameMainScene;
class Stage01Scene;
class Stage02Scene;
class Stage03Scene;
class Stage04Scene;
class Stage05Scene;

class Stage01MainScene;
class MyShipActor;
class Shot001Actor;
class Explosion001Actor;
class TamagoActor;
class MyUtil;
class GameGlobal;

class DefaultMeshEnemyActor;
class DefaultSpriteEnemyActor;
class DefaultSpriteEffectActor;
class EnemyCeres;
class EnemyPallas;

class FormationActor;
class RotationActor;
class FormationCeres001;

class MyFactory;

#include "gecchi/God.h"
#include "gecchi/scene/World.h"
#include "gecchi/scene/World/GameScene.h"
#include "gecchi/scene/World/GameScene/GameDemoScene.h"
#include "gecchi/scene/World/GameScene/MyShipScene.h"
#include "gecchi/scene/World/GameScene/GameMainScene.h"
#include "gecchi/scene/World/GameScene/GameMainScene/Stage01Scene.h"
#include "gecchi/scene/World/GameScene/GameMainScene/Stage01Scene/Stage01MainScene.h"
#include "gecchi/scene/World/GameScene/GameMainScene/Stage02Scene.h"
#include "gecchi/scene/World/GameScene/GameMainScene/Stage03Scene.h"
#include "gecchi/scene/World/GameScene/GameMainScene/Stage04Scene.h"
#include "gecchi/scene/World/GameScene/GameMainScene/Stage05Scene.h"

#include "gecchi/actor/enemy/mesh/DefaultMeshEnemyActor.h"
#include "gecchi/actor/enemy/sprite/DefaultSpriteEnemyActor.h"
#include "gecchi/actor/effect/sprite/DefaultSpriteEffectActor.h"

#include "gecchi/actor/my/mesh/MyShipActor.h"
#include "gecchi/actor/my/sprite/Shot001Actor.h"
#include "gecchi/actor/effect/sprite/Explosion001Actor.h"
#include "gecchi/actor/enemy/mesh/TamagoActor.h"
#include "gecchi/actor/enemy/sprite/EnemyShotSpriteActor.h"
#include "gecchi/actor/enemy/sprite/EnemyShot001Actor.h"
#include "gecchi/actor/_debug/DispFpsActor.h"
#include "gecchi/actor/background/plate/BackGround01Plate.h"
#include "gecchi/GameGlobal.h"

#include "gecchi/actor/enemy/mesh/EnemyCeres.h"
#include "gecchi/actor/enemy/mesh/EnemyPallas.h"
#include "gecchi/actor/enemy/mesh/EnemyJuno.h"

#include "gecchi/actor/FormationActor.h"
#include "gecchi/actor/RotationActor.h"

#include "gecchi/actor/enemy/FormationCeres001.h"
#include "gecchi/actor/enemy/FormationJuno001.h"
#include "gecchi/MyFactory.h"


#endif /*MYSTG2NDHEADER_H_*/
