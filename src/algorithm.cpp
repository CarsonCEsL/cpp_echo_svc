//
// Created by Carson on 2026/3/12.
//

#include "algorithm.h"
#include <iostream>
#include <sstream>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {
    }

    ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode *next) : val(x), next(next) {
    }
};

bool isPalindrome(ListNode *head) {
    vector<int> num;
    while (head != nullptr) {
        num.push_back(head->val);
        head = head->next;
    }

    int left = 0, right = num.size() - 1;
    while (left <= right) {
        if (num[left] != num[right]) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

ListNode *reverseListNode(ListNode *head) {
    ListNode *pre = nullptr;
    ListNode *cur = head;
    while (cur != nullptr) {
        ListNode *tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    return pre;
}

bool isPalindrome2(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *tmp = reverseListNode(slow);
    while (tmp != nullptr) {
        if (tmp->val != head->val) {
            return false;
        }
        tmp = tmp->next;
        head = head->next;
    }


    return true;
}

int majorityElement(vector<int> &nums) {
    unordered_map<int, int> nums_map;
    int result = 0, cnt = 0;
    for (auto i: nums) {
        nums_map[i]++;
        if (nums_map[i] > cnt) {
            result = i;
            cnt = nums_map[i];
        }
    }

    // int max = 0;
    // int result = nums[0];
    // for (auto i : nums_map) {
    //     if (i.second >= max) {
    //         max = i.second;
    //         result = i.first;
    //     }
    // }

    return result;
}

int majorityElement2(vector<int> &nums) {
    int current = 0, count = 0;
    for (auto num: nums) {
        if (count == 0) {
            current = num;
        }

        if (num == current) {
            count++;
        } else {
            count--;
        }
    }

    return current;
}

vector<int> findDisappearedNumbers(vector<int> &nums) {
    vector<int> result;
    unordered_set<int> nums_set;
    for (auto num: nums) {
        nums_set.insert(num);
    }

    for (int i = 1; i <= nums.size(); i++) {
        if (nums_set.find(i) == nums_set.end()) {
            result.push_back(i);
        }
    }

    return result;
}

vector<int> findDisappearedNumbers2(vector<int> &nums) {
    vector<int> result;
    for (size_t i = 0; i < nums.size(); i++) {
        int idx = abs(nums[i]) - 1;
        int &tmp = nums[idx];
        if (tmp > 0) {
            tmp = -tmp;
        }
    }

    for (size_t i = 0; i < nums.size(); i++) {
        if (nums[i] > 0) {
            result.push_back(i + 1);
        }
    }

    return result;
}

int test0() {
    int numRows = 6;
    // dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j], j<= i
    vector<vector<int> > vec(numRows);
    for (int i = 0; i < vec.size(); i++) {
        vec[i].resize(i + 1);
        vec[i][0] = 1;
        vec[i][i] = 1;
        for (int j = 1; j < i; j++) {
            vec[i][j] = vec[i - 1][j - 1] + vec[i - 1][j];
        }
    }

    for (auto i: vec) {
        for (auto j: i) {
            cout << j << " ";
        }
        cout << "" << endl;
    }
}

int maxArea(vector<int> &height) {
    if (height.size() < 2) {
        return 0;
    }
    int left = 0, right = height.size() - 1;
    int result = (right - left) * min(height[left], height[right]);

    while (left < right) {
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
        result = max(result, (right - left) * min(height[left], height[right]));
    }

    return result;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int cur = m + n - 1;
    int p = m - 1;
    int q = n - 1;
    while (q >= 0 && p >= 0) {
        if (nums1[p] >= nums2[q]) {
            nums1[cur] = nums1[p];
            p--;
            cur--;
        } else {
            nums1[cur] = nums2[q];
            q--;
            cur--;
        }
    }
    if (p < 0) {
        while (cur >= 0) {
            nums1[cur] = nums2[q];
            q--;
            cur--;
        }
    }
}

int removeElement(vector<int>& nums, int val) {
    int slow = 0, fast = 0;
    for (; fast < nums.size(); fast++) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    return slow;
}

int removeDuplicates(vector<int>& nums) {
    int slow = 0, fast = 1;
    while (fast < nums.size()) {
        if (nums[slow] == nums[fast]) {
            fast++;
        } else {
            nums[++slow] = nums[fast];
            fast++;
        }
    }

    return slow + 1;
}

void rotateFunc(vector<int> &nums, int left, int right) {
    int tmp = 0;
    while (left < right) {
        tmp = nums[left];
        nums[left] = nums[right];
        nums[right] = tmp;
        left++;
        right--;
    }
}

void rotate(vector<int> &nums, int k) {
    if (k > nums.size()) {
        k %= nums.size();
    }

    rotateFunc(nums, 0 ,nums.size() - 1);
    rotateFunc(nums, 0, k -1);
    rotateFunc(nums, k, nums.size() - 1);
}

int maxProfit(vector<int>& prices) {
    int minNum = INT32_MAX;
    int result = 0;
    for (int i = 0; i < prices.size(); i++) {
        minNum = min(minNum, prices[i]);
        result = max(result, prices[i] - minNum);
    }

    return result;
}

bool canJump(vector<int>& nums) {
    int maxReach = 0;
    for (int i = 0; i < nums.size(); i++) {
        maxReach = max(maxReach, nums[i] + i);
        if (maxReach >= nums.size() - 1) {
            return true;
        }
    }

    return false;
}

int jump(vector<int>& nums) {
    int cnt = 0;
    int next = 0;
    int maxResult = INT32_MIN;
    for (int i = 0; i < nums.size();) {
        for (int j = i + 1; j < i + nums[i] && j < nums.size(); j++) {
            if (nums[j] + j > maxResult) {
                maxResult = nums[j] + j;
                next = j;
            }
        }
        cnt += 1;
        if (nums[i] + i >= nums.size() - 1) {
            return cnt;
        }
        i = next;
    }

    return cnt;
}

class RandomizedSet {
public:
    RandomizedSet() {
        srand((unsigned)time(nullptr));
    }

    bool insert(int val) {
        if (indices.find(val) != indices.end()) {
            return false;
        }
        // 不存在，把新元素插入到数组的最后，然后更新map
        int index = nums.size();
        nums.push_back(val);
        indices[val] = index;
        return true;
    }

    bool remove(int val) {
        if (indices.find(val) == indices.end()) {
            return false;
        }
        int index = indices[val];
        nums[index] = nums[nums.size() - 1];
        indices[nums[index]] = index;
        nums.pop_back();
        indices.erase(val);
        return true;
    }

    int getRandom() {
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }
private:
    vector<int> nums;
    unordered_map<int, int> indices;
};

vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    vector<int> pre(n), later(n);
    pre[0] = later[n - 1] = 1;
    //计算前缀
    for (int i = 1; i < n; i++) {
        pre[i] = pre[i - 1] * nums[i - 1];
    }
    for (int i = n - 2; i >= 0; i--) {
        later[i] = later[i + 1] * nums[i + 1];
    }
    for (int i = 0; i < n; i++) {
        ans[i] = pre[i] * later[i];
    }

    return ans;
}

bool wordPattern(string pattern, string s) {
    vector<string> str;
    string word;
    istringstream iss(s);

    while (iss >> word) {
        str.push_back(word);
    }
    if (pattern.size() != str.size()) return false;
    unordered_map<char, string> ctos;
    unordered_map<string, char> stoc;
    for (int i = 0; i < pattern.size(); i++) {
        if ((ctos.find(pattern[i]) != ctos.end() && ctos[pattern[i]] != str[i])
            || (stoc.find(str[i]) != stoc.end() && stoc[str[i]] != pattern[i])) {
            return false;
        }
        ctos[pattern[i]] = str[i];
        stoc[str[i]] = pattern[i];
    }

    return true;
}

int lengthOfLastWord(string s) {
    int result = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == ' ') {
            continue;
        }
        for (; i >= 0; i--) {
            if (s[i] == ' ') {
                return result;
            }
            result++;
        }
    }

    return result;
}

