#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int searchInsert(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            return mid;
        }
    }

    return left;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;

    while (left <= right) {
        int p = 0, q = 0;
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            p = mid - 1;
            q = mid + 1;
            while (p >= 0 && nums[p] == target) {
                p--;
            }
            while (q < nums.size() && nums[q] == target) {
                q++;
            }

            return vector<int>{p + 1, q - 1};
        }
    }

    return vector<int>{-1, -1};
}

int mySqrt(int x) {
    if (x == 0) return 0;
    int left = 1, right = x / 2;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (x / mid == mid) {
            return mid;
        } else if (x / mid > mid) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return right;
}

bool isPerfectSquare(int num) {
    if (num == 1) return true;
    int left = 1, right = num / 2;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (num / mid == mid) {
            return true;
        } else if (num / mid > mid) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

int removeElement(vector<int>& nums, int val) {
    int slow = 0, fast = 0;
    for (; fast < nums.size(); fast++) {
        if (nums[fast] == val) {
            nums[slow] = nums[fast];
            slow++;
        }
    }

    return slow;
}

int removeDuplicates(vector<int>& nums) {
    int slow = 0, fast = 0;
    for (; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            nums[++slow] = nums[fast];
        }
    }

    return slow;
}

void moveZeroes(vector<int>& nums) {
    int slow = 0, fast = 0;
    for (; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            nums[slow++] = nums[fast];
        }
    }

    for (; slow < nums.size(); slow++) {
        nums[slow] = 0;
    }
}

vector<char> revertStrToVector(string str) {
    vector<char> vec;
    for (char c : str) {
        vec.push_back(c);
    }

    return vec;
}

int changeVector(vector<char>& vec) {
    int slow = 0, fast = 0;
    for (; fast < vec.size(); fast++) {
        if (vec[fast] != '#') {
            vec[slow++] = vec[fast];
        } else {
            if (slow > 0) {
                slow--;
            }
        }
    }

    return slow;
}

bool backspaceCompare(string s, string t) {
    vector<char> vec = revertStrToVector(s);
    vector<char> vec2 = revertStrToVector(t);
    int num = changeVector(vec);
    int num2 = changeVector(vec2);

    if (num == num2) {
        for (int i = 0; i < num; i++) {
            if (vec[i] != vec2[i]) {
                return false;
            }
        }

        return true;
    }

    return false;
}

vector<int> sortedSquares(vector<int>& nums) {
    vector<int> res(nums.size());
    int left = 0, right = nums.size() - 1;
    int i = nums.size() - 1;
    while (left <= right) {
        if (nums[left] * nums[left] > nums[right] * nums[right]) {
            res[i] = nums[left] * nums[left];
            left++;
        } else {
            res[i] = nums[right] * nums[right];
            right--;
        }
        i--;
    }
}

int minSubArrayLen(int target, vector<int>& nums) {
    int result = INT32_MAX;
    int left = 0;
    int sum = 0;
    int length = 0;
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        while (sum >= target) {
            length = right - left + 1;
            sum -= nums[left++];
            result = result < length ? result : length;
        }
    }

    return result == INT32_MAX ? 0 : result;
}

int totalFruit(vector<int>& nums) {
    int curCount = 0, left = 0, result = 0;
    unordered_map<int, int> typeCount;
    bool isFull = false;
    for (int right = 0; right < nums.size(); right++) {
        if (typeCount.find(nums[right]) == typeCount.end()) {
            if (isFull) {
                // 去除一个元素，加入新元素
                while (typeCount.size() != 1) {
                    --typeCount[nums[left]];
                    if (typeCount[nums[left]] == 0) {
                        typeCount.erase(nums[left]);
                    }
                    left++;
                }
                typeCount[nums[right]]++;
            } else {
                typeCount[nums[right]]++;
                if (typeCount.size() == 2) {
                    isFull = true;
                }
            }
        } else {
            typeCount[nums[right]]++;
        }
        curCount = right - left + 1;
        result = result > curCount ? result : curCount;
    }

    return result;
}

