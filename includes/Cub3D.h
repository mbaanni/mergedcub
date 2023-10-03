/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:43:21 by mbaanni           #+#    #+#             */
/*   Updated: 2023/10/03 20:16:36 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX/MLX42.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 1000
# define HEIGHT 700
# define BLOCSIZE 64
# define RESIZE 0.2
# define RADIUS 130
# define ANGLE_SPEED 0.05
# define PLAYER_SPEED 12
# define FIELD_OF_VIEW 60
# ifndef BONUS
#  define BONUS 0
# endif

enum
{
	NO,
	SO,
	WE,
	EA,
	START = 0,
	END,
	TOP = 0,
	BOTTOM,
	RIGHT,
	LEFT,
	DOR,
	DOR1,
	X = 0,
	Y
};

typedef struct t_ray
{
	float			hx;
	float			hy;
	float			hxblock;
	float			hyblock;
	float			vx;
	float			vy;
	float			vxblock;
	float			vyblock;
	float			angle_step;
}					t_ray;

typedef struct t_mlx
{
	mlx_image_t		*img;
	mlx_image_t		*minimap_img;
	mlx_texture_t	*tile[6];
	mlx_texture_t	*sprite[8];
	mlx_t			*mlx;
	t_ray			*ray;
	mlx_image_t		*txt;
	int				side;
	void			*mlx_win;
	int				start;
	int				max;
	float			offset;
	int				map_hight;
	int				map_width;
	float			angle;
	int				movex;
	int				movey;
	int				color;
	int				f_color;
	int				c_color;
	char			**map;
	float			rx;
	float			ry;
	float			ra;
}					t_mlx;

typedef struct s_info
{
	int				start;
	int				end;
	int				ray;
	uint32_t		color;
}					t_info;

typedef struct s_dirs
{
	char			*key;
	char			*path;
	struct s_dirs	*next;
}					t_dirs;

typedef struct s_mapinfo
{
	t_dirs			*directions;
	int				dirnbs;
	char			**map;
	int				c_color[3];
	int				f_color[3];
	int				max_x;
	int				max_y;
	float			pa;
	char			p_value;
	mlx_t			*init;
	mlx_image_t		*img;
	t_mlx			*mlx;

}					t_mapinfo;

typedef struct s_player
{
	int				x;
	int				y;
}					t_player;

/*********MAP PARSING*************/
int					is_all_value(char *str, char c);
int					check_door_borders(int i, int j);
int					valid_borders(int i, int j);
int					ft_parse(char *str);
int					check_path(char *str);
int					is_direction(char *str);
int					check_elements(char *str);
int					check_directions(char *str);
t_mapinfo			*get_type(void);
void				ft_intersection(void *ptr);
int					print_error(int i);
void				ft_move(void *arg);
int					check_chars(char **map, int i, int j);
int					is_valid_charset(char *str);
void				print_map(void);
t_player			*get_player(void);
int					is_all_value(char *str, char c);
int					check_map_errors(char **map);
int					check_borders(char **map, char c);
int					max_len(void);
int					check_file_name(char *str);
void				print_map_error(int i);
int					print_error(int i);
int					empty_line(char *str);
/*************CHECK DIRECTIONS************/
int					print_error(int i);
void				print_map_error(int i);
int					check_dirs(char dir, char *str);
int					save_colors_value(char dir, char *str);
int					count_point(char *str);
int					check_path(char *path);
/*********************************/

/*********LINKED LIST UTILS*******************/

t_dirs				*lstnew(char *key, char *path);
void				lstadd_back(t_dirs **lst, t_dirs *newnode);

/*********************************************/

void				ft_clean(t_mlx *mlx);
int					drow_map(t_mlx *mlx);
void				drow_player(void *mlx);
void				event_win(void *param);
int					creat_block(t_mlx *mlx);
void				dor_click(mlx_key_data_t key, void *ptr);
void				put_on_minimap(t_mlx *mlx, int x, int y, int color);
int					drow_map(t_mlx *mlx);
void				calculate_vertical(float ra, t_mlx *mlx, t_ray *ray);
void				draw_miniplayer(t_mlx *mlx);
void				calculate_horizontal(float ra, t_mlx *mlx, t_ray *ray);
int					calculate_dist(int px, int py, int dstx1, int dsty1);
float				wall_calculation(float *distray, float angle_step, int r,
						float *wall);
float				bound_angle(float angle);
float				small_dist(t_ray *ray, t_mlx *mlx);
uint32_t			get_color(t_mlx *mlx, int y, int x);
float				small_dist(t_ray *ray, t_mlx *mlx);
/**************************************************/
#endif