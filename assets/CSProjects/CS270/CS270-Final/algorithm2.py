# Certification of Authenticity:
# I certify that this is entirely my own work, except for where I have given fully-documented
# references to the work of others. I understand the definition and consequences of plagiarism and
# acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
# - Reproduce this assignment and provide a copy to another member of academic
# - staff; and/or Communicate a copy of this assignment to a plagiarism checking
# - service (which may then retain a copy of this assignment on its database for
# - the purpose of future plagiarism checking)
# Tate Morris

import timeit

class ListNode:
    """Singly linked list node."""
    def __init__(self, value, next=None):
        self.value = value
        self.next = next

    def __repr__(self):
        return f"ListNode({self.value})"


def build_linked_list(values):
    """
    Create a singly linked list from a Python list of ints.
    Returns the head (ListNode).
    """
    head = None
    tail = None
    for v in values:
        node = ListNode(v)
        if head is None:
            head = node
            tail = node
        else:
            tail.next = node
            tail = node
    return head


def linked_list_to_list(head):
    """
    Convert a linked list (head: ListNode) back to a Python list.
    """
    out = []
    curr = head
    while curr is not None:
        out.append(curr.value)
        curr = curr.next
    return out


class TreeNode:
    """
    Node of the binary tree.
    Each TreeNode holds:
      - list_head: head of a linked list (ListNode)
      - left: left child (TreeNode or None)
      - right: right child (TreeNode or None)
    """
    def __init__(self, list_head, left=None, right=None):
        self.list_head = list_head
        self.left = left
        self.right = right

    def __repr__(self):
        return f"TreeNode({linked_list_to_list(self.list_head)})"


def can_split_list(list_head):
    """
    Returns True if any element in the linked list is > 1,
    meaning further splitting is possible.
    """
    curr = list_head
    while curr is not None:
        if curr.value > 1:
            return True
        curr = curr.next
    return False


def split_list(list_head):
    """
    Given a linked list, split each element x into two values according to:
      - if x > 1:
          * even:  left = x // 2, right = x // 2
          * odd:   left = x // 2, right = x // 2 + 1
      - if x <= 1:
          * treated as not splittable
          * left = x, right = 0  (no further splits)

    Returns (left_head, right_head) where both are heads of new linked lists.
    """
    left_head = left_tail = None
    right_head = right_tail = None

    curr = list_head
    while curr is not None:
        x = curr.value

        if x > 1:
            base = x // 2
            if x % 2 == 0:
                left_val = base
                right_val = base
            else:
                left_val = base
                right_val = base + 1
        else:
            # x <= 1: no more splits
            left_val = x
            right_val = 0

        # Append to left list
        left_node = ListNode(left_val)
        if left_head is None:
            left_head = left_node
            left_tail = left_node
        else:
            left_tail.next = left_node
            left_tail = left_node

        # Append to right list
        right_node = ListNode(right_val)
        if right_head is None:
            right_head = right_node
            right_tail = right_node
        else:
            right_tail.next = right_node
            right_tail = right_node

        curr = curr.next

    return left_head, right_head


def _build_children(node):
    """
    Recursively build left and right children for a given TreeNode
    until no more splits are possible (all elements <= 1).
    """
    if node is None:
        return

    if not can_split_list(node.list_head):
        # Leaf node: nothing more to split
        return

    # Split current node's list into two child lists
    left_head, right_head = split_list(node.list_head)
    node.left = TreeNode(left_head)
    node.right = TreeNode(right_head)

    # Recurse
    _build_children(node.left)
    _build_children(node.right)


def build_tree_from_list(values):
    """
    Entry point.
    Takes a Python list of ints as the root linked list values,
    builds the entire binary tree according to the splitting rules,
    and returns the root TreeNode.
    """
    root_list = build_linked_list(values)
    root = TreeNode(root_list)
    _build_children(root)
    return root

#Compute the total sum and diversity for a linked list
def list_sum_and_diversity(list_head):
    total = 0
    diversity = 0
    curr = list_head
    while curr is not None:
        total += curr.value
        if curr.value > 0:
            diversity += 1
        curr = curr.next
    return total, diversity

