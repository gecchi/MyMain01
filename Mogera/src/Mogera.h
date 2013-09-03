#ifndef SIMPLEMOGERA_H_
#define SIMPLEMOGERA_H_

//「Gecchi Game App Freamework ライブラリ」を利用する場合
//次のように"GgafLibCommonHeader.h" をインクルードします。
#include "GgafLibCommonHeader.h"

//その他のヘッダファイルはこの様に記述

#undef P_GOD
#define P_GOD ((Mogera::MgrGod*)Mogera::MgrGod::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((Mogera::MgrUniverse*)(P_GOD->_pUniverse))

//前方宣言
namespace Mogera {
class MgrGod;
class MgrUniverse;
class MgrWorld;
class MgrCamera;
class MgrActor;
class TestActor;
class Teki001;
class Mikata001;
class MgrUtil;

}

#endif /*SIMPLEMOGERA_H_*/
