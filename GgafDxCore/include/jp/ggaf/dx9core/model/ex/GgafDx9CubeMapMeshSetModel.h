#ifndef GGAFDX9CUBEMAPMESHSETMODEL_H_
#define GGAFDX9CUBEMAPMESHSETMODEL_H_
namespace GgafDx9Core {

/**
 * ���}�b�v���b�V���Z�b�g���f�� .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshSetModel : public GgafDx9MeshSetModel {
    friend class GgafDx9ModelManager;

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9CubeMapMeshSetModel(char* prm_model_name);

    virtual ~GgafDx9CubeMapMeshSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMESHSETMODEL_H_*/

