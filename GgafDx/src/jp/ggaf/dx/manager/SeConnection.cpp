#include "jp/ggaf/dx/manager/SeConnection.h"


using namespace GgafDx;

SeConnection::SeConnection(const char* prm_idstr, Se* prm_pSe) :
    GgafCore::ResourceConnection<Se> (prm_idstr, prm_pSe) {
}

void SeConnection::processReleaseResource(Se* prm_pResource) {
    _TRACE_("Se="<<prm_pResource->_wave_file_name<<" ‚ðŠJ•ú‚µ‚Ü‚·B");
    GGAF_DELETE(prm_pResource);
}

