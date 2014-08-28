#ifndef FORMATIONGERIA001_H_
#define FORMATIONGERIA001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/FormationGeria.h"

namespace VioletVreath {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * ���g�͏o���|�C���g�̒��S
 */
class FormationGeria001 : public FormationGeria {

public:
    FormationGeria001(const char* prm_name);

    void processBehavior() override;
    void processJudgement() override;

    virtual ~FormationGeria001();
};

}
#endif /*FORMATIONGERIA001_H_*/
