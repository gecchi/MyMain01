#ifndef XPMMANAGER_H_
#define XPMMANAGER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/core/util/Xpm.h"
namespace VioletVreath {

/**
 * Pixmap(GgafCore::Xpm)�����Ǘ��N���X .
 * �����ς� GgafCore::Xpm �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2014/10/06
 * @author Masatoshi Tsuge
 */
class XpmManager : public GgafCore::ResourceManager<GgafCore::Xpm> {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    XpmManager(const char* prm_manager_name);

    GgafCore::Xpm* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<GgafCore::Xpm>* processCreateConnection(const char* prm_idstr, GgafCore::Xpm* prm_pResource) override;


    virtual ~XpmManager() {
    }
};

}
#endif /*CURVELINEMANAGER_H_*/
