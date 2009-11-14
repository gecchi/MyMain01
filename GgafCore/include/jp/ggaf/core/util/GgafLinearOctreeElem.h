#ifndef GGAFLINEAROCTREEELEM_H_
#define GGAFLINEAROCTREEELEM_H_
namespace GgafCore {


/**
 * 空間要素クラス .
 */
class GgafLinearOctreeElem {
public:
    /** 所属ツリー */
    GgafLinearOctree* _pLinearOctree;
    /** 所属空間 */
    GgafLinearOctreeSpace* _pSpace_Current;
    /** 次要素 */
    GgafLinearOctreeElem* _pNext;
    /** 前要素 */
    GgafLinearOctreeElem* _pPrev;
    /** 対象オブジェクト */
    GgafObject* _pObject;
    /** 対象オブジェクト種別 */
    DWORD _kindbit;
    /** 登録リスト用リンク */
    GgafLinearOctreeElem* _pRegLinkNext;

    GgafLinearOctreeElem(GgafObject* prm_pObject, DWORD prm_kindbit);

    /**
     * 自身が自ら離脱
     */
    void extract();

    /**
     * 自身が自ら空間の末尾に追加
     */
    void addElem(GgafLinearOctreeSpace* prm_pSpace_target);

    /**
     * 自身が自ら他空間へ移動
     * extract()してaddElem()します.
     * @param prm_pSpace_target
     */
    //void moveToSpace(GgafLinearOctreeSpace* prm_pSpace_target);
    void dump();

    virtual ~GgafLinearOctreeElem();
};

}
#endif /*GGAFLINEAROCTREEELEM_H_*/

