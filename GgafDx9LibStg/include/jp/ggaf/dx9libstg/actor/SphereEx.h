#ifndef SPHEREEX_H_
#define SPHEREEX_H_
namespace GgafDx9LibStg {

/**
 * 当たり判定表示用球クラス
 * DefaultSphereActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class SphereEx : public GgafDx9Core::GgafDx9SphereEx {
    static SphereEx* _pObj;

public:
    static SphereEx* get();
    static void release();

    SphereEx(const char* prm_name);

    //void processDraw() {} //オーバーライド未実装にする。


    void drawHitarea(CollisionChecker* prm_pChecker);

    virtual ~SphereEx();

};

}
#endif /*SPHEREEX_H_*/
