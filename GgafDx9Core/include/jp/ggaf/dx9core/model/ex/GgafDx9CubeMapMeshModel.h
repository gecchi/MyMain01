#ifndef GGAFDX9CUBEMAPMESHMODEL_H_
#define GGAFDX9CUBEMAPMESHMODEL_H_
namespace GgafDx9Core {

class GgafDx9CubeMapMeshModel : public GgafDx9MeshModel {
    friend class GgafDx9ModelManager;

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9CubeMapMeshModel(char* prm_model_name);

    virtual ~GgafDx9CubeMapMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMESHMODEL_H_*/

