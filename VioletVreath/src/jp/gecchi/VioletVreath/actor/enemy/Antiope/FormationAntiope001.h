#ifndef FORMATIONANTIOPE001_H_
#define FORMATIONANTIOPE001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * 敵機アテ用フォーメーションその１ .
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class FormationAntiope001 : public GgafLib::DefaultGeometricActor {

public:
    /** 編隊数(RANK変動) */
    int num_Antiope_;
    int cnt_Antiope_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    DepositoryConnection* pConn_depo_pAntiopeP_;
    DepositoryConnection* pConn_depo_pAntiopeN_;

public:
    FormationAntiope001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;


    virtual ~FormationAntiope001();
};

}
#endif /*FORMATIONANTIOPE001_H_*/
