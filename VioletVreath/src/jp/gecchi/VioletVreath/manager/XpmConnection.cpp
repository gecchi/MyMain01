#include "XpmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

XpmConnection::XpmConnection(char* prm_idstr, GgafCore::GgafXpm* prm_pResource) :
    GgafResourceConnection<GgafCore::GgafXpm> (prm_idstr, prm_pResource) {
}

void XpmConnection::processReleaseResource(GgafCore::GgafXpm* prm_pResource) {
    _DTRACE_("XpmConnection::processReleaseResource‚ÅŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    GGAF_DELETE(prm_pResource);
}
