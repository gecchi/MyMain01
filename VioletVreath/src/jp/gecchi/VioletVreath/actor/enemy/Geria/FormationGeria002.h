#ifndef FORMATIONGERIA002_H_
#define FORMATIONGERIA002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/FormationGeria.h"

namespace VioletVreath {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * ���g�͏o���|�C���g�̒��S
 */
class FormationGeria002 : public FormationGeria {

public:
    FormationGeria002(const char* prm_name);

    void processBehavior() override;
    void processJudgement() override;

    virtual ~FormationGeria002();
};

}
#endif /*FORMATIONGERIA002_H_*/
