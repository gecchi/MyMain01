#ifndef ENEMYAPPHO_H_
#define ENEMYAPPHO_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機アッポー .
 * 超連射６８Kの雑魚のように、
 * 現れて、目の前にスーっと来て、
 * ちょっとウロウロして、スーっと逃げる。
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class EnemyAppho : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_MOVE02 ,
        PROG_MOVE03 ,
        PROG_MOVE04 ,
        PROG_BANPEI ,
    };

    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** [r]出現座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem entry_pos_;
    /** [r]ウロウロする座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem stagnating_pos_;
    /** [r]退出座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem leave_pos_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAppho(const char* prm_name);

    void onCreateModel() override;

    /**
     * アッポーの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アッポーのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アッポーの振る舞い .
     */
    void processBehavior() override;

    /**
     * アッポーの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アッポーの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyAppho();
};

}
#endif /*ENEMYAPPHO_H_*/

