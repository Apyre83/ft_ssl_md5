
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

int ft_strlen_u(uint8_t *s) { int i = 0; while (s[i]) i++; return (i); }
int	ft_isalpha(int c) { if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return (1); return (0); }
int	ft_isalnum(int c) { return (ft_isdigit(c) || ft_isalpha(c)); }

char	*ft_strchr(const char *s, int c)
{
    int	i;

    i = 0;
    while (s[i])
    {
        if (s[i] == (char) c)
            return ((char *) s + i);
        i++;
    }
    if (c == '\0')
        return ((char *) &s[i]);
    return (0);
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


void	print_crypted(crypted_string cs, bool nl) {
	for (int i = 0; i < cs.len; i++) {
		ft_printf("%02x", cs.hash[i]);
	}
	if (nl == true) ft_printf("\n");
}
