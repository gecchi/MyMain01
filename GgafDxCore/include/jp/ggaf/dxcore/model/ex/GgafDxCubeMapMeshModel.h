#ifndef GGAFDXCUBEMAPMESHMODEL_H_
#define GGAFDXCUBEMAPMESHMODEL_H_
namespace GgafDxCore {

/**
 * 環境マップメッシュモデル .
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshModel : public GgafDxMeshModel {
    friend class GgafDxModelManager;

public:

    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxCubeMapMeshModel(char* prm_model_name);

    virtual ~GgafDxCubeMapMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCUBEMAPMESHMODEL_H_*/

