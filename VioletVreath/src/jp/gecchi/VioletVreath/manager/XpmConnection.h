#ifndef XPMCONNECTION_H_
#define XPMCONNECTION_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/core/util/Xpm.h"

namespace VioletVreath {

/**
 * Pixmap(GgafCore::Xpm)�����R�l�N�V����.
 * @version 1.00
 * @since 2014/10/06
 * @author Masatoshi Tsuge
 */
class XpmConnection : public GgafCore::ResourceConnection<GgafCore::Xpm> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pResource GgafCore::Xpm�I�u�W�F�N�g
     */
    XpmConnection(const char* prm_idstr, GgafCore::Xpm* prm_pResource);

    void processReleaseResource(GgafCore::Xpm* prm_pResource);

    virtual ~XpmConnection() {
    }
};

}
#endif /*XPMCONNECTION_H_*/
