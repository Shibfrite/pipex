#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dnode
{
	void			*data;
	struct s_dnode	*prev;
	struct s_dnode	*next;
}	t_dnode;

int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));

int		ft_dlstsize(t_dnode *dlst);
t_dnode	*ft_dlstnew(void *content);
t_dnode	*ft_dlstlast(t_dnode *dlst);
void	ft_dlstadd_front(t_dnode **dlst, t_dnode *new);
void	ft_dlstadd_back(t_dnode **dlst, t_dnode *new);
void	ft_dlstdelone(t_dnode *dlst, void (*del)(void*));
void	ft_dlstclear(t_dnode **dlst, void (*del)(void*));
void	ft_dlstiter(t_dnode *dlst, void (*f)(void*));
t_dnode	*ft_dlstmap(t_dnode *dlst, void *(*f)(void*), void (*del)(void *));
t_dnode *ft_dlst_rotate(t_dnode **head, int k);

#endif
