#ifndef CUBEMAPMORPHMESHACTOR_H_
#define CUBEMAPMORPHMESHACTOR_H_
namespace GgafLib {

/**
 * 環境マップモーフメッシュアクターの具象クラス .
 * GgafDxCore::GgafDxMorphMeshActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>参照変数</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>_pProg</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKrokoA</TD><TD>黒子A。移動回転支援</TD><TD>GgafDxCore::GgafDxKurokoA</TD></TR>
 * <TR><TD>_pKrokoB</TD><TD>黒子B。移動支援</TD><TD>GgafDxCore::GgafDxKurokoB</TD></TR>
 * <TR><TD>_pFader</TD><TD>フィードイン・アウト支援</TD><TD> GgafDxCore::GgafDxAlphaFader</TD></TR>
 * <TR><TD>_pSeTxer</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pScaler</TD><TD>拡大縮小支援</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pMorpher</TD><TD>モーフィング支援</TD><TD>GgafDxCore::GgafDxMorpher</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshActor : public GgafDxCore::GgafDxCubeMapMorphMeshActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pColliChecker;

    CubeMapMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=NULL);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~CubeMapMorphMeshActor();
};

}
#endif /*CUBEMAPMORPHMESHACTOR_H_*/
