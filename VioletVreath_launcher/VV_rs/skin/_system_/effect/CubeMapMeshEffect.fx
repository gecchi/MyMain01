#include "GgafDx_World3DimEffect.fxh"
/**
 * @author Masatoshi Tsuge
 * @since 2010/12/21
 */
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_reflectance;
float g_specular;
float g_specular_power;

/** �J������World�ʒu */
float3 pos_camera;



/** ���f����World�ϊ��s�� */
float4x4 g_matWorld;
/** ���f����World�ϊ��s��̋t�s�� */
float4x4 g_matInvWorld;
/** ���C�g�̕��� */
float3 g_vecLightFrom_World;
/** �����F�i���ːF�j*/
float4 g_colLightAmbient;
/** �g�U���F�i���ːF�j*/
float4 g_colLightDiffuse;
/** ���f���̃}�e���A���F�i�\�ʐF�j�B������g�U�����ːF�Ŋ������ːF�����˂� */
float4 g_colMaterialDiffuse;
/** ���f���̃e�N�X�`���_�ŋ@�\(GgafDx::TextureBlinker�Q��)�̓_�ŋ��x */
float g_tex_blink_power;
/** ���f���̃e�N�X�`���_�ŋ@�\(GgafDx::TextureBlinker�Q��)�̑ΏۂƂȂ�RGB�̂������l(0.0�`1.0) */
float g_tex_blink_threshold;
/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);
sampler BumpMapTextureSampler : register(s2);

/** ���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS {
    float4 posModel_Proj   : POSITION;    //�ŏI�I�Ȓ��_���W(���[���h�E�r���[�E�ˉe�ϊ��ς�)
    float2 uv              : TEXCOORD0;   //���_�e�N�X�`��UV
    float4 color           : COLOR0;      //���_�J���[
    float3 vecNormal_World : TEXCOORD1;   //���_�̖@���x�N�g��(���[���h���W�n)
    float3 vecEye_World    : TEXCOORD2;   //���_�̎���(���_->���_)�x�N�g��(���[���h���W�n)
};

/** �o���v�}�b�s���O�p���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS_BM {
    float4 posModel_Proj    : POSITION;    //�ŏI�I�Ȓ��_���W(���[���h�E�r���[�E�ˉe�ϊ��ς�)
    float2 uv               : TEXCOORD0;   //���_�e�N�X�`��UV
    float4 color            : COLOR0;      //���_�J���[
    float3 vecNormal_World  : TEXCOORD1;   //���_�̖@���x�N�g��(���[���h���W�n)
    float3 vecEye_World    : TEXCOORD2;   //���_�̎���(���_->���_)�x�N�g��(���[���h���W�n)
    //float3 vecEye_Tangent   : TEXCOORD2;   //���_�̎���(���_->���_)�x�N�g��(���[�J���̐ڋ�ԍ��W�n)
    float4 vecLight_Tangent : TEXCOORD3;   //���_�̃��C�g�x�N�g��(���[�J���̐ڋ�ԍ��W�n)
    float4 vecHarf_Tangent  : TEXCOORD4;   //���_�̃n�[�t�x�N�g��(���[�J���̐ڋ�ԍ��W�n)
};

/**
 * �W���I�Ȓ��_�V�F�[�_�[ .
 * ���_�o�b�t�@�ɂ́A
 * ���_�� World > View > �ˉe �ϊ����A���_�J���[�̐ݒ���s���Ă���B
 * ���f���̃}�e���A���F�t�A�܂�
 * �g�U���F�A�g�U�����ːF�A�����F�A�}�X�^�[�A���t�@�A�t�H�O�A��
 * ���x�d���̂��߃s�N�Z���V�F�[�_�[�ōs�킸�A���_�J���[�Ŏ������Ă���B
 * @param prm_posModel_Local    ���f�����_�̃��[�J�����W
 * @param prm_vecNormal_Local ���f�����_�̖@��
 * @param prm_vecNormal_Local ���f�����_��UV���W
 */
