/** �����_�����O�^�[�Q�b�g�̉���(px) */
float g_dbd_offset_x;
/** �����_�����O�^�[�Q�b�g�̏c��(px) */
float g_dbd_offset_y;


/**
 * dot by dot �l��
 */
float4 adjustDotByDot(float4 pos) {
    pos.x += g_dbd_offset_x*pos.w;
    pos.y += g_dbd_offset_y*pos.w;
    return pos;
}
