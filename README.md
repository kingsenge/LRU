# LRU

- 用unorder_map实现哈希表，leetcode测试通过时间为82ms。 
- 可以采用数组的方式提高哈希的检索速度，真正做到O(1)的时间复杂度。

目前在删除哈希节点时，采用标签的方式，以赋值-1表示该节点已移除哈希表，而不是erase，这样可以提高后期节点重入的速度。
但是在处理节点时要注意特殊情况，如缓存已满时，若已被移除的节点重入，也需要删除最旧的节点，否则最大节点数将超过预设值！
如 (-1,2,3,4,5,-1,10)，最大节点数为5，若此时第一个-1 更新成7，则最大节点数6不符合要求。
