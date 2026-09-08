/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* swapPairs(struct ListNode* head) {
    // If the list is empty or has only one node, no swapping is needed
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Initialize a dummy node to easily track the new head of the list
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;

    // Traverse the list while there are at least two nodes left to swap
    while (prev->next != NULL && prev->next->next != NULL) {
        struct ListNode* first = prev->next;
        struct ListNode* second = prev->next->next;

        // Readjust pointers to swap the 'first' and 'second' nodes
        first->next = second->next;
        second->next = first;
        prev->next = second;

        // Move the prev pointer forward by two nodes for the next iteration
        prev = first;
    }

    return dummy.next;
}
