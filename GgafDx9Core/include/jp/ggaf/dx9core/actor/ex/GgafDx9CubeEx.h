#ifndef GGAFDX9CUBEEX_H_
#define GGAFDX9CUBEEX_H_
namespace GgafDx9Core {

/**
 * 当たり判定表示用キューブクラス
 * DefaultCubeActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeEx : public GgafDx9CubeActor {

public:

    GgafDx9CubeEx(const char* prm_name);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
        return false;
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    //void processDraw() {} //オーバーライド未実装にする。

    virtual ~GgafDx9CubeEx();

};

}
#endif /*GGAFDX9CUBEEX_H_*/
