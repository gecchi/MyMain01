#ifndef GGAFDXSPRITEMESHSETACTOR_H_
#define GGAFDXSPRITEMESHSETACTOR_H_
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

    GgafDxSpriteMeshSetActor(const char* prm_name,
                              const char* prm_model,
                              GgafCore::GgafStatus* prm_pStat,
                              GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxSpriteMeshSetActor();

};

}
#endif /*GGAFDXSPRITEMESHSETACTOR_H_*/
