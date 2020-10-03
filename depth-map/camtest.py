import cv2 as cv
import numpy as np

WIDTH = 1920
HEIGHT = 1080
SIZE = (WIDTH, HEIGHT)

INTERFACE = "csi"

def get_source(id, interface=INTERFACE):
    if interface == "usb":
        return id
    elif interface == "csi":
        return (
            "nvarguscamerasrc sensor-id=%d sensor-mode=%d ! "
            "video/x-raw(memory:NVMM), "
            "width=(int)%d, height=(int)%d, "
            "format=(string)NV12, framerate=(fraction)%d/1 ! "
            "nvvidconv flip-method=%d ! "
            "video/x-raw, width=(int)%d, height=(int)%d, format=(string)BGRx ! "
            "videoconvert ! "
            "video/x-raw, format=(string)BGR ! appsink"
            % (
                id, # camera id
                3, # mode
                WIDTH, # width
                HEIGHT, # height
                10, # frame rate
                0, # flip method
                WIDTH, # display width
                HEIGHT, # display height
            )
        )
    else:
        raise Exception("Unknown camera source.")

# Starting streaming
def stream():
    camera0 = cv.VideoCapture(get_source(0))
    camera0.set(cv.CAP_PROP_FRAME_WIDTH, WIDTH)
    camera0.set(cv.CAP_PROP_FRAME_HEIGHT, HEIGHT)

    camera1 = cv.VideoCapture(get_source(1))
    camera1.set(cv.CAP_PROP_FRAME_WIDTH, WIDTH)
    camera1.set(cv.CAP_PROP_FRAME_HEIGHT, HEIGHT)
    try: 
        while True:
            camera0.grab()
            camera1.grab()

            _, frame0 = camera0.retrieve()
            _, frame1 = camera1.retrieve()
            
            frame0 = cv.GaussianBlur(frame0, (5, 5), 1000)
            frame1 = cv.GaussianBlur(frame1, (5, 5), 1000)
            
            frame0 = cv.cvtColor(frame0, cv.COLOR_BGR2GRAY)
            frame1 = cv.cvtColor(frame1, cv.COLOR_BGR2GRAY)

            #frame0 = cv.rescale(frame0, (1280, 720))
            #frame1 = cv.rescale(frame1, (1280, 720))

            cv.imshow('left', frame0)
            cv.imshow('right', frame1)

            if cv.waitKey(1) == ord('q'):
                break
    except KeyboardInterrupt:
        pass
    camera0.release()
    camera1.release()
    print("Stream Stopped")
    
stream()
cv.destroyAllWindows()