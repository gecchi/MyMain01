#ifndef CURSORCONFIG001_H_
#define CURSORCONFIG001_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * �R���t�B�O���j���[�J�[�\�� .
 * @version 1.00
 * @since 2013/02/18
 * @author Masatoshi Tsuge
 */
class CursorConfig001 : public GgafLib::DefaultBoardActor {

public:
    CursorConfig001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorConfig001();
};

}
#endif /*CURSORCONFIG001_H_*/

