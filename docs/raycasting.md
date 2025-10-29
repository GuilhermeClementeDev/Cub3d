## **1. `set_draw_points`**

```c
static void	set_draw_points(t_game *g)
{
	if (g->ray.side == 0)
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x;
	else
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y;

	g->ray.wall_height = (int)(g->screen_height / g->ray.perp_wall_dist);

	g->ray.draw_start = (-g->ray.wall_height / 2) + (g->screen_height / 2);
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;

	g->ray.draw_end = (g->ray.wall_height / 2) + (g->screen_height / 2);
	if (g->ray.draw_end >= g->screen_height)
		g->ray.draw_end = g->screen_height - 1;
}

```

**Explicação detalhada:**

1. **`g->ray.perp_wall_dist`**
    - Calcula a distância perpendicular da câmera até a parede.
    - `side == 0` → parede vertical (eixo X), então usamos `side_dist_x - delta_dist_x`.
    - `side == 1` → parede horizontal (eixo Y), então usamos `side_dist_y - delta_dist_y`.
    - **Matemática**: `perp_wall_dist = distância do raio até a parede no grid`.
2. **`g->ray.wall_height`**
    - Altura da parede projetada na tela: inversamente proporcional à distância.
    - Fórmula: `wall_height = screen_height / perp_wall_dist`.
        - Quanto mais longe a parede (`perp_wall_dist` grande), menor a parede na tela.
        - Quanto mais perto (`perp_wall_dist` pequeno), maior a parede.
3. **`g->ray.draw_start` e `g->ray.draw_end`**
    - Determina os pixels verticalmente onde a parede será desenhada:
        - Centro da tela: `screen_height / 2`.
        - Começo da parede: `draw_start = -wall_height/2 + screen_height/2`.
        - Fim da parede: `draw_end = wall_height/2 + screen_height/2`.
    - Ajustes garantem que os valores não saiam da tela (0 a `screen_height-1`).

---

## **2. `wall_check`**

```c
static void	wall_check(t_game *g)
{
	int	hit = 0;

	while (!hit)
	{
		if (g->ray.side_dist_x < g->ray.side_dist_y)
		{
			g->ray.side_dist_x += g->ray.delta_dist_x;
			g->ray.map_x += g->ray.step_x;
			g->ray.side = 0;
		}
		else
		{
			g->ray.side_dist_y += g->ray.delta_dist_y;
			g->ray.map_y += g->ray.step_y;
			g->ray.side = 1;
		}

		if (g->map_game.map[g->ray.map_y][g->ray.map_x] == '1')
			hit = 1;
	}
}

```

**Explicação detalhada:**

- Implementa o **algoritmo DDA (Digital Differential Analyzer)** para caminhar no grid do mapa até encontrar uma parede.
- **Como funciona**:
    1. Compara `side_dist_x` e `side_dist_y` → decide se o próximo passo é no eixo X ou Y.
    2. Atualiza `map_x` ou `map_y` e soma `delta_dist` correspondente.
    3. Marca `side = 0` ou `1` para indicar se bateu numa parede vertical ou horizontal.
    4. Se a célula do mapa é `'1'` → parede encontrada, termina o loop.
- **Matemática**:
    - `side_dist_x += delta_dist_x` → distância percorrida pelo raio até próximo grid no X.
    - `side_dist_y += delta_dist_y` → idem para Y.

---

## **3. `calculate_step_and_distance`**

```c
static void	calculate_step_and_distance(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (g->map_game.player.width - g->ray.map_x) * g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + 1.0 - g->map_game.player.width) * g->ray.delta_dist_x;
	}

	if (g->ray.ray_dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (g->map_game.player.height - g->ray.map_y) * g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + 1.0 - g->map_game.player.height) * g->ray.delta_dist_y;
	}
}

```

**Explicação detalhada:**

- Define a direção do passo no grid (`step_x`, `step_y` = -1 ou 1) dependendo da direção do raio.
- Calcula a distância inicial do raio até o primeiro grid a ser atingido:
    - `side_dist_x` = distância do jogador até a próxima linha vertical.
    - `side_dist_y` = distância do jogador até a próxima linha horizontal.
