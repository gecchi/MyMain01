#ifndef GGAFDXCORE_GGAFDXSPRITEMESHSETACTOR_H_
#define GGAFDXCORE_GGAFDXSPRITEMESHSETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"

namespace GgafDxCore {

/**
 * �X�v���C�g���b�V���A�N�^�[.
 * GgafDxMeshSetActor ���p�����A
 * �����UV��؂�ւ���@�\��L�����A�N�^�[
 * ���b�V���RD�I�u�W�F�N�g�̕\�ʂ̃e�N�X�`�����A�j���[�V�����ł��܂��B
 * �����Set�ŁB
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteMeshSetActor : public GgafDxMeshSetActor {

public:
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* _pUvFlipper;

public:
    GgafDxSpriteMeshSetActor(const char* prm_name,
                             const char* prm_model,
                             GgafCore::GgafStatus* prm_pStat,
                             GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~GgafDxSpriteMeshSetActor();

};

}
#endif /*GGAFDXCORE_GGAFDXSPRITEMESHSETACTOR_H_*/
