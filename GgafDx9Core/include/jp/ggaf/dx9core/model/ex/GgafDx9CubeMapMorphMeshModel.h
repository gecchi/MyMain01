#ifndef GGAFDX9CUBEMAPMORPHMESHMODEL_H_
#define GGAFDX9CUBEMAPMORPHMESHMODEL_H_
namespace GgafDx9Core {

/**
 * ���}�b�v���[�t���b�V�����f�� .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMorphMeshModel : public GgafDx9MorphMeshModel {
    friend class GgafDx9ModelManager;

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9CubeMapMorphMeshModel(char* prm_model_name);

    virtual ~GgafDx9CubeMapMorphMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMORPHMESHMODEL_H_*/

