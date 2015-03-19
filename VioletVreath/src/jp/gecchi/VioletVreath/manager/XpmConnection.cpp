#include "XpmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

XpmConnection::XpmConnection(const char* prm_idstr, GgafCore::GgafXpm* prm_pResource) :
    GgafResourceConnection<GgafCore::GgafXpm> (prm_idstr, prm_pResource) {
}

void XpmConnection::processReleaseResource(GgafCore::GgafXpm* prm_pResource) {
    _TRACE_("XpmConnection::processReleaseResourceで開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    GGAF_DELETE(prm_pResource);
}