string minWindow(string s, string t) {
    int left = 0;
    int length = INT32_MAX;
    string result = "";
    int count = 0;// 记录S中已包含的t中的字符数，count == t.size()才满足要求返回
    unordered_map<char, int> tCount;
    unordered_map<char, int> sCount;
    for (int right = 0; right < t.size(); right++) {
        tCount[t[right]]++;
    }

    for (int right = 0; right < s.size(); right++) {
        sCount[s[right]]++;
        if (tCount.count(s[right]) != 0 && sCount[s[right]] <= tCount[s[right]]) {
            count++;
        }

        while (left < right && (tCount.count(s[left]) == 0 || sCount[s[left]] > tCount[s[left]])) {
            if (sCount[s[left]] > 0) {
                sCount[s[left]]--;
            }
            left++;
        }

        if (count == t.size() && right - left + 1 < length) {
            length = right - left + 1;
            result = s.substr(left, right - left + 1);
        }
    }

    return result;
}

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n, 0));
    int left = 0, right = n - 1;
    int top = 0, bottom = n - 1;
    int num = 1, end = n * n;
    while (num <= end) {
        for (int i = left; i<= right; i++) {
            res[top][i] = num++;
        }
        top++;
        for (int i = top; i <= bottom; i++) {
            res[i][right] = num++;
        }
        right--;
        for (int i = right; i >= left; i--) {
            res[bottom][i] = num++;
        }
        bottom--;
        for (int i = bottom; i >= top; i--) {
            res[i][left] = num++;
        }
        left++;
    }

    return res;
}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;
    vector<int> res;
    int num = 1, count = matrix.size() * matrix[0].size();
    while (num <= count) {
        for (int i = left; i <= right; i++) {
            res.push_back(matrix[top][i]);
            num++;
        }
        top++;
        for (int i = top; i <= bottom; i++) {
            res.push_back(matrix[i][right]);
            num++;
        }
        right--;
        for (int i = right; i >= left; i--) {
            res.push_back(matrix[bottom][i]);
            num++;
        }
        bottom--;
        for (int i = bottom; i >= top; i--) {
            res.push_back(matrix[i][left]);
            num++;
        }
        left++;
    }

    return res;
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(NULL) {}
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *removeElements(ListNode *head, int val) {
    if (head == NULL) {
        return NULL;
    }
    ListNode *node = new ListNode(0);
    node->next = head;
    ListNode * pre = node;
    ListNode * cur = head;
    while (cur != NULL) {
        if (cur->val == val) {
            pre->next = cur->next;
            ListNode *tmp = cur;
            cur = cur->next;
            delete tmp;
        } else {
            pre = cur;
            cur = cur->next;
        }
    }

    return node->next;
}

class MyLinkedList {
    public:
    struct LinkedNode {
        int val;
        LinkedNode *next;
        LinkedNode(int x) : val(x), next(NULL) {}
    };
    MyLinkedList() {
        _size = 0;
        _node = new LinkedNode(0);
    }

    int get(int index) {
        if (index < 0 || index >= _size) {
            return -1;
        }
        LinkedNode *cur = _node->next;
        while (index-- > 0) {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val) {
        LinkedNode *newNode = new LinkedNode(val);
        newNode->next = _node->next;
        _node->next = newNode;
        _size++;
    }

    void addAtTail(int val) {
        LinkedNode *newNode = new LinkedNode(val);
        if (_size == 0) {
            _node->next = newNode;
        } else {
            LinkedNode *cur = _node->next;
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur ->next = newNode;
        }
        _size++;
    }

    void addAtIndex(int index, int val) {
        if (index < 0 || index > _size) {
            return;
        }
        LinkedNode *newNode = new LinkedNode(val);
        if (_size == 0) {
            _node->next = newNode;
        } else {
            LinkedNode *cur = _node->next;
            LinkedNode *pre = _node;
            while (index-- > 0) {
                pre = cur;
                cur = cur->next;
            }
            newNode->next = cur;
            pre->next = newNode;
        }
        _size++;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= _size) {
            return;
        }

        LinkedNode *cur = _node->next;
        LinkedNode *pre = _node;
        while (index-- > 0) {
            pre = cur;
            cur = cur->next;
        }
        pre->next = cur->next;
        delete cur;
        _size--;
    }

private:
    int _size;
    LinkedNode *_node;
};

