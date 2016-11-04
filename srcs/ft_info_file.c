/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:30:44 by amoinier          #+#    #+#             */
/*   Updated: 2016/11/04 13:48:07 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_info_file(char *filename)
{
	struct	stat	info;
	//char *test;

	//test = ft_strjoin("./", filename);
	stat(filename, &info);
	printf("%llu\n", info.st_ino);
	printf("%hu\n", info.st_mode);
	printf("%hu\n", info.st_nlink);
	printf("%u\n", info.st_uid);
	printf("%u\n", info.st_gid);
	printf("%d\n", info.st_rdev);
	printf("%d\n", info.st_blksize);
	printf("%lld\n", info.st_blocks);
	printf("%ld\n", info.st_atime);
	printf("%ld\n", info.st_mtime);
	printf("%ld\n", info.st_ctime);
	printf((info.st_mode & S_IRUSR) ? "r" : "-");
	printf("DIR : %d\n", S_ISDIR(info.st_mode));
	printf("REG : %d\n", S_ISREG(info.st_mode));
	printf("LINK : %d\n", S_ISLNK(info.st_mode));
	printf("CHARMOD : %d\n", S_ISCHR(info.st_mode));
	printf("BLOCK : %d\n", S_ISBLK(info.st_mode));
	printf("FIFO : %d\n", S_ISFIFO(info.st_mode));
	printf("SOCKET : %d\n", S_ISSOCK(info.st_mode));
	return ;
}
