#ifndef GGAFDX9SELEAD_H_
#define GGAFDX9SELEAD_H_
namespace GgafDx9Core {

/**
 * GgafDx9Seコネクション.
 */
class GgafDx9SeLead : public GgafCore::GgafResourceLead<GgafDx9Se> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_texture_file_name OGG識別名(＝ファイル名)
     * @param prm_pGgafDx9Se OGG
     */
    GgafDx9SeLead(char* prm_idstr, GgafDx9Se* prm_pGgafDx9Se);

    void processReleaseResource(GgafDx9Se* prm_pResource);

    virtual ~GgafDx9SeLead() {
    }
};

}
#endif /*GGAFDX9SELEAD_H_*/
