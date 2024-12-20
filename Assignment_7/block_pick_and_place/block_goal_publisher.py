import lcm
import time
import numpy as np
from block_goal_msg import block_goal_t

def read_goal(fname):
    # Initialize empty lists for translation and rotation
    translation = []
    rotation = []
    
    # Read the file line by line
    with open(fname, 'r') as file:
        # Read translation (first line)
        translation = [float(x) for x in file.readline().strip().split()]
        
        # Read rotation matrix (next three lines)
        for _ in range(3):
            row = [float(x) for x in file.readline().strip().split()]
            rotation.append(row)
    
    # Create 4x4 homogeneous transformation matrix
    transform = np.eye(4)
    transform[:3, :3] = np.array(rotation)  # Set rotation part
    transform[:3, 3] = np.array(translation)  # Set translation part
    
    return transform
    

def publish_transform(transform):
    lc = lcm.LCM()
    msg = block_goal_t()
    # Convert numpy array to 4x4 nested list
    msg.transform = [[float(transform[i,j]) for j in range(4)] for i in range(4)]
    # Set timestamp (optional but good practice)
    msg.timestamp = int(time.time() * 1000000)
    lc.publish("BLOCK_GOAL", msg.encode())

if __name__ == "__main__":
    transform = read_goal('inputs1.txt')
    
    while True:
        publish_transform(transform)
        time.sleep(0.1)