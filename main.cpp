#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// Function to calculate the dynamic programming table for the LCS
// Parameters:
//   str1: The first input string.
//   str2: The second input string.
// Returns:
//   A 2D vector representing the dynamic programming table.
std::vector<std::vector<size_t>> calculateDPTable(const std::string& str1, const std::string& str2)
{
    // Get the length of the first and second string
    const size_t lenStr1 = str1.length();
    const size_t lenStr2 = str2.length();

    // Create a 2D dynamic programming table to store the intermediate results
    std::vector<std::vector<size_t>> dp(lenStr1 + 1, std::vector<size_t>(lenStr2 + 1));

    // Initialize the first row and first column of the DP table to zeros
    for (size_t i = 0; i < lenStr1 + 1; i++)
    {
        dp[i][0] = 0;
    }
    for (size_t j = 0; j < lenStr2 + 1; j++)
    {
        dp[0][j] = 0;
    }

    // Fill the DP table
    for (size_t i = 1; i < lenStr1 + 1; i++)
    {
        for (size_t j = 1; j < lenStr2 + 1; j++)
        {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
        }
    }

    return dp;
}

// Function to find the longest common subsequence (LCS) using backtracking
// Parameters:
//   dp: Dynamic programming table storing the intermediate results.
//   str1: The first input string.
//   str2: The second input string.
//   x: Current position in the first string.
//   y: Current position in the second string.
// Returns:
//   The longest common subsequence between str1 and str2.
std::string backtrackLongestCommonSubsequence(const std::vector<std::vector<size_t>>& dp, const std::string& str1, const std::string& str2, size_t x, size_t y)
{
    // Base case: If one of the strings is empty, return an empty string
    if (x == 0 || y == 0)
        return "";

    // If the last characters of both strings match, include it in the LCS and move diagonally
    if (str1[x - 1] == str2[y - 1])
        return backtrackLongestCommonSubsequence(dp, str1, str2, x - 1, y - 1) + str1[x - 1];

    // If the characters don't match, move to the cell with the maximum LCS value
    if (dp[x][y - 1] > dp[x - 1][y])
        return backtrackLongestCommonSubsequence(dp, str1, str2, x, y - 1);

    
    return backtrackLongestCommonSubsequence(dp, str1, str2, x - 1, y);
}

// Function to calculate the Longest Common Subsequence (LCS) of two strings
// Parameters:
//   str1: The first input string.
//   str2: The second input string.
// Returns:
//   The longest common subsequence between str1 and str2.
std::string findLongestCommonSubsequence(const std::string& str1, const std::string& str2)
{
    const size_t lenStr1 = str1.length();
    const size_t lenStr2 = str2.length();

    // Calculate the dynamic programming table for LCS
    std::vector<std::vector<size_t>> dp = calculateDPTable(str1, str2);

    // Use the DP table to find the LCS using backtracking
    return backtrackLongestCommonSubsequence(dp, str1, str2, lenStr1, lenStr2);
}

int main(int argc, char** argv)
{
    // Ensure that the user's input is valid, and display a straightforward help message if it is invalid.
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <string1> <string2>" << std::endl;
        std::cout << "This program calculates the Longest Common Subsequence (LCS) between two strings." << std::endl;
        return -1;
    }

    // Calculate the Longest Common Subsequence (LCS) of the two input strings
    std::cout << findLongestCommonSubsequence(argv[1], argv[2]);

    return 0;
}
