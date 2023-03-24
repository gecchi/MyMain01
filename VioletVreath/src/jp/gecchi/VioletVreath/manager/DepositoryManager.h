#ifndef DEPOSITORYMANAGER_H_
#define DEPOSITORYMANAGER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"

namespace VioletVreath {

/**
 * Depository �Ǘ��N���X .
 * �����ς� Depository �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class DepositoryManager : public GgafCore::ResourceManager<GgafCore::ActorDepository> {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    DepositoryManager(const char* prm_manager_name);

    GgafCore::ActorDepository* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<GgafCore::ActorDepository>* processCreateConnection(const char* prm_idstr, GgafCore::ActorDepository* prm_pResource) override;

    virtual ~DepositoryManager() {
    }
};

}
#endif /*DEPOSITORYMANAGER_H_*/