- **Matemática**:
    - `(map_x + 1 - player.width) * delta_dist_x` → projeta a distância até o próximo lado da célula.
    - `delta_dist_x` e `delta_dist_y` → distância que o raio percorre para atravessar uma célula no grid.

---

## **4. `calculate_wall_x`**

```c
static void calculate_wall_x(t_game *g)
{
	if (g->ray.side == 0)
		g->ray.wall_x = g->map_game.player.height + g->ray.perp_wall_dist * g->ray.ray_dir_y;
	else
		g->ray.wall_x = g->map_game.player.width + g->ray.perp_wall_dist * g->ray.ray_dir_x;

	g->ray.wall_x -= floor(g->ray.wall_x);
}

```

- Calcula a posição exata do ponto de impacto da parede **em coordenadas do mundo**.
- `wall_x` será usado para mapear a textura corretamente.
- `wall_x -= floor(wall_x)` → transforma em **coordenada relativa na parede (0 a 1)**.

---

## **5. `get_wall_texture`**

```c
static t_sprite	*get_wall_texture(t_game *g)
{
	if (g->ray.side == 0)
	{
		if (g->ray.ray_dir_x > 0)
			return (&g->map_game.tex_we);
		else
			return (&g->map_game.tex_ea);
	}
	else
	{
		if (g->ray.ray_dir_y > 0)
			return (&g->map_game.tex_no);
		else
			return (&g->map_game.tex_so);
	}
}

```

- Escolhe a textura da parede com base na **orientação da parede e direção do raio**:
    - `side == 0` → parede vertical → leste ou oeste.
    - `side == 1` → parede horizontal → norte ou sul.

---

## **6. `calc_tex_x`**

```c
static int	calc_tex_x(t_game *g, t_sprite *tex)
{
	int tex_x;

	tex_x = (int)(g->ray.wall_x * (double)tex->width);
	if ((g->ray.side == 0 && g->ray.ray_dir_x > 0)
		|| (g->ray.side == 1 && g->ray.ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

```

- Converte `wall_x` (0 a 1) para coordenada X da textura.
- Ajuste necessário para inverter a textura dependendo da orientação do raio.

---

## **7. `draw_wall`**

```c
static void	draw_wall(t_game *g, int x, t_sprite *tex, int tex_x)
{
	double step = 1.0 * tex->height / g->ray.wall_height;
	double tex_pos = (g->ray.draw_start - g->screen_height / 2 + g->ray.wall_height / 2) * step;

	int y = g->ray.draw_start;
	while (y < g->ray.draw_end)
	{
		int tex_y = (int)tex_pos;
		color = *(unsigned int*)(tex->path + (tex_y * tex->line_len) + (tex_x * 4));
		my_mlx_pixel_put(&g->background, x, y++, color);
		tex_pos += step;
	}
}

```

- **`step`** → quantidade de pixels na textura para cada pixel vertical da parede.
- **`tex_pos`** → posição inicial na textura considerando a posição de desenho na tela.
- Loop percorre cada pixel da coluna da parede na tela e mapeia a cor correta da textura.

---

## **8. `draw_raycast_column`**

- Desenha **uma coluna vertical da tela**:
    1. Preenche o teto (`ceiling_color`) até `draw_start`.
    2. Desenha a parede usando `draw_wall`.
    3. Preenche o chão (`floor_color`) de `draw_end` até a base da tela.

---

## **9. `ft_raycasting`**

```c
void	ft_raycasting(t_game *game)
{
	int x = 0;
	while (x < game->screen_width)
	{
		init_raycast(game, x);         // Inicializa raio para coluna x
		calculate_step_and_distance(game);
		wall_check(game);              // Detecta parede
		set_draw_points(game);         // Define start/end de parede
		calculate_wall_x(game);        // Calcula ponto de impacto exato
		draw_raycast_column(game, x);  // Desenha coluna na tela
		x++;
	}
}

```

- Faz **raycasting para cada coluna da tela**, simulando visão 3D:
    1. Cada `x` é uma coluna de pixels na tela.
    2. Um raio é lançado e percorre o mapa até bater em uma parede.
    3. Altura da parede é calculada e a textura é mapeada.
    4. Repetido para todas as colunas → efeito 3D.
