#ifndef SIMPLEHOGERA_H_
#define SIMPLEHOGERA_H_
#include "Hogera.h"

//�uGecchi Game App Freamework ���C�u�����v�𗘗p����ꍇ
//���̂悤��"GgafLibCommonHeader.h" ���C���N���[�h���܂��B
#include "GgafLibCommonHeader.h"

//���̑��̃w�b�_�t�@�C���͂��̗l�ɋL�q

#undef P_GOD
#define P_GOD ((Hogera::HgrGod*)Hogera::HgrGod::_pGod)

#define HGR_MIKATA (0x01U)
#define HGR_TEKI   (0x10U)

//�O���錾
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
