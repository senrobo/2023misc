import sensor, image, time, math,struct
from pyb import UART

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max), declare variables
bluethresh = [(8, 35, -19, 25, -50, 20)] #to set pre-match
yellowthresh = [(54, 95, -10, 20, 20, 57)]
goalthresh = 0
goalX = 0
blueX = 0
yellowX = 0
goalcolour = 0




uart = UART(3, 115200, timeout_char=100) #(only UART 1 or 3 available,baud rate,delay b/w frames)
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=10)

clock = time.clock()
print("Waiting for Arduino...")
#sensor.reset()
#sensor.set_pixformat(sensor.RGB565)
#sensor.set_framesize(sensor.QQVGA) #for 160x120 resolution
#sensor.skip_frames(time = 2000)
#sensor.set_auto_exposure(3, 8750)
#sensor.set_auto_gain(False) # must be turned off for color tracking
#sensor.set_auto_whitebal(False) # must be turned off for color tracking
#clock = time.clock()
#img=sensor.snapshot()

#for blob in img.find_blobs(yellowthresh, pixels_threshold=700, area_threshold=200):
    #img=sensor.snapshot()
    #img.draw_rectangle(blob.rect())
    #img.draw_cross(blob.cx(), blob.cy())
    #yellowX = blob.cx()

#for blob in img.find_blobs(bluethresh, pixels_threshold=700, area_threshold=200):
    #img=sensor.snapshot()
    #img.draw_rectangle(blob.rect())
    #img.draw_cross(blob.cx(), blob.cy())
    #blueX = blob.cx()

#if yellowX > blueX: #test for which goal it is facing
    #goalthresh = yellowthresh
    #goalcolour = 1
#else:
    #goalthresh = bluethresh
    #goalcolour = 2

while(True):
    #clock.tick()
    #img=sensor.snapshot()
    #for blob in img.find_blobs(goalthresh, pixels_threshold=600, area_threshold=200, merge=True): #change area threshold in case localisation marks fail
        #img.draw_rectangle(blob.rect())
        #img.draw_cross(blob.cx(), blob.cy())
        #goalX = blob.cx()
    #try:
        #uart.write(struct.pack("<b",goalX))
        uart.writechar(1)
        #print(goalX)
        print("sent")


    #except OSError as error:
        #pyb.LED(1).on()
        #pyb.LED(2).off()
        #pyb.LED(3).off()
        #print(error)
        #time.sleep(3000)
        #pass
