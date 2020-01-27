#!/usr/bin/python3
"""Solution to the problem."""


def find_all_bigger(array, num_of_elements, needed_sum):
    """Find al lnumbers."""
    if num_of_elements < 2:
        return len([a for a in array if a >= needed_sum])
    all_bigger_count = 0
    for a, i in enumerate(array):
        all_bigger_count += find_all_bigger(array[:i] + array[i + 1:],
                                            num_of_elements - 1,
                                            needed_sum - a)
    return all_bigger_count


def main():
    """Do stuff."""
    array = [4, 3, 2, 1]
    print(find_all_bigger(array, 2, 6))


if __name__ == "__main__":
    main()
