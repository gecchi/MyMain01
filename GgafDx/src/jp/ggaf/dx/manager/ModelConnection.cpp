#include "jp/ggaf/dx/manager/ModelConnection.h"

#include "jp/ggaf/dx/model/Model.h"


using namespace GgafDx;

ModelConnection::ModelConnection(const char* prm_idstr, Model* prm_pModel) :
    GgafCore::ResourceConnection<Model> (prm_idstr, prm_pModel) {
}

void ModelConnection::processReleaseResource(Model* prm_pResource) {
    _TRACE_("Model="<<prm_pResource->getName()<<" ���J�����܂��B");
    prm_pResource->release(); //�e���f���N���X����release()���s�B�d�v
    GGAF_DELETE(prm_pResource);
}

