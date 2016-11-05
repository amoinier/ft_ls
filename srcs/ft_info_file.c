/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:30:44 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/05 14:00:21 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	char	ft_let_type(mode_t st_mode) {
	if (S_ISSOCK(st_mode))
		return ('s');
	else if (S_ISFIFO(st_mode))
		return ('f');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISREG(st_mode))
		return ('-');
	else
		return ('-');
}

char	*ft_get_right(struct stat info) {
	char	*right;

	if (!(right = (char *)malloc(sizeof(right) * (10 + 1))))
		return (NULL);

	right[0] = ft_let_type(info.st_mode);
	right[1] = ((info.st_mode & S_IRUSR) ? 'r' : '-');
	right[2] = ((info.st_mode & S_IWUSR) ? 'w' : '-');
	right[3] = ((info.st_mode & S_IXUSR) ? 'x' : '-');
	right[4] = ((info.st_mode & S_IRGRP) ? 'r' : '-');
	right[5] = ((info.st_mode & S_IWGRP) ? 'w' : '-');
	right[6] = ((info.st_mode & S_IXGRP) ? 'x' : '-');
	right[7] = ((info.st_mode & S_IROTH) ? 'r' : '-');
	right[8] = ((info.st_mode & S_IWOTH) ? 'w' : '-');
	right[9] = ((info.st_mode & S_IXOTH) ? 'x' : '-');
	return (right);
}

void			ft_info_file(char *filename)
{
	struct	stat	info;

	stat(filename, &info);
	ft_get_right(info);
	// printf("%llu\n", info.st_ino);
	// printf("%hu\n", info.st_mode);
	ft_putstr(ft_get_right(info));
	printf(" %hu", info.st_nlink);
	printf(" %s", getpwuid(info.st_uid)->pw_name);
	printf(" %s", getgrgid(info.st_gid)->gr_name);
	// printf("%d\n", info.st_rdev);
	printf(" %lld", info.st_size);
	// printf("%d\n", info.st_blksize);
	// printf("%lld\n", info.st_blocks);
	// printf("%s\n", ctime(&info.st_atime));
	printf(" %s %s", ctime(&info.st_mtime), filename);
	// printf("%s\n", ctime(&info.st_ctime));
	// printf((info.st_mode & S_IRUSR) ? "r" : "-");
	// printf("DIR : %d\n", S_ISDIR(info.st_mode));
	// printf("REG : %d\n", S_ISREG(info.st_mode));
	// printf("LINK : %d\n", S_ISLNK(info.st_mode));
	// printf("CHARMOD : %d\n", S_ISCHR(info.st_mode));
	// printf("BLOCK : %d\n", S_ISBLK(info.st_mode));
	// printf("FIFO : %d\n", S_ISFIFO(info.st_mode));
	// printf("SOCKET : %d\n", S_ISSOCK(info.st_mode));
	return ;
}
