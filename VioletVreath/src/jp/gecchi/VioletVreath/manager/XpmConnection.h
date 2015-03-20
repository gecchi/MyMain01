#ifndef XPMCONNECTION_H_
#define XPMCONNECTION_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/core/util/GgafXpm.h"

namespace VioletVreath {

/**
 * Pixmap(GgafCore::GgafXpm)�����R�l�N�V����.
 * @version 1.00
 * @since 2014/10/06
 * @author Masatoshi Tsuge
 */
class XpmConnection : public GgafCore::GgafResourceConnection<GgafCore::GgafXpm> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pSpl3D SplineLine�I�u�W�F�N�g
     */
    XpmConnection(char* prm_idstr, GgafCore::GgafXpm* prm_pSpl3D);

    void processReleaseResource(GgafCore::GgafXpm* prm_pResource);

    virtual ~XpmConnection() {
    }
};

}
#endif /*XPMCONNECTION_H_*/
