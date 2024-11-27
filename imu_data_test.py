from smbus2 import SMBus

IMU_I2C_ADDRESS = 0x6a  # Replace with your IMU's actual address
bus = SMBus(1)

try:
    # Example: Read WHO_AM_I register (commonly at 0x75 for many IMUs like MPU6050)
    who_am_i = bus.read_byte_data(IMU_I2C_ADDRESS, 0x75)
    print(f"WHO_AM_I: {hex(who_am_i)}")

    # Read accelerometer data (start register might vary, e.g., 0x3B for MPU6050)
    accel_data = bus.read_i2c_block_data(IMU_I2C_ADDRESS, 0x3B, 6)
    accel_x = (accel_data[0] << 8) | accel_data[1]
    accel_y = (accel_data[2] << 8) | accel_data[3]
    accel_z = (accel_data[4] << 8) | accel_data[5]
    print(f"Accel X: {accel_x}, Y: {accel_y}, Z: {accel_z}")

except Exception as e:
    print(f"Error: {e}")
finally:
    bus.close()
