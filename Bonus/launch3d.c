/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 05:43:14 by mbouderr          #+#    #+#             */
/*   Updated: 2024/02/12 08:52:30 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	init_rendring(t_mymlx *mymlx)
{
	mymlx->s_3d.distance = get_short_distance(mymlx);
	mymlx->s_3d.new_distance = mymlx->distance * cos(mymlx->ray_angle
			- mymlx->rotation_angle);
	mymlx->s_3d.projected_wall_height = (BLOCK / mymlx->s_3d.new_distance)
		* ((WIDTH / 2) / tan(mymlx->fov_angle / 2));
	mymlx->s_3d.wallstripheight = (int)mymlx->s_3d.projected_wall_height;
	mymlx->s_3d.walltoppixel = (HEIGHT / 2) - (mymlx->s_3d.wallstripheight / 2);
}

void	rendring_wall(t_mymlx *mymlx)
{
	if (mymlx->s_3d.walltoppixel < 0)
		mymlx->s_3d.walltoppixel = 0;
	else
		mymlx->s_3d.walltoppixel = mymlx->s_3d.walltoppixel + 1;
	mymlx->s_3d.wallbottompixel = (HEIGHT / 2) + (mymlx->s_3d.wallstripheight
			/ 2);
	if (mymlx->s_3d.wallbottompixel > HEIGHT)
		mymlx->s_3d.wallbottompixel = HEIGHT;
}

void	texture_wenw(t_scene *scene, t_mymlx *mymlx, int id, int i)
{
	if (mymlx->horzhitdistance > mymlx->verthitdistance)
	{
		if (scene->mymlx->rayfaceright)
			mlx_put_pixel(mymlx->img2, id, i, get_texture(mymlx, mymlx->ea,
					mymlx->offset_x, i));
		else if (scene->mymlx->rayfaceleft)
			mlx_put_pixel(mymlx->img2, id, i, get_texture(mymlx, mymlx->we,
					mymlx->offset_x, i));
	}
	else
	{
		if (scene->mymlx->rayfaceup)
			mlx_put_pixel(mymlx->img2, id, i, get_texture(mymlx, mymlx->no,
					mymlx->offset_x, i));
		else if (scene->mymlx->rayfacedown)
			mlx_put_pixel(mymlx->img2, id, i, get_texture(mymlx, mymlx->so,
					mymlx->offset_x, i));
	}
}

void	printing_wall(t_scene *scene, t_mymlx *mymlx, int id)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		if (i < mymlx->s_3d.walltoppixel)
			mlx_put_pixel(mymlx->img2, id, i, get_rgba(scene->mymlx->cred,
					scene->mymlx->cgreen, scene->mymlx->cblue, 255));
		else if (i > mymlx->s_3d.wallbottompixel)
			mlx_put_pixel(mymlx->img2, id, i, get_rgba(scene->mymlx->fred,
					scene->mymlx->fgreen, scene->mymlx->fblue, 255));
		else
		{
			texture_wenw(scene, mymlx, id, i);
		}
		i++;
	}
}

void	three_drendring(t_scene *scene, t_mymlx *mymlx, int id)
{
	init_rendring(mymlx);
	rendring_wall(mymlx);
	mymlx->offset_x = 0;
	if (mymlx->horzhitdistance > mymlx->verthitdistance)
		mymlx->offset_x = (int)mymlx->vertwallhity % BLOCK;
	else
		mymlx->offset_x = (int)mymlx->horiwallhitx % BLOCK;
	printing_wall(scene, mymlx, id);
}
