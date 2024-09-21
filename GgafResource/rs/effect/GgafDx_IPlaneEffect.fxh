/** (1.0 / CONFIG::RENDER_TARGET_BUFFER_WIDTH) / 2.0 */
float g_dbd_offset_x;
/** (1.0 / CONFIG::RENDER_TARGET_BUFFER_HEIGHT) / 2.0 */
float g_dbd_offset_y;


/**
 * dot by dot �l��
 */
float4 adjustDotByDot(float4 pos) {
    float w = pos.w;
    pos /= w; //w�Ŋ����� -1 �` 1 x -1 �` 1 �̍��W�n�ɖ߂�
    pos.x -= g_dbd_offset_x; // -0.5px �����炷
    pos.y += g_dbd_offset_x; // +0.5px �����炷
    pos *= w; //w���悶 ���Ƃ̒l�ɖ߂�
    return pos;
}
