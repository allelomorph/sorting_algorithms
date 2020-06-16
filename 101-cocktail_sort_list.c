#include "sort.h"

/**
 * dll_adj_swap - swaps two adjacent nodes of a doubly linked list
 * @list: doubly linked list of integers to be sorted
 * @left: node closer to head, right->prev
 * @right: node closer to tail, left->next
 */
void dll_adj_swap(listint_t **list, listint_t *left, listint_t *right)
{
	listint_t *swap;

	if (left->prev)
		left->prev->next = right;
	else
		*list = right;
	if (right->next)
		right->next->prev = left;
	right->prev = left->prev;
	left->prev = right;
	swap = right;
	left->next = right->next;
	swap->next = left;
}

/**
 * cocktail_sort_list - sorts a doubly linked list of integers in ascending
 * order using an cocktail shaker sort algorithm
 * @list: doubly linked list of integers to be sorted
 */
void cocktail_sort_list(listint_t **list)
{
	bool first_loop = true, swapped;
	int i = 0, shake_range = 1000000, comparisons;
	listint_t *temp, *one, *two;

	if (!list || !(*list) || !(*list)->next)
	return;

	temp = *list;
	do {
		comparisons = 0;
		while (temp->next && comparisons < shake_range)
		{
			swapped = false;
			one = temp;
			two = temp->next;
			if (two->n < one->n)
			{
				dll_adj_swap(list, one, two);
				print_list(*list);
				swapped = true;
			}
			else
				temp = temp->next;
			comparisons++;
			i++;
		}
		if (first_loop)
			shake_range = i;
		first_loop = false;
		if (swapped)
			temp = temp->prev;
		comparisons = 0;
		shake_range--;
		while (temp->prev && comparisons < shake_range)
		{
			swapped = false;
			one = temp->prev;
			two = temp;
			if (two->n < one->n)
			{
				dll_adj_swap(list, one, two);
				print_list(*list);
				swapped = true;
			}
			else
				temp = temp->prev;
			comparisons++;
		}
		if (swapped)
			temp = temp->next;
		comparisons = 0;
		shake_range -= 2;
	} while (shake_range > 1);
}
