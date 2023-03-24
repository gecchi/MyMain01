#ifndef LABELMENUITEMFONT01_H_
#define LABELMENUITEMFONT01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * ���j���[�̃^�C�g���p�t�H���g .
 * @version 1.00
 * @since 2013/03/26
 * @author Masatoshi Tsuge
 */
class LabelMenuItemFont01 : public GgafLib::FontBoardActor {

public:
    LabelMenuItemFont01(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onUpdate() override;

    void processBehavior() override;

    virtual ~LabelMenuItemFont01();

};

}
#endif /*LABELMENUITEMFONT01_H_*/
