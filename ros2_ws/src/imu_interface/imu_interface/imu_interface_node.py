import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from smbus2 import SMBus

IMU_I2C_ADDRESS = 0x68  # Replace with your IMU address

class IMUInterface(Node):
    def __init__(self):
        super().__init__('imu_interface_node')

        # Publisher for IMU data
        self.imu_publisher = self.create_publisher(Imu, 'imu/data_raw', 10)

        # Timer to publish data at regular intervals (20 Hz)
        self.timer = self.create_timer(0.05, self.publish_imu_data)

        # Initialize I2C communication
        self.bus = SMBus(1)  # Use I2C bus 1 (or adjust as needed)
        if not self.initialize_imu():
            self.get_logger().error('Failed to initialize IMU!')
            rclpy.shutdown()
        else:
            self.get_logger().info('IMU initialized successfully.')

    def initialize_imu(self):
        try:
            # Example: Wake up IMU by writing 0x00 to PWR_MGMT_1 (register 0x6B)
            self.bus.write_byte_data(IMU_I2C_ADDRESS, 0x6B, 0x00)
            return True
        except Exception as e:
            self.get_logger().error(f'IMU initialization failed: {e}')
            return False

    def publish_imu_data(self):
        try:
            # Read accelerometer data (6 bytes starting at 0x3B)
            accel_data = self.bus.read_i2c_block_data(IMU_I2C_ADDRESS, 0x3B, 6)
            accel_x = self._combine_bytes(accel_data[0], accel_data[1])
            accel_y = self._combine_bytes(accel_data[2], accel_data[3])
            accel_z = self._combine_bytes(accel_data[4], accel_data[5])

            # Create and populate Imu message
            imu_msg = Imu()
            imu_msg.header.stamp = self.get_clock().now().to_msg()
            imu_msg.header.frame_id = 'imu_link'

            # Fill linear acceleration data
            imu_msg.linear_acceleration.x = accel_x / 16384.0  # Example scale factor
            imu_msg.linear_acceleration.y = accel_y / 16384.0
            imu_msg.linear_acceleration.z = accel_z / 16384.0

            # Publish the message
            self.imu_publisher.publish(imu_msg)
        except Exception as e:
            self.get_logger().error(f'Failed to read IMU data: {e}')

    @staticmethod
    def _combine_bytes(msb, lsb):
        """Combine two bytes to form a signed 16-bit integer."""
        value = (msb << 8) | lsb
        return value - 65536 if value > 32767 else value


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


if __name__ == '__main__':
    main()
