#!/usr/bin/python3
import pygame as pg
import fileinput

from math import *

pg.init()                                 # inicialização do sistema

# altura e largura da arena, em células
H, W = 15,15

# largura da célula
l = 30
# altura da célula
L = 2*l/sqrt(3)

# cria a janela
scr = pg.display.set_mode((2*W*l+l,int(1.5*L*H+L/2)))
# só para simplificar, atualização da imagem
atu = pg.display.update


# pinta o fundo da janela
scr.fill((0,200,0))
atu()

def convert(i ,j):
    """
    Converte a coordenada (i,j) para a posição em pixels na janela
    """
    x = (1 + i%2)*l + 2*j*l
    y = 1.5*i*L + L
    return x,y

class Robô(pg.sprite.Sprite):
    """
    Representa um Robô, possui uma imagem
    """
    def __init__(s, img):
        """
        Construtor, img é o nome do arquivo com a imagem
        """
        pg.sprite.Sprite.__init__(s)
        s.image = pg.image.load(img)
        s.rect = s.image.get_rect()

    def draw(s, i,j):
        """
        Desenha o robô na célula (i,j)
        """
        x, y = convert(i,j)

        # fronteiras do sprite
        l0,h0,l1,h1 = s.rect

        # corrije a posição de acordo com o tamanho do sprite
        s.rect.topleft = [x-l1/2,y-h1/2]
        # desenha
        scr.blit(s.image, s.rect)

    
class cell:
    """
    Representa uma das células da arena
    """
    def __init__(s,i,j):
        """
        Construtor, i e j formam a coordenada
        """
        # Posição do centro
        s.cx, s.cy = convert(i,j)
        # Cor (pode ser passada para o construtor no futuro)
        s.cor = (200,200,200)

        # Vértices do hexágono
        s.pontos = (
            (s.cx,   s.cy-L),
            (s.cx+l, s.cy-L/2),
            (s.cx+l, s.cy+L/2),
            (s.cx,   s.cy+L),
            (s.cx-l, s.cy+L/2),
            (s.cx-l, s.cy-L/2),
            )
        
    def draw(s) :
        """
        Desenha a célula
        """
        pg.draw.polygon(scr, s.cor, s.pontos, 0)
        pg.draw.lines(scr, (0,0,0), True, s.pontos, 2)


# Construção da matriz que representa a arena
arena = []
for i in range(15):
    arena.append([])
    for j in range(15):
        arena[i].append(cell(i,j))
        arena[i][j].draw()

# lista dos robôs definidos
robs = []

# atualiza a janela
atu()

# Leitura dos comandos pela entrada padrão ou de um arquivo
for line in fileinput.input():
    r = line.split()

    # linha começando com 'fim', termina o programa
    if r[0] == 'fim':
        break

    # linha começando com 'rob', inclui um robô,
    # o segundo argumento na linha é a imagem   
    if r[0] == 'rob':
        robs.append(Robô(r[1]))
        continue

    # linha de movimentação:
    # robô, corrdenadas originais, coordenadas finais
    ri, oi, oj, di, dj = list(map(int, r))

    # redesenha a célula original (apaga o robô)
    if 0 <= oi  < W and 0 <= oj < H:
        arena[oi][oj].draw()
    # desenha o robô na célula de destino
    if 0 <= di  < W and 0 <= dj < H and ri < len(robs):
        robs[ri].draw(di,dj)

    # tempo de espera para atualização, apenas para testes
    pg.time.wait(100)

    atu()

pg.quit()
# Local variables:
# mode: python
# End:
