#ifndef FORMATIONDELHEID001_H_
#define FORMATIONDELHEID001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/FormationDelheid.h"

namespace VioletVreath {

/**
 * 敵機デルヘイド用フォーメーション001グループ .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid001 : public FormationDelheid {

public:
    /** [r]スプライン情報オブジェクト資源への接続 */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;

    FormationDelheid001(const char* prm_name);

    /**
     * 編隊メンバーとして招集された瞬間に呼び出されるコールバック実装、設置座標と向きをセット。
     * @param pEnemyDelheid 招集された編隊メンバー
     */
    void onCalledUpDelheid(EnemyDelheid* pEnemyDelheid) override;

    /**
     * スプライン情報オブジェクトを取得 .
     * @return スプライン情報オブジェクト
     */
    GgafDx::CurveManufacture* getSplManuf() override;

    /**
     * 振る舞い実装 .
     */
    virtual void processBehavior() override;

    virtual ~FormationDelheid001();
};

}
#endif /*FORMATIONDELHEID001_H_*/
