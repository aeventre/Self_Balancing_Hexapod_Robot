import busio
import board
from adafruit_pca9685 import PCA9685

try:
    # Initialize I2C bus
    i2c = busio.I2C(board.SCL, board.SDA)

    # Initialize PCA9685 at 0x41
    pca = PCA9685(i2c, address=0x41)
    pca.frequency = 50

    # Set channel 0 on the second PCA chip to 50% duty cycle
    pca.channels[0].duty_cycle = 0x7FFF
    print("Channel 0 on PCA @ 0x41 set to 50% duty cycle.")

except Exception as e:
    print(f"Error communicating with PCA @ 0x41: {e}")