string longestCommonPrefix(vector<string>& strs) {
    if (strs.size() == 0) return "";
    for (int i = 0; i < strs[0].size(); i++) {
        for (int j = 1; j < strs.size(); j++) {
            if (i < strs[j].size() && strs[j][i] == strs[0][i]) {
                continue;
            }
            return strs[0].substr(0, i);
        }
    }

    return strs[0];
}

bool isPalindrome(string s) {
    vector<char> tmp;
    for (char i : s) {
        if ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'z')) {
            tmp.push_back(i);
        } else if (i >= 'A' && i <= 'Z') {
            tmp.push_back(static_cast<char>(i + 32));
        }
    }
    cout << "hello" << endl;
    cout << string(tmp.begin(), tmp.end()) << endl;
    int left = 0;
    int right = tmp.size() - 1;
    while (left <= right) {
        if (tmp[left] == tmp[right]) {
            left++;
            right--;
        } else {
            cout << "1" << endl;
            return false;
        }
    }

    return true;
}

int countOnes(int n) {
    int count = 0;
    while (n > 0) {
        n = n & (n - 1);
        count++;
    }

    return count;
}

vector<int> countBits(int n) {
    vector<int> ans;
    ans.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        ans[i] = countOnes(i);
    }

    return ans;
}

int main() {
    vector<string> test = {"flower", "flo", "flo"};
    // cout << "testcase" << endl;
    isPalindrome("A man, a plan, a canal: Panama");
}
