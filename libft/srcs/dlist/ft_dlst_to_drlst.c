int ft_dlst_to_drlst(t_dnode **head)
{
	int size;
	t_dnode *current;

	size = 0;
	if (!head || !*head)
		return (0);
	current = *head;
	while (current)
	{
		size++;
		if (!current->next)
		{
			current->next = *head;
			(*head)->prev = current;
			break ;
		}
		current = current->next;
	}
	return (size);
}
