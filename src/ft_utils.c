
#include "ft_ssl.h"


int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (((unsigned char *) s1)[i] && ((unsigned char *) s2)[i]
		&& ((unsigned char *) s1)[i] == ((unsigned char *) s2)[i])
		i++;
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (dest);
	i = 0;
	while (i < n)
	{
		((char *) dest)[i] = ((char *) src)[i];
		i++;
	}
	return (dest);
}
