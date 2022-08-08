#ifndef SMPCARETAKER_H_
#define SMPCARETAKER_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

#undef pCARETAKER
#define pCARETAKER ((SimpleSample::SmpCaretaker*)GgafCore::Caretaker::ask())

namespace SimpleSample {

/**
 * �Ǘ��҂̐��` .
 * GgafLib::DefaultCaretaker ���p�����A�Ǘ��҃N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::Spacetime* createSpacetime() ���I�[�o�[���C�h���A�������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpCaretaker : public GgafLib::DefaultCaretaker {

public:
    /**
     * �R���X�g���N�^ .
     */
    SmpCaretaker();

    /**
     * ���̐��������@�̎��� .
     * �Ǘ��҃N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual ~SmpCaretaker();
};

}
#endif /*SMPCARETAKER_H_*/
