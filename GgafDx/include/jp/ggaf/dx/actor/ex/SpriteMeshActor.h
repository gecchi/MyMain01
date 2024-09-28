#ifndef GGAF_DX_SPRITEMESHACTOR_H_
#define GGAF_DX_SPRITEMESHACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * �X�v���C�g���b�V���Z�b�g�A�N�^�[.
 *
 * �����UV��؂�ւ���@�\��L�����A�N�^�[
 * ���b�V���RD�I�u�W�F�N�g�̕\�ʂ̃e�N�X�`�����A�j���[�V�����ł��܂��B
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshActor : public MeshActor {

public:
    /** UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* _pUvFlipper;

public:
    /**
     * �R���X�g���N�^.
     * SpriteMeshSetActor �Ŏg�p���郂�f��ID�͔����ĉ������B
     * @param prm_name
     * @param prm_model
     * @param prm_pColliChecker
     */
    SpriteMeshActor(const char* prm_name,
                    const char* prm_model);

    virtual void processDraw() override;

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~SpriteMeshActor();
};

}
#endif /*GGAF_DX_SPRITEMESHACTOR_H_*/
