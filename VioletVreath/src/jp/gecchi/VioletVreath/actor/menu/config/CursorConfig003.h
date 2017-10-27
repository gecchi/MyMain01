#ifndef CURSORCONFIG003_H_
#define CURSORCONFIG003_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * �X�N���[���R���t�B�O�̕⏕�J�[�\�� .
 * @version 1.00
 * @since 2013/06/12
 * @author Masatoshi Tsuge
 */
class CursorConfig003 : public GgafLib::DefaultBoardActor {

public:
    CursorConfig003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorConfig003();
};

}
#endif /*CURSORCONFIG003_H_*/

