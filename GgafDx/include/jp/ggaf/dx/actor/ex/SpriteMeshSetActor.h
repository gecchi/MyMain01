#ifndef GGAF_DX_SPRITEMESHSETACTOR_H_
#define GGAF_DX_SPRITEMESHSETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshSetActor.h"

namespace GgafDx {

/**
 * �X�v���C�g���b�V���A�N�^�[.
 * MeshSetActor ���p�����A
 * �����UV��؂�ւ���@�\��L�����A�N�^�[
 * ���b�V���RD�I�u�W�F�N�g�̕\�ʂ̃e�N�X�`�����A�j���[�V�����ł��܂��B
 * �����Set�ŁB
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshSetActor : public MeshSetActor {

public:
    /** UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* _pUvFlipper;

public:
    SpriteMeshSetActor(const char* prm_name,
                       const char* prm_model,
                       Checker* prm_pChecker );

    virtual void processDraw() override;

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~SpriteMeshSetActor();

};

}
#endif /*GGAF_DX_SPRITEMESHSETACTOR_H_*/
