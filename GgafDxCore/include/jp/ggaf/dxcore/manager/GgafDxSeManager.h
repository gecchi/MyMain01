#ifndef GGAFDXCORE_GGAFDXSEMANAGER_H_
#define GGAFDXCORE_GGAFDXSEMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/sound/GgafDxSe.h"

namespace GgafDxCore {

/**
 * GgafDxSe �Ǘ��N���X .
 * �����ς� GgafDxSe �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxSeManager : public GgafCore::GgafResourceManager<GgafDxSe> {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    GgafDxSeManager(const char* prm_manager_name);

    GgafCore::GgafResourceConnection<GgafDxSe>* processCreateConnection(const char* prm_idstr, GgafDxSe* prm_pResource) override;

    GgafDxSe* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    void updateVolume();

    virtual ~GgafDxSeManager() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXSEMANAGER_H_*/
