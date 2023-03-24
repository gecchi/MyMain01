#ifndef SIMPLEHOGERA_H_
#define SIMPLEHOGERA_H_
#include "Hogera.h"

//�uGecchi Game App Freamework ���C�u�����v�𗘗p����ꍇ
//���̂悤��"GgafLib::LibCommonHeader.h" ���C���N���[�h���܂��B
#include "jp/ggaf/GgafLibCommonHeader.h"

//���̑��̃w�b�_�t�@�C���͂��̗l�ɋL�q

#undef pCARETAKER
#define pCARETAKER ((Hogera::HgrCaretaker*)Hogera::HgrCaretaker::_pCaretaker)

#define HGR_MIKATA (0x01U)
#define HGR_TEKI   (0x10U)

//�O���錾
namespace Hogera {
class HgrCaretaker;
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
