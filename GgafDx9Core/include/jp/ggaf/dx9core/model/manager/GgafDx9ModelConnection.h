#ifndef GGAFDX9MODELCONNECTION_H_
#define GGAFDX9MODELCONNECTION_H_
namespace GgafDx9Core {

/**
 * ���f���̃R�l�N�V����.
 */
class GgafDx9ModelConnection : public GgafCore::GgafResourceConnection<GgafDx9Model> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
     * @param prm_pModel ���\�[�X�ƂȂ郂�f��
     */
    GgafDx9ModelConnection(char* prm_idstr, GgafDx9Model* prm_pModel);

    void processReleaseResource(GgafDx9Model* prm_pResource);

    virtual ~GgafDx9ModelConnection() {
    }
};

}
#endif /*GGAFDX9MODELCONNECTION_H_*/
