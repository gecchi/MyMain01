#include "XpmConnection.h"



using namespace GgafLib;
using namespace VioletVreath;

XpmConnection::XpmConnection(const char* prm_idstr, GgafCore::Xpm* prm_pResource) :
    GgafCore::ResourceConnection<GgafCore::Xpm> (prm_idstr, prm_pResource) {
}

void XpmConnection::processReleaseResource(GgafCore::Xpm* prm_pResource) {
    _TRACE_("XpmConnection::processReleaseResource‚ÅŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    GGAF_DELETE(prm_pResource);
}
