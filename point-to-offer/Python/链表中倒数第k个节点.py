# 题目描述
# 输入一个链表，输出该链表中倒数第k个结点。

# -*- coding:utf-8 -*-
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def FindKthToTail(self, head, k):
        if head is None:
            return

        first = head
        second = head
        while k and first:
            first = first.next
            k -= 1
        
        if k > 0:
            return
        
        while first:
            first = first.next
            second = second.next
        
        return second