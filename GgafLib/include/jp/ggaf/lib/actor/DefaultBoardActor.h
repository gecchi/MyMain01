#ifndef DEFAULTBOARDACTOR_H_
#define DEFAULTBOARDACTOR_H_
namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDxCore::GgafDxBoardActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>参照変数</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>_pProg</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKrokoA</TD><TD>黒子A。移動回転支援</TD><TD>GgafDxCore::GgafDxKurokoA</TD></TR>
 * <TR><TD>_pKrokoB</TD><TD>黒子B。移動支援</TD><TD>GgafDxCore::GgafDxKurokoB</TD></TR>
 * <TR><TD>_pFader</TD><TD>フィードイン・アウト支援</TD><TD> GgafDxCore::GgafDxAlphaFader</TD></TR>
 * <TR><TD>_pScaler</TD><TD>拡大縮小支援</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pUvFlipper</TD><TD>パラパラアニメーション支援</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>_pSeTx</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/03/11
 * @author Masatoshi Tsuge
 */
class DefaultBoardActor : public GgafDxCore::GgafDxBoardActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;

public:
    DefaultBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultBoardActor();

};

}
#endif /*DEFAULTBOARDACTOR_H_*/
