import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from hexapod_kinematics_py.kinematics import HexapodKinematics

class IKNode(Node):
    def __init__(self):
        super().__init__('inverse_kinematics_node')
        self.kinematics = HexapodKinematics()

        self.leg_commands_sub = self.create_subscription(
            Float32MultiArray, 'leg_commands', self.leg_commands_callback, 10)
        self.joint_angles_pub = self.create_publisher(
            Float32MultiArray, 'joint_angles', 10)

        self.get_logger().info("Inverse Kinematics Node initialized.")

    def leg_commands_callback(self, msg):
        targets = np.array(msg.data).reshape(-1, 3)  # Reshape into N x 3 array
        joint_angles = []

        for i, target in enumerate(targets):
            try:
                angles = self.kinematics.inverse_kinematics(target)
                joint_angles.extend(angles)
                self.get_logger().info(f"Leg[{i}] Target: {target}, Angles: {angles}")
            except ValueError as e:
                self.get_logger().error(f"Leg[{i}] IK Error: {e}")

        # Publish joint angles
        joint_angles_msg = Float32MultiArray(data=joint_angles)
        self.joint_angles_pub.publish(joint_angles_msg)

def main(args=None):
    rclpy.init(args=args)
    node = IKNode()
    rclpy.spin(node)
    rclpy.shutdown()
