/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   NOOT NOOT MOTHER FUCKER                      :#:  :#:         :#:  :#:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: the-day-it-was updated by UwU                                   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	if (argc != 2)
		return (write(1, "need the path dumbass\n", 23), 2);
	if (chdir(argv[1]) == -1)
		return (write(1, "you fail the path dumbass\n", 27), 2);
	int fd = open("./Makefile", O_CREAT, 0664);
	if (fd == -1)
		return (write(1, "check your perm dumbass\n", 25), 2);
	close(fd);
}
