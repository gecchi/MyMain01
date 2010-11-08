#ifndef STAGE01WALLEDSECTION001_H_
#define STAGE01WALLEDSECTION001_H_


namespace MyStg2nd {


/**
 * GROUNDBOX .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01WalledSection001 : public GgafDx9LibStg::WalledSectionScene {

public:

    float _bound_alpha;

    Stage01WalledSection001(const char* prm_name,  GgafDx9LibStg::ScrolledScene* prm_pScrolledScene, const char* prm_data_filename);

    void processBehavior() override;

    virtual ~Stage01WalledSection001();
};

}
#endif /*STAGE01WALLEDSECTION001_H_*/
