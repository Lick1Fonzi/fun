import sys
import os
import pygame
from pygame.locals import *
from f4helper import *

#starting pygame
pygame.init()
pygame.mouse.set_visible(False)
#variabili
white=[255,255,255]
red=[255,0,0]
yell=[255,255,0]
heightgscreen=400
widthgscreen=350
heighttable=300
widthtable=350
righe=6                 #default game 6
colonne=7               #default game 7
n=350//colonne
m=300//righe
noffset=25
moffset=125

#schermata iniziale
starting_screen=Schermo(480,480) #dimensions of "startbckg.png" image
pygame.display.set_caption("Forza 4")
fscreen=pygame.display.set_mode(starting_screen.Dim())
inizio = pygame.image.load("startbckg.png").convert()

#schermata di gioco
game_screen=Schermo(widthgscreen,heightgscreen)
frecciar=Freccia(100,40,0,-5)
fred=pygame.image.load("frecciarossa.png").convert()
fyell=pygame.image.load("frecciagialla.png").convert()
winred=pygame.image.load("youwinred.png").convert()
winyell=pygame.image.load("youwinyell.png").convert()
griglia=[[white,white,white,white,white,white,white],
         [white,white,white,white,white,white,white],
         [white,white,white,white,white,white,white],
         [white,white,white,white,white,white,white],
         [white,white,white,white,white,white,white],
         [white,white,white,white,white,white,white]]

#funzioni secondarie
def diag(j,i,sign1,sign2):
    countyell=0
    countred=0
    for f in range(4):
        if(griglia[j+(f*sign1)][i+(f*sign2)]==red):
                countred+=1
                countyell=0
        elif(griglia[j+(f*sign1)][i+(f*sign2)]==yell):
                countyell+=1
                countred=0
        if(countred==4 or countyell==4):
            return True
        
    
def controlladiag():
    for j in range(6):
        for i in range (7):
            if(i<4):
                if(j<3):
                    if(diag(j,i,1,1)):
                        return False   #downright
                elif(j>2):
                    if(diag(j,i,-1,1)):
                        return False    #upright
            if(i>2):
                if(j>2):
                    if(diag(j,1,-1,-1)):
                        return False   #upleft
                elif(j<3):
                    if(diag(j,i,1,-1)):
                        return False    #downleft
    return True
            
def controllariga():
    for j in range(6):
        countyell=0
        countred=0
        for i in range (7):
            if(griglia[j][i]==red):
                countred+=1
                countyell=0
            elif(griglia[j][i]==yell):
                countyell+=1
                countred=0
            elif(griglia[j][i]==white):
                countyell=0
                countred=0
            if(countred==4 or countyell==4):
                return False
    return True
                
def controllacolonna():
    for i in range(7):
        countyell=0
        countred=0
        for j in range (6):
            if(griglia[j][i]==red):
                countred+=1
                countyell=0
            elif(griglia[j][i]==yell):
                countyell+=1
                countred=0
            elif(griglia[j][i]==white):
                countyell=0
                countred=0
            if(countred==4 or countyell==4):
               return False
    return True
        
def inseriscicoin(posiz):
    for j in range(6):
        if(j==5 and griglia[j][posiz]==white):
            if(frecciar.turno==0 or frecciar.turno%2==0):
                griglia[j][posiz]=red
            else:
                griglia[j][posiz]=yell
        elif(j<5 and((griglia[j+1][posiz]==red or griglia[j+1][posiz]==yell) and (griglia[j][posiz]==white))):
            if(frecciar.turno==0 or frecciar.turno%2==0):
                griglia[j][posiz]=red
            else:
                griglia[j][posiz]=yell

def draw():
    for i in range(7):
        for j in range(6):
            if(griglia[j][i]== white):
                return False
    return  True
            
#funzioni principali
def arcadestrt():   #schermata principale
    pygame.mixer.music.load('epicsongf4.mp3')
    pygame.mixer.music.play()
    temp=True
    while(temp):
        for event in pygame.event.get():
            temp2=pygame.key.get_pressed()
            if temp2[K_SPACE]:
                temp=False
            if event.type== pygame.QUIT:
                temp=False
        fscreen.blit(inizio,(0,0))
        pygame.display.update()
    pygame.mixer.music.stop()

def gaming():
    pygame.mixer.music.load('startmusic.mp3')
    pygame.mixer.music.play()
    gscreen=pygame.display.set_mode(game_screen.Dim())
    gametable=Table(gscreen,[0,127,255],[0,100,widthtable,heighttable])
    loop=True 
    #loop di gioco
    while(controllariga() and controllacolonna() and controlladiag() and loop):
        pygame.time.delay(80)
        for event in pygame.event.get():
            keypr=pygame.key.get_pressed()
            if event.type== pygame.QUIT:
               loop=False
            if(keypr[K_RIGHT] and frecciar.x<(n*(colonne-1))):
                frecciar.spostafreccia(1)
            elif(keypr[K_LEFT] and frecciar.x>(noffset)):
                frecciar.spostafreccia(-1)           
            elif(keypr[K_SPACE]):
                posiz=(frecciar.x)//50      #indice di colonna
                inseriscicoin(posiz)
                frecciar.turno+=1           #if choosing a full column changes turn dammit

        #drawing
        pygame.draw.rect(gscreen,(0,0,0),(0,0,widthgscreen,heightgscreen))
        pygame.draw.rect(gametable.surface,gametable.colour,gametable.pos_lat)
        for i in range(7):  #columns
            for j in range(6):  #rows
                pygame.draw.circle(gscreen,griglia[j][i],((noffset+(n)*i),(moffset+(m)*j)),noffset)
        if(frecciar.turno==0 or frecciar.turno%2==0):
            gscreen.blit(fred,(frecciar.x,frecciar.y))
        else:
            gscreen.blit(fyell,(frecciar.x,frecciar.y))
        frecciar.saltafreccia()
        pygame.display.update()
        if(draw()):
            return false
    pygame.mixer.music.stop()
    return loop  
        
def youwin():
    winscreen=pygame.display.set_mode(game_screen.Dim())
    wintable=Table(winscreen,[0,127,255],[0,100,widthtable,heighttable])
    temp=True
    while(temp):
        pygame.time.delay(80)
        for event in pygame.event.get():
            keypr=pygame.key.get_pressed()
            if event.type== pygame.QUIT:
               temp=False
            if keypr[K_y]:
                return True
            if keypr[K_n]:
                return False
        pygame.draw.rect(winscreen,(0,0,0),(0,0,widthgscreen,heightgscreen))
        if((frecciar.turno-1)%2==0):
            winscreen.blit(winred,(0,0))
        else:
            winscreen.blit(winyell,(0,0))
        pygame.draw.rect(wintable.surface,wintable.colour,wintable.pos_lat)
        for i in range(7):  #columns
            for j in range(6):  #rows
                pygame.draw.circle(winscreen,griglia[j][i],((noffset+(n)*i),(moffset+(m)*j)),noffset)
        pygame.display.update()

def drawgame():
    drawscreen=pygame.display.set_mode((150,40))
    drawimage=pygame.image.load("draw.png").convert()
    drawscreen.blit(drawimage,(0,0))
    pygame.display.update()
    pygame.time.delay(2000)
    
    
def easteregg():
    eggscreen=pygame.display.set_mode((300,155))
    egg=pygame.image.load("easteregg.jpg").convert()
    eggscreen.blit(egg,(0,0))
    pygame.display.update()
    pygame.time.delay(2000)
    
def rules():
    rulescreen=pygame.display.set_mode((500,400))
    imgrule=pygame.image.load("rules.png").convert()
    temp=True
    while(temp):
        pygame.time.delay(80)
        for event in pygame.event.get():
            keypr=pygame.key.get_pressed()
            if(keypr[K_SPACE]):
                temp=False
        rulescreen.blit(imgrule,(0,0))
        pygame.display.update()
    
    
#main
if __name__ == "__main__":
    try:
        arcadestrt()
        rules()
        if(gaming()):
            if(youwin()):
                easteregg()
        if(draw()):
            drawgame()
        
    finally:
        pygame.quit()
    
    
