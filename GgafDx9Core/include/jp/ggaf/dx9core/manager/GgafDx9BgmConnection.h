#ifndef GGAFDX9BGMCONNECTION_H_
#define GGAFDX9BGMCONNECTION_H_
namespace GgafDx9Core {

/**
 * GgafDx9Bgm�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDx9BgmConnection : public GgafCore::GgafResourceConnection<GgafDx9Bgm> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name OGG���ʖ�(���t�@�C����)
     * @param prm_pGgafDx9Bgm OGG
     */
    GgafDx9BgmConnection(char* prm_idstr, GgafDx9Bgm* prm_pGgafDx9Bgm);

    void processReleaseResource(GgafDx9Bgm* prm_pResource);

    virtual ~GgafDx9BgmConnection() {
    }
};

}
#endif /*GGAFDX9BGMCONNECTION_H_*/
