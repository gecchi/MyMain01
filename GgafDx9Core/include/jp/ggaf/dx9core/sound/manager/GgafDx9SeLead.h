#ifndef GGAFDX9SELEAD_H_
#define GGAFDX9SELEAD_H_
namespace GgafDx9Core {

/**
 * GgafDx9Se�R�l�N�V����.
 */
class GgafDx9SeLead : public GgafCore::GgafResourceLead<GgafDx9Se> {

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_texture_file_name OGG���ʖ�(���t�@�C����)
     * @param prm_pGgafDx9Se OGG
     */
    GgafDx9SeLead(char* prm_idstr, GgafDx9Se* prm_pGgafDx9Se);

    void processReleaseResource(GgafDx9Se* prm_pResource);

    virtual ~GgafDx9SeLead() {
    }
};

}
#endif /*GGAFDX9SELEAD_H_*/
