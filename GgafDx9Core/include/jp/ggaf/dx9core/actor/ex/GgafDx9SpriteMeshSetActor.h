#ifndef GGAFDX9SPRITEMESHSETACTOR_H_
#define GGAFDX9SPRITEMESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * �X�v���C�g���b�V���A�N�^�[.
 * GgafDx9MeshSetActor ���p�����A
 * �����UV��؂�ւ���@�\��L�����A�N�^�[
 * ���b�V���RD�I�u�W�F�N�g�̕\�ʂ̃e�N�X�`�����A�j���[�V�����ł��܂��B
 * �����Set�ŁB
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteMeshSetActor : public GgafDx9MeshSetActor {

public:
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFlipper* _pUvFlipper;

    GgafDx9SpriteMeshSetActor(const char* prm_name,
                              const char* prm_model,
                              GgafCore::GgafStatus* prm_pStat,
                              GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9SpriteMeshSetActor();

};

}
#endif /*GGAFDX9SPRITEMESHSETACTOR_H_*/
