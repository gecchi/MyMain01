#ifndef FORMATIONSAPPHO001_H_
#define FORMATIONSAPPHO001_H_
namespace VioletVreath {

/**
 * 敵機サッフォー用フォーメーションその１ .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationSappho001 : public GgafLib::TreeFormation {

public:
    /** 編隊数(RANK変動) */
    int num_Sappho_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;

    bool can_fetch_;
public:
    FormationSappho001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onActiveSappho(EnemySappho* prm_pSappho) = 0;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationSappho001();
};

}
#endif /*FORMATIONSAPPHO001_H_*/
