
#include "include/libft.h"
#include <stdio.h>

int main()
{
	t_list *lst;
	t_list *l = NULL;

	lst = ft_lstnew("two");
	ft_lstadd_front(&lst, ft_lstnew("one"));
	printf("%i\n", ft_lstsize(lst));
	printf("%s\n", (char *)ft_lstlast(lst)->content);
	ft_lstadd_back(&lst, ft_lstnew("three"));
	printf("%i\n", ft_lstsize(lst));
	printf("%s\n", (char *)ft_lstlast(lst)->content);
	
	ft_lstadd_back(&l, ft_lstnew((void*)1));
	printf("%i\n", *(int *)l->content);

}
