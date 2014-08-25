#ifndef SMPGOD_H_
#define SMPGOD_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/DefaultGod.h"

namespace SimpleSample {

/**
 * �_�̐��` .
 * GgafLib::DefaultGod ���p�����A�_�N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::GgafUniverse* createUniverse() ���I�[�o�[���C�h���������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpGod : public GgafLib::DefaultGod {

public:
    /**
     * �R���X�g���N�^ .
     */
    SmpGod();

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~SmpGod();
};

}
#endif /*SMPGOD_H_*/
