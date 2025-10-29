🧠 Raycasting — Documentação Completa
📘 O que é Raycasting?

Raycasting é uma técnica de renderização usada para gerar uma projeção 3D a partir de um mapa 2D.
Ela foi amplamente usada em jogos clássicos como Wolfenstein 3D, Doom (parcialmente) e é o método principal de renderização do projeto Cub3D da 42.

A ideia é simples:

Para cada coluna da tela, é lançado um “raio” (ray) a partir da posição do jogador, seguindo a direção que ele está olhando.
O algoritmo calcula onde esse raio colide com uma parede no mapa 2D e, a partir disso, desenha uma linha vertical (coluna) na tela, proporcional à distância até a parede.

Isso cria a ilusão de profundidade 3D, mesmo com o mapa sendo completamente bidimensional.

🎯 Objetivo do Raycasting

O objetivo principal é:

Calcular qual parede está à frente do jogador em cada direção (coluna de pixels);

Descobrir a distância até ela;

Determinar o tamanho da parede na tela (quanto mais longe, menor ela parece);

E finalmente, desenhar essa parede na tela, aplicando cores ou texturas.

⚙️ Como funciona matematicamente

O jogador é um ponto (posX, posY) no mapa 2D.
Ele tem uma direção de visão (dirX, dirY) e um plano de câmera (planeX, planeY) — este plano define o campo de visão (FOV).

Para cada coluna de pixel x da tela, é calculada uma direção de raio (ray_dir_x, ray_dir_y).

O algoritmo DDA (Digital Differential Analyzer) é usado para andar no mapa passo a passo até encontrar uma célula que contenha uma parede ('1').

Ao encontrar a colisão, calcula-se:

Distância perpendicular até a parede (para evitar distorção visual);

Altura da parede na tela;

Posição inicial e final da parede (para desenhar).

Por fim, a parede, o teto e o chão são desenhados na respectiva coluna.

🧩 Estrutura do seu código

O seu ft_raycasting.c implementa esse processo passo a passo.
Vamos detalhar cada função:

### ft_raycasting(t_game *game)
void	ft_raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->screen_width)
	{
		init_raycast(game, x);
		calculate_step_and_distance(game);
		wall_check(game);
		set_draw_points(game);
		draw_raycast_column(game, x);
		x++;
	}
}


Responsabilidade:
É a função principal que:

percorre cada coluna da tela (x),

calcula a direção do raio para aquela coluna (init_raycast),

faz o DDA para encontrar onde ele colide com uma parede,

calcula a distância até essa parede,

e desenha a coluna correspondente na tela.

Essa função é chamada uma vez por frame — ou seja, toda vez que o jogador se move ou gira, o mapa é re-renderizado.

### calculate_step_and_distance(t_game *g)
static void	calculate_step_and_distance(t_game *g)


O que faz:
Determina para qual direção o raio deve andar no mapa (E/O ou N/S) e calcula a distância inicial até a primeira linha de grade.

Conceitos:

Cada célula do mapa é um quadrado unitário (1x1).

O jogador pode estar em qualquer posição dentro de uma célula (ex: posX = 3.42).

Precisamos descobrir qual será o primeiro ponto de interseção do raio com as linhas de grade no eixo X e no eixo Y.

Variáveis importantes:

step_x / step_y: indica se o raio anda no mapa para frente (1) ou para trás (-1);

side_dist_x / side_dist_y: distância do jogador até o primeiro lado de uma célula;

delta_dist_x / delta_dist_y: distância entre duas interseções consecutivas de grade (usado no DDA).

### wall_check(t_game *g)
static void	wall_check(t_game *g)


O que faz:
Executa o algoritmo DDA para encontrar onde o raio colide com uma parede.

Como funciona:

Compara side_dist_x e side_dist_y;

Avança o menor (isto é, anda para o lado da grade mais próximo);

Atualiza map_x ou map_y (posição no mapa);

Verifica se a célula atual contém uma parede ('1') ou uma porta ('D').

Quando encontra algo sólido, o loop para — o raio “bateu”.

Por que DDA?

O Digital Differential Analyzer é um método rápido para percorrer grades uniformes (como um mapa 2D).
Evita cálculos trigonométricos caros e permite caminhar célula por célula até a colisão.

### set_perp_distance(t_game *g)
static void	set_perp_distance(t_game *g)


O que faz:
Após encontrar a parede, calcula a distância perpendicular entre o jogador e a parede.

Por que “perpendicular”?

Se usássemos a distância real do raio, haveria efeito “fisheye” (paredes distorcidas nas bordas da tela).
Então, o valor é corrigido de acordo com a direção do raio e o lado atingido.

Essa distância é essencial para o cálculo da altura da parede na tela.

### set_draw_points(t_game *g)
static void	set_draw_points(t_game *g)


O que faz:
Com base na distância até a parede (perp_wall_dist), calcula:

wall_height: altura projetada da parede na tela;

draw_start e draw_end: linhas verticais que delimitam a parte da tela onde a parede será desenhada.

Fórmula:
wall_height = screen_height / perp_wall_dist


Quanto menor a distância, maior a parede parece.

### draw_raycast_column(t_game *g, int x)
static void	draw_raycast_column(t_game *g, int x)


O que faz:
Desenha uma coluna vertical da tela:

De 0 até draw_start → cor do teto;

De draw_start até draw_end → parede (no seu caso, WHITE);

De draw_end até screen_height → chão.

No futuro, essa parte normalmente é substituída por amostragem de textura, onde cada pixel da parede é desenhado conforme a textura da parede atingida.

🧮 Fluxo resumido do Raycasting
        |--------- screen_width --------|
Column: 0                                N

For each column:
    ↓
1️⃣ Calcular direção do raio
2️⃣ Descobrir distância até o primeiro lado (step e delta)
3️⃣ Avançar no mapa até colidir (DDA)
4️⃣ Calcular distância perpendicular
5️⃣ Calcular tamanho e posição da parede na tela
6️⃣ Desenhar teto / parede / chão

🔍 Por que precisamos disso?

Sem raycasting, você só teria um mapa 2D visto de cima.
O raycasting permite converter essa informação em uma perspectiva 3D simulada — é o coração de todo o motor Cub3D.

Ele permite:

Visualização tridimensional de um mapa 2D;

Detecção de colisão (paredes e portas);

Aplicação de texturas e iluminação básica;

E, eventualmente, renderização de sprites e objetos.

📄 Conclusão

O raycasting é a base matemática e lógica do Cub3D.
Ele transforma coordenadas de mapa em projeções visuais realistas.
Seu código implementa todas as etapas fundamentais:

Direcionamento do raio,

DDA para colisão,

Cálculo de distância,

Projeção da parede,

Desenho da coluna.

É uma técnica simples, rápida e eficiente — ideal para jogos 3D de primeira geração e perfeita para aprendizado de motores gráficos.
