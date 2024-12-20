import numpy as np
from ga_trajopt import GATrajectoryOptimizer


class GATrajectoryOptimizerSolution(GATrajectoryOptimizer):

    def fitness(self, x):
        fit = 0
        # Compute cumulative sum of positions
        positions = np.concatenate((self.start.reshape(1, 2), x))
        positions = np.cumsum(positions, axis=0)
        
        # Terminal position error
        xT = positions[-1]
        terminal_error = -np.linalg.norm(xT - self.goal)**2
        
        # Sum of squared step sizes
        step_sizes = np.sum(np.linalg.norm(x, axis=1)**2)
        
        # Obstacle penalties
        obstacle_penalty = 0
        for pos in positions:
            for center, radius in zip(self.obstacle_centres, self.obstacle_radii):
                # Check if point is inside obstacle
                distance = np.linalg.norm(pos - center)
                if distance <= radius:
                    obstacle_penalty += 100
        
        fit = terminal_error - step_sizes - obstacle_penalty
        return fit

    def crossover(self, parent1, parent2, crossover_point):
        # Initialize children with same shape as parents
        child1 = np.zeros_like(parent1)
        child2 = np.zeros_like(parent2)
        
        # First child takes parent1's first part and parent2's second part
        child1[:crossover_point] = parent1[:crossover_point]
        child1[crossover_point:] = parent2[crossover_point:]
        
        # Second child takes parent2's first part and parent1's second part
        child2[:crossover_point] = parent2[:crossover_point]
        child2[crossover_point:] = parent1[crossover_point:]
        
        return child1, child2

    def select_children(self, child, parent):
        # Compute fitness for both parent and child
        child_fitness = self.fitness(child)
        parent_fitness = self.fitness(parent)
        
        # Determine which has better fitness
        if child_fitness > parent_fitness:
            best = child
            best_fitness = child_fitness
            worst = parent
            worst_fitness = parent_fitness
        else:
            best = parent
            best_fitness = parent_fitness
            worst = child
            worst_fitness = child_fitness
        
        # Select best with probability select_best_child_p
        if np.random.rand() < self.params['select_best_child_p']:
            chosen = best
            fitness = best_fitness
        else:
            chosen = worst
            fitness = worst_fitness
            
        return chosen, fitness


if __name__ == "__main__":
    # GA path planning

    # Setup start, goal and spherical obstacles
    goal = np.array([1.0, 1.0])
    start = np.array([0.0, 0.0])
    obstacle_centres = np.array([
        [0.5, 0.2],
        [0.2, 0.8]
    ])
    obstacle_radii = np.array([0.5, 0.15])

    # Solver parameters
    N = 500
    T = 20
    params = {
        'N': 500,
        'iters': 200,
        'cross_over_p': 0.5,
        'mutate_p': 0.5,
        'select_best_parent_p': 0.9,
        'select_best_child_p': 0.9
    }

    solver = GATrajectoryOptimizerSolution(start, goal, obstacle_radii, obstacle_centres, T, params)
    # Solve to get best trajectory and plot
    best = solver.solve()
    solver.plot_trajectory(best)