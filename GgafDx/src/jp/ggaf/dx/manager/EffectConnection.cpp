#include "jp/ggaf/dx/manager/EffectConnection.h"


using namespace GgafDx;


EffectConnection::EffectConnection(const char* prm_idstr, Effect* prm_pEffect)
    :GgafCore::ResourceConnection<Effect>(prm_idstr, prm_pEffect) {
}

void EffectConnection::processReleaseResource(Effect* prm_pResource) {
    _TRACE_("Effect="<<prm_pResource->getName()<<" を開放します。");
    GGAF_DELETE(prm_pResource);
}

