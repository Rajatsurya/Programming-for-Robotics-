#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

using State = vector<int>;  // defines the type State to be a vector of ints
using Action = vector<int>;  // defines the type Action to be a vector of ints

// Function to print out a state to the given stream
void printState(const State& state, ostream & stream){
    for (size_t i = 0; i < state.size(); ++i) {
        stream << state[i];
        if (i < state.size() - 1) {
            stream << " ";  // Separate elements with a space
        }
    }
    stream << endl;  // End the line after printing the state
}

// Dynamics function to calculate the next state
State dynamics(const State& state, const Action& action) {
    State next_state(state.size());
    for (int j = 0; j < state.size(); j++) {
        next_state[j] = state[j] + action[j];
    }
    return next_state;
}

int main() {
    ifstream policyfile("policy.txt");
    ifstream rolloutfile("rollout.txt");
    ofstream outputfile("output.txt");

    const int StateSize = 2;
    const int ActionSize = 2;

    State key(StateSize);  // State (x, y)
    Action value(ActionSize);  // Action (dx, dy)
    map<State, Action> policy;

    // Read the policy file information into std::pair objects,
    // insert each std::pair into the map
    while (policyfile >> key[0] >> key[1] >> value[0] >> value[1]) {
        policy[key] = value;
    }

        // Optional: Print out the policy to cout to ensure it's read correctly
    for (const auto& pair : policy) {
        cout << "State: ";
        printState(pair.first, cout);
        cout << "Action: ";
        printState(pair.second, cout);
    }

    // Read the rollout file to get the start state and number of steps
    State current_state(StateSize);
    int num_steps;
    rolloutfile >> current_state[0] >> current_state[1] >> num_steps;
    rolloutfile.close();

    // Write the initial state to the output file
    printState(current_state, outputfile);

    // Execute the rollout for the specified number of steps (0 to num_steps)
    for (int step = 0; step < num_steps; ++step) {
        if (policy.find(current_state) == policy.end()) {
            cerr << "State " << current_state[0] << " " << current_state[1] << " is not in policy, terminating." << endl;
            return 1;  // Exit if state is not in the policy
        }
        Action action = policy[current_state];  // Get the action from the policy
        current_state = dynamics(current_state, action);  // Calculate the next state
        printState(current_state, outputfile);  // Write the next state to the output file
    }

    return 0;
}
