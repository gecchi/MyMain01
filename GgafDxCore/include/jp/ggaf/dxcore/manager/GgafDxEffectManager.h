#ifndef GGAFDXCORE_GGAFDXEFFECTMANAGER_H_
#define GGAFDXCORE_GGAFDXEFFECTMANAGER_H_
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxEffectConnection �Ǘ��N���X .
 * �����ς� GgafDxEffectConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxEffectManager : public GgafCore::GgafResourceManager<GgafDxEffect> {

public:
    static GgafDxEffect* _pEffect_active;

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDxEffectManager(const char* prm_manager_name);

    /**
     * �G�t�F�N�g����ID�ɂ��A�G�t�F�N�g�u�W�F�N�g�𐶐����� .
     * <pre>
     * ��prm_idstr�̌`��������
     * prm_idstr�́A
     * �w�G�t�F�N�g�^�C�v  + "/" + fx�t�@�C����(�g���q .fx ������������)�x
     * �Ƃ���������ɂȂ��Ă���B�G�t�F�N�g�^�C�v�͈ȉ��̒ʂ�
     * 'D': GgafDxMeshEffect �I�u�W�F�N�g
     * 'd': GgafDxMeshEffect �I�u�W�F�N�g
     * 'X': GgafDxMeshEffect �I�u�W�F�N�g
     * 'x': GgafDxMeshSetEffect �I�u�W�F�N�g
     * 'A': GgafDxD3DXAniMeshEffect �I�u�W�F�N�g
     * 'M': GgafDxMorphMeshEffect �I�u�W�F�N�g
     * 'S': GgafDxSpriteEffect �I�u�W�F�N�g
     * 's': GgafDxSpriteSetEffect �I�u�W�F�N�g
     * 'B': GgafDxBoardEffect �I�u�W�F�N�g
     * 'b': GgafDxBoardSetEffect �I�u�W�F�N�g
     *
     * ��F"x/LaserChipEffect" �̏ꍇ�B
     * "LaserChipEffect.fx"��ǂݍ��� GgafDxMeshSetEffect�C���X�^���X ��Ԃ��B
     * </pre>
     * @param prm_idstr �G�t�F�N�g����ID
     * @param prm_p ���R�p�����[�^�A���ݖ��g�p
     * @return �G�t�F�N�g�I�u�W�F�N�g
     */
    GgafDxEffect* processCreateResource(char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<GgafDxEffect>* processCreateConnection(char* prm_idstr, GgafDxEffect* prm_pResource) override;

    void setParamPerFrameAll();

    void restoreAll();

    void onDeviceLostAll();

    virtual ~GgafDxEffectManager() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXEFFECTMANAGER_H_*/
