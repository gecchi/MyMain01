#ifndef GGAF_DX_CURVEPROGRAMMANAGER_H_
#define GGAF_DX_CURVEPROGRAMMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

namespace GgafDx {

/**
 * Curve �Ǘ��N���X .
 * �����ς� CurveSource �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class CurveSourceManager : public GgafCore::ResourceManager<CurveSource> {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    CurveSourceManager(const char* prm_manager_name);

    /**
     * �f�|�W�g�������ʕ����񂩂琶���B
     * �{�A�v���̃X�v���C�����W�Z�b�g�̓R�R�ɏW�񂵂悤�Ǝv���Ă���B
     * @param prm_idstr ����ID
     * @param prm_p ���R�p�����[�^�i���g�p�j
     * @return CurveSource�I�u�W�F�N�g
     */
    virtual CurveSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual GgafCore::ResourceConnection<CurveSource>* processCreateConnection(const char* prm_idstr, CurveSource* prm_pResource) override;

    virtual ~CurveSourceManager() {
    }
};

}
#endif /*GGAF_DX_CURVEPROGRAMMANAGER_H_*/
