import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/alec/Documents/SpiderBot/ros2_ws/install/servo_control'
