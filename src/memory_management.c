#include "../includes/header.h"

int	init_memory_list(t_mem_list **m)
{
	t_mem_list	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (1);
	ret->address = NULL;
	ret->next = NULL;
	ret->prev = NULL;
	*m = ret;
	return (0);
}

void	clean_memory_list(t_mem_list **mem)
{
	t_mem_list	*temp;

	if (!mem || !(*mem))
		return ;
	while ((*mem)->prev != NULL)
		(*mem) = (*mem)->prev;
	while ((*mem))
	{
		temp = (*mem)->next;
		if ((*mem)->address)
			free((*mem)->address);
		free(*mem);
		*mem = temp;
	}
	free(temp);
}

void	*x_malloc(t_mem_list **mem, size_t size)
{
	t_mem_list	*curr;

	if (!mem || !*mem || size == 0)
		return (NULL);
	curr = *mem;
	while (curr->next)
		curr = curr->next;
	curr->address = malloc(size);
	if (!curr->address)
		return (NULL);
	init_memory_list(&curr->next);
	curr->next->prev = curr;
	return (curr->address);
}