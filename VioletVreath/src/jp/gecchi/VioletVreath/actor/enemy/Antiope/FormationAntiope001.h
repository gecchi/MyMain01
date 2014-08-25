#ifndef FORMATIONANTIOPE001_H_
#define FORMATIONANTIOPE001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * �G�@�A�e�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class FormationAntiope001 : public GgafLib::DefaultGeometricActor {

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Antiope_;
    int cnt_Antiope_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    DepositoryConnection* pConn_depo_pAntiopeP_;
    DepositoryConnection* pConn_depo_pAntiopeN_;

public:
    FormationAntiope001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;


    virtual ~FormationAntiope001();
};

}
#endif /*FORMATIONANTIOPE001_H_*/
