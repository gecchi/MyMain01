#ifndef VVVGOD_H_
#define VVVGOD_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/VvvSpacetime.h"

#undef pGOD
#define pGOD ((VVViewer::VvvGod*)GgafCore::God::ask())

namespace VVViewer {

/**
 * VVViewer�_ .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvGod : public GgafLib::DefaultGod {

public:
    static bool is_wm_dropfiles_;
    static char dropfiles_[2048];

public:
    /**
     * �R���X�g���N�^ .
     */
    VvvGod();

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual VvvSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (VvvSpacetime*)_pSpacetime;
    }

    virtual ~VvvGod();
};

}
#endif /*VVVGOD_H_*/
