#ifndef SIMPLEMOGERA_H_
#define SIMPLEMOGERA_H_
#include "Mogera.h"

//「Gecchi Game App Freamework ライブラリ」を利用する場合
//次のように"GgafLib::LibCommonHeader.h" をインクルードします。
#include "GgafLibCommonHeader.h"

//その他のヘッダファイルはこの様に記述

#undef pCARETAKER
#define pCARETAKER ((Mogera::MgrCaretaker*)Mogera::MgrCaretaker::_pCaretaker)

#define MGR_MIKATA (0x01U)
#define MGR_TEKI   (0x10U)

//前方宣言
namespace Mogera {
class MgrCaretaker;
class MgrSpacetime;
class MgrWorld;
class TrialAndErrScene;
class ParallelCurveTestScene;
class TestScene;

class MgrCamera;
class MgrCameraViewPoint;
class MgrCameraUpVector;
class MgrCameraWorker;
class MgrMouseCamWorker;
class Zako;
class Zakoko;
class FormationZako;
class FormationZako001;
class MgrUtil;
class SmpActor1;
class SmpActor2;
class SmpSprite;
class BoardTest;
class BoardTest2;
class PointSpriteTest;
class EffectExplosion004;
class SmpPieGraphSprite;
class SeActor3;
class EnemyIda;
class EnemyIdaBase;
class Box;
class AniTest;
class AniTest2;
class SkinMeshAnimeTestScene;
class PointerTest;
class ItemBoardTest;
class LabelMenuItemFont01;
}

#endif /*SIMPLEMOGERA_H_*/
