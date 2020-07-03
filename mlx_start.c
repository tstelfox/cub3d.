/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:38:05 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/03 19:26:21 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	if (data->ray.frame % 2 == 0)
		dst = data->mlx.addr2 + (y * data->mlx.linelen + x * (data->mlx.bpp / 8));
	else
		dst = data->mlx.addr + (y * data->mlx.linelen + x * (data->mlx.bpp / 8));
	*(unsigned int*)dst = colour;
}

int			frame_update(t_data *data)
{
	if (data->ray.frame % 2 == 0)
	{
		// printf("Should come in here immediately\n");
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
			data->mlx.img, 0, 0);
	}
	else
	{
		// printf("Should come in here on first keypress\n");
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
			data->mlx.img2, 0, 0);
	}
	return (0);
}

int			movement(t_data *data)
{
	if (data->ray.key == 1)
	{
		if (data->maparr[(int)(data->player.posy + data->player.diry * data->ray.mspeed)][(int)data->player.posx] != '1')
			data->player.posy += (data->player.diry * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx + data->player.dirx * data->ray.mspeed)] != '1')
			data->player.posx += (data->player.dirx * data->ray.mspeed);
		// printf("so posx, y have changed to: %f %f\n", data->player.posx, data->player.posy);
		// printf("frame should be two: %d\n", data->ray.frame);
		// data->player.posx += (data->player.dirx * data->ray.mspeed);
		// data->player.posy += (data->player.diry * data->ray.mspeed);
		raycaster(data);
	} //WHY DOESN'T == '0' WORK!?!?
	if (data->ray.key == 2)
	{
		if (data->maparr[(int)(data->player.posy - data->player.diry * data->ray.mspeed)][(int)data->player.posx] != '1')
			data->player.posy -= (data->player.diry * data->ray.mspeed);
		if (data->maparr[(int)data->player.posy][(int)(data->player.posx - data->player.dirx * data->ray.mspeed)] != '1')
			data->player.posx -= (data->player.dirx * data->ray.mspeed);
		raycaster(data);
	}
	data->ray.key = 0;
	return (0);
}

int			keypressed(int keycode, t_data *data)
{
	if (keycode == 13)
	{
		data->ray.key = 1;
		printf("AVANTI TUTTA DIOCANEEE\n");
	}
	if (keycode == 1)
	{
		data->ray.key = 2;
		printf("FAI RETROMARCIA CE STANNO E GUARDIE\n");
	}
	movement(data);
	return (0);
}

int			raycaster(t_data *data)
{
	int x;

	x = 0;
	while (x < data->resx)
	{
		// Ray position and direction
		data->ray.camx = (2. * x / (double)data->resx) - 1;
		data->ray.raydirx = data->player.dirx + data->player.planex * data->ray.camx;
		data->ray.raydiry = data->player.diry + data->player.planey * data->ray.camx;
		data->ray.mapx = (int)data->player.posx;
		data->ray.mapy = (int)data->player.posy;
		data->ray.hit = 0;
		//Box of map
		//Length of ray from current pos to next x or y side
		//			sidedx & sidedy

		//Length of ray from x or y-side to next x or y side
		data->ray.deltadx = fabs(1. / data->ray.raydirx);
		data->ray.deltady = fabs(1. / data->ray.raydiry);
		//Direction to step in
		//			stepx & stepy

		//calculate step and initial sidedist
		if (data->ray.raydirx < 0)
		{
			data->ray.stepx = -1;
			data->ray.sidedx = (data->player.posx - data->ray.mapx) * data->ray.deltadx;
		}
		else
		{
			data->ray.stepx = 1;
			data->ray.sidedx = (data->ray.mapx + 1.0 - data->player.posx) * data->ray.deltadx;
		}
		if (data->ray.raydiry < 0)
		{
			data->ray.stepy = -1;
			data->ray.sidedy = (data->player.posy - data->ray.mapy) * data->ray.deltady;
		}
		else
		{
			data->ray.stepy = 1;
			data->ray.sidedy = (data->ray.mapy + 1.0 - data->player.posy) * data->ray.deltady;
		}
		//Perform DDA
		while (data->ray.hit == 0)
		{
			//Jump to next map square
			if (data->ray.sidedx < data->ray.sidedy)
			{
				data->ray.sidedx += data->ray.deltadx;
				data->ray.mapx += data->ray.stepx;
				data->ray.side = 0;
			}
			else
			{
				data->ray.sidedy += data->ray.deltady;
				data->ray.mapy += data->ray.stepy;
				data->ray.side = 1;
			}
			//Check if ray has hit wall
			if (data->maparr[(int)data->ray.mapy][(int)data->ray.mapx] == '1')
				data->ray.hit = 1;
		}
		//Calculate distance projected on camera direction
		if (data->ray.side == 0)
			data->ray.walldist = (data->ray.mapx - data->player.posx + (1. - data->ray.stepx) / 2.) / data->ray.raydirx;
		else
			data->ray.walldist = (data->ray.mapy - data->player.posy + (1. - data->ray.stepy) / 2.) / data->ray.raydiry;
		//Calculate height of line to draw
		data->ray.lineheight = (int)(data->resy / data->ray.walldist);
		//Calculate lowest and highest pixel
		data->ray.drawstart = -data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawstart < 0)
			data->ray.drawstart = 0;
		data->ray.drawend = data->ray.lineheight / 2 + data->resy / 2;
		if (data->ray.drawend >= data->resy)
			data->ray.drawend = data->resy - 1;
		//ACtually drawing
		unsigned int colour = 0xFF0000;
		if (data->ray.side == 1)
			colour = 0xFFFFFF;
		while (data->ray.drawstart <= data->ray.drawend)
		{
			my_mlx_pixel_put(data, x, data->ray.drawstart, colour);
			data->ray.drawstart++;
		}
		x++;
		// mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		// 	data->mlx.img, 0, 0);
		// printf("Walldist = [%f] || mapx,y [%d][%d] || stepx,y [%d][%d] || raydirx,y [%f][%f] || posx, y [%f][%f]\nDeltadx, y = [%f][%f] || sidedx, y [%f][%f]\n", data->ray.walldist,
		// 		data->ray.mapx, data->ray.mapy, data->ray.stepx, data->ray.stepy, data->ray.raydirx, data->ray.raydiry, data->player.posx, data->player.posy, data->ray.deltadx, data->ray.deltady, data->ray.sidedx, data->ray.sidedy);
	}
	frame_update(data);
	data->ray.frame++;
	return (0);
}

void		mlx_start(t_data *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->resx,
			data->resy, "mumyer");

	data->mlx.img = mlx_new_image(data->mlx.mlx, data->resx, data->resy);
	data->mlx.img2 = mlx_new_image(data->mlx.mlx, data->resx, data->resy);

	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.linelen, &data->mlx.endian);
	data->mlx.addr2 = mlx_get_data_addr(data->mlx.img2, &data->mlx.bpp,
			&data->mlx.linelen, &data->mlx.endian);

	raycaster(data);
	mlx_key_hook(data->mlx.mlx_win, keypressed, data);
	mlx_loop_hook(data->mlx.mlx, raycaster, data);
	mlx_loop(data->mlx.mlx);
}
