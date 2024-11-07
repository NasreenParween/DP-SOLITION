//weightedIntervalScheduling
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an interval with a start time, end time, and weight
struct Interval {
    int start, end, weight;
};

// Comparator to sort intervals by end time
bool compareByEnd(const Interval &a, const Interval &b) {
    return a.end < b.end;
}

// Function to find the latest non-overlapping interval
int latestNonOverlapping(const vector<Interval> &intervals, int index) {
    int low = 0, high = index - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (intervals[mid].end <= intervals[index].start) {
            if (intervals[mid + 1].end <= intervals[index].start)
                low = mid + 1;
            else
                return mid;
        } else {
            high = mid - 1;
        }
    }
    return -1; // No compatible interval found
}

// Function to find the maximum weight using DP
int weightedIntervalScheduling(const vector<Interval> &intervals) {
    int n = intervals.size();
    if (n == 0) return 0;

    // Sort intervals by end time
    vector<Interval> sortedIntervals = intervals;
    sort(sortedIntervals.begin(), sortedIntervals.end(), compareByEnd);

    // DP array to store the maximum weight up to each interval
    vector<int> dp(n, 0);
    dp[0] = sortedIntervals[0].weight;

    for (int i = 1; i < n; ++i) {
        // Include the current interval
        int includeWeight = sortedIntervals[i].weight;
        int prevIndex = latestNonOverlapping(sortedIntervals, i);
        if (prevIndex != -1) {
            includeWeight += dp[prevIndex];
        }

        // Exclude the current interval
        int excludeWeight = dp[i - 1];

        // Take the maximum of including or excluding the interval
        dp[i] = max(includeWeight, excludeWeight);
    }

    return dp[n - 1];
}

int main() {
    vector<Interval> intervals = {
        {1, 3, 5}, {2, 5, 6}, {4, 6, 5}, {6, 7, 4}, {5, 8, 11}, {7, 9, 2}
    };
    cout << "Maximum weight of non-overlapping intervals: "<< weightedIntervalScheduling(intervals) <<endl;
    return 0;
}