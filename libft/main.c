#include "libft.h"
#include <stdio.h>

int	main()
{
	// char *s = "**hdjsj**jdsj*123**456";
	// char **arr = ft_split(s, '*');
	// int i = 0;

	// while (arr[i])
	// {
	// 	printf("%s\n", arr[i]);
	// 	i++;
	// }

	char *a = "123";

	printf("%s\n", ft_memmove(a, "456", 2));

	return (0);
}