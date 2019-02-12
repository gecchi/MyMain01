#include "XpmConnection.h"



using namespace GgafLib;
using namespace VioletVreath;

XpmConnection::XpmConnection(const char* prm_idstr, GgafCore::Xpm* prm_pResource) :
    GgafCore::ResourceConnection<GgafCore::Xpm> (prm_idstr, prm_pResource) {
}

void XpmConnection::processReleaseResource(GgafCore::Xpm* prm_pResource) {
    _TRACE_("XpmConnection::processReleaseResourceで開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    GGAF_DELETE(prm_pResource);
}
