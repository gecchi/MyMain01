#ifndef STAGE01WALLEDSECTION001_H_
#define STAGE01WALLEDSECTION001_H_
namespace VioletVreath {

/**
 * ステージ01の壁セクション(種別001) .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01WalledSection001 : public GgafLib::WalledSectionScene {

public:
    float bound_alpha_;

public:
    Stage01WalledSection001(const char* prm_name,  GgafLib::WalledScene* prm_pWalledScene, const char* prm_data_filename);

    void processBehavior() override;

    virtual void onBlockLaunch(int prm_loop_count, int prm_wall_count, coord prm_wall_X) override;

    virtual ~Stage01WalledSection001();
};

}
#endif /*STAGE01WALLEDSECTION001_H_*/
