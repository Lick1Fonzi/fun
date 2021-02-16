import sys
import os
import pygame
from pygame.locals import *


class Schermo(): #screen class
    def __init__(self,height,width):
        self.height=height
        self.width=width

    def Dim(self):
        return [self.height,self.width]

class Table():   #gametable class
    def __init__(self,surface,colour,pos_lat):
        self.surface=surface
        self.colour=colour
        self.pos_lat=pos_lat

class Freccia():     #arrow to the table class
    def __init__(self,x,y,turno,direz):
        self.x=x
        self.y=y
        self.turno=turno
        self.direz=direz
    def saltafreccia(self): #moving arrow up and down
        self.y+=self.direz
        if(self.y>40 or self.y<25):
            self.direz=-self.direz
    def spostafreccia(self,dxsx):  #moving arrow right (1) or left (-1)
        if(dxsx>0):
            self.x+= (350//7)
        elif(dxsx<0):
            self.x-= (350//7)
            
            
    
    


