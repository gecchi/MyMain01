#ifndef GGAFDX9CUBEMAPMESHSETMODEL_H_
#define GGAFDX9CUBEMAPMESHSETMODEL_H_
namespace GgafDx9Core {

/**
 * 環境マップメッシュセットモデル .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshSetModel : public GgafDx9MeshSetModel {
    friend class GgafDx9ModelManager;

public:

    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9CubeMapMeshSetModel(char* prm_model_name);

    virtual ~GgafDx9CubeMapMeshSetModel(); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMESHSETMODEL_H_*/

