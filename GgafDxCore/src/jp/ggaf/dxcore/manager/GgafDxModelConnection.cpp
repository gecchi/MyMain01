#include "jp/ggaf/dxcore/manager/GgafDxModelConnection.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxModelConnection::GgafDxModelConnection(char* prm_idstr, GgafDxModel* prm_pModel) :
    GgafResourceConnection<GgafDxModel> (prm_idstr, prm_pModel) {
}

void GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) {
    _TRACE_("GgafDxModel="<<prm_pResource->getName()<<" ���J�����܂��B");
    prm_pResource->release(); //�e���f���N���X����release()���s�B�d�v
    GGAF_DELETE(prm_pResource);
}

