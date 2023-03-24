#ifndef FORMATIONGERIA001_H_
#define FORMATIONGERIA001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Geria/FormationGeria.h"

namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 * 自身は出現ポイントの中心
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
