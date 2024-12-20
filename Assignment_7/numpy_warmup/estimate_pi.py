import numpy as np


def estimate_pi(N):
    pi_estimate = None
    # --- Your code here 
        # Step 1: Generate random x, y coordinates in the range [-0.5, 0.5]
    x = np.random.uniform(-0.5, 0.5, N)
    y = np.random.uniform(-0.5, 0.5, N)
    
    # Step 2: Check if points lie inside the circle (x^2 + y^2 <= 0.25)
    inside_circle = x**2 + y**2 <= 0.25
    
    # Step 3: Count the number of points inside the circle
    Ncircle = np.sum(inside_circle)
    
    # Step 4: Estimate the value of pi
    pi_estimate = 4 * Ncircle / N
    
    # ---

    return pi_estimate


if __name__ == "__main__":
    N = 1000
    approx_pi = estimate_pi(N)
    print(f'Estimate of pi is {approx_pi}')