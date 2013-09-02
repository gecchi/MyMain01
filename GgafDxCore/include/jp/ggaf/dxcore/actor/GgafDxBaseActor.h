#ifndef GGAFDXCORE_GGAFDXBASEACTOR_H_
#define GGAFDXCORE_GGAFDXBASEACTOR_H_
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace GgafDxCore {

/**
 * GgafDxCore名前空間の基底アクタークラス.
 * GgafMainActorを継承しただけです。<BR>
 * GgafDxCore名前空間内では、このクラスを基底アクターとします。<BR>
 * @version 1.00
 * @since 2009/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxBaseActor : public GgafCore::GgafMainActor {

public:

    GgafDxBaseActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat);

    virtual ~GgafDxBaseActor(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXBASEACTOR_H_*/
