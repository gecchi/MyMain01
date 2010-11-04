#ifndef GROUNDBOXSCENE_H_
#define GROUNDBOXSCENE_H_


namespace MyStg2nd {
class GroundBoxActor : public GgafDx9LibStg::WallActor {
public:
    GroundBoxActor(const char* prm_name);
    void onCreateModel() override;
    bool isOutOfUniverse() override;
    virtual ~GroundBoxActor() {}
};

/**
 * GROUNDBOX .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class GroundBoxScene : public GgafDx9LibStg::WalledSectionScene {



public:

    float _bound_alpha;

    GroundBoxScene(const char* prm_name,  GgafDx9LibStg::ScrolledScene* prm_pScrolledScene, const char* prm_data_filename);

    void processBehavior() override;

    virtual ~GroundBoxScene();
};

}
#endif /*STAGE01_01_H_*/
