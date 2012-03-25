#ifndef STAGE02_CLIMAX_H_
#define STAGE02_CLIMAX_H_
namespace VioletVreath {

/**
 * �X�e�[�W�P�|�Ō� .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage02_Climax : public GgafLib::DefaultScene {


public:
    bool waiting_;

    EnemyAstraea* pBoss_;

    Stage02_Climax(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage02_Climax();
};

}
#endif /*STAGE02_CLIMAX_H_*/