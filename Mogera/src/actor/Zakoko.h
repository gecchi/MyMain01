#ifndef ZAKOKO_H_
#define ZAKOKO_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include <iostream>
#include <fstream>

namespace Mogera {

/**
 * �G�@�G�����q .
 * @version 1.00
 * @since 2015/02/13
 * @author Masatoshi Tsuge
 */
class Zakoko : public GgafLib::DefaultMeshSetActor {
public:
    std::ofstream* pOs_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    Zakoko(const char* prm_name);

    void onCreateModel() override;

    /**
     * �G�����q�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�����q���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G�����q�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G�����q�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G�����q�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * �U��U��ɂȂ� .
     */
    void scatter();


    virtual ~Zakoko();
};

}
#endif /*ZAKOKO_H_*/

