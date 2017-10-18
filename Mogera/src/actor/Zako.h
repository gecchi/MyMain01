#ifndef ZAKO_H_
#define ZAKO_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include <iostream>
#include <fstream>

namespace Mogera {

/**
 * �G�@�G�� .
 * @version 1.00
 * @since 2015/02/12
 * @author Masatoshi Tsuge
 */
class Zako : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT   ,
        PROG_SPLINE ,
        PROG_LEAVE ,
        PROG_BANPEI,
    };

    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;

    std::ofstream* pOs_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    Zako(const char* prm_name);

    void onCreateModel() override;

    /**
     * �G���̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�����A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G���̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G���̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G���̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~Zako();
};

}
#endif /*ZAKO_H_*/

