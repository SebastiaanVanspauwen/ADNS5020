import serial
import matplotlib.pyplot as plt
import numpy as np


plt.ion()
fig, ax = plt.subplots()
ser = serial.Serial('COM5', 115200)
index = 0;
w, h = 15, 15;
pixel_data = np.zeros([15,15])
im = ax.imshow(pixel_data, cmap='gray', vmin=0, vmax=128)

while True:
    # Read raw data
    ser_bytes = ser.readline().decode("utf-8")
    #print(ser_bytes)

    pixel_row_data = str(ser_bytes).split(',')

    if len(pixel_row_data) == 15:
        pixel_row_data = [float(i) for i in pixel_row_data]
        pixel_data[index] = pixel_row_data
        index = index + 1
        if index == 15:
            np.rot90(pixel_data)
            index = 0;
            im.set_array(pixel_data)
            plt.pause(0.1)
plt.ioff()
