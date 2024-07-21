#include "../../includes/header_mig.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size -1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	size;

	if (!s)
		return (NULL);
	size = strlen(s);
	if (start > size)
		return (strdup(""));
	else if (len > size - start)
		len = size - start;
	substring = calloc(len + 1, sizeof(char));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}

static void ft_previous (char *current)
{
	int last_slash;
	char *pwd;
	char *prev;
	int i;
	
	pwd = current;
	i = 0;
	while(pwd[i])
	{
		if (pwd[i] == '/')
			last_slash = i;
		i++;
	}
	prev = ft_substr(pwd, 0, last_slash);
	chdir(prev);
	printf("infuntion pwd: %s\n", prev);
	free(prev);
}

int main (void)
{
    char *cd = "/mnt/c/Users/MarcisBokmanis/Desktop/42";
    
    ft_previous(cd);
    
    char *pwd = getcwd(NULL, 0);
    printf("main pwd: %s\n", pwd);

}