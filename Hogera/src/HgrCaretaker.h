#ifndef HGRCARETAKER_H_
#define HGRCARETAKER_H_
#include "Hogera.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "scene/HgrSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((Hogera::HgrCaretaker*)GgafCore::Caretaker::_pCaretaker)

namespace Hogera {

/**
 * �Ǘ��҂̐��` .
 * GgafLib::DefaultCaretaker ���p�����A�Ǘ��҃N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::Spacetime* createSpacetime() ���I�[�o�[���C�h���������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrCaretaker : public GgafLib::DefaultCaretaker {

public:
    /**
     * �R���X�g���N�^ .
     */
    HgrCaretaker();

    /**
     * ���̐��������@�̎��� .
     * �Ǘ��҃N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual HgrSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (HgrSpacetime*)_pSpacetime;
    }

    virtual ~HgrCaretaker();
};

}
#endif /*HGRCARETAKER_H_*/
