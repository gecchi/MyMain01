#ifndef VVVCARETAKER_H_
#define VVVCARETAKER_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "scene/VvvSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((VVViewer::VvvCaretaker*)GgafCore::Caretaker::ask())

namespace VVViewer {

/**
 * VVViewer�Ǘ��� .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCaretaker : public GgafLib::DefaultCaretaker {

public:
    static bool is_wm_dropfiles_;
    static char dropfiles_[2048];

public:
    /**
     * �R���X�g���N�^ .
     */
    VvvCaretaker();

    /**
     * ���̐��������@�̎��� .
     * �Ǘ��҃N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual VvvSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (VvvSpacetime*)_pSpacetime;
    }

    virtual ~VvvCaretaker();
};

}
#endif /*VVVCARETAKER_H_*/
