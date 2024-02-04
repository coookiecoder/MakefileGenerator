/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abareux <abareux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:38:58 by abareux           #+#    #+#             */
/*   Updated: 2024/02/04 16:09:19 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define ENTRY 1024

size_t	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

void	write_source(int fd, int file_nb, char **file_path)
{
	write(fd, "SRC = ", 6);
	for (int written_file = 0; written_file < file_nb; written_file++)
	{
		write(fd, file_path[written_file], ft_strlen(file_path[written_file]) - 1);
		write(fd, "c ", 2);
	}
	write(fd, "\n", 1);
}


void	write_object(int fd, int file_nb, char **file_path)
{
	write(fd, "OBJ = ", 6);
	for (int written_file = 0; written_file < file_nb; written_file++)
	{
		write(fd, file_path[written_file], ft_strlen(file_path[written_file]) - 1);
		write(fd, "o ", 2);
	}
	write(fd, "\n", 1);
}

void	write_name(int fd, char *name)
{
	write(fd, "NAME = ", 7);
	write(fd, name, ft_strlen(name));
	write(fd, "\n", 1);
}

void	write_compiler(int fd, char *compiler)
{
	write(fd, "CC = ", 5);
	write(fd, compiler, ft_strlen(compiler));
	write(fd, "\n", 1);
}

void	write_flags(int fd)
{
	char	flags[] = "-Wall -Wextra -Werror";

	write(fd, "CFLAGS = ", 9);
	write(fd, flags, ft_strlen(flags));
	write(fd, "\n", 1);
}

void	write_rules(int fd)
{
	write(fd, "all: $(NAME)\n", 13);
	write(fd, "\n", 1);
	write(fd, "\n", 1);

	write(fd, "$(NAME): $(OBJ)\n", 16);
	write(fd, "\t$(CC) $(CFLAGS) $(OBJ) -o $(NAME)\n", 35);
	write(fd, "\n", 1);

	write(fd, "clean:\n", 7);
	write(fd, "\trm -rf $(OBJ)\n", 15);
	write(fd, "\n", 1);

	write(fd, "fclean: clean\n", 14);
	write(fd, "\trm -rf $(NAME)\n", 16);
	write(fd, "\n", 1);

	write(fd, "re: fclean all\n", 15);
	write(fd, "\n", 1);
	write(fd, "\n", 1);

	write(fd, ".PHONY: all clean fclean re debug\n", 34);
}

int	main(int argc, char **argv)
{
	int		fd;

	if (argc < 2)
		return (write(1, "need the path dumbass\n", 23), 2);
	if (argc < 3)
		return (write(1, "need the name dumbass\n", 23), 2);
	if (argc < 4)
		return (write(1, "need the compiler dumbass\n", 27), 2);
	if (argc < 5)
		return (write(1, "need the file dumbass\n", 23), 2);
	if (chdir(argv[1]) == -1)
		return (write(1, "you fail the path dumbass\n", 27), 2);
	fd = open("./Makefile", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
		return (write(1, "check your perm dumbass\n", 25), 2);
	write_source(fd, argc - 4, argv + 4);
	write_object(fd, argc - 4, argv + 4);
	write(fd, "\n", 1);
	write_name(fd, argv[2]);
	write(fd, "\n", 1);
	write_compiler(fd, argv[3]);
	write(fd, "\n", 1);
	write_flags(fd);
	write(fd, "\n", 1);
	write_rules(fd);
	close(fd);
}
