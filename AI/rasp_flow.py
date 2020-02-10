#! /usr/bin/env python3
#import sys
#from abc import ABC, abstractmethod
from picamera import PiCamera
#from picamera.array import PiRGBArray
#import time
#from darkflow.net import flow
import os
import time
import numpy as np
#import tensorflow as tf
#import pickle
#from multiprocessing.pool import ThreadPool

from darkflow.net.build import TFNet
import cv2
import paho.mqtt.client as mqtt


# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
x_res = 1280
y_res = 720
camera.resolution = (x_res, y_res)
#camera.framerate = 32
#rawCapture = PiRGBArray(camera, size=(640, 480))

# allow the camera to warm up
time.sleep(0.1)

options = {"model": "cfg/tiny-yolo-voc.cfg", "load": "bin/tiny-yolo-voc.weights", "threshold": 0.1}
#options = {"model": "cfg/yolo.cfg", "load": "bin/yolov2.weights", "threshold": 0.1}
tfnet = TFNet(options)

broker_address="222.113.57.108"
client = mqtt.Client()
client.connect(broker_address)

# take images from the stream and make detection on it.
# And visualize results:
#camera.start_preview()
#for frame in camera.capture_continuous(rawCapture, format="bgr",
#                                      use_video_port=True):
while True:

    # grab the raw NumPy array representing the image, then 
    # initialize the timestamp and occupied/unoccupied text
#    image = frame.array
    
    imgcapture = camera.capture('./test.jpg')
    #os.system("raspistill -o test.jpg")
    
    image_flip = cv2.imread("./test.jpg")
    image = cv2.flip(image_flip, 0)
    
    result = tfnet.return_predict(image);
    print(result)
    
    person_count = 0
    
    
    for obj in result:
        #.info('coordinates: {} {}. class: "{}". confidence: {:.2f}'.
        #            format(obj[0], obj[1], obj[3], obj[2]))
# obj format example
#[
# {'label': 'aeroplane', 'confidence': 0.13171835, 'topleft': {'x': 139, 'y': 0}, 'bottomright': {'x': 1919, 'y': 964}},
# {'label': 'chair', 'confidence': 0.118859015, 'topleft': {'x': 68, 'y': 346}, 'bottomright': {'x': 629, 'y': 912}},
# {'label': 'sofa', 'confidence': 0.10129978, 'topleft': {'x': 72, 'y': 428}, 'bottomright': {'x': 640, 'y': 972}}
#]
        
        topleft = (obj['topleft']['x'], obj['topleft']['y'])
        bottomright = (obj['bottomright']['x'], obj['bottomright']['y'])
        

        cv2.rectangle(image, topleft, bottomright, (0, 255, 0), 2)
        cv2.putText(image, '{}: {:.2f}'.format(obj['label'], obj['confidence']),
                    topleft,
                    cv2.FONT_HERSHEY_PLAIN, 1, (0, 255, 0), 2)
        if obj['label'] == 'person':
            person_count = person_count + 1

    if person_count != 0:
        client.publish("test/rasp", "{'Num' : %s}" % str(person_count))
        person_count = 0
        
    # show the frame
    cv2.imshow("Stream", image)
    cv2.waitKey(1000)
    #if cv2.waitKey(60) & 0xff == ord('q'):
    #    break
    #key = cv2.waitKey(1) & 0xFF
    
    
    
cv2.destroyAllWindows()
    
    
    
    
    
