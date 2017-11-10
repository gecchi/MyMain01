#ifndef GGAFDXCORE_GGAFDXBGMMANAGER_H_
#define GGAFDXCORE_GGAFDXBGMMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"

namespace GgafDxCore {

/**
 * GgafDxBgm �Ǘ��N���X .
 * �����ς� GgafDxBgm �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxBgmManager : public GgafCore::GgafResourceManager<GgafDxBgm> {

    /** [r]BGM�E�}�X�^�[�{�����[���̊��� 0.0�`1.0 */
    double _bgm_master_volume_rate;

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDxBgmManager(const char* prm_manager_name);

    GgafDxBgm* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<GgafDxBgm>* processCreateConnection(const char* prm_idstr, GgafDxBgm* prm_pResource) override;

    void setBgmMasterVolumeRate(double prm_volume_rate);

    float getBgmMasterVolumeRate();


    /**
     * ���݉��t���̑S�Ă�BGM�{�����[�����X�V .
     */
    void updateVolume();

    virtual ~GgafDxBgmManager() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXBGMMANAGER_H_*/
