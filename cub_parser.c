/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 11:56:20 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/10 20:31:10 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_floor(char *l, t_data *data, int i)
{
	while (ft_whitespace(l[i]))
		i++;
	ft_isdigit(l[i]) ? grgb(l, &data->floor.t_rgb.r, i, 0)
		: bad_input(ERR_F);
	while (ft_isdigit(l[i]))
		i++;
	while (ft_whitespace(l[i]))
		i++;
	l[i] != ',' ? bad_input(ERR_F) : i++;
	while (ft_whitespace(l[i]))
		i++;
	ft_isdigit(l[i]) ? grgb(l, &data->floor.t_rgb.g, i, 0) :
			bad_input(ERR_F);
	while (ft_isdigit(l[i]))
		i++;
	while (ft_whitespace(l[i]))
		i++;
	l[i] != ',' ? bad_input(ERR_F) : i++;
	while (ft_whitespace(l[i]))
		i++;
	ft_isdigit(l[i]) ? grgb(l, &data->floor.t_rgb.b, i, 0) : bad_input(ERR_F);
	while (ft_isdigit(l[i]))
		i++;
	while (l[i] != '\0')
		ft_whitespace(l[i]) ? i++ : bad_input(ERR_F);
}

void		get_ceiling(char *l, t_data *data, int i)
{
	while (ft_whitespace(l[i]))
		i++;
	ft_isdigit(l[i]) ? grgb(l, &data->ceiling.t_rgb.r, i, 1)
		: bad_input(ERR_C);
	while (ft_isdigit(l[i]))
		i++;
	while (ft_whitespace(l[i]))
		i++;
	l[i] != ',' ? bad_input(ERR_C) : i++;
	while (ft_whitespace(l[i]))
		i++;
	ft_isdigit(l[i]) ? grgb(l, &data->ceiling.t_rgb.g, i, 1)
		: bad_input(ERR_C);
	while (ft_isdigit(l[i]))
		i++;
	while (ft_whitespace(l[i]))
		i++;
	l[i] != ',' ? bad_input(ERR_C) : i++;
	while (ft_whitespace(l[i]))
		i++;
	ft_isdigit(l[i]) ? grgb(l, &data->ceiling.t_rgb.b, i, 1) : bad_input(ERR_C);
	while (ft_isdigit(l[i]))
		i++;
	while (l[i] != '\0')
		ft_whitespace(l[i]) ? i++ : bad_input(ERR_C);
}

void		get_configs(t_data *data, char *line, int i)
{
	if (line[i] == 'R')
		get_res(line, data, i + 1);
	if (line[i] == 'F')
		get_floor(line, data, i + 1);
	if (line[i] == 'C')
		get_ceiling(line, data, i + 1);
	if (line[i] == 'N' && line[i + 1] == 'O')
		get_texture(line, data, i + 2, 0);
	if (line[i] == 'E' && line[i + 1] == 'A')
		get_texture(line, data, i + 2, 1);
	if (line[i] == 'S' && line[i + 1] == 'O')
		get_texture(line, data, i + 2, 2);
	if (line[i] == 'W' && line[i + 1] == 'E')
		get_texture(line, data, i + 2, 3);
	if (line[i] == 'S' && line[i + 1] != 'O')
		get_sprite(line, data, i + 1);
	if (data->parse[8] == 1)
		get_map(line, data);
	free(line);
	line = NULL;
}

void		count_configs(t_data *data, char *line, int i)
{
	if (line[i] == 'R')
		data->parse[0] == 0 ? data->parse[0] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'F')
		data->parse[1] == 0 ? data->parse[1] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'C')
		data->parse[2] == 0 ? data->parse[2] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'N' && line[i + 1] == 'O')
		data->parse[3] == 0 ? data->parse[3] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'E' && line[i + 1] == 'A')
		data->parse[4] == 0 ? data->parse[4] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'S' && line[i + 1] == 'O')
		data->parse[5] == 0 ? data->parse[5] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'W' && line[i + 1] == 'E')
		data->parse[6] == 0 ? data->parse[6] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'S' && line[i + 1] != 'O')
		data->parse[7] == 0 ? data->parse[7] = 1 : bad_input(ERR_ELEM);
	if (!findchar(line[i], "RFCNESW120\n\0 ") && !ft_whitespace(line[i]))
		bad_input("Error\nUnknown element\n");
	if (line[i] && findchar(line[i], "012 ") && data->parse[8] != 1)
	{
		bad_input("Error\nMap is not at bottom or config missing\n");
	}
	if (elem_check(data, i))
		data->parse[8] = 1;
}

int			prs_wrld(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line))
	{
		count_configs(data, line, i);
		get_configs(data, line, i);
	}
	count_configs(data, line, i);
	get_configs(data, line, i);
	if (data->parse[8] == 0)
		bad_input(ERR_ELEM);
	if (data->maptemp == NULL)
		bad_input(ERR_MAP);
	data->maparr = ft_split_extra(data->maptemp, '\n');
	map_check(data);
	sprites_init(data);
	free(data->maptemp);
	return (0);
}