ListNode *reverseList(ListNode *head) {
    ListNode *pre = NULL;
    ListNode *cur = head;
    ListNode *tmp = NULL;
    while (cur != NULL) {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    return pre;
}

ListNode *reverseList2(ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    ListNode *newNode = reverseList2(head->next);
    head->next->next = head;
    head->next = NULL;

    return newNode;
}

ListNode *swapPairs(ListNode *head) {
    ListNode *node = new ListNode(0);
    node->next = head;
    ListNode *cur = node;
    while (cur->next != NULL && cur->next->next != NULL) {
        ListNode *tmp = cur->next;
        ListNode *tmp2 = cur->next->next;
        ListNode *tmp3 = cur->next->next->next;

        cur->next = tmp2;
        cur->next->next = tmp;
        cur->next->next->next = tmp3;

        cur = cur->next->next;
    }
    ListNode *result = node->next;
    delete node;
    return result;
}

ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *tmp = head;
    int count = 0;
    int remain = 0;
    while (tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    // cout << count << endl;
    remain = count - n;

    ListNode *node = new ListNode(0);
    node->next = head;
    ListNode *cur = node;
    while (remain-- > 0) {
        cur = cur->next;
    }
    ListNode *newNode = cur->next;
    cur->next = cur->next->next;
    delete newNode;

    return node->next;
}

ListNode *removeNthFromEnd2(ListNode *head, int n) {
    ListNode *fast = head;
    ListNode *newNode = new ListNode(0);
    newNode->next = head;
    ListNode *slow = newNode;
    while (n-- > 0) {
        fast = fast->next;
    }

    while (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
    }

    ListNode *tmp = slow->next;
    slow->next = slow->next->next;
    delete tmp;

    return newNode->next;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (headA == NULL || headB == NULL) {
        return NULL;
    }

    unordered_set<ListNode *> nodesA;
    unordered_set<ListNode *> nodesB;

    while (headA != NULL) {
        nodesA.insert(headA);
        headA = headA->next;
    }

    while (headB != NULL) {
        if (nodesA.find(headB) != nodesA.end()) {
            return headB;
        }
        headB = headB->next;
    }

    return NULL;
}

ListNode *detectCycle(ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            ListNode *tmp1 = fast;
            ListNode *tmp2 = head;
            while (tmp2 != tmp1) {
                tmp2 = tmp2->next;
                tmp1 = tmp1->next;
            }

            return tmp2;
        }
    }

    return NULL;
}

bool isAnagram(string s, string t) {
    vector<char> result(26, 0);
    for (int i = 0; i < s.length(); i++) {
        result[s[i] - 'a']++;
    }
    for (int i = 0; i < t.length(); i++) {
        result[t[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (result[i] != 0) {
            return false;
        }
    }

    return true;
}

bool isAnagram2(string s, string t) {
    unordered_map<char, int> s_map;
    unordered_map<char, int> t_map;
    for (char c : s) {
        s_map[c]++;
    }
    for (char c : t) {
        t_map[c]++;
    }
    for (auto it : s_map) {
        if (t_map.find(it.first) == t_map.end()) {
            return false;
        } else {
            if (s_map[it.first] != t_map[it.first]) {
                return false;
            }
            t_map.erase(it.first);
        }
    }
    return t_map.size() == 0 ? true : false;
}

bool canConstruct(string ransomNote, string magazine) {
    vector<int> result(26, 0);
    for (char c : magazine) {
        result[c - 'a']++;
    }
    for (char c : ransomNote) {
        result[c - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (result[i] < 0) {
            return false;
        }
    }

    return true;
}

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> result;
    for (string s : strs) {
        string tmp = s;
        sort(tmp.begin(), tmp.end());
        result[tmp].push_back(s);
    }

    vector<vector<string>> return_result;
    for (auto it : result) {
        return_result.push_back(it.second);
    }

    return return_result;
}

vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    sort(p.begin(), p.end());
    int length = p.length();
    int left = 0;
    int right = left + length - 1;
    for (; left < s.length() && right < s.length(); left++) {
        string tmp = s.substr(left, length);
        sort(tmp.begin(), tmp.end());
        if (tmp == p) {
            result.push_back(left);
        }
    }

    return result;
}

int maxVowels(string s, int k) {
    int left = 0, right = k - 1;
    int i = left;
    int count = 0;
    while (i <= right) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
            count++;
        }
        i++;
    }
    int max = count;
    while (++right < s.length()) {
        if (s[left] != 'a' && s[left] != 'e' && s[left] != 'i' && s[left] != 'o' && s[left] != 'u') {
            if (s[right] == 'a' || s[right] == 'e' || s[right] == 'i' || s[right] == 'o' || s[right] == 'u') {
                count++;
            }
        } else {
            if (s[right] != 'a' && s[right] != 'e' && s[right] != 'i' && s[right] != 'o' && s[right] != 'u') {
                count--;
            }
        }
        max = max > count ? max : count;
    }

    return max;
}

bool test(unordered_map<char, int> &s_map, unordered_map<char, int> &t_map) {
    for (auto it : s_map) {
        cout << it.first << " " << it.second << endl;
    }
    for (auto it : s_map) {
        cout << it.first << " " << it.second << endl;
        if (t_map.find(it.first) == t_map.end()) {
            cout << "aaaa" << endl;
            return false;
        } else {
            if (t_map[it.first] != it.second) {
                return false;
                cout << "222" << endl;
            }
        }
    }

    cout << "ccc" << endl;
    return true;
}

