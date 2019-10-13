#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::MorphMeshModel�p�V�F�[�_�[
// author : Masatoshi Tsuge
// date:2009/05/12
////////////////////////////////////////////////////////////////////////////////

//�G���[���o��̂łƂ肠�����錾
/** �X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j */
float g_specular;
/** �X�y�L�����[�̋��x */
float g_specular_power;
/** �J�����i���_�j�̈ʒu�x�N�g�� */
float3 g_posCam_World;
float g_reflectance;


float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��
int g_morph_target_num;  //���b�V���p�^�[����(���[�t�^�[�Q�b�g���j�A���ݖ��g�p
float g_weight1; //���[�t�^�[�Q�b�g�P�̏d��
float g_weight2; //���[�t�^�[�Q�b�g�Q�̏d��
float g_weight3; //���[�t�^�[�Q�b�g�R�̏d��
float g_weight4; //���[�t�^�[�Q�b�g�S�̏d��
float g_weight5; //���[�t�^�[�Q�b�g�T�̏d��
float g_weight6; //���[�t�^�[�Q�b�g�U�̏d��
//float g_weight7; //���[�t�^�[�Q�b�g�V�̏d��

float3 g_vecLightFrom_World; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float g_tex_blink_power;
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);

struct OUT_VS {
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color  : COLOR0;
    float3 vecNormal_World : TEXCOORD1;   // ���[���h�ϊ������@��
    float3 vecEye_World    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
};

///////////////////////////////////////////////////////////////////////////

//���[�t�^�[�Q�b�g�Ȃ�
OUT_VS VS_CubeMapMorphMesh0(
     float4 prm_posPrimary_Local       : POSITION0,      // ���f���̒��_
     float3 prm_vecNormalPrimary_Local : NORMAL0,        // ���f���̒��_�̖@��
     float2 prm_uv0                    : TEXCOORD0       // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_�v�Z
    const float4 posModel_World = mul(prm_posPrimary_Local, g_matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv0;  //���̂܂�
    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    out_vs.vecNormal_World = normalize(mul(prm_vecNormalPrimary_Local, g_matWorld));
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

//���[�t�^�[�Q�b�g�P��
OUT_VS VS_CubeMapMorphMesh1(
     float4 prm_posPrimary_Local       : POSITION0,      // ���f���̒��_
     float3 prm_vecNormalPrimary_Local : NORMAL0,        // ���f���̒��_�̖@��
     float2 prm_uv0                    : TEXCOORD0,      // ���f���̒��_��UV
     float4 prm_posMorphTarget1_Local  : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
     float3 prm_vecNormal1_Local       : NORMAL1         // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local, g_weight1);
    }
    return VS_CubeMapMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}


//���[�t�^�[�Q�b�g�Q��
OUT_VS VS_CubeMapMorphMesh2(
     float4 prm_posPrimary_Local       : POSITION0,      // ���f���̒��_
     float3 prm_vecNormalPrimary_Local : NORMAL0,        // ���f���̒��_�̖@��
     float2 prm_uv0                    : TEXCOORD0,      // ���f���̒��_��UV
     float4 prm_posMorphTarget1_Local  : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
     float3 prm_vecNormal1_Local       : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
     float4 prm_posMorphTarget2_Local  : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
     float3 prm_vecNormal2_Local       : NORMAL2         // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local, g_weight2);
    }
    return VS_CubeMapMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}

//���[�t�^�[�Q�b�g�R��
OUT_VS VS_CubeMapMorphMesh3(
     float4 prm_posPrimary_Local       : POSITION0,      // ���f���̒��_
     float3 prm_vecNormalPrimary_Local : NORMAL0,        // ���f���̒��_�̖@��
     float2 prm_uv0                    : TEXCOORD0,      // ���f���̒��_��UV
     float4 prm_posMorphTarget1_Local  : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
     float3 prm_vecNormal1_Local       : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
     float4 prm_posMorphTarget2_Local  : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
     float3 prm_vecNormal2_Local       : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
     float4 prm_posMorphTarget3_Local  : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
     float3 prm_vecNormal3_Local       : NORMAL3         // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local, g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Local += ((prm_posMorphTarget3_Local - prm_posPrimary_Local) * g_weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local, g_weight3);
    }
    return VS_CubeMapMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}

//���[�t�^�[�Q�b�g�S��
OUT_VS VS_CubeMapMorphMesh4(
     float4 prm_posPrimary_Local       : POSITION0,      // ���f���̒��_
     float3 prm_vecNormalPrimary_Local : NORMAL0,        // ���f���̒��_�̖@��
     float2 prm_uv0                    : TEXCOORD0,      // ���f���̒��_��UV
     float4 prm_posMorphTarget1_Local  : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
     float3 prm_vecNormal1_Local       : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
     float4 prm_posMorphTarget2_Local  : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
     float3 prm_vecNormal2_Local       : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
     float4 prm_posMorphTarget3_Local  : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
     float3 prm_vecNormal3_Local       : NORMAL3,        // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
     float4 prm_posMorphTarget4_Local  : POSITION4,      // ���f���̃��[�t�^�[�Q�b�g4���_
     float3 prm_vecvecNormal4_Local    : NORMAL4         // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local, g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Local += ((prm_posMorphTarget3_Local - prm_posPrimary_Local) * g_weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local, g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Local += ((prm_posMorphTarget4_Local - prm_posPrimary_Local) * g_weight4);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecvecNormal4_Local, g_weight4);
    }
    return VS_CubeMapMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}

