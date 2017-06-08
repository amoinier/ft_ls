/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:30:44 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/08 15:47:59 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	char	*ft_get_right(struct stat info, char *right)
{
	right[0] = ft_let_type(info.st_mode);
	right[1] = ((info.st_mode & S_IRUSR) ? 'r' : '-');
	right[2] = ((info.st_mode & S_IWUSR) ? 'w' : '-');
	right[3] = ((info.st_mode & S_IXUSR) ? 'x' : '-');
	if ((info.st_mode & S_IRWXU))
		right[3] = ((info.st_mode & S_ISUID) ? 's' : right[3]);
	else
		right[3] = ((info.st_mode & S_ISUID) ? 'S' : right[3]);
	right[4] = ((info.st_mode & S_IRGRP) ? 'r' : '-');
	right[5] = ((info.st_mode & S_IWGRP) ? 'w' : '-');
	right[6] = ((info.st_mode & S_IXGRP) ? 'x' : '-');
	if ((info.st_mode & S_IRWXG))
		right[6] = ((info.st_mode & S_ISGID) ? 's' : right[6]);
	else
		right[6] = ((info.st_mode & S_ISGID) ? 'S' : right[6]);
	right[7] = ((info.st_mode & S_IROTH) ? 'r' : '-');
	right[8] = ((info.st_mode & S_IWOTH) ? 'w' : '-');
	right[9] = ((info.st_mode & S_IXOTH) ? 'x' : '-');
	if ((info.st_mode & S_IRWXO))
		right[9] = ((info.st_mode & S_ISVTX) ? 't' : right[9]);
	else
		right[9] = ((info.st_mode & S_ISVTX) ? 'T' : right[9]);
	right[10] = '\0';
	return (right);
}

static	char	*ft_real_name(struct stat info, char *newpath)
{
	char	*buf;

	if (S_ISLNK(info.st_mode))
	{
		if (!(buf = ft_strnew(1024)))
			return (NULL);
		readlink(newpath, buf, 1024);
		return (buf);
	}
	return (NULL);
}

t_file			*ft_add_info(t_file *list, struct stat info, char *filename)
{
	char *right;

	if (!(right = ft_strnew(10 + 1)))
		return (NULL);
	if (!info.st_dev || info.st_dev < 0)
	{
		ft_putstr("ls: ");
		ft_putstr(filename);
		ft_putstr(": No such file or directory\n");
	}
	list->realname = ft_real_name(info, filename);
	list->nb_block = info.st_blocks;
	list->right = ft_get_right(info, right);
	list->nblk = info.st_nlink;
	list->major = (list->right[0] == 'c' || list->right[0] == 'b' ?
	major(info.st_rdev) : list->major);
	list->minor = (list->right[0] == 'c' || list->right[0] == 'b' ?
	minor(info.st_rdev) : list->minor);
	list->prop = (getpwuid(info.st_uid) && getpwuid(info.st_uid)->pw_name ?
	ft_strdup(getpwuid(info.st_uid)->pw_name) : ft_strdup(""));
	list->groupe = ft_strdup(getgrgid(info.st_gid)->gr_name);
	list->size = (unsigned int)info.st_size;
	list->date = info.st_mtime;
	return (list);
}

t_file			*ft_info_dir(t_file *list, char *filename)
{
	struct stat	info;
	char		*fpath;
	char		*newpath;

	fpath = ft_strjoin(filename, "/");
	newpath = ft_strjoin(fpath, list->name);
	lstat(newpath, &info);
	list = ft_add_info(list, info, newpath);
	list->type = ft_strdup("dir");
	ft_strdel(&fpath);
	ft_strdel(&newpath);
	return (list);
}

t_file			*ft_info_file(t_file *list, char *filename)
{
	struct stat	info;

	lstat(filename, &info);
	list = ft_add_info(list, info, filename);
	list->type = ft_strdup("file");
	return (list);
}
