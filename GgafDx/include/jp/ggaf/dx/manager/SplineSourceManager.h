#ifndef GGAF_DX_SPLINEPROGRAMMANAGER_H_
#define GGAF_DX_SPLINEPROGRAMMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

namespace GgafDx {

/**
 * Spline �Ǘ��N���X .
 * �����ς� SplineSource �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSourceManager : public GgafCore::ResourceManager<SplineSource> {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    SplineSourceManager(const char* prm_manager_name);

    /**
     * �f�|�W�g�������ʕ����񂩂琶���B
     * �{�A�v���̃X�v���C�����W�Z�b�g�̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr ����ID
     * @param prm_p ���R�p�����[�^�i���g�p�j
     * @return SplineSource�I�u�W�F�N�g
     */
    virtual SplineSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual GgafCore::ResourceConnection<SplineSource>* processCreateConnection(const char* prm_idstr, SplineSource* prm_pResource) override;

    virtual ~SplineSourceManager() {
    }
};

}
#endif /*GGAF_DX_SPLINEPROGRAMMANAGER_H_*/
