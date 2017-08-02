#ifndef SIMPLEHOGERA_H_
#define SIMPLEHOGERA_H_
#include "Hogera.h"

//「Gecchi Game App Freamework ライブラリ」を利用する場合
//次のように"GgafLibCommonHeader.h" をインクルードします。
#include "GgafLibCommonHeader.h"

//その他のヘッダファイルはこの様に記述

#undef P_GOD
#define P_GOD ((Hogera::HgrGod*)Hogera::HgrGod::_pGod)

#define HGR_MIKATA (0x01U)
#define HGR_TEKI   (0x10U)

//前方宣言
namespace Hogera {
class HgrGod;
class HgrSpacetime;
class HgrWorld;
class TrialAndErrScene;
class HgrCamera;
class HgrCameraViewPoint;
class HgrCameraUpVector;
class HgrCameraWorker;
class HgrMouseCamWorker;
class Zako;
class Zakoko;
class FormationZako;
class FormationZako001;
class HgrUtil;

class BoardTest;
class PointSpriteTest;
}

#endif /*SIMPLEHOGERA_H_*/
