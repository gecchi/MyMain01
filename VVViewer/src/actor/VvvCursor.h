#ifndef VVVCURSOR_H_
#define VVVCURSOR_H_
namespace VVViewer {

/**
 * テストキャラ .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCursor : public GgafLib::DefaultSpriteActor {

public:
    enum {
        CUR_SINK =1,
        CUR_ON_MOVE,
        CUR_STAY,
    };
    coord tX_, tY_, tZ_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    VvvCursor(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;
    void moveTo(GgafDxCore::GgafDxGeometricActor* pT) {
        moveTo(pT->_X,pT->_Y,pT->_Z);
    }
    void moveTo(coord X, coord Y, coord Z);
    void sink();


    virtual ~VvvCursor();
};

}
#endif /*SMPACTOR_H_*/

