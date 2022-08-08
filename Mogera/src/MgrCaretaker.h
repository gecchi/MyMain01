#ifndef MGRCARETAKER_H_
#define MGRCARETAKER_H_
#include "Mogera.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#include "scene/MgrSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((Mogera::MgrCaretaker*)GgafCore::Caretaker::_pCaretaker)

namespace Mogera {

/**
 * �Ǘ��҂̐��` .
 * GgafLib::DefaultCaretaker ���p�����A�Ǘ��҃N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::Spacetime* createSpacetime() ���I�[�o�[���C�h���������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrCaretaker : public GgafLib::DefaultCaretaker {

public:
    /**
     * �R���X�g���N�^ .
     */
    MgrCaretaker();

    /**
     * ���̐��������@�̎��� .
     * �Ǘ��҃N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual MgrSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (MgrSpacetime*)_pSpacetime;
    }

    virtual ~MgrCaretaker();
};

}
#endif /*MGRCARETAKER_H_*/
