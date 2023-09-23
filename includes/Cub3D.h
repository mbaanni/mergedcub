#ifndef CUB3D_H
#define CUB3D_H

#include "../42mx/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include <fcntl.h>
#include <stdio.h> //remove this library
#include <math.h>

#define PI M_PI
#define WIDTH 1920
#define HEIGHT 1080
#define mini_map_w 1920
#define mini_map_h 1080
#define BLOCSIZE 64
#define map_size 0.2
#define angle_speed 0.05
#define PLAYER_SPEED 6
#define field_of_view 60

enum prespective {
    NO,
    SO,
    WE,
    EA
};

enum
{
    TOP,
    BOTTOM,
    RIGHT,
    LEFT,
    DOR
};

typedef struct  s_dirs
{
	char	*key;
	char	*path;
	struct s_dirs		*next;
} 	t_dirs;

typedef struct	s_mapInfo
{
	t_dirs			*directions;
	int				dirNbs;
	char			**map;
	int				colors[3];
	int				max_x;
	int				max_y;
	float			pa;
	mlx_t  		    *init;
    mlx_image_t     *img;

}	t_mapInfo;

typedef struct s_player 
{
	float				x;
	float				y;
}	t_player;
;
/*********MAP PARSING*************/

int				mapParsing(char *str);
int				checkPath(char *str);
int				isDirection(char *str);
int				checkElements(char	*str);
int				checkDirs(char *str);
t_mapInfo*		getType(void);
void	ft_intersection(void *ptr);
int				printError(int	i);
void  		    ft_move(void *arg);
void    		 print_map();
t_player*		get_player(void);
/*********************************/

/*********LINKED LIST UTILS*******************/

t_dirs		*lstnew(char	 *key, char *path);
void		lstadd_back(t_dirs **lst, t_dirs *newnode);

/*********************************************/

typedef struct t_ray {
    float   hx;
    float   hy;
    float   rx;
    float   ry;
    float   vx;
    float   vy;
    float   hxblock;
    float   hyblock;
    float   vxblock;
    float   vyblock;
    int     max;
}t_ray;

typedef struct t_mlx {
    mlx_image_t *img;
    mlx_image_t *minimap_img;
    mlx_texture_t* tile[6];
    t_ray   *ray;
    mlx_t*  mlx;
    mlx_image_t *txt;
    int     side;
    void    *mlx_win;
    int start;
    int max;
    float offset;
    int map_hight;
    int map_width;
    float angle;
    int movex;
    int movey;
    int color;
    char **map;
}   t_mlx;

int     drow_map(t_mlx *mlx);
void    clean_it(t_mlx *mlx);
int     parse_map(t_mlx *mlx);
void    drow_player(void *mlx);
void    event_win(void *param);
char    **open_map(char *link);
int     creat_block(t_mlx *mlx);
void    dor_click(mlx_key_data_t key, void *ptr);
int     drow_map(t_mlx *mlx);
void    draw_line(mlx_image_t *image, int startx, int starty, int endx, int endy, int color);
void    calculate_vertical(float ra, t_mlx *mlx, t_ray *ray);
void    calculate_horizontal(float ra, t_mlx *mlx, t_ray *ray);
void	small_dist(t_ray *ray, t_mlx *mlx, float *distray);

#endif