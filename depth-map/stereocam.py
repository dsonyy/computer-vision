import cv2 as cv
import numpy as np

WIDTH = 1280
HEIGHT = 1024
SIZE = (WIDTH, HEIGHT)

# Loading coefficients from file
calibration = np.load("stereo-12cm.npz", allow_pickle=False)

left_max_x = calibration["left_max_x"]
left_map_y = calibration["left_map_y"]
left_roi = tuple(calibration["left_roi"])
left_matrix = calibration["left_matrix"]
left_distortion_coeff = calibration["left_distortion_coeff"]

right_max_x = calibration["right_max_x"]
right_map_y = calibration["right_map_y"]
right_roi = tuple(calibration["right_roi"])
right_matrix = calibration["right_matrix"]
right_distortion_coeff = calibration["right_distortion_coeff"]

# Creating stereo vision
stereo = cv.StereoBM_create()
stereo.setMinDisparity(4)
stereo.setNumDisparities(128)
stereo.setBlockSize(21)
stereo.setSpeckleRange(16)
stereo.setSpeckleWindowSize(45)

# Calculating depth from 2 images
def get_depth(left, right):
    fixed_left = cv.remap(left, left_max_x, left_map_y, cv.INTER_LINEAR)
    fixed_right = cv.remap(right, right_max_x, right_map_y, cv.INTER_LINEAR)

    fixed_left = cv.cvtColor(fixed_left, cv.COLOR_BGR2GRAY)
    fixed_right = cv.cvtColor(fixed_right, cv.COLOR_BGR2GRAY)

    depth = stereo.compute(fixed_left, fixed_right)

    return depth

# Starting streaming
def depth_stream():
    camera0 = cv.VideoCapture(0)
    camera0.set(cv.CAP_PROP_FRAME_WIDTH, 1280)
    camera0.set(cv.CAP_PROP_FRAME_HEIGHT, 1024)

    camera1 = cv.VideoCapture(1)
    camera1.set(cv.CAP_PROP_FRAME_WIDTH, 1280)
    camera1.set(cv.CAP_PROP_FRAME_HEIGHT, 1024)
    try: 
        while True:
            camera0.grab()
            camera1.grab()

            _, frame0 = camera0.retrieve()
            _, frame1 = camera1.retrieve()
            
            frame0 = cv.GaussianBlur(frame0, (5, 5), 1000)
            frame1 = cv.GaussianBlur(frame1, (5, 5), 1000)

            kernel = np.ones((20, 20), dtype=np.uint8)
            #frame0 = cv.erode(frame0, kernel, iterations=1)
            #frame1 = cv.erode(frame1, kernel, iterations=1)

            depth = get_depth(frame0, frame1)
            
            frame0 = cv.cvtColor(frame0, cv.COLOR_BGR2GRAY)
            frame1 = cv.cvtColor(frame1, cv.COLOR_BGR2GRAY)

            kernel = np.ones((5, 5), dtype=np.uint8)
            depth = cv.dilate(depth, kernel)

            DEPTH_VISUALIZATION_SCALE = 2048
            cv.imshow('depth', depth / DEPTH_VISUALIZATION_SCALE)
            cv.imshow('left', frame0)
            cv.imshow('right', frame1)

            if cv.waitKey(1) == ord('q'):
                break
    except KeyboardInterrupt:
        pass
    camera0.release()
    camera1.release()
    print("Stream Stopped")
    
depth_stream()
cv.destroyAllWindows()