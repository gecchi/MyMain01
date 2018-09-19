#coding: utf-8

from PIL import Image
from PIL import ImageOps

print "start"
INPUT_FILE = "msmincho.png"
#フォント幅ピクセルを指定
CHIP_W = 64
#フォント高さピクセルを指定
CHIP_H = 64
#結果テクスチャの幅を指定
DEST_WIDTH = 1024
#結果テクスチャの高さを指定
DEST_HEIGHT = 1024
FONT_COLOR = (255, 255, 255)
#TRNS_COLOR = (0, 0, 0)

# font_col_r_r = FONT_COLOR[0]/255.0
# font_col_g_r = FONT_COLOR[1]/255.0
# font_col_b_r = FONT_COLOR[2]/255.0

col_level = list()
for i in range(256):
    m = (i+1) / 256.0
    r = int(FONT_COLOR[0] * m)
    g = int(FONT_COLOR[1] * m)
    b = int(FONT_COLOR[2] * m)
    col_level.append( (r, g, b) )

for i in range(256):
    print "col_level[" +str(i) +"] = ", col_level[i]

imgOrg = Image.open(INPUT_FILE)
imgDest = Image.new('RGBA', imgOrg.size, (0, 0, 0, 0))

img_w = imgOrg.size[0]
img_h = imgOrg.size[1]
for y in range(img_h):
    for x in range(img_w):
        pixel = imgOrg.getpixel(( x , y ))
        org_r = pixel[0]
        org_g = pixel[1]
        org_b = pixel[2]
        org_a = 0 if len(pixel) < 4 else pixel[3]

        for i in range(255, 0, -1):
            th_r = col_level[i][0]
            th_g = col_level[i][1]
            th_b = col_level[i][2]
            if (org_r >= th_r and org_g >= th_g and org_b >= th_b):
                imgDest.putpixel(( x , y ), (FONT_COLOR[0], FONT_COLOR[1], FONT_COLOR[2], i))
                break
src_x_chip_num = img_w // CHIP_W;
src_y_chip_num = img_h // CHIP_H;
#チップの倍数の大きさにリサイズ。1,1 からなのは、EXCELを罫線を消すため
imgResize = imgDest.crop((1, 1, src_x_chip_num*CHIP_W, src_y_chip_num*CHIP_H))

img_w = imgResize.size[0]
img_h = imgResize.size[1]

chip = list()

for y in range(src_y_chip_num):
    for x in range(src_x_chip_num):
        left = x*CHIP_W
        top = y*CHIP_H
        right = left+CHIP_W
        bottom = top+CHIP_H
        box = (left, top, right, bottom)
        chip.append(imgResize.crop(box))


dest_texture = Image.new('RGBA', (DEST_WIDTH, DEST_HEIGHT), (0, 0, 0))
dest_x_chip_num = DEST_WIDTH // CHIP_W;
dest_y_chip_num = DEST_HEIGHT // CHIP_H;

idx = 0
chip_num = len(chip)
is_finish = False
for y in range(dest_y_chip_num):
    for x in range(dest_x_chip_num):
        left = x*CHIP_W
        top = y*CHIP_H
#         print "idx=" + str(idx) + " chip_num=" + str(chip_num)
        dest_texture.paste(chip[idx], (left, top))
        if (idx < (chip_num-1)):
            idx += 1
        else:
            is_finish = True
            break

    if (is_finish):
        break
#for num in range(src_x_chip_num*src_y_chip_num):
#    chip[num].save(str(num)+'.png', 'PNG')


dest_texture.save(INPUT_FILE + ".dest.png")
print "finish"