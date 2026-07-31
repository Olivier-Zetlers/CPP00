#include <cctype>
#include <iostream>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(argv[i][j])));
			j++;
		}
		i++;
	}
	std::cout << std::endl;
	return (0);
}
