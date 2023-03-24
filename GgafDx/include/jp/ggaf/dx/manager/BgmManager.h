#ifndef GGAF_DX_BGMMANAGER_H_
#define GGAF_DX_BGMMANAGER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/dx/sound/Bgm.h"

namespace GgafDx {

/**
 * Bgm �Ǘ��N���X .
 * �����ς� Bgm �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class BgmManager : public GgafCore::ResourceManager<Bgm> {

    /** [r]BGM�E�}�X�^�[�{�����[���̊��� 0.0�`1.0 */
    double _bgm_master_volume_rate;

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    BgmManager(const char* prm_manager_name);

    Bgm* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<Bgm>* processCreateConnection(const char* prm_idstr, Bgm* prm_pResource) override;

    void setBgmMasterVolumeRate(double prm_volume_rate);

    float getBgmMasterVolumeRate();


    /**
     * ���݉��t���̑S�Ă�BGM�{�����[�����X�V .
     */
    void updateVolume();

    virtual ~BgmManager() {
    }
};

}
#endif /*GGAF_DX_BGMMANAGER_H_*/
