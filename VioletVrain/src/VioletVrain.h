#ifndef SIMPLEVIOLETVRAIN_H_
#define SIMPLEVIOLETVRAIN_H_
#include "VioletVrain.h"

//「Gecchi Game App Freamework ライブラリ」を利用する場合
//次のように"GgafLibCommonHeader.h" をインクルードします。
#include "GgafLibCommonHeader.h"

//その他のヘッダファイルはこの様に記述

#undef P_GOD
#define P_GOD ((VioletVrain::VvGod*)VioletVrain::VvGod::_pGod)

#define VV_MIKATA (0x01U)
#define VV_TEKI   (0x10U)

//前方宣言
namespace VioletVrain {
class VvGod;
class VvSpacetime;
class VvWorld;
class TrialAndErrScene;
class VvCamera;
class VvCameraViewPoint;
class VvCameraUpVector;
class VvCameraWorker;
class VvMouseCamWorker;
class Zako;
class Zakoko;
class FormationZako;
class FormationZako001;
class VvUtil;

class BoardTest;
class PointSpriteTest;
}

#endif /*SIMPLEVIOLETVRAIN_H_*/
