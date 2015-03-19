#ifndef GGAFLIB_SPLINEPROGRAMMANAGER_H_
#define GGAFLIB_SPLINEPROGRAMMANAGER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

namespace GgafLib {

/**
 * Spline �Ǘ��N���X .
 * �����ς� SplineSource �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSourceManager : public GgafCore::GgafResourceManager<SplineSource> {

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
    SplineSource* processCreateResource(const char* prm_idstr, void* prm_pConnector);

    GgafCore::GgafResourceConnection<SplineSource>* processCreateConnection(const char* prm_idstr, SplineSource* prm_pResource);

    virtual ~SplineSourceManager() {
    }
};

}
#endif /*GGAFLIB_SPLINEPROGRAMMANAGER_H_*/
