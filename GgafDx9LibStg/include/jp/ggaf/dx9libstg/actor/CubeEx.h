#ifndef CUBEEX_H_
#define CUBEEX_H_
namespace GgafDx9LibStg {

/**
 * 当たり判定表示用キューブクラス
 * DefaultCubeActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class CubeEx : public GgafDx9Core::GgafDx9CubeEx {
    static CubeEx* _pObj;

public:
    static CubeEx* get();
    static void release();

    CubeEx(const char* prm_name);

    //void processDraw() {} //オーバーライド未実装にする。


    void drawHitarea(CollisionChecker* prm_pChecker);

    virtual ~CubeEx();

};

}
#endif /*CUBEEX_H_*/
