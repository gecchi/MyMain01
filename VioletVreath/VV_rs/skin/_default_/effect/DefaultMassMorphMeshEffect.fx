#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::MassMorphMeshModel�p�V�F�[�_�[
// author : Masatoshi Tsuge
// date:2016/03/18
////////////////////////////////////////////////////////////////////////////////

/** �X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j */
float g_specular;
/** �X�y�L�����[�̋��x */
float g_specular_power;
/** �J�����i���_�j�̈ʒu�x�N�g�� */
float3 g_posCam_World;

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_vecLightFrom_World; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

//float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float g_tex_blink_power;
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj   : POSITION;
    float2 uv              : TEXCOORD0;
    float4 color           : COLOR0;
    float3 vecNormal_World : TEXCOORD1;   // ���[���h�ϊ������@��
    float3 vecEye_World    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
};


///////////////////////////////////////////////////////////////////////////

OUT_VS VS_DefaultMassMorphMesh(
    float4 prm_posPrimary_Local      ,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local,  // ���f���̒��_�̖@��
    float2 prm_uv0                   ,  // ���f���̒��_��UV

    float4 prm_world0,
    float4 prm_world1,
    float4 prm_world2,
    float4 prm_world3,
    float4 prm_color
) {
    OUT_VS out_vs = (OUT_VS)0;

    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};

    //���_�v�Z
    const float4 posModel_World = mul(prm_posPrimary_Local, matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv0;  //���̂܂�

    //�@���� World �ϊ����Đ��K��
    out_vs.vecNormal_World = normalize(mul(prm_vecNormalPrimary_Local, matWorld));
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
    const float power = max(dot(out_vs.vecNormal_World, -g_vecLightFrom_World ), 0);
    //�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * prm_color;
    //�u���_���J�������_�v�����x�N�g��
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = prm_color.a;
    //���t�H�O
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
    return out_vs;
}


//���[�t�^�[�Q�b�g�Ȃ�
OUT_VS VS_DefaultMassMorphMesh0(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World�s��v�f
    float4 prm_world1                 : TEXCOORD2,  // World�s��v�f
    float4 prm_world2                 : TEXCOORD3,  // World�s��v�f
    float4 prm_world3                 : TEXCOORD4,  // World�s��v�f
    float4 prm_color                  : TEXCOORD5   // �}�e���A���J���[
) {
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


//���[�t�^�[�Q�b�g�P��
OUT_VS VS_DefaultMassMorphMesh1(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1  ,  // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World�s��v�f
    float4 prm_world1                 : TEXCOORD2,  // World�s��v�f
    float4 prm_world2                 : TEXCOORD3,  // World�s��v�f
    float4 prm_world3                 : TEXCOORD4,  // World�s��v�f
    float4 prm_color                  : TEXCOORD5   // �}�e���A���J���[
) {
    //�d�݂����o���āA���ɖ߂�
    float weight1 = prm_world0[3];
    prm_world0[3] = 0;
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (weight1 != 0.0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , weight1);
    }

    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


//���[�t�^�[�Q�b�g�Q��
OUT_VS VS_DefaultMassMorphMesh2(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1,    // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    float4 prm_posMorphTarget2_Local  : POSITION2,  // ���f���̃��[�t�^�[�Q�b�g2���_
    float3 prm_vecNormal2_Local       : NORMAL2  ,  // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World�s��v�f
    float4 prm_world1                 : TEXCOORD2,  // World�s��v�f
    float4 prm_world2                 : TEXCOORD3,  // World�s��v�f
    float4 prm_world3                 : TEXCOORD4,  // World�s��v�f
    float4 prm_color                  : TEXCOORD5   // �}�e���A���J���[
) {
    //�d�݂����o���āA���ɖ߂�
    float weight1 = prm_world0[3];
    float weight2 = prm_world1[3];
    prm_world0[3] = 0;
    prm_world1[3] = 0;
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (weight1 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , weight1);
    }
    if (weight2 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , weight2);
    }
    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


