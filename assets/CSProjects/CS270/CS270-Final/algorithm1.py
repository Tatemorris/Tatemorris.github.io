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


# Return the sum of all entries in a partition (list of ints)
def partition_sum(partition):
    return sum(partition)

# Return the number of indices in the partition with strictly positive values
def partition_diversity(partition):
    count = 0
    for x in partition:
        if x > 0:
            count += 1
    return count

# Verify that summing all partitions index-wise reconstructs 'original'
def check_reconstruction(partitions, original):

    if not partitions:
        return False

    n = len(original)

    # Every partition must match the original length
    for p in partitions:
        if len(p) != n:
            return False

    # Sum index-wise
    reconstructed = [0] * n
    for p in partitions:
        for i in range(n):
            reconstructed[i] += p[i]

    return reconstructed == original

# Builds a partition
def build_one_partition(remaining, k, l):
    n = len(remaining)
    temp_remaining = remaining[:]  # local copy so we can roll back on failure (thanks w3schools)
    partition = [0] * n
    total = 0
    diversity = 0

    # Continue until both constraints are satisfied
    while total < k or diversity < l:
        best_idx = -1
        best_val = 0
        for i in range(n):
            if temp_remaining[i] > best_val:
                best_val = temp_remaining[i]
                best_idx = i

        # If nothing left but constraints are not met, we cannot build another valid partition.
        if best_val == 0:
            return None, False

        # Take 1 unit from the chosen index.
        temp_remaining[best_idx] -= 1

        # If this index was previously zero in the partition, increase diversity
        if partition[best_idx] == 0:
            diversity += 1

        partition[best_idx] += 1
        total += 1

    # If we succeeded, commit the local remaining back to the real remaining
    for i in range(n):
        remaining[i] = temp_remaining[i]

    return partition, True


def greedy_partition_algorithm(values, k, l):
    # Quick checks
    total_sum = sum(values)
    if total_sum < k:
        # Not enough total mass to form even one valid partition :(
        return False, []

    total_diversity = 0
    for x in values:
        if x > 0:
            total_diversity += 1
    if total_diversity < l:
        # Not enough distinct non-zero indices to ever reach diversity l...
        return False, []

    remaining = values[:]  # make a copy so we do not modify the original
    partitions = []

    while True:
        partition, ok = build_one_partition(remaining, k, l)
        if not ok:
            break
        partitions.append(partition)

    # If there is leftover mass, fold it into an existing partition if possible.
    leftover_sum = sum(remaining)
    if leftover_sum > 0:
        if not partitions:
            return False, []
        # Add all leftover to the first partition.
        n = len(remaining)
        for i in range(n):
            partitions[0][i] += remaining[i]
        # Now all remaining mass is assigned.
        remaining = [0] * len(remaining)

    # Sanity Check
    if not check_reconstruction(partitions, values):
        return False, []

    return True, partitions


if __name__ == "__main__":

    print("Algorithm 1 (Greedy): Largest-first partitioner")

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

    success, partitions = greedy_partition_algorithm(values, k, l)

    if not success or not partitions:
        print("\nNo valid full partitioning found by Algorithm 1 (Greedy).")
    else:
        print("\nAlgorithm 1 (Greedy) found a valid full partitioning.")
        print("Number of partitions:", len(partitions))
        for i, part in enumerate(partitions, start=1):
            print("Partition", i, ":", part)

        print("\nReconstruction check:", "All good, champ" if check_reconstruction(partitions, values) else "FAILED IDIOT")
    runs = 10
    elapsed = timeit.timeit("greedy_partition_algorithm(values, k, l)", number=runs, globals=globals())
    print(f"\nAverage time over {runs} runs: {elapsed / runs:.6f} seconds")
