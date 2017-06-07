/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 19:30:44 by amoinier          #+#    #+#             */
/*   Updated: 2017/06/07 18:59:32 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	char	ft_let_type(mode_t st_mode)
{
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

static	char	*ft_get_right(struct stat info)
{
	char	*right;

	if (!(right = ft_strnew(10 + 1)))
		return (NULL);

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
	struct passwd	*pwuid;

	if (!info.st_dev || info.st_dev < 0)
 	{
 		ft_putstr("ls: ");
 		ft_putstr(filename);
 		ft_putstr(": No such file or directory\n");
 	}

	pwuid = getpwuid(info.st_uid);

	list->realname = ft_real_name(info, filename);
	list->nb_block = info.st_blocks;
	list->right = ft_get_right(info);
	list->nblk = info.st_nlink;
	list->major = (list->right[0] == 'c' || list->right[0] == 'b' ? major(info.st_rdev) : list->major);
	list->minor = (list->right[0] == 'c' || list->right[0] == 'b' ? minor(info.st_rdev) : list->minor);
	list->prop = (pwuid && pwuid->pw_name ? ft_strdup(pwuid->pw_name) : ft_strdup(""));
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
