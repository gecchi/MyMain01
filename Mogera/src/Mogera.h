#ifndef SIMPLEMOGERA_H_
#define SIMPLEMOGERA_H_

//�uGecchi Game App Freamework ���C�u�����v�𗘗p����ꍇ
//���̂悤��"GgafLibCommonHeader.h" ���C���N���[�h���܂��B
#include "GgafLibCommonHeader.h"

//���̑��̃w�b�_�t�@�C���͂��̗l�ɋL�q

#undef P_GOD
#define P_GOD ((Mogera::MgrGod*)Mogera::MgrGod::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((Mogera::MgrUniverse*)(P_GOD->_pUniverse))

namespace Mogera {
class MgrGod;
class MgrUniverse;
class MgrWorld;
class MgrCamera;
class MgrActor;
}

#include "MgrGod.h"
#include "scene/MgrUniverse.h"
#include "scene/MgrUniverse/MgrWorld.h"
#include "actor/MgrCamera.h"
#include "actor/MgrActor.h"

#endif /*SIMPLEMOGERA_H_*/
