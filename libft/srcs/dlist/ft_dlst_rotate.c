#include "libft_list.h"

static t_dnode *ft_dlstnth(t_dnode *head, int n)
{
    while (n > 0 && head)
    {
        head = head->next;
        n--;
    }
    while (n < 0 && head)
    {
        head = head->prev;
        n++;
    }
    return head;
}

t_dnode *ft_dlst_rotate(t_dnode **head, int k)
{
    int size;
    t_dnode *new_head, *last;

    if (!head || !*head || !(*head)->next || !k)
        return *head;

    size = ft_dlstsize(*head);
    k %= size;
    if (!k)
        return *head;

    last = ft_dlstlast(*head);
    last->next = *head;
    (*head)->prev = last;

    if (k > 0)
        new_head = ft_dlstnth(*head, size - k);
    else
        new_head = ft_dlstnth(*head, -k);

    new_head->prev->next = NULL;
    new_head->prev = NULL;
    *head = new_head;

    return *head;
}

