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

int main() {
    ListNode *head = new ListNode(1);
    // while (head != NULL) {
    //     cout << head->val << endl;
    //     head = head->next;
    // }
    ListNode *newNode = removeNthFromEnd(head, 1);
    while (newNode != NULL) {
        cout << newNode->val << endl;
        newNode = newNode->next;
    }
}