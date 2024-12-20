#include "robots.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Define compareBotsByName function
bool compareBotsByName(const Robot &a, const Robot &b) {
    return a.getName() < b.getName();
}

int main() {
    ifstream botfile("bots.txt");
    ifstream jobfile("jobs.txt");
    ofstream outfile("output.txt");

    queue<Robot> bot_queue;

    // Read robots from bots.txt into bot_queue
    string bot_name, bot_type;
    while (botfile >> bot_name >> bot_type) {
        bot_queue.push(Robot(bot_name, bot_type));
    }

    // Check if there are no robots
    if (bot_queue.empty()) {
        cerr << "No robots available." << endl;
        return 1;
    }

    // Read jobs from jobs.txt and assign them
    int job_id;
    string job_name;
    while (jobfile >> job_id >> job_name) {
        bool job_assigned = false;
        int queue_size = bot_queue.size();

        for (int i = 0; i < queue_size && !job_assigned; ++i) {
            Robot current_bot = bot_queue.front();
            bot_queue.pop();

            // Check if robot can do the job
            auto it = TYPES2JOBS.find(current_bot.getType());
            if (it != TYPES2JOBS.end() && find(it->second.begin(), it->second.end(), job_name) != it->second.end()) {
                current_bot.assignJob(job_id);
                job_assigned = true;
            }

            // Move robot to back of the line
            bot_queue.push(current_bot);
        }

        // Check if no robot could be assigned the job (should not happen per problem statement)
        if (!job_assigned) {
            cerr << "No robot could be assigned to job ID: " << job_id << endl;
        }
    }

    vector<Robot> bots;

    // Transfer robots from queue to vector
    while (!bot_queue.empty()) {
        bots.push_back(bot_queue.front());
        bot_queue.pop();
    }

    // Sort robots alphabetically by name
    sort(bots.begin(), bots.end(), compareBotsByName);

    // Print the sorted robots and their jobs to output.txt and console
    for (const auto &bot : bots) {
        cout << bot.print(false);
        outfile << bot.print(false);
    }

    return 0;
}
