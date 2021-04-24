#ifndef GGAF_LIB_DEFAULTMASSBOARDACTOR_H_
#define GGAF_LIB_DEFAULTMASSBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassBoardActor.h"

namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx::MassBoardActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::Progress</TD></TR>
 * <TR><TD>getVecDriver()</TD><TD>力車。移動回転支援</TD><TD>GgafDx::VecDriver</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * </TABLE>
 * <B>【注意】</B>拡大縮小支援(GgafDx::Scaler)は使用出来ません。
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class DefaultMassBoardActor : public GgafDx::MassBoardActor {
private:
    /**
     * 使用禁止 .
     * @return
     */
    GgafDx::Scaler* getScaler();

protected:
    struct VERTEX_instancedata {
        float px_x, px_y, depth_z;    // : TEXCOORD1
        float local_px_x, local_px_y; // : TEXCOORD2
        float r_sx, r_sy, rad_rz;     // : TEXCOORD3
        float offset_u, offset_v;     // : TEXCOORD4
        float r, g, b, a;             // : TEXCOORD5  マテリアルカラー
    };
    static VERTEX_instancedata _aInstancedata[];

    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);

public:
    DefaultMassBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }
    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual ~DefaultMassBoardActor();

};

}
#endif /*GGAF_LIB_DEFAULTMASSBOARDACTOR_H_*/
