class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int start =  0, end = 0;
        int length = 0, maxLength = 0;
        while (end < s.size())
        {
            char tmp = s[end];
            for (int i = start; i < end; i++)
            {
                if (s[i] == tmp)
                {
                    start = i + 1;
                    length = end - start;
                    break;
                }
            }
            end++;
            length++;
            maxLength = max(length, maxLength);
        }
        return maxLength;
    }
};
