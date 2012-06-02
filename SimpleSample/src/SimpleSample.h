#ifndef SIMPLESAMPLE_H_
#define SIMPLESAMPLE_H_

//「Gecchi Game App Freamework ライブラリ」を利用する場合
//次のように"GgafLibHeader.h" をインクルードします。
#include "GgafLibHeader.h"

//その他のヘッダファイルはこの様に記述
namespace SimpleSample {
class SmpGod;
class SmpUniverse;
class SmpWorld;
class SmpCamera;
class SmpActor;
class SmpLabel;
}

#include "SmpGod.h"
#include "scene/SmpUniverse.h"
#include "scene/SmpUniverse/SmpWorld.h"
#include "actor/SmpCamera.h"
#include "actor/SmpActor.h"
#include "actor/SmpLabel.h"

#endif /*SIMPLESAMPLE_H_*/
