#ifndef SIMPLESAMPLEHEADER_H_
#define SIMPLESAMPLEHEADER_H_

//「Gecchi Game App Freamework ライブラリ」を利用する場合
//次のように"GgafLibHeader.h" をインクルードします。
#include "GgafLibHeader.h"

//その他のヘッダファイルはこの様に記述
namespace SimpleSample {
class God;
class Universe;
class World;
class Camera;
class TestActor;
}

#include "God.h"
#include "scene/Universe.h"
#include "scene/Universe/World.h"
#include "actor/Camera.h"
#include "actor/TestActor.h"

#endif /*SIMPLESAMPLEHEADER_H_*/
