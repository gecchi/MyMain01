#ifndef CURSOR001_H_
#define CURSOR001_H_


namespace MyStg2nd {

/**
 * ÉJÅ[É\ÉãÇªÇÃÇP .
 * @version 1.00
 * @since 2011/04/07
 * @author Masatoshi Tsuge
 */
class Cursor001 : public GgafDx9LibStg::DefaultBoardActor {

public:
    Cursor001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    virtual ~Cursor001();
};

}
#endif /*CURSOR001_H_*/

