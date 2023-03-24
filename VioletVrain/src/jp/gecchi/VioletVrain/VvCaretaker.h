#ifndef VVCARETAKER_H_
#define VVCARETAKER_H_
#include "jp/gecchi/VioletVrain/VioletVrain.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "scene/VvSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((VioletVrain::VvCaretaker*)GgafCore::Caretaker::_pCaretaker)

namespace VioletVrain {

/**
 * �Ǘ��� .
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvCaretaker : public GgafLib::DefaultCaretaker {

public:
    /**
     * �R���X�g���N�^ .
     */
    VvCaretaker();

    /**
     * ���̐��������@�̎��� .
     * �Ǘ��҃N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual VvSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (VvSpacetime*)_pSpacetime;
    }

    virtual ~VvCaretaker();
};

}
#endif /*VVCARETAKER_H_*/
