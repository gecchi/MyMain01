#ifndef FORMATIONJUNO001_H_
#define FORMATIONJUNO001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Juno/FormationJuno.h"

namespace VioletVreath {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * ���g�͏o���|�C���g�̒��S
 */
class FormationJuno001 : public FormationJuno {

public:
    FormationJuno001(const char* prm_name);

    void processJudgement() override;

    virtual ~FormationJuno001();
};

}
#endif /*FORMATIONJUNO001_H_*/
