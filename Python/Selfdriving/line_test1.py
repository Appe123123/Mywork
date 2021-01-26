from PIL.Image import NONE, register_encoder
import cv2
import numpy as np
import math


height = 478
width = 635

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

region_of_interest_vertices = [
    (0,height),
    (width/2,height/2),
    (width,height),
]

def region_of_interest(frame,vertices):
    
    mask = np.zeros_like(frame)
    
    match_mask_color = 255
    
    cv2.fillPoly(mask, vertices, match_mask_color)
    
    masked_frame = cv2.bitwise_and(frame, mask)
    
    return masked_frame

def draw_lines(img, lines, color=[255,255,255], thickness=3):
    if lines is NONE:
        return
    img = np.copy(img)
    '''
    line_img = np.zeros(
        (
            height,
            width,
            3
        ),
        dtype=np.uint8,

    )
    '''
    ###################이부분은 방향검출을 위함
    x = []
    y = []
    flag = False
    ###################

    line_img = np.zeros_like(img)
    if lines is not None:
        for line in lines:
            for x1,y1,x2,y2 in line:
                cv2.line(line_img, (x1, y1),(x2, y2),color,thickness)
                #이부분은 방향검출을 위함
                x.extend([x1, x2])
                y.extend([y1, y2])
                flag = True
                #

    #img = cv2.addWeighted(img, 0.8, line_img, 1.0, 0)

    #####################################이부분은 방향검출을 위함
    min_y = int(width * 0.6)
    max_y = int(width)

    font = cv2.FONT_HERSHEY_SIMPLEX

    if flag:
        poly = np.poly1d(np.polyfit(
            y,
            x,
            deg=1
        ))

        x_start = int(poly(max_y))
        x_end = int(poly(min_y))

        dx = int((x_end - x_start) * 0.23)
        dy = int(max_y - min_y)

        # Get radian of angle, and converts it to degree
        dir = math.atan2(dy, dx) / math.pi * 180 - 90
        dir = -dir

        cv2.line(img, (x_start, min_y), (x_end, max_y), (0, 255, 0), 2)

        if(dir > 0):
            cv2.putText(img, 'Right', (10, height - 10), font,
                        1, (255, 0, 255), 2, cv2.LINE_AA)
        else:
            cv2.putText(img, 'Left', (10, height - 10), font,
                        1, (255, 0, 255), 2, cv2.LINE_AA)

        #img = cv2.resize(img, (width * 2, height * 2))

        return {'angle': dir, 'image': img}
    else:
        cv2.putText(img, 'No way', (10, height - 10), font,
                    1, (255, 0, 255), 2, cv2.LINE_AA)
        #img = cv2.resize(img, (width * 2, height * 2))
        return {'image': img}
        ############################################



while True:
    
    ret,frame = cap.read()
    
    gray_frame = cv2.cvtColor(frame,cv2.COLOR_RGB2GRAY)
    
    cannyed_frame = cv2.Canny(frame,100, 200)
    
    cropped_frame = region_of_interest(
        cannyed_frame,
        np.array([region_of_interest_vertices], np.int32),
    )

    lines = cv2.HoughLinesP(

        cropped_frame,
        rho=6,
        theta=np.pi/60,
        threshold=160,
        lines=np.array([]),
        minLineLength =30,
        maxLineGap = 20

    )
    #print(lines)
    #print(frame)

    
    tmp = draw_lines(frame, lines)

    #cv2.imshow("iii", line_image)
    cv2.imshow("iii", tmp.get('image', None)) #before add
    if cv2.waitKey(1)>0:
        break

cap.release()
cv2.destroyAllWindows()