# Verify that summing all partitions index-wise reconstructs 'original'
def check_reconstruction_from_partitions(partitions, original):

    if not partitions:
        return False

    n = len(original)
    for p in partitions:
        if len(p) != n:
            return False

    reconstructed = [0] * n
    for p in partitions:
        for i in range(n):
            reconstructed[i] += p[i]

    return reconstructed == original


def compute_best_partitions(node, k, l, memo):
    """
    For each TreeNode, decide:
      - "self": treat this node's list as a whole partition (if feasible), OR
      - "children": rely on left & right subtrees,
    whichever yields a valid solution with maximum partition count
    """
    if node is None:
        return None

    if node in memo:
        return memo[node]

    total, diversity = list_sum_and_diversity(node.list_head)
    feasible_self = (total >= k and diversity >= l)

    # Case 1: try "self"
    self_solution = None
    if feasible_self:
        # This subtree is handled entirely by this node => 1 partition
        self_solution = (1, "self")

    # Case 2: try "children"
    child_solution = None
    if node.left is not None and node.right is not None:
        left_res = compute_best_partitions(node.left, k, l, memo)
        right_res = compute_best_partitions(node.right, k, l, memo)
        if left_res is not None and right_res is not None:
            left_count, _ = left_res
            right_count, _ = right_res
            child_solution = (left_count + right_count, "children")

    # Now choose the better valid solution, if any
    if self_solution is None and child_solution is None:
        memo[node] = None
        return None
    elif self_solution is None:
        memo[node] = child_solution
        return child_solution
    elif child_solution is None:
        memo[node] = self_solution
        return self_solution
    else:
        # Both are valid; pick the one with larger count
        if self_solution[0] >= child_solution[0]:
            memo[node] = self_solution
            return self_solution
        else:
            memo[node] = child_solution
            return child_solution

# Given 'memo' from compute_best_partitions, collect the partitions.
def collect_partitions(node, memo, partitions):
    if node is None:
        return

    result = memo.get(node)
    if result is None:
        return

    count, choice = result

    if choice == "self":
        partitions.append(linked_list_to_list(node.list_head))
    elif choice == "children":
        collect_partitions(node.left, memo, partitions)
        collect_partitions(node.right, memo, partitions)
    # If choice is None (impossible), nothing to collect

#Algorithm 2: Tree-based DP using the starter code
def tree_based_dp_algorithm(values, k, l):
    # Quick check
    total_sum = sum(values)
    if total_sum < k:
        return False, []

    diversity = sum(1 for x in values if x > 0)
    if diversity < l:
        return False, []

    # Build tree
    root = build_tree_from_list(values)

    memo = {}
    result = compute_best_partitions(root, k, l, memo)
    if result is None:
        return False, []

    count, _ = result
    partitions = []
    collect_partitions(root, memo, partitions)

    if not check_reconstruction_from_partitions(partitions, values):
        return False, []

    return True, partitions

if __name__ == "__main__":

    print("Algorithm 2 (Tree-based DP): partitioning via splitting tree")

    while True:
        print("Enter the collection of integers (space-separated), e.g. '10 5 8':")
        try:
            values = list(map(int, input().split()))
            break
        except ValueError:
            print("Invalid input: collection must be integers. Please try again.\n")

    while True:
        try:
            k = int(input("Enter k (minimum sum per partition): ").strip())
            break
        except ValueError:
            print("Invalid input: k must be an integer. Please try again.\n")

    while True:
        try:
            l = int(input("Enter l (minimum number of non-zero indices per partition): ").strip())
            break
        except ValueError:
            print("Invalid input: l must be an integer. Please try again.\n")

    success, partitions = tree_based_dp_algorithm(values, k, l)

    if not success or not partitions:
        print("\nNo valid partitioning found by Algorithm 2 in this splitting tree.")
    else:
        print("\nAlgorithm 2 found a valid partitioning in the splitting tree.")
        print("Number of partitions:", len(partitions))
        for i, part in enumerate(partitions, start=1):
            print("Partition", i, ":", part)

        print("\nReconstruction check:", "All good, Champ!" if check_reconstruction_from_partitions(partitions, values) else "FAILED IDIOT"
        )

    runs = 10
    elapsed = timeit.timeit("tree_based_dp_algorithm(values, k, l)", number=runs, globals=globals())
    print(f"\nAverage time over {runs} runs: {elapsed / runs:.6f} seconds")