//���[�t�^�[�Q�b�g�T��
OUT_VS VS_CubeMapMorphMesh5(
     float4 prm_posPrimary_Local       : POSITION0,      // ���f���̒��_
     float3 prm_vecNormalPrimary_Local : NORMAL0,        // ���f���̒��_�̖@��
     float2 prm_uv0                    : TEXCOORD0,      // ���f���̒��_��UV
     float4 prm_posMorphTarget1_Local  : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
     float3 prm_vecNormal1_Local       : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
     float4 prm_posMorphTarget2_Local  : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
     float3 prm_vecNormal2_Local       : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
     float4 prm_posMorphTarget3_Local  : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
     float3 prm_vecNormal3_Local       : NORMAL3,        // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
     float4 prm_posMorphTarget4_Local  : POSITION4,      // ���f���̃��[�t�^�[�Q�b�g4���_
     float3 prm_vecvecNormal4_Local    : NORMAL4,        // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
     float4 prm_posMorphTarget5_Local  : POSITION5,      // ���f���̃��[�t�^�[�Q�b�g5���_
     float3 prm_vecNormal5_Local       : NORMAL5         // ���f���̃��[�t�^�[�Q�b�g5���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local, g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Local += ((prm_posMorphTarget3_Local - prm_posPrimary_Local) * g_weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local, g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Local += ((prm_posMorphTarget4_Local - prm_posPrimary_Local) * g_weight4);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecvecNormal4_Local, g_weight4);
    }
    if (g_weight5 != 0 ) {
        posModel_Local += ((prm_posMorphTarget5_Local - prm_posPrimary_Local) * g_weight5);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal5_Local, g_weight5);
    }
    return VS_CubeMapMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}

//���[�t�^�[�Q�b�g�U��
OUT_VS VS_CubeMapMorphMesh6(
     float4 prm_posPrimary_Local       : POSITION0,      // ���f���̒��_
     float3 prm_vecNormalPrimary_Local : NORMAL0,        // ���f���̒��_�̖@��
     float2 prm_uv0                    : TEXCOORD0,      // ���f���̒��_��UV
     float4 prm_posMorphTarget1_Local  : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
     float3 prm_vecNormal1_Local       : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
     float4 prm_posMorphTarget2_Local  : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
     float3 prm_vecNormal2_Local       : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
     float4 prm_posMorphTarget3_Local  : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
     float3 prm_vecNormal3_Local       : NORMAL3,        // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
     float4 prm_posMorphTarget4_Local  : POSITION4,      // ���f���̃��[�t�^�[�Q�b�g4���_
     float3 prm_vecvecNormal4_Local    : NORMAL4,        // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
     float4 prm_posMorphTarget5_Local  : POSITION5,      // ���f���̃��[�t�^�[�Q�b�g5���_
     float3 prm_vecNormal5_Local       : NORMAL5,        // ���f���̃��[�t�^�[�Q�b�g5���_�̖@��
     float4 prm_posMorphTarget6_Local  : POSITION6,      // ���f���̃��[�t�^�[�Q�b�g6���_
     float3 prm_vecNormal6_Local       : NORMAL6         // ���f���̃��[�t�^�[�Q�b�g6���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local, g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Local += ((prm_posMorphTarget3_Local - prm_posPrimary_Local) * g_weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local, g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Local += ((prm_posMorphTarget4_Local - prm_posPrimary_Local) * g_weight4);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecvecNormal4_Local, g_weight4);
    }
    if (g_weight5 != 0 ) {
        posModel_Local += ((prm_posMorphTarget5_Local - prm_posPrimary_Local) * g_weight5);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal5_Local, g_weight5);
    }
    if (g_weight6 != 0 ) {
        posModel_Local += ((prm_posMorphTarget6_Local - prm_posPrimary_Local) * g_weight6);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal6_Local, g_weight6);
    }
    return VS_CubeMapMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}


float4 PS_CubeMapMorphMesh(
    float2 prm_uv	           : TEXCOORD0,
    float4 prm_color           : COLOR0,
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


float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    const float4 colTex2D  = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex2D * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return 	colOut;
}

technique CubeMapMorphMeshTechnique
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh0();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh1();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh2();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh3();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh4();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh5();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh6();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

//	//���[�t�^�[�Q�b�g�V��
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = InvSrcAlpha;
//		VertexShader = compile VS_VERSION VS_CubeMapMorphMesh7();
//		PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
//	}
}


technique DestBlendOne
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh0();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh1();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh2();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh3();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh4();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh5();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh6();
        PixelShader  = compile PS_VERSION PS_CubeMapMorphMesh();
    }
}

technique Flush
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh0();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh1();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh2();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh3();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh4();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh5();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMorphMesh6();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

}
