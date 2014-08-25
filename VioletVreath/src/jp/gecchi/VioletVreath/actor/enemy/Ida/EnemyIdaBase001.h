#ifndef ENEMYIDABASE001_H_
#define ENEMYIDABASE001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ida/EnemyIdaBase.h"

namespace VioletVreath {

/**
 * �G�@�C�[�_�̊�Ղ��̂P .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIdaBase001 : public EnemyIdaBase {

public:
    enum {
        PROG_INIT ,
        PROG_MOVE ,
        PROG_BANPEI,
    };
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineKurokoLeader* pKurokoLeader_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyIdaBase001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~EnemyIdaBase001();
};

}
#endif /*ENEMYIDABASE_H_*/

