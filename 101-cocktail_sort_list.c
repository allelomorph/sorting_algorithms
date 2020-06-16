#include "sort.h"
#include <limits.h>

void dll_adj_swap(listint_t **list, listint_t *left, listint_t *right);
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
	int i = 0, shake_range, list_length;
	listint_t *temp, *one, *two;

	if (!list || !(*list) || !(*list)->next)
	return;

	temp = *list;
	shake_range = INT_MAX;
	do {
		while (temp->next && i < shake_range)
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
			i++;
		}
		if (first_loop)
			shake_range = list_length = i + 1;
		first_loop = false;
		if (swapped)
		{
			temp = temp->prev;
			i--;
		}
		while (temp->prev && i >= list_length - shake_range)
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
			i--;
		}
		if (swapped)
		{
			temp = temp->next;
			i++;
		}
		shake_range -= 2;
	} while (shake_range > 2);
}
