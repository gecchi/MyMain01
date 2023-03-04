#include "jp/ggaf/lib/manager/DefaultModelManager.h"

#include "jp/ggaf/lib/model/SingleLaserModel.h"
#include "jp/ggaf/dx/model/SkinAniMeshModel.h"

using namespace GgafLib;
using namespace GgafDx;

DefaultModelManager::DefaultModelManager(const char* prm_manager_name) :
        GgafDx::ModelManager(prm_manager_name) {
}


GgafDx::Model* DefaultModelManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1); //�ŏ��̃X���b�V���ŕ���
    if (names.size() != 2) {
        throwCriticalException("�����́A��Ɏ��̌`���ŗ^���Ă��������B�w���f���^�C�v1����  + \",\" + ���f����`���x\n"
                "���ۂ̈����́Aprm_idstr="<<prm_idstr);
    }
    char model_type = (names[0])[0];
    const char* model_id = names[1].c_str();
    Model* pResourceModel;
    switch (model_type) {
        case TYPE_SINGLELASER_MODEL: {
            SingleLaserModel* pModel_new = NEW SingleLaserModel(model_id);
            pModel_new->_model_type = TYPE_SINGLELASER_MODEL;
            pModel_new->restore();
            pResourceModel = (Model*)pModel_new;
            break;
        }
        default:
            pResourceModel = GgafDx::ModelManager::processCreateResource(prm_idstr, prm_pConnector);
            break;

    }
    return pResourceModel;
}


