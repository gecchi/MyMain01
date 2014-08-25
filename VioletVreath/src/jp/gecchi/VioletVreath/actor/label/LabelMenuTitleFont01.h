#ifndef LABELMENUTITLEFONT01_H_
#define LABELMENUTITLEFONT01_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/StringBoardActor.h"

namespace VioletVreath {

/**
 * ���j���[�̃^�C�g���p�t�H���g .
 * @version 1.00
 * @since 2013/03/26
 * @author Masatoshi Tsuge
 */
class LabelMenuTitleFont01 : public GgafLib::StringBoardActor {

public:
    LabelMenuTitleFont01(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelMenuTitleFont01();

};

}
#endif /*LABELFIX16FONT01_H_*/
