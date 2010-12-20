#ifndef GGAFDX9CUBEMAPMESHACTOR_H_
#define GGAFDX9CUBEMAPMESHACTOR_H_
namespace GgafDx9Core {

/**
 * �X�v���C�g���b�V���Z�b�g�A�N�^�[.
 * GgafDx9MeshActor ���p�����A
 * �����UV��؂�ւ���@�\��L�����A�N�^�[
 * ���b�V���RD�I�u�W�F�N�g�̕\�ʂ̃e�N�X�`�����A�j���[�V�����ł��܂��B
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshActor : public GgafDx9MeshActor {

public:

    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFlipper* _pUvFlipper;

    /**
     * �R���X�g���N�^.
     * GgafDx9SpriteMeshSetActor �Ŏg�p���郂�f��ID�͔����ĉ������B
     * @param prm_name
     * @param prm_model
     * @param prm_pChecker
     * @return
     */
    GgafDx9CubeMapMeshActor(const char* prm_name,
                           const char* prm_model,
                           GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9CubeMapMeshActor();
};

}
#endif /*GGAFDX9CUBEMAPMESHACTOR_H_*/
