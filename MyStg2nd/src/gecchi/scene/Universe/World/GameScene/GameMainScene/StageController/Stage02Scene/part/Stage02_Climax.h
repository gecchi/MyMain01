#ifndef STAGE02_CLIMAX_H_
#define STAGE02_CLIMAX_H_
namespace MyStg2nd {

/**
 * �X�e�[�W�P�|�Ō� .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage02_Climax : public GgafDx9LibStg::DefaultScene {


public:
    bool _waiting;

    EnemyAstraea* _pBoss;

    Stage02_Climax(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage02_Climax();
};

}
#endif /*STAGE02_CLIMAX_H_*/
