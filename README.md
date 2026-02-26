# cub3D

![Language](https://img.shields.io/badge/language-C-blue)
![42](https://img.shields.io/badge/school-42-black)
![Status](https://img.shields.io/badge/status-concluído-brightgreen)

> Engine gráfica 3D em C inspirada no Wolfenstein 3D, utilizando raycasting.

## Descrição

**cub3D** é um motor gráfico de primeira pessoa desenvolvido em C, inspirado no clássico **Wolfenstein 3D**.  
Renderiza um labirinto em perspectiva 3D a partir de um arquivo de mapa `.cub`, utilizando a técnica de **raycasting com o algoritmo DDA** (Digital Differential Analysis) e a biblioteca gráfica **miniLibX**.

### Funcionalidades
- Renderização 3D em tempo real com texturas diferentes para cada parede (Norte, Sul, Leste, Oeste)
- Cores configuráveis para o chão e o teto
- Movimentação do jogador com `W`, `A`, `S`, `D`
- Rotação da câmera com as setas `←` `→`
- Detecção de colisão com paredes
- Parsing e validação completa do arquivo `.cub`
- Fechamento limpo com `ESC` ou clique no botão `X` da janela

---

## Instruções

### Dependências

- **Linux** (o projeto usa a miniLibX para Linux)
- `make`, `gcc`
- Pacotes X11: `libx11-dev`, `libxext-dev`

```bash
sudo apt-get install libx11-dev libxext-dev
```

### Clonar a miniLibX (caso não use a do sistema)

```bash
# Na raiz do projeto:
git clone https://github.com/42Paris/minilibx-linux.git mlx
```

> Se usar a miniLibX do sistema (`/usr/local/lib`), ajuste o `MLX_FLAGS` no `Makefile`.

### Compilar

```bash
make
```

### Usar o jogo

```bash
./cub3D maps/test.cub
```

### Controles

| Tecla | Ação |
|-------|------|
| `W` | Mover para frente |
| `S` | Mover para trás |
| `A` | Mover para a esquerda (strafe) |
| `D` | Mover para a direita (strafe) |
| `←` | Girar câmera para a esquerda |
| `→` | Girar câmera para a direita |
| `ESC` | Fechar o jogo |

### Formato do arquivo `.cub`

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 50,50,150

1111111
1000001
100N001
1000001
1111111
```

#### Elementos obrigatórios
- `NO`, `SO`, `WE`, `EA` — caminhos para as texturas `.xpm`
- `F R,G,B` — cor do chão (RGB 0–255)
- `C R,G,B` — cor do teto (RGB 0–255)
- Mapa: somente `0` (vazio), `1` (parede), `N/S/E/W` (posição inicial do jogador)
- O mapa **deve** estar rodeado de paredes em todos os lados
- O mapa **deve** ser o último elemento do arquivo

---

## Estrutura do projeto

```
.
├── Makefile
├── README.md
├── includes/
│   └── cub3d.h
├── src/
│   ├── main.c
│   ├── init.c
│   ├── parse/
│   │   ├── parse.c
│   │   ├── parse_map.c
│   │   └── parse_textures.c
│   ├── raycasting/
│   │   ├── raycasting.c    ← Algoritmo DDA
│   │   └── render.c        ← Renderização de paredes/chão/teto
│   ├── player/
│   │   └── movement.c      ← Movimentação e rotação
│   └── utils/
│       ├── error.c
│       └── free.c
├── libft/                  ← Biblioteca de funções utilitárias
├── mlx/                    ← miniLibX (clonar separadamente)
├── textures/               ← Texturas XPM (N, S, E, W)
└── maps/
    └── test.cub
```

---

## Recursos

### Raycasting
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — referência principal do algoritmo DDA
- [Wolfenstein 3D source code](https://github.com/id-Software/wolf3d) — inspiração histórica
- [Wikipedia: Ray casting](https://en.wikipedia.org/wiki/Ray_casting)

### miniLibX
- [Repositório miniLibX (42Paris)](https://github.com/42Paris/minilibx-linux)
- [Documentação miniLibX](https://harm-smits.github.io/42docs/libs/minilibx)


