#ifndef SIMPLEVIOLETVRAIN_H_
#define SIMPLEVIOLETVRAIN_H_
#include "VioletVrain.h"

//�uGecchi Game App Freamework ���C�u�����v�𗘗p����ꍇ
//���̂悤��"GgafLibCommonHeader.h" ���C���N���[�h���܂��B
#include "GgafLibCommonHeader.h"

//���̑��̃w�b�_�t�@�C���͂��̗l�ɋL�q

#undef P_GOD
#define P_GOD ((VioletVrain::VvGod*)VioletVrain::VvGod::_pGod)

#define VV_MIKATA (0x01U)
#define VV_TEKI   (0x10U)

//�O���錾
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
