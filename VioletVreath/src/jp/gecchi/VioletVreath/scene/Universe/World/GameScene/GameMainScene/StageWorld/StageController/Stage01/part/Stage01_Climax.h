#ifndef STAGE01_CLIMAX_H_
#define STAGE01_CLIMAX_H_
namespace VioletVreath {

/**
 * �X�e�[�W�P�|�Ō� .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage01_Climax : public GgafLib::DefaultScene {


public:
    bool _waiting;

    EnemyAstraea* _pBoss;

    Stage01_Climax(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage01_Climax();
};

}
#endif /*STAGE01_CLIMAX_H_*/
