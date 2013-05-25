#ifndef GGAFDXALLOCHIERARCHY_H_
#define GGAFDXALLOCHIERARCHY_H_

#include <list>
#include <d3dx9.h>

namespace GgafDxCore {

/**
 * ID3DXAllocateHierarchy�����N���X .
 */
class GgafDxAllocHierarchy : public ID3DXAllocateHierarchy
{
protected:
    class DeleterBase {
    public:
        virtual ~DeleterBase() {}
    };

    template< class T >
    class Deleter : public DeleterBase {
    public:
        T* pObj;
        bool isAry;

        Deleter( T* deletePtr, bool is_Ary = false ) : pObj(deletePtr), isAry( is_Ary ) {};
        virtual ~Deleter(){
            if ( isAry ) {
                T* pa = (T*)pObj;
                GGAF_DELETEARR(pa);
            } else {
                T* p = (T*)pObj;
                GGAF_DELETE(p);
            }
        }
    };

protected:
    std::list<DeleterBase*> m_DelList;   // �������X�g
    std::list<IUnknown*> m_ReleaseList;   // �����[�X���X�g

public:
    GgafDxAllocHierarchy(void);
    virtual ~GgafDxAllocHierarchy(void);

    // �t���[���𐶐�����
    STDMETHOD(CreateFrame)(THIS_
        LPCSTR Name,
        LPD3DXFRAME *ppNewFrame
    ) override;

    // �R���e�i�𐶐�����
    STDMETHOD(CreateMeshContainer)(THIS_
        LPCSTR Name,
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials,
        CONST D3DXEFFECTINSTANCE *pEffectInstances,
        DWORD NumMaterials,
        CONST DWORD *pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER *ppNewMeshContainer
    ) override;

    // �t���[�����폜����
    STDMETHOD(DestroyFrame)(THIS_
        LPD3DXFRAME pFrameToFree
    ) override;

    // �R���e�i���폜����
    STDMETHOD(DestroyMeshContainer)(THIS_
        LPD3DXMESHCONTAINER pMeshContainerToFree
    ) override;


protected:
    // �������X�g�ɓo�^����
    virtual void addDelList( DeleterBase* ptr, bool isAry = false );

    // ��������R�s�[����
    virtual LPSTR copyStr(LPCSTR name);

    // �t���[���\���̂𐶐�����
    virtual D3DXFRAME* createNewFrame();

    // ���b�V���R���e�i�\���̂𐶐�����
    virtual D3DXMESHCONTAINER* createNewMeshContainer();

    // ���b�V���f�[�^��o�^
    virtual void registMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest);

    // �����[�X���X�g�ɓo�^
    virtual void addReleaseList( IUnknown *comptr);

    // �}�e���A���o�^
    virtual void registMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **pDest);

    // �G�t�F�N�g�o�^
    virtual void registEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest);

    // �אڃ|���S���o�^
    virtual void registAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest);

    // �X�L���o�^
    virtual void registSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest);
};

}

#endif /*GGAFDXALLOCHIERARCHY_H_*/
