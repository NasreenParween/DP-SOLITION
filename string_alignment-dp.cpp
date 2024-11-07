#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


int editDistance(const string &s1, const string &s2) {
    int m = s1.length();
    int n = s2.length();

    // DP table to store the edit distance between prefixes of s1 and s2
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Initialize base cases
    for (int i = 0; i <= m; ++i) dp[i][0] = i; // Deletion cost
    for (int j = 0; j <= n; ++j) dp[0][j] = j; // Insertion cost

    // Fill DP table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // Characters match, no operation
            } else {
                dp[i][j] = 1 + min({ dp[i - 1][j],   // Deletion
                                          dp[i][j - 1],   // Insertion
                                          dp[i - 1][j - 1] }); // Substitution
            }
        }
    }

    return dp[m][n]; // Minimum edit distance between the entire s1 and s2
}

int main() {
    string s1 = "kitten";
    string s2 = "sitting";
    cout << "Minimum Edit Distance: " << editDistance(s1, s2) <<endl;
    return 0;
}
