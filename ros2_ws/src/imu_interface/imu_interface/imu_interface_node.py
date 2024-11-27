import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from smbus2 import SMBus

IMU_I2C_ADDRESS = 0x6A  # Default I2C address for LSM6DSO32

class IMUInterface(Node):
    def __init__(self):
        super().__init__('imu_interface_node')
        self.imu_publisher = self.create_publisher(Imu, 'imu/data_raw', 10)

        # Initialize I2C
        self.bus = SMBus(1)
        if not self.initialize_imu():
            self.get_logger().error('Failed to initialize IMU!')
            rclpy.shutdown()
            return

        self.get_logger().info('IMU initialized successfully.')

        # Timer to publish IMU data at 50 Hz
        self.timer = self.create_timer(0.02, self.publish_imu_data)

    def initialize_imu(self):
        try:
            # Verify WHO_AM_I
            who_am_i = self.bus.read_byte_data(IMU_I2C_ADDRESS, 0x0F)
            if who_am_i != 0x6C:
                self.get_logger().error(f'Unexpected WHO_AM_I value: {hex(who_am_i)}')
                return False

            # Configure accelerometer: 104 Hz, ±4g
            self.bus.write_byte_data(IMU_I2C_ADDRESS, 0x10, 0x50)
            # Configure gyroscope: 104 Hz, ±250 dps
            self.bus.write_byte_data(IMU_I2C_ADDRESS, 0x11, 0x50)

            return True
        except Exception as e:
            self.get_logger().error(f'IMU initialization failed: {e}')
            return False

    def publish_imu_data(self):
        try:
            # Read accelerometer data
            accel_x = self.read_raw_data(0x28)
            accel_y = self.read_raw_data(0x2A)
            accel_z = self.read_raw_data(0x2C)

            # Read gyroscope data
            gyro_x = self.read_raw_data(0x22)
            gyro_y = self.read_raw_data(0x24)
            gyro_z = self.read_raw_data(0x26)

            # Scale raw data to physical units
            accel_x_g = accel_x * 0.122 / 1000  # ±4g range
            accel_y_g = accel_y * 0.122 / 1000
            accel_z_g = accel_z * 0.122 / 1000
            gyro_x_dps = gyro_x * 0.07  # ±250 dps range
            gyro_y_dps = gyro_y * 0.07
            gyro_z_dps = gyro_z * 0.07

            # Populate and publish Imu message
            imu_msg = Imu()
            imu_msg.header.stamp = self.get_clock().now().to_msg()
            imu_msg.header.frame_id = 'imu_link'

            imu_msg.linear_acceleration.x = accel_x_g
            imu_msg.linear_acceleration.y = accel_y_g
            imu_msg.linear_acceleration.z = accel_z_g

            imu_msg.angular_velocity.x = gyro_x_dps
            imu_msg.angular_velocity.y = gyro_y_dps
            imu_msg.angular_velocity.z = gyro_z_dps

            self.imu_publisher.publish(imu_msg)
        except Exception as e:
            self.get_logger().error(f'Failed to read IMU data: {e}')

    def read_raw_data(self, reg):
        try:
            low = self.bus.read_byte_data(IMU_I2C_ADDRESS, reg)
            high = self.bus.read_byte_data(IMU_I2C_ADDRESS, reg + 1)
            value = (high << 8) | low
            return value - 65536 if value > 32767 else value
        except Exception as e:
            self.get_logger().error(f'Error reading register {hex(reg)}: {e}')
            return 0

def main(args=None):
    rclpy.init(args=args)
    imu_interface = IMUInterface()
    try:
        rclpy.spin(imu_interface)
    except KeyboardInterrupt:
        pass
    finally:
        imu_interface.destroy_node()
        rclpy.shutdown()
