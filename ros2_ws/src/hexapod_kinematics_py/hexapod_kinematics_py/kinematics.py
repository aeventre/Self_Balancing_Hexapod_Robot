import numpy as np

class HexapodKinematics:
    def __init__(self):
        # Define the link lengths based on your robot's dimensions
        self.coxa_length = 0.044  # Coxa length in meters
        self.femur_length = 0.08  # Femur length in meters
        self.tibia_length = 0.155  # Tibia length in meters

    def forward_kinematics(self, angles):
        """
        Compute the Cartesian foot position given joint angles.
        :param angles: [coxa_angle, femur_angle, tibia_angle]
        :return: [x, y, z] foot position
        """
        coxa_angle, femur_angle, tibia_angle = angles

        # Compute the x, y, z position of the foot
        x = (self.coxa_length +
             self.femur_length * np.cos(femur_angle) +
             self.tibia_length * np.cos(femur_angle + tibia_angle))
        z = (-self.femur_length * np.sin(femur_angle) -
             self.tibia_length * np.sin(femur_angle + tibia_angle))
        y = 0  # No offset in the y-direction for single leg calculation

        return [x, y, z]

    def inverse_kinematics(self, target_position):
        """
        Compute the joint angles for a given target foot position.
        :param target_position: [x, y, z] desired foot position
        :return: [coxa_angle, femur_angle, tibia_angle]
        """
        x, _, z = target_position

        # Distance from coxa joint to target point in the x-z plane
        r = np.sqrt(x**2 + z**2)

        # Law of cosines to find tibia angle
        cos_tibia = (r**2 - self.femur_length**2 - self.tibia_length**2) / \
                    (2 * self.femur_length * self.tibia_length)
        tibia_angle = np.arccos(np.clip(cos_tibia, -1.0, 1.0))

        # Law of cosines to find femur angle
        cos_femur = (r**2 + self.femur_length**2 - self.tibia_length**2) / \
                    (2 * r * self.femur_length)
        femur_angle = np.arccos(np.clip(cos_femur, -1.0, 1.0))

        # Adjust femur angle based on target position
        femur_angle = np.arctan2(-z, x) - femur_angle

        # Coxa angle
        coxa_angle = 0  # Assuming single leg calculation

        return [coxa_angle, femur_angle, tibia_angle]
