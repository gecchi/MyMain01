#ifndef SMPGOD_H_
#define SMPGOD_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "jp/ggaf/lib/util/VirtualButton.h"

#undef pGOD
#define pGOD ((SimpleSample::SmpGod*)GgafCore::God::ask())

namespace SimpleSample {

/**
 * �_�̐��` .
 * GgafLib::DefaultGod ���p�����A�_�N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::Spacetime* createSpacetime() ���I�[�o�[���C�h���A�������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpGod : public GgafLib::DefaultGod {

public:
    /** ���z�{�^���I�u�W�F�N�g */
    GgafLib::VirtualButton vb_;

    /**
     * �R���X�g���N�^ .
     */
    SmpGod();

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    /**
     * ���z�{�^���I�u�W�F�N�g��Ԃ� .
     * @return ���z�{�^��
     */
    GgafLib::VirtualButton* getVB() {
        return &vb_;
    }

    virtual ~SmpGod();
};

}
#endif /*SMPGOD_H_*/
