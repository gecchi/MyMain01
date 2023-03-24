#ifndef GGAF_DX_BASEACTOR_H_
#define GGAF_DX_BASEACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/actor/MainActor.h"

namespace GgafDx {

/**
 * Core���O��Ԃ̊��A�N�^�[�N���X.
 * GgafCore::MainActor���p�����������ł��B<BR>
 * Core���O��ԓ��ł́A���̃N���X�����A�N�^�[�Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2009/09/08
 * @author Masatoshi Tsuge
 */
class BaseActor : public GgafCore::MainActor {

public:
    BaseActor(const char* prm_name);

    virtual ~BaseActor();

};

}
#endif /*GGAF_DX_BASEACTOR_H_*/
