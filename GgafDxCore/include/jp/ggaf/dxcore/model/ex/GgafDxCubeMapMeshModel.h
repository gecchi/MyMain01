#ifndef GGAFDXCUBEMAPMESHMODEL_H_
#define GGAFDXCUBEMAPMESHMODEL_H_
namespace GgafDxCore {

/**
 * ���}�b�v���b�V�����f�� .
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshModel : public GgafDxMeshModel {
    friend class GgafDxModelManager;

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxCubeMapMeshModel(char* prm_model_name);

    virtual ~GgafDxCubeMapMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCUBEMAPMESHMODEL_H_*/
