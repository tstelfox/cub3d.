/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 13:27:44 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/03 21:11:48 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_init(t_data *data)
{
	data->resx = 0;
	data->resy = 0;
	data->floor.t_rgb.a = 0;
	data->ceiling.t_rgb.a = 0;
	data->player.posx = 0;
	data->player.posy = 0;
	data->player.planey = 0;
	data->player.planex = 0;
	data->ray.mapx = 0;
	data->ray.mapy = 0;
	data->ray.camx = 0;
	data->ray.raydirx = 0;
	data->ray.raydiry = 0;
	data->ray.sidedx = 0;
	data->ray.sidedy = 0;
	data->ray.deltadx = 0;
	data->ray.deltady = 0;
	data->ray.walldist = 0;
	data->ray.stepx = 0;
	data->ray.stepy = 0;
	data->ray.hit = 0;
	data->ray.side = 0;
	data->ray.lineheight = 0;
	data->ray.drawstart = 0;
	data->ray.drawend = 0;
	data->ray.mspeed = 0.05;
	data->ray.rotspeed = 0.02;
	data->maptemp = NULL;
	data->ray.frame = 1;
	data->ray.key = 0;
}

void	zero_mlx(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->mlx_win = NULL;
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->bpp = 0;
	mlx->linelen = 0;
	mlx->endian = 0;
}

int		main(int argc, char *argv[])
{
	t_data	data;
	t_mlx	mlx;

	data_init(&data);
	zero_mlx(&mlx);
	data.mlx = mlx;
	prs_wrld(&data, argc, argv);
	mlx_start(&data);
	// raycast(&data);
	return (0);
}