vector<int> findAnagrams2(string s, string p) {
    int p_length = p.length();
    vector<int> result;
    unordered_map<char, int> p_map;
    unordered_map<char, int> s_map;
    for (char i : p) {
        p_map[i]++;
    }
    int left = 0, right = p_length - 1;
    while (left < p_length) {
        s_map[s[left++]]++;
    }
    left = 0;
    if (s_map == p_map) {
        result.push_back(left);
    }
    right = p_length - 1;
    cout << "sada" << endl;
    for (auto it : s_map) {
        cout << it.first << " " << it.second << endl;
    }
    while (++right < s.length()) {
        s_map[s[left]]--;
        if (s_map[s[left]] == 0) {
            s_map.erase(s[left]);
        }
        s_map[s[right]]++;
        if (s_map == p_map) {
            result.push_back(left + 1);
        }
        left++;
    }

    return result;
}

vector<int> findAnagrams3(string s, string p) {
    int p_length = p.length();
    array<int, 26> cnt_p{};
    array<int, 26> cnt_s{};
    vector<int> result;
    for (char i : p) {
        cnt_p[i - 'a']++;
    }
    int right = 0;
    while (right < s.length()) {
        int left = right + 1 - p_length;
        cnt_s[s[right++] - 'a']++;
        if (left < 0) {
            continue;
        }
        if (cnt_s == cnt_p) {
            result.push_back(left);
        }
        cnt_s[s[left] - 'a']--;
    }

    return result;
}

vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int> result;
    unordered_set<int> s1(nums1.begin(), nums1.end());
    for (auto it : nums2) {
        if (s1.find(it) != s1.end()) {
            result.push_back(it);
        }
    }

    return result;
}

vector<int> intersect2(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> map1;
    vector<int> result;
    for (int i : nums1) {
        map1[i]++;
    }

    for (int i : nums2) {
        if (map1.find(i) != map1.end()) {
            result.push_back(i);
            map1[i]--;
            if (map1[i] == 0) {
                map1.erase(i);
            }
        }
    }

    return result;
}

int getSum(int n) {
    int sum = 0;
    while (n != 0) {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }

    return sum;
}

bool isHappy(int n) {
    unordered_set<int> s1;
    while (1) {
        int sum = getSum(n);
        if (sum == 1) {
            return true;
        }
        if (s1.find(sum) != s1.end()) {
            return false;
        } else {
            s1.insert(sum);
        }
        n = sum;
    }
}

int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    unordered_map<int, int> map1;
    unordered_map<int, int> map2;
    int result = 0;
    for (int i : nums1) {
        for (int j : nums2) {
            map1[i + j]++;
        }
    }

    for (int i : nums3) {
        for (int j : nums4) {
            map2[i + j]++;
        }
    }

    for (auto it : map1) {
        if (map2.find(0 - it.first) != map2.end()) {
            result += it.second * map2[0 - it.first];
        }
    }

    return result;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        int left = i + 1;
        int right = nums.size() - 1;
        if (i > 0 &&  nums[i] == nums[i - 1]) {
            continue;
        }
        while (left < nums.size() && left < right) {
            cout << "i " << i << "left " << left << " , right " << right << endl;
            int tmp = nums[i] + nums[left] + nums[right];
            if (tmp == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            } else if (tmp < 0) {
                left++;
            } else {
                right--;
            }
        }
    }

    return result;
}

void reverseString(vector<char>& s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        left++;
        right--;
    }
}

string reverseStr(string s, int k) {
    int left = 0, right = k - 1;
    int p, q;
    while (right < s.length()) {
        p = left, q = right;
        while (p < q) {
            swap(s[p], s[q]);
            p++;
            q--;
        }
        left += 2 * k;
        right += 2 * k;
    }
    right = s.size() - 1;
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }

    return s;
}

string reverseWords(string s) {
    int right = s.size() - 1;
    vector<char> result;

    while (right >= 0) {
        if (s[right] == ' ') {
            right--;
        } else {
            break;
        }
    }

    while (right > 0) {
        if (s[right] == ' ' && s[right - 1] == ' ') {
            right--;
        } else {
            result.push_back(s[right]);
            right--;
        }
    }

    int p = 0, q = 1;
    int tmp;
    while (q < result.size()) {
        while (q < result.size() && result[q] != ' ') {
            q++;
        }
        tmp = q + 1;
        q =  q - 1;
        while (p < q) {
            swap(result[p], result[q]);
            p++;
            q--;
        }
        q = tmp;
        p = tmp;
    }

    return string(result.begin(), result.end());
}

int main() {
    cout << reverseWords("12");
    cout << "aaaa" << endl;
}