//���[�t�^�[�Q�b�g�R��
OUT_VS VS_DefaultMassMorphMesh3(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1,    // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    float4 prm_posMorphTarget2_Local  : POSITION2,  // ���f���̃��[�t�^�[�Q�b�g2���_
    float3 prm_vecNormal2_Local       : NORMAL2,    // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
    float4 prm_posMorphTarget3_Local  : POSITION3,  // ���f���̃��[�t�^�[�Q�b�g3���_
    float3 prm_vecNormal3_Local       : NORMAL3,    // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World�s��v�f
    float4 prm_world1                 : TEXCOORD2,  // World�s��v�f
    float4 prm_world2                 : TEXCOORD3,  // World�s��v�f
    float4 prm_world3                 : TEXCOORD4,  // World�s��v�f
    float4 prm_color                  : TEXCOORD5   // �}�e���A���J���[
) {
    //�d�݂����o���āA���ɖ߂�
    float weight1 = prm_world0[3];
    float weight2 = prm_world1[3];
    float weight3 = prm_world2[3];
    prm_world0[3] = 0;
    prm_world1[3] = 0;
    prm_world2[3] = 0;
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (weight1 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , weight1);
    }
    if (weight2 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , weight2);
    }
    if (weight3 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget3_Local, weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local     , weight3);
    }
    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


//���[�t�^�[�Q�b�g�S��
OUT_VS VS_DefaultMassMorphMesh4(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1,    // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    float4 prm_posMorphTarget2_Local  : POSITION2,  // ���f���̃��[�t�^�[�Q�b�g2���_
    float3 prm_vecNormal2_Local       : NORMAL2,    // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
    float4 prm_posMorphTarget3_Local  : POSITION3,  // ���f���̃��[�t�^�[�Q�b�g3���_
    float3 prm_vecNormal3_Local       : NORMAL3,    // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
    float4 prm_posMorphTarget4_Local  : POSITION4,  // ���f���̃��[�t�^�[�Q�b�g4���_
    float3 prm_vecNormal4_Local       : NORMAL4,    // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World�s��v�f
    float4 prm_world1                 : TEXCOORD2,  // World�s��v�f
    float4 prm_world2                 : TEXCOORD3,  // World�s��v�f
    float4 prm_world3                 : TEXCOORD4,  // World�s��v�f
    float4 prm_color                  : TEXCOORD5   // �}�e���A���J���[
) {
    //�d�݂����o���āA���ɖ߂�
    float weight1 = prm_world0[3];
    float weight2 = prm_world1[3];
    float weight3 = prm_world2[3];
    float weight4 = prm_world3[3];
    prm_world0[3] = 0;
    prm_world1[3] = 0;
    prm_world2[3] = 0;
    prm_world3[3] = 1;
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (weight1 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , weight1);
    }
    if (weight2 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , weight2);
    }
    if (weight3 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget3_Local, weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local     , weight3);
    }
    if (weight4 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget4_Local, weight4);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal4_Local     , weight4);
    }
    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


float4 PS_DefaultMassMorphMesh(
    float2 prm_uv	           : TEXCOORD0,
    float4 prm_color           : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }
    float4 colOut = (colTex2D * prm_color) + s;
    //Blinker���l��
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }
    colOut.a = prm_color.a * g_alpha_master;
    return colOut;
}


float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    const float4 colTex2D  = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex2D * prm_color * FLUSH_COLOR;
    colOut *= g_alpha_master;
    return 	colOut;
}

//////////////////////////////////////////////////////////////////////////////
technique DefaultMassMorphMeshTechnique0
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh0();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DefaultMassMorphMeshTechnique1
{
    //���[�t�^�[�Q�b�g1��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh1();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DefaultMassMorphMeshTechnique2
{
    //���[�t�^�[�Q�b�g2��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh2();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DefaultMassMorphMeshTechnique3
{
    //���[�t�^�[�Q�b�g3��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh3();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DefaultMassMorphMeshTechnique4
{
    //���[�t�^�[�Q�b�g4��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh4();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

//////////////////////////////////////////////////////////////////////////////
technique DestBlendOne0
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh0();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DestBlendOne1
{
    //���[�t�^�[�Q�b�g1��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh1();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DestBlendOne2
{
    //���[�t�^�[�Q�b�g2��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh2();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DestBlendOne3
{
    //���[�t�^�[�Q�b�g3��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh3();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DestBlendOne4
{
    //���[�t�^�[�Q�b�g4��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh4();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

//////////////////////////////////////////////////////////////////////////////
technique Flush0
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh0();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique Flush1
{
    //���[�t�^�[�Q�b�g1��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh1();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique Flush2
{
    //���[�t�^�[�Q�b�g2��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh2();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique Flush3
{
    //���[�t�^�[�Q�b�g3��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh3();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique Flush4
{
    //���[�t�^�[�Q�b�g3��
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh4();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

