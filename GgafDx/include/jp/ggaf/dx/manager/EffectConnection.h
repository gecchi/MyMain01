#ifndef GGAF_DX_EFFECTCONNECTION_H_
#define GGAF_DX_EFFECTCONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class EffectConnection : public GgafCore::ResourceConnection<Effect> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �G�t�F�N�g���ʖ�(���t�@�C����)
     * @param prm_pEffect �G�t�F�N�g
     */
    EffectConnection(const char* prm_idstr, Effect* prm_pEffect);

    /**
     * �I�[�o�[���C�h
     */
    void processReleaseResource(Effect* prm_pResource);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~EffectConnection() {
    }
};

}
#endif /*GGAF_DX_EFFECTCONNECTION_H_*/