OUT_VS VS_CubeMapMesh(
      float4 prm_posModel_Local  : POSITION,
      float3 prm_vecNormal_Local : NORMAL,
      float2 prm_uv              : TEXCOORD0
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_�v�Z
    const float4 posModel_World = mul(prm_posModel_Local, g_matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�
    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld));
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
    float refl_power = dot(out_vs.vecNormal_World, -g_vecLightFrom_World);
    //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse;
    //�u���_���J�������_�v�����x�N�g��
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = g_colMaterialDiffuse.a;
    //���t�H�O
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
    return out_vs;
}

/**
 * �ʏ�s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
 */
float4 PS_CubeMapMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {
    const float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, prm_vecNormal_World));
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        const float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 colOut = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinker���l��
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }

    colOut.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master;
    return colOut;
}

/**
 * ���[�J�����ڋ�ԕϊ� �s���Ԃ� .
 * �ڋ�ԂƂ̓��b�V���T�[�t�F�C�X��̂���_�ɂ����āA
 * �e�N�X�`��u�����x�N�g��, �e�N�X�`��v�����x�N�g��, �@���x�N�g�� ��
 * �R���ŕ\���������W�n�̎��B�R���͒������Ă���B<BR>
 * �w�}���y�P����[�ǂ��ƃR���x�̋L�� <BR>
 * http://marupeke296.com/DXPS_S_No5_NormalMap.html<BR>
 * ������p�����Ē����܂����B<BR>
 * @param prm_vecTangent  �ڃx�N�g��(u�����P�ʃx�N�g��)
 * @param prm_vecBinormal �]�@���x�N�g��(v�����P�ʃx�N�g��)
 * @param prm_vecNormal   �@���x�N�g��
 **/
float4x4 getInvTangentMatrix(
    float3 prm_vecTangent,
    float3 prm_vecBinormal,
    float3 prm_vecNormal )
{
    float4x4 mat = { float4(prm_vecTangent , 0.0f),
                     float4(prm_vecBinormal, 0.0f),
                     float4(prm_vecNormal  , 0.0f)  ,
                     {  0.0f, 0.0f, 0.0f, 1.0f } };
    return transpose( mat );  // �]�u(�搳�K�����n�̍s��̋t�s��͓]�u�s��ŗǂ�����)
}


OUT_VS_BM VS_BumpMapping(
      float4 prm_posModel_Local    : POSITION,
      float3 prm_vecNormal_Local : NORMAL,
      float2 prm_uv     : TEXCOORD0,
      float3 prm_vecTangent_Local  : TEXCOORD1,
      float3 prm_vecBinormal_Local : TEXCOORD2
) {
    OUT_VS_BM out_vs = (OUT_VS_BM)0;

    //���_�v�Z
    const float4 posModel_World = mul(prm_posModel_Local, g_matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�
    //�@���� World �ϊ����Đ��K��
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld));
    // �ڋ�ԍs��̋t�s����Z�o
    const float4x4 matTangent = getInvTangentMatrix(prm_vecTangent_Local, prm_vecBinormal_Local, prm_vecNormal_Local );

    // World���C�g�x�N�g����ڋ�ԂɈڂ�
    const float3 vecLight_Local = mul(-g_vecLightFrom_World, g_matInvWorld); //���[�J���ɖ߂��āiTODO:�����͗\�ߌv�Z�ł���c�j
    out_vs.vecLight_Tangent = mul(vecLight_Local, matTangent);         //�ڋ�ԍ��W�n��

    //���[���h���_�u���_���J�������_�v�����x�N�g����ڋ�ԂɈڂ��i�X�y�L�����Ŏg�p�j
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);

    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        const float3 vecHarf_World = normalize(out_vs.vecEye_World + (-g_vecLightFrom_World));
        //World�n�[�t�x�N�g����ڋ�ԂɈڂ�
        const float3 vecHarf_Local = mul(vecHarf_World, g_matInvWorld); //���[�J���ɖ߂���
        out_vs.vecHarf_Tangent = mul(vecHarf_Local, matTangent ); //�ڋ�ԍ��W�n��
    }

    out_vs.color = g_colMaterialDiffuse;
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = g_colMaterialDiffuse.a;
    //���t�H�O
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
    return out_vs;
}


