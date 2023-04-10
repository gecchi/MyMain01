#include "jp/ggaf/dx/manager/BgmConnection.h"


using namespace GgafDx;

BgmConnection::BgmConnection(const char* prm_idstr, Bgm* prm_pBgm) :
    GgafCore::ResourceConnection<Bgm>(prm_idstr, prm_pBgm) {
}

void BgmConnection::processReleaseResource(Bgm* prm_pResource) {
    _TRACE_("Bgm="<<prm_pResource->_ogg_file_name<<" ‚ðŠJ•ú‚µ‚Ü‚·B");
    GGAF_DELETE(prm_pResource);
}

