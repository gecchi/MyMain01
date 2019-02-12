#ifndef VVGOD_H_
#define VVGOD_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/VvSpacetime.h"

#undef P_GOD
#define P_GOD ((VioletVrain::VvGod*)GgafCore::God::_pGod)

namespace VioletVrain {

/**
 * �_ .
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvGod : public GgafLib::DefaultGod {

public:
    /**
     * �R���X�g���N�^ .
     */
    VvGod();

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual VvSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (VvSpacetime*)_pSpacetime;
    }

    virtual ~VvGod();
};

}
#endif /*VVGOD_H_*/