/**
 * GgafLib::DefaultMeshActor �o���v�}�b�s���O�p�̃s�N�Z���V�F�[�_�[ .
 * @param prm_uv               UV���W
 * @param prm_color            �F�i���_�J���[�ɂ��j
 * @param prm_vecNormal_World  �@���x�N�g��(World���W�n)
 * @param prm_vecEye_World     ����(���_->���_)�x�N�g��(World���W�n)
 * @param prm_vecLight_Tangent �g�U�������x�N�g��(�ڋ�ԍ��W�n)
 * @param prm_vecHarf_Tangent  �n�[�t�x�N�g��(�ڋ�ԍ��W�n)
 */
float4 PS_BumpMapping(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_vecNormal_World  : TEXCOORD1,
    float3 prm_vecEye_World     : TEXCOORD2,   //���_ -> ���_ �x�N�g��
    float3 prm_vecLight_Tangent : TEXCOORD3,  //�ڋ�ԍ��W�n�ɕϊ����ꂽ�g�U�������x�N�g��
    float3 prm_vecHarf_Tangent  : TEXCOORD4   //�ڋ�ԍ��W�n�ɕϊ����ꂽ�n�[�t�x�N�g��
) : COLOR  {
    const float a = prm_color.a; //���ێ�
    //�@���}�b�v����̖@��
    const float3 vecNormal_Tangent = normalize(2.0f * tex2D( BumpMapTextureSampler, prm_uv ).xyz - 1.0);
    //�@��(�@���}�b�v�̖@���A�܂�ڋ�ԍ��W�n�̖@���ɂȂ�j�ƁA
    //�g�U�������x�N�g��(���_�V�F�[�_�[�Őڋ�ԍ��W�n�ɗ\�ߕϊ��ς�) �̓��ς���
    //���C�g���ˊp�����߁A�ʂɑ΂���g�U���̌�����(power)�����߂�
    float refl_power = dot(vecNormal_Tangent, normalize(prm_vecLight_Tangent) );
    //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;

    const float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, prm_vecNormal_World)); //�@���}�b�v�̓ʉ��͖��l���B
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);  //�@���}�b�v�̓ʉ��͖��l���B

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g����
        //�ڋ�ԍ��W�n�ɗ\�ߕϊ��ς݁j�Ɩ@��(�@���}�b�v�̖@���A�܂�ڋ�ԍ��W�n�̖@��)�̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(vecNormal_Tangent, prm_vecHarf_Tangent)), g_specular ) * g_specular_power; //�@���}�b�v�̓ʉ����l���B
    }

    //�F�v�Z
    float4 colOut = colTex2D * ((g_colLightAmbient + ( g_colLightDiffuse * refl_power)) * prm_color ) + (colTexCube*g_reflectance) +s; //prm_color == g_colMaterialDiffuse
    //TODO:���F�v�Z����������ƒ��_�V�F�[�_�ŏ����ł��Ȃ����̂��E�E�E
    //float4 colOut = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;

    //Blinker���l��
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }

    colOut.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {
    const float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, prm_vecNormal_World));
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = ((colTex2D * prm_color) + (colTexCube*g_reflectance))  * FLUSH_COLOR;
    colOut.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master;
    return colOut;
}

/**
 * �ʏ�e�N�j�b�N
 */
technique CubeMapMeshTechnique
{
    //pass P0�u���b�V���W���V�F�[�_�[�v
    //���b�V����`�悷��
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMesh();
        PixelShader  = compile PS_VERSION PS_CubeMapMesh();
    }
}

technique BumpMapping
{
    //pass P0�u���b�V���W���V�F�[�_�[�v
    //���b�V����`�悷��
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_BumpMapping();
        PixelShader  = compile PS_VERSION PS_BumpMapping();
    }
}


technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMesh();
        PixelShader  = compile PS_VERSION PS_CubeMapMesh();